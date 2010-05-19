<?php
// $Id: sxjmusers.profile.inc$

/**
 * Display sxjmusers profile page.
 *
 * @param object $account
 *  user object
 */
function sxjmusers_view(&$account) {
  $title = sxjmusers_get_basetitle($account);
  $genders = sxjmusers_get_genders();
  $colleges = sxjmusers_get_colleges();
  $mobile_services = sxjmusers_get_mobile_services();

  $fields = sxjmusers_fields($title);
  $account->content['个人资料'] = array(
    '#type' => 'user_profile_category',
    '#title' => t('个人资料'),
    '#weight' => 0,
  );
  $counter = 0;
  foreach ($fields as $k => $v) {
    if ($k == 'name' || $k == 'mail' || $k == 'tid') {
      continue;
    }
    if($k == 'gender') {
      $account->$k = $genders[$account->$k];
    }
    if($k == 'college') {
      $account->$k = $colleges[$account->$k];
    }
    if($k == 'mphone_service') {
      $account->$k = $mobile_services[$account->$k];
    }
    if($k == 'quit_time') {
      $account->$k = date('Y-m-d',$account->$k);
    }
    if($k == 'current_state') {
      $account->$k = sxjmusers_state_current($account->$k);
    }
    $account->content['个人资料'][$k] = array (
      '#type' => 'user_profile_item',
      '#title' => $v['label'],
      '#value' => $account->$k,
      '#weight' => $counter,
    );
    $counter++;
  }
}

function sxjmusers_legal($values = NULL) {
  $form = sxjmlegal_register_form($values);
  $form['legal']['#weight'] = 0;
  return $form;
}

function sxjmusers_legal_save(&$edit, &$account, $category) {
  //虽然这个表单最先出现，但是他的保存操作必须再用户建立成功之后
  sxjmlegal_register_insert($edit,$account);
}

function sxjmusers_legal_validate($form, &$form_state) {
  return;
}

function sxjmusers_base($values = NULL) {
  $form = user_register ();
  if (isset($form['account'])) {
    $form['account']['name']['#title'] = t('学号工号');
    $form['account']['name']['#default_value'] = $values['name'];
    $form['account']['name']['#description'] = t('请输入您的学号');
    $form['account']['mail']['#default_value'] = $values['mail'];
  } else {
    $form['name']['#title'] = t('学号工号');
    $form['name']['#default_value'] = $values['name'];
    $form['name']['#description'] = t('请输入您的学号');
    $form['mail']['#default_value'] = $values['mail'];
  }
  //可能需要文件表单进行单独的处理
  //移除表单的提交项
  unset($form['sxjmlegal']);
  unset($form['submit']);
  unset($form['#validate']);
  unset($form['#submit']);

  return $form;
}

function sxjmusers_base_save(&$edit, &$account, $category) {
  return;
}

function sxjmusers_base_validate($form,&$form_state) {
  user_register_validate($form,$form_state);
  //使用学号工号做为用户名，这里是对其进行格式的验证
  $schoolid = $form_state['values']['name'];
  if(!ereg('^[0-9]{5,9}$',$schoolid) && !ereg('^[0-9]{11}$',$schoolid) && !ereg('^[0-9a-zA-Z]{12,13}$',$schoolid) && !ereg('^[0-9a-zA-Z]{8}$',$schoolid))
    form_set_error('name', t('您填写的可能不是有效的学号工号，请检查！'));
  return;
}

function sxjmusers_title ($values = NULL) {
  $teacher_title_id = sxjmusers_get_title_id('指导老师');
  $student_title_id = sxjmusers_get_title_id('数模会员');
  $form['titles'] = array(
    '#type' => 'fieldset',
    '#title' => t('用户身份'),
    '#weight' => 0,
  );
  $form['titles']['title'] = array(
    '#type' => 'radios',
    '#title' => t('您的身份'),
    '#options' => array(
      $student_title_id => t('数模会员'),
      $teacher_title_id => t('指导老师'),
    ),
    '#description' => t('请告知您的身份'),
    '#default_value' => $values['title'],
    '#required' => TRUE,
  );
  return $form;
}

function sxjmusers_title_save(&$edit, &$account, $category) {
  //radio 表单，只有一项
  //这里暂不对用户添加系统用户角色，只是赋予一定的数模用户身份，当
  //用户通过审核后，再赋予系统用户角色
  sxjmusers_title_users_save(array($edit['title']),$edit['uid']);
}

function sxjmusers_title_validate($form,&$form_state) {
  //radio 表单，只有一项
  $title = $form_state['values']['title'];
  $titles = sxjmusers_titles();
  if (!array_key_exists($title,$titles)) {
    form_set_error('role','不会是恶意攻击吧。。');
  }
  $form_state['redirect'] = 'user/register';
}

function sxjmusers_realinfo ($values = NULL,$title = NULL) {

  jquery_ui_add(array('ui.datepicker','i18n/ui.datepicker-zh-CN'));
  drupal_add_js(array('sxjmusers' => array('path' => drupal_get_path('module', 'sxjmusers'))),'setting');
  drupal_add_js(drupal_get_path('module', 'sxjmusers') . '/scripts/sxjmusers.datepicker.js');

  $fields = sxjmusers_fields($title);
  $form['realinfo'] = array(
    '#type' => 'fieldset',
    '#title' => t('个人资料'),
    '#weight' => 0,
    '#attributes' => array('id'=>'sxjmusers-realinfo'),
  );
  $form['realinfo']['personal'] = array(
    '#type' => 'fieldset',
    '#title' => t('私人信息'),
    '#weight' => 0,
    '#attributes' => array('id'=>'sxjmusers-personal'),
  );
  $form['realinfo']['personal']['realname'] = array(
    '#type' => 'textfield',
    '#title' => $fields['realname']['label'],
    '#description' => $fields['realname']['description'],
    '#default_value' => $values['realname'],
    '#required' => TRUE,
  );

  // Using Jquery datepicker
  $form['realinfo']['personal']['birthday'] = array(
/*
    '#type' => 'date',
*/
    '#type' => 'textfield',
    '#title' => $fields['birthday']['label'],
    '#description' => $fields['birthday']['description'],
/*
    '#default_value' => array(
      'year' => format_date(time(), 'custom', 'Y'),
      'month' => format_date(time(), 'custom', 'n'),
      'day' => format_date(time(), 'custom', 'j'),
     ),
*/
    '#default_value' => $values['birthday'],
    '#required' => TRUE,
    '#attributes' => array('class'=>'datepicker'),
  );
  $form['realinfo']['personal']['gender'] = array(
    '#type' => 'radios',
    '#title' => $fields['gender']['label'],
    '#description' => $fields['gender']['description'],
    '#options' => sxjmusers_get_genders(),
    '#default_value' => $values['gender'],
    '#required' => TRUE,
  );
  $form['realinfo']['academic'] = array(
    '#type' => 'fieldset',
    '#title' => t('专业信息'),
    '#weight' => 1,
    '#attributes' => array('id'=>'sxjmusers-academic'),
  );
  $form['realinfo']['academic']['college'] = array(
    '#type' => 'select',
    '#title' => $fields['college']['label'],
    '#description' => $fields['college']['description'],
    '#options' =>  sxjmusers_get_colleges(),
    '#default_value' => $values['college'],
    '#required' => TRUE,
  );
  $form['realinfo']['academic']['major'] = array(
    '#type' => 'textfield',
    '#title' => $fields['major']['label'],
    '#description' => $fields['major']['description'],
    '#default_value' => $values['major'],
    '#required' => TRUE,
  );
  $form['realinfo']['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('联络信息'),
    '#weight' => 2,
    '#attributes' => array('id'=>'sxjmusers-contact'),
  );
  $form['realinfo']['contact']['phone'] = array(
    '#type' => 'textfield',
    '#title' => $fields['phone']['label'],
    '#description' => $fields['phone']['description'],
    '#default_value' => $values['phone'],
    '#required' => TRUE,
  );
  $form['realinfo']['contact']['address'] = array(
    '#type' => 'textfield',
    '#title' => $fields['address']['label'],
    '#description' => $fields['address']['description'],
    '#default_value' => $values['address'],
    '#required' => TRUE,
  );
  $form['realinfo']['mphone'] = array(
    '#type' => 'fieldset',
    '#title' => t('通迅信息'),
    '#weight' => 3,
    '#attributes' => array('id'=>'sxjmusers-mphone'),
  );
  $form['realinfo']['mphone']['mphone_service'] = array(
    '#type' => 'select',
    '#title' => $fields['mphone_service']['label'],
    '#description' => $fields['mphone_service']['description'],
    '#options' => sxjmusers_get_mobile_services(),
    '#default_value' => $values['mphone_services'],
    '#required' => TRUE,
  );
  $form['realinfo']['mphone']['mphone_long'] = array(
    '#type' => 'textfield',
    '#title' => $fields['mphone_long']['label'],
    '#description' => $fields['mphone_long']['description'],
    '#default_value' => $values['mphone_long'],
    '#required' => TRUE,
  );
  $form['realinfo']['mphone']['mphone_short'] = array(
    '#type' => 'textfield',
    '#title' => $fields['mphone_short']['label'],
    '#description' => $fields['mphone_short']['description'],
    '#default_value' => $values['mphone_short'],
  );
  return $form;
}

function sxjmusers_realinfo_save(&$edit, $account, $category, $is_update = FALSE) {
  if (isset($account->uid) || $is_update) {
    $fields = sxjmusers_fields();
    $fields_name = array_keys($fields);
    foreach($fields as $name => $field) {
      if ($name == 'name' || $name == 'mail' || $name == 'tid') {
        continue;
      }
      $fields_type[]= $field['type'];
    }
    foreach ($fields_name as $key => $name) {
      if ($name == 'name' || $name == 'mail' || $name == 'tid') {
        unset($fields_name[$key]);
        continue;
      }
      if(!isset($edit[$name]) && !$is_update) {
        if ($name != 'uid' && $name != 'tid' && $name != 'reg_year' && $name != 'quit_time' && $name != 'current_state') {
          form_set_error($name,t("出现错误，这不是更新表单，但是 $name 项未设置！"));
        }
      }
      switch($name) {
        case 'reg_year':
          $fields_value[] = $is_update?$account->reg_year:time() > strtotime("1 September " . date('Y',time())) ? date('Y',time()):date('Y',time())-1;
          break;
        case 'quit_time':
          $fields_value[] = isset($edit[$name])?$edit[$name]:($is_update && ($account->quit_time != 0)?$account->quit_time:strtotime("1 September " . date('Y',time())) + 3600*24*365*variable_get('sxjmusers_time_limit',1));
          break;
        case 'current_state':
          $fields_value[] = isset($edit[$name])?$edit[$name]:(($is_update && $account->current_state >= SXJMUSERS_STATE_ACTIVE)?$account->current_state:SXJMUSERS_STATE_CONFIRM);
        default:
          $fields_value[] = isset($edit[$name])?$edit[$name]:$account->$name;
      }
      unset($edit[$name]);
    }

    $fields_name = array_merge(array('uid'),$fields_name);
    $fields_type = array_merge(array('%d'),$fields_type);
    $fields_value = array_merge(array($account->uid),$fields_value);

    $query = 'INSERT INTO {sxjmusers} (`' . implode('`, `', $fields_name) .'`) VALUES (\''. implode('\', \'', $fields_type) . '\')';
    db_query('DELETE FROM {sxjmusers} WHERE uid = %d', $account->uid);
    db_query($query, $fields_value);
  }
}

function sxjmusers_realinfo_validate($form,&$form_state) {

  $realname = $form_state['values']['realname'];
  if (strlen($realname) < 2 || ereg('^[0-9a-zA-Z]*$',$realname))
    form_set_error('realname', t('您是不是没有填写您的真实的姓名？'));

  $gender = $form_state['values']['gender'];
  if (!in_array($gender,array_keys(sxjmusers_get_genders())))
    form_set_error('gender', t('站点可能收到恶意攻击。'));

  $college = $form_state['values']['college'];
  if (!in_array($college,array_keys(sxjmusers_get_colleges())))
    form_set_error('college', t('站点可能收到恶意攻击。'));

  $major = $form_state['values']['major'];
  if (strlen($major) < 6 || ereg('^[0-9a-zA-Z]*$',$major))
    form_set_error('major', t('您是不是没有填写您的真实的专业？'));

  $phone = $form_state['values']['phone'];
  if (!ereg('^[0-9]*$',$phone))
    form_set_error('phone', t('您填写的电话可能不正确，请检查！'));

  $address = $form_state['values']['address'];
  if (strlen($address) < 6 || ereg('^[0-9a-zA-Z]*$',$address))
    form_set_error('address', t('您是不是没有填写您的真实的地址？'));

  $mphone_service = $form_state['values']['mphone_service'];
  if (!in_array($mphone_service,array_keys(sxjmusers_get_mobile_services())))
    form_set_error('mphone_service', t('站点可能收到恶意攻击。'));

  $mphone_long = $form_state['values']['mphone_long'];
  if (!ereg('^[0-9]*$',$mphone_long))
    form_set_error('mphone_long', t('您填写的手机号码可能不正确，请检查！'));

  $mphone_short = $form_state['values']['mphone_short'];
  if (!ereg('^[0-9]*$',$mphone_short))
    form_set_error('mphone_short', t('您填写的移动短号可能不正确，请检查！'));
  //添加 birthday 的格式检查
}

function sxjmusers_admin_title(&$form_state,$uid) {
  $titles = sxjmusers_titles();
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );
  $form['titles'] = array(
    '#type' => 'fieldset',
    '#title' => t('用户身份'),
    '#weight' => 0,
  );
  $form['titles']['title'] = array(
    '#type' => 'checkboxes',
    '#title' => t('身份设置'),
    '#options' => $titles,
    '#description' => t('用户的身份'),
    '#default_value' =>array(),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('确定'),
  );
  return $form;
}

function sxjmusers_admin_title_submit($form,&$form_state) {
  //使用 user 模块内建的机制来保存角色
  $title = array_filter($form_state['values']['title']);
  $title = array_keys($title);
  $uid = $form_state['values']['uid'];
  sxjmusers_title_users_save($title,$uid);
}

function sxjmusers_admin_title_validate($form,&$form_state) {
  $titles = sxjmusers_titles();
  if(!isset($form_state['values']['titles'])) {
    form_set_error('submit','您在开玩笑么？');
    return;
  }
  foreach(array_keys($form_state['values']['title']) as $title) {
    if (!array_key_exists($title,$titles)) {
      form_set_error('title','不会是恶意攻击吧。。');
    }
  }
}
