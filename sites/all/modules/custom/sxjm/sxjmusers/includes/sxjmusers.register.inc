<?php
// $Id: sxjmusers.egister.inc$

define('sxjmusers_REG_STEP_LEGAL',1);
define('sxjmusers_REG_STEP_BASE',2);
define('sxjmusers_REG_STEP_ROLE',3);
define('sxjmusers_REG_STEP_REALINFO',4);


/**
 * Implementation of hook_menu_alter()
 */
function sxjmusers_menu_alter (&$items) {
  $items['user/register']['page arguments'] = array('sxjmusers_register');
  $items['admin/user/user/create']['page callback'] = 'drupal_get_form';
  $items['admin/user/user/create']['page arguments'] = array('sxjmusers_register');
}


/**
 * sxjmusers register callback.
 *
 * @param array $form_state
 * @return array
 */
function sxjmusers_register($form_state) {
  //如果不是自己的表单请求，则返回，总会有个表单处理这个表单请求。
  //否则，由于 $form_state['storage'] 的设置，使表单重建，导致
  //$_POST 变量被清除，而使真正的处理表单无法起作用，而自己的表单
  //则可以不经验证就通过
  if (isset($form_state['post']['form_id']) && $form_state['post']['form_id'] != 'sxjmusers_register') return;

  $admin = user_access('administer users');
  $current_step = $form_state['storage']['current_step'];
  if (!isset($current_step)) {
    $conditions = sxjmlegal_get_conditions();
    if ($admin || empty($conditions)) {
      $current_step = $form_state['storage']['current_step'] = 2;
    } else {
      if(!variable_get('sxjmusers_reg_status',0)) {
        return array('reg_close'=>array('#type'=>'item','#value'=>'对不起，本站暂不开放注册。'));
      }
      $current_step = $form_state['storage']['current_step'] = 1;
    }
  }
  switch ($current_step) {
    default:
      break;
    case sxjmusers_REG_STEP_LEGAL:
      $form = sxjmusers_register_step_one($form_state);
      break;
    case sxjmusers_REG_STEP_BASE:
      $form = sxjmusers_register_step_two($form_state);
      break;
    case sxjmusers_REG_STEP_ROLE:
      $form = sxjmusers_register_step_three($form_state);
      break;
    case sxjmusers_REG_STEP_REALINFO:
      $form =  sxjmusers_register_step_four($form_state);
      break;
  }
  $form['#after_build'] = array('sxjmusers_register_rebuild');
  return $form;
}


function sxjmusers_register_step_one($form_state) {
  $step_values = isset($form_state['storage']['step'][sxjmusers_REG_STEP_LEGAL]['values']) ? $form_state['storage']['step'][sxjmusers_REG_STEP_LEGAL]['values'] : $form_state['values'];
  $form = sxjmusers_legal($step_values);
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => '重置',
    '#weight' => 9,
  );
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('下一步'),
    '#weight' => 10,
  );
  return $form;
}


function sxjmusers_register_step_two($form_state) {
  $step_values = isset($form_state['storage']['step'][sxjmusers_REG_STEP_BASE]['values']) ? $form_state['storage']['step'][sxjmusers_REG_STEP_BASE]['values'] : $form_state['values'];
  $form = sxjmusers_base($step_values);
  $admin = user_access('administer users');
  if ($admin) {
    //TODOneed check
  } else {
    $form['previous'] = array(
      '#type' => 'submit',
      '#value' => t('上一步'),
      '#weight' => 8,
    );
  }
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('重置'),
    '#weight' => 9,
  );
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('下一步'),
    '#weight' => 10,
  );
  return $form;
}


function sxjmusers_register_step_three($form_state) {
  $step_values = isset($form_state['storage']['step'][sxjmusers_REG_STEP_ROLE]['values']) ? $form_state['storage']['step'][sxjmusers_REG_STEP_ROLE]['values'] : $form_state['values'];
  $form = sxjmusers_title($step_values);
  $form['previous'] = array(
    '#type' => 'submit',
    '#value' => t('上一步'),
    '#weight' => 8,
  );
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('重置'),
    '#weight' => 9,
  );
  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('下一步'),
    '#weight' => 10,
  );
  return $form;
}


function sxjmusers_register_step_four($form_state) {
  $step_values = isset($form_state['storage']['step'][sxjmusers_REG_STEP_REALINFO]['values']) ? $form_state['storage']['step'][sxjmusers_REG_STEP_REALINFO]['values'] : $form_state['values'];
  $role = $form_state['storage']['step'][sxjmusers_REG_STEP_ROLE]['values']['role'];
  $form = sxjmusers_realinfo($step_values,$role);
  $form['previous'] = array(
    '#type' => 'submit',
    '#value' => t('上一步'),
    '#weight' => 8,
  );
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('重置'),
    '#weight' => 9,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('确认注册'),
    '#weight' => 10,
  );
  return $form;
}


function sxjmusers_register_validate($form, &$form_state) {
  $current_step = $form_state['storage']['current_step'];
  switch ($current_step) {
    default:
    case sxjmusers_REG_STEP_LEGAL:
      sxjmusers_legal_validate($form,$form_state);
      break;
    case sxjmusers_REG_STEP_BASE:
      sxjmusers_base_validate($form,$form_state);
      break;
    case sxjmusers_REG_STEP_ROLE:
      sxjmusers_title_validate($form,$form_state);
      break;
    case sxjmusers_REG_STEP_REALINFO:
      sxjmusers_realinfo_validate($form,$form_state);
      break;
  }
}


function sxjmusers_register_rebuild ($form, &$form_state) {
  $current_step = $form_state['storage']['current_step'];
  if ($form_state['clicked_button']['#id'] == 'edit-previous') {
    $form['#post'] = '';
    $form_state['rebuild'] = TRUE;
    $form_state['storage']['current_step']--;
    $form_state['storage']['step'][$current_step]['values'] = $form_state['values'];
//     保留每一步的 $form 是否有意义需要重新考虑
//    $form_state['storage']['step'][$current_step]['form'] = $form;
  }
  if ($form_state['clicked_button']['#id'] == 'edit-reset') {
    $form['#post'] = '';
    $form_state['rebuild'] = TRUE;
    unset ($form_state['values']);
    unset ($form_state['storage']['step'][$current_step]);
  }
  return $form;
}


function sxjmusers_register_submit($form, &$form_state) {
  $current_step = $form_state['storage']['current_step'];

  if ($form_state['clicked_button']['#id'] == 'edit-next') {

    if (!isset($form_state['storage']['current_step'])) {
      $form_state['storage']['current_step'] = 1;
    }

    if ($current_step == sxjmusers_REG_STEP_ROLE && isset($form_state['storage']['step'][sxjmusers_REG_STEP_ROLE]) && isset($form_state['storage']['step'][sxjmusers_REG_STEP_REALINFO]) && $form_state['storage']['step'][sxjmusers_REG_STEP_ROLE]['values']['role'] != $form_state['values']['role']) {
      unset($form_state['storage']['step'][sxjmusers_REG_STEP_REALINFO]);
    }

    $form_state['storage']['step'][$current_step]['values'] = $form_state['values'];
//    $form_state['storage']['step'][$current_step]['form'] = $form;

    $form_state['storage']['current_step']++;

    //防止删除cache中的form缓存，在表单最后提交的时候统一删除
    unset($form_state['values']['form_build_id']);

  } elseif( $form_state['clicked_button']['#id'] == 'edit-submit') {

    $form_state['storage']['step'][$current_step]['values'] = $form_state['values'];
//    $form_state['storage']['step'][$current_step]['form'] = $form;

    foreach ($form_state['storage']['step'] as $step) {
      $form_state['values'] += $step['values'];
//      $form += $step['form'];

      //清理前几步的表单缓存
      cache_clear_all('form_'. $step['values']['form_build_id'], 'cache_form');
      cache_clear_all('storage_'. $step['values']['form_build_id'], 'cache_form');
     }

    //利用user模块的注册处理函数完成用户的注册
    unset($form_state['values']['previous'], $form_state['values']['reset'], $form_state['values']['next']);

    user_register_submit($form,$form_state);

    //$form_state['storage']不为空将导致表单重建
    unset($form_state['storage']);

    drupal_set_message("恭喜您，您已经注册成功，请等待管理员对您的注册信息进行审核后，您将获得数学建模会员的基本权限。在您的账户尚未通过前，你可以仅访问公开的页面和资源。");
  }
}


function sxjmusers_register_withpic() {
  if (variable_get('user_pictures', 0)) {
    $form['picture'] = array(
      '#type' => 'fieldset',
      '#title' => t('用户头像'),
      '#weight' => 0,
    );
    $form['picture']['picture_upload_register'] = array(
      '#type' => 'file',
      '#title' => t('上传头像'),
      '#description' => t('您的头像。图像尺寸不超过 %dimensions ，文件大小不超过 %size kB。', array('%dimensions' => variable_get('user_picture_dimensions', '85x85'), '%size' => variable_get('user_picture_file_size', '30'))) .' '. variable_get('user_picture_guidelines', ''),
    );
    $form['#attributes']['enctype'] = 'multipart/form-data';
  }
  return $form;
}


function sxjmusers_register_withpic_validate(&$edit, &$account, $category) {
  if (variable_get('user_pictures', 0)) {
    $validators = array(
      'file_validate_is_image' => array(),
      'file_validate_image_resolution' => array(variable_get('user_picture_dimensions', '85x85')),
      'file_validate_size' => array(variable_get('user_picture_file_size', '30') * 1024),
    );
    $file = file_save_upload('picture_upload_register', $validators);
    //由于这是多步表单，而文件的操作的生命周期只在当前的页面周期，无法在页面间传递，因此采用这种办法来传递 $file 数组，$edit 是对form_state['values']的引用
    if($file) $edit['sxjmusers_register_picture']['file'] = $file;
    unset($edit['picture_upload_register']);
  }
}


function sxjmusers_register_withpic_save(&$edit, &$account, $category) {
  if (variable_get('user_pictures', 0)) {
    //$file = file_save_upload('picture_upload_register');
    //由于file_save_upload依靠静态变亮来保存数组，只有页面的生命周期，无法再页面之间传递，故直接取得前面步骤中保存在$form_state['values']（$edit的引用传递的）的 $file 数组
    if (!isset($edit['sxjmusers_register_picture']['file'])) return;

    $file = $edit['sxjmusers_register_picture']['file'];
    $info = image_get_info($file->filepath);
    $destination = variable_get('user_picture_path', 'pictures') .'/picture-'. $account->uid .'.'. $info['extension'];

    if (file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
      db_query("UPDATE {users} SET picture='%s' WHERE uid=%d", $file->filepath, $account->uid);
    }

    unset($edit['sxjmusers_register_picture']);
  }
}
