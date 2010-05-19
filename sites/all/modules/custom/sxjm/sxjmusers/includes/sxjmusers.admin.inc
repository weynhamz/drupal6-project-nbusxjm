<?php
// $Id: sxjmusers.admin.inc$

/**
 * sxjmusers administrator page.
 *
 * @return string
 *  page html string
 */
function sxjmusers_admin() {
  jquery_ui_add(array('ui.datepicker','i18n/ui.datepicker-zh-CN'));
  drupal_add_js(array('sxjmusers' => array('path' => drupal_get_path('module', 'sxjmusers'))),'setting');
  drupal_add_js(drupal_get_path('module', 'sxjmusers') . '/scripts/sxjmusers.datepicker.js');
  if (!empty($_POST['accounts']) && isset($_POST['operation']) && ($_POST['operation'] == 'delete')) {
    $output = drupal_get_form('sxjmusers_multiple_delete_confirm');
  }
  else {
    $output = drupal_get_form('sxjmusers_filters_form');
    $output .= drupal_get_form('sxjmusers_accounts_form');
  }
  return $output;
}

/**
 * sxjmusers filter form struture.
 *
 * @param array $form
 *
 * @return array
 *  sxjmusers filter form struture
 */
function sxjmusers_filters_form($form) {
  $fields = sxjmusers_fields();
  foreach ($fields as $k => $v){
    $fields[$k] = $v['label'];
  }
  // 默认选择的字段
  $fields_default = array(
    'name' => 'name',
    'mail' => '',
    'tid' => 'tid',
    'realname'=> 'realname',
    'gender' => 'gender',
    'birthday' => '',
    'college' => '',
    'major' => '',
    'phone' => '',
    'address' => '',
    'mphone_services' => '',
    'mphone_long' => '',
    'mphone_short' => '',
    'reg_year' => 'reg_year',
    'quit_time' => 'quit_time',
    'current_state' => 'current_state',
  );
  $status = sxjmusers_options();
  foreach($status as $k => $v) {
    $status[$k]['options']['--none--'] = '<无>';
  }
  $searchs = sxjmusers_searchs();

  $field_session = &$_SESSION['sxjmusers_fields'];
  $field_session = is_array($field_session) ? $field_session : array();
  $status_session = &$_SESSION['sxjmusers_status'];
  $status_session = is_array($status_session) ? $status_session : array();
  $search_session = &$_SESSION['sxjmusers_search'];
  $search_session = is_array($search_session) ? $search_session : array();
  $categories_session = &$_SESSION['sxjmusers_categories'];

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('筛选用户'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('数学建模用户筛选界面。'),
    '#theme' => 'sxjmusers_filters',
  );

  $form['filters']['status'] = array(
    '#type' => 'fieldset',
    '#title' => t('条件过滤'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($status_session),
    '#description' => t('请选择相应的条件进行过滤，可多选。'),
    '#tree' => TRUE,//to have a nested value array
  );
  foreach ($status as $key => $value) {
    $form['filters']['status'][$key] = array(
      '#size' => 8,
      '#type' => 'select',
      '#title' => $value['title'],
      '#options' => $value['options'],
      '#multiple' => ($key != 'title')?TRUE:FALSE,
    );
    if (!empty($status_session[$key])) {
      $form['filters']['status'][$key]['#default_value'] = $status_session[$key];
    }
  }

  $form['filters']['search'] = array (
    '#type' => 'fieldset',
    '#title' => t('关键字过滤'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($search_session),
    '#description' => t('输入相关字段的关键字进行过滤。'),
    '#tree' => TRUE,
  );
  foreach ($searchs as $key => $value) {
    $form['filters']['search'][$key] = array(
      '#type' => 'textfield',
      '#title' => $value['title'],
      '#default_value' => !empty($search_session)?$search_session[$key]:'',
    );
  }
  $form['filters']['search']['birthday']['#attributes'] = array('class'=>'datepicker');
  $form['filters']['search']['quit_time_min']['#attributes'] = array('class'=>'datepicker');
  $form['filters']['search']['quit_time_max']['#attributes'] = array('class'=>'datepicker');

  $form['filters']['fields'] = array(
    '#title' => '可选字段',
    '#type' => 'checkboxes',
    '#options' => $fields,
    '#default_value' => !empty($field_session)?$field_session:$fields_default,
  );

  $form['filters']['categories'] = array(
    '#title' => '默认策略',
    '#type' => 'radios',
    '#options' => array(t('默认资料'),t('全部资料'),t('用户资料'),t('联系方式')),
    '#description' => t(''),
    '#default_value' => !empty($categories_session)?$categories_session:'0',
  );

  $form['filters']['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('过滤'),
  );
  if (!empty($status_session) || !empty($search_session)) {
    $form['filters']['buttons']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('重设')
    );
  }
  $form['filters']['buttons']['print'] = array(
    '#type' => 'submit',
    '#value' => t('打印'),
  );
  return $form;
}

/**
 * sxjmusers filter form submit handler,save needed values into
 * session or reset the session.
 *
 * @param array $form
 * @param array $form_state
 *
 */
function sxjmusers_filters_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = sxjmusers_options();
  switch ($op) {
    case t('重设'):
      $_SESSION['sxjmusers_status'] = array();
      $_SESSION['sxjmusers_search'] = array();
      $_SESSION['sxjmusers_fields'] = array();
      $_SESSION['sxjmusers_categories'] = array();
      break;
    case t('过滤'):
      $_SESSION['sxjmusers_status'] = $form_state['values']['status'];
      $_SESSION['sxjmusers_search'] = $form_state['values']['search'];
      $_SESSION['sxjmusers_fields'] = $form_state['values']['fields'];
      $_SESSION['sxjmusers_categories'] = $form_state['values']['categories'];
      break;
    case t('打印'):
      $_SESSION['sxjmusers_status'] = $form_state['values']['status'];
      $_SESSION['sxjmusers_search'] = $form_state['values']['search'];
      $_SESSION['sxjmusers_fields'] = $form_state['values']['fields'];
      $_SESSION['sxjmusers_categories'] = $form_state['values']['categories'];
      $form_state['redirect'] = 'sxjm/user/print';
      break;
  }
}

/**
 * sxjmusers filter form validate handler.
 *
 * @param array $form
 * @param array $form_state
 */
function sxjmusers_filters_form_validate($form, &$form_state) {
  return;
}

/**
 * sxjmusers accounts manager form struture.
 *
 * @param array $form
 * @param boolen $print
 *  Boolen value that indicates whether the accounts table should be printable
 *
 * @return array
 *  sxjmusers accounts manager form struture.
 */
function sxjmusers_accounts_form($form,$print = FALSE) {
  drupal_add_js('misc/form.js', 'core');

  $fields = sxjmusers_fields();

  $header[] = array('data'=>'','sort' => 'desc');
  foreach ($fields as $key => $value) {
    if (!$value['display']) continue;
    if ($key == 'name') {
      $header[] = array('data' => $fields[$key]['label'],'field' => 'u.' . $key);
    } elseif ($key == 'mail') {
      $header[] = array('data' => $fields[$key]['label'],'field' => 'u.' . $key);
    } elseif ($key == 'tid') {
      $header[] = array('data' => $fields[$key]['label'],'field' => 'st.' . $key);
    } else {
      $header[] = array('data' => $fields[$key]['label'],'field' => 'su.' . $key);
    }
  }
  $header[] = t('Operations');

  $tablesort = tablesort_sql($header);

  $fields_sql = sxjmusers_field_query_build();
  $filter_sql = sxjmusers_status_query_build();
  $search_sql = sxjmusers_search_query_build();

  if(!empty($search_sql['where'])) $search_sql['where'] = 'AND ' . $search_sql['where'];

  $sql = 'SELECT su.uid' . $fields_sql . ' FROM {sxjmusers} su';
  $sql .= ' INNER JOIN {users} u ON su.uid = u.uid';
  $sql .= ' INNER JOIN {sxjmusers_title_users} stu ON su.uid = stu.uid';
  $sql .= ' INNER JOIN {sxjmusers_title} st ON stu.tid = st.tid';

  if($print) {
    $result = db_query($sql . " WHERE " . $filter_sql['where'] . $search_sql['where'] . $tablesort, array_merge($filter_sql['args'],$search_sql['args']));
  } else {
    $result = pager_query($sql . " WHERE " . $filter_sql['where'] . $search_sql['where'] . $tablesort, 50, 0, NULL, array_merge($filter_sql['args'],$search_sql['args']));
  }

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );
  $options = array();
  foreach (module_invoke_all('sxjmusers_operations') as $operation => $array) {
    $options[$operation] = $array['label'];
  }
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => 'unblock',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  $genders = sxjmusers_get_genders();
  $colleges = sxjmusers_get_colleges();
  $mphone_service = sxjmusers_get_mobile_services();

  $destination = drupal_get_destination();

  $accounts = array();
  while ($sxjmuserss = db_fetch_object($result)) {
    $accounts[$sxjmuserss->uid] = '';
    foreach($fields as $key => $value) {

      if (!$value['display']) continue;
      switch ($key) {
        case 'name':
          $form[$key][$sxjmuserss->uid] = array('#value'=>l($sxjmuserss->name, 'user/'. $sxjmuserss->uid, array('html' => TRUE)));
          break;
        case 'tid':
          $form[$key][$sxjmuserss->uid] = array('#value'=>implode('<br />',sxjmusers_get_titles($sxjmuserss->uid)));
          break;
        case 'gender':
          $form[$key][$sxjmuserss->uid] = array('#value'=>$genders[$sxjmuserss->gender]);
          break;
        case 'college':
          $form[$key][$sxjmuserss->uid] = array('#value'=>$colleges[$sxjmuserss->college]);
          break;
        case 'mphone_service':
          $form[$key][$sxjmuserss->uid] = array('#value'=>$mphone_service[$sxjmuserss->mphone_service]);
          break;
        case 'quit_time':
          $form[$key][$sxjmuserss->uid] = array('#value'=>date('Y-m-d',$sxjmuserss->quit_time));
          break;
        case 'current_state':
          $form[$key][$sxjmuserss->uid] = array('#value'=>sxjmusers_state_current($sxjmuserss->current_state));
          break;
        default:
          $form[$key][$sxjmuserss->uid] = array('#value'=>$sxjmuserss->$key);
          break;
      }
    }
    $form['operations_edit'][$sxjmuserss->uid] = array('#value' => l(t('edit'), "user/$sxjmuserss->uid/edit", array('query' => $destination)));
  }

  $form['accounts'] = array(
    '#type' => 'checkboxes',
    '#options' => $accounts
  );

  $form['pager'] = array('#value' => theme('pager', NULL, 50, 0));

  $form['print']['#value'] = $print;

  $form['#theme'] = 'sxjmusers_accounts';

  return $form;
}

/**
 * sxjmusers accounts manager form submit handler.
 *
 * @param array $form
 * @param array $form_state
 */
function sxjmusers_accounts_form_submit($form, &$form_state) {
  $operations = module_invoke_all('sxjmusers_operations', $form_state);

  $operation = $operations[$form_state['values']['operation']];

  // Filter out unchecked accounts.
  $accounts = array_filter($form_state['values']['accounts']);
  if ($function = $operation['callback']) {
    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($accounts), $operation['callback arguments']);
    }
    else {
      $args = array($accounts);
    }
    call_user_func_array($function, $args);

    drupal_set_message(t('The update has been performed.'));
  }
}

/**
 * sxjmusers accounts manager form validate handler.
 *
 * @param array $form
 * @param array $form_state
 */
function sxjmusers_accounts_form_validate($form, &$form_state) {
  $form_state['values']['accounts'] = array_filter($form_state['values']['accounts']);
  if (count($form_state['values']['accounts']) == 0) {
    form_set_error('', t('No users selected.'));
  }
}

/**
 * Build a part of sql query string based on the values user choosed.
 *
 * @return string
 *  field query sql
 */
function sxjmusers_field_query_build() {
  $fields = sxjmusers_fields();

  $fields_sql = '';
  foreach ($fields as $key => $value) {
    if (!$value['display']) continue;
    if ($key == 'name' || $key == 'mail') {
      $fields_sql .= ', u.' . $key;
    } elseif ($key == 'tid') {
      $fields_sql .= ', st.' . $key;
    } else {
      $fields_sql .= ', su.' . $key;
    }
  }

  return $fields_sql;
}

/**
 * Build a part of sql query string based on the values user choosed.
 *
 * @return string
 *  field query sql
 */
function sxjmusers_status_query_build() {
  $teacher_title_id = sxjmusers_get_title_id('指导老师');
  $student_title_id = sxjmusers_get_title_id('数模会员');

  $filters = sxjmusers_options();

  $where = $args = array();

  $sxjmusers_filter = isset($_SESSION['sxjmusers_status'])?$_SESSION['sxjmusers_status']:array('title'=>array($teacher_title_id,$student_title_id));

  //在没有使用角色过滤时提供默认的过滤设置
  if (empty($sxjmusers_filter['title'])) $sxjmusers_filter['title'] = array($teacher_title_id,$student_title_id);

  foreach ( $sxjmusers_filter as $key => $filter) {
    $filter_where = array();
    if(empty($filter)) $filter = array();
    //titlle filter is not a multiple select boxes.
    if($key == 'title') $filter = array($filter);
    //multiple select boxes.
    foreach ($filter as $value) {
      if($value == '--none--') continue;
      $filter_where[] = $filters[$key]['where'];
      $args[] = $value;
    }
    if (!empty($filter_where)) {
      $where[] = '('. implode(' OR ', $filter_where) .')';
    }
  }

  $where = !empty($where) ? implode(' AND ', $where) : '';

  return array(
    'where' => $where,
    'args' => $args,
  );
}

/**
 * Build a part of sql query string based on the values user choosed.
 *
 * @return string
 *  field query sql
 */
function sxjmusers_search_query_build() {
  $where = $args = array();

  $searchs = sxjmusers_searchs();

  $sxjmusers_search = isset($_SESSION['sxjmusers_search'])?$_SESSION['sxjmusers_search']:array();

  foreach ( $sxjmusers_search as $key => $value) {
    if(empty($value)) break;//如果没有值则跳过
    $filter_where = array();
    if($key == 'quit_time_min' || $key == 'quit_time_max') {
      if(!empty($sxjmusers_search[$key])) {
        $args[] = strtotime($value);
      } else {
        continue;
      }
    } else {
      $args[] = '%' . $value . '%';
    }
    $filter_where[] = $searchs[$key]['where'];
    if (!empty($filter_where)) {
      $where[] = '('. implode(' OR ', $filter_where) .')';
    }
  }

  $where = !empty($where) ? implode(' AND ', $where) : '';

  return array(
    'where' => $where,
    'args' => $args,
  );
}

/**
 * sxjmusers fields define.
 *
 * @param int $role sxjmusers role id
 *
 * @return array
 *  sxjmusers fields define array.
 */
function sxjmusers_fields($title=NULL) {
  $teacher_title_id = sxjmusers_get_title_id('指导老师');
  $is_teacher = $title==$teacher_title_id?1:0;

  $field_session = &$_SESSION['sxjmusers_fields'];

  $fields = array(
    'name' => array(
      'type'=>'%s',
      'label'=>$is_teacher?t('工号'):t('学号'),
      'description'=> $is_teacher?t('您的工号'):t('您的学号'),
      'display'=>!empty($field_session)?$field_session['name']:TRUE,
      'weight'=>'0',
      ),
    'mail'=>array(
      'type'=>'%s',
      'label'=>t('邮箱'),
      'description'=> t('您的邮箱'),
      'display'=>!empty($field_session)?$field_session['mail']:FALSE,
      'weight'=>'10',
      ),
    'tid'=>array(
      'type'=>'%d',
      'label'=>t('身份'),
      'description'=> t('您的身份'),
      'display'=>!empty($field_session)?$field_session['tid']:TRUE,
      'weight'=>'2',
      ),
    'realname'=>array(
      'type'=>'%s',
      'label'=>t('姓名'),
      'description'=>t('您的姓名'),
      'display'=>!empty($field_session)?$field_session['realname']:TRUE,
      'weight'=>'1',
      ),
    'gender'=>array(
      'type'=>'%d',
      'label'=>t('性别'),
      'description'=>t('您的性别'),
      'display'=>!empty($field_session)?$field_session['gender']:TRUE,
      'weight'=>'6',
      ),
    'birthday'=>array(
      'type'=>'%s',
      'label'=>t('生日'),
      'description'=>t('您的生日'),
      'display'=>!empty($field_session)?$field_session['birthday']:FALSE,
      'weight'=>'7',
      ),
    'college'=>array(
      'type'=>'%d',
      'label'=>t('学院'),
      'description'=>t('您所在的学院'),
      'display'=>!empty($field_session)?$field_session['college']:FALSE,
      'weight'=>'8',
      ),
    'major'=>array(
      'type'=>'%s',
      'label'=>$is_teacher?t('专业方向'):t('所学专业'),
      'description'=>$is_teacher?t('您的研究方向'):t('您所学的专业'),
      'display'=>!empty($field_session)?$field_session['major']:FALSE,
      'default'=>FALSE,
      'weight'=>'8',
      ),
    'phone'=>array(
      'type'=>'%s',
      'label'=>$is_teacher?t('办公电话'):t('寝室电话'),
      'description'=>$is_teacher?t('您的办公室固定电话，方便联系'):t('您的寝室电话，方便联系'),
      'display'=>!empty($field_session)?$field_session['phone']:FALSE,
      'weight'=>'8',
      ),
    'address'=>array(
      'type'=>'%s',
      'label'=>$is_teacher?t('办公地址'):t('寝室地址'),
      'description'=>$is_teacher?t('您的办公室地址，方便联系'):t('您的寝室地址，方便联系'),
      'display'=>!empty($field_session)?$field_session['address']:FALSE,
      'weight'=>'12',
      ),
    'mphone_service'=>array(
      'type'=>'%d',
      'label'=>t('手机接入'),
      'description'=>t('您的使用手机服务商'),
      'display'=>!empty($field_session)?$field_session['mphone_service']:FALSE,
      'weight'=>'13',
      ),
    'mphone_long'=>array(
      'type'=>'%s',
      'label'=>t('手机长号'),
      'description'=>t('您的手机号码'),
      'display'=>!empty($field_session)?$field_session['mphone_long']:FALSE,
      'weight'=>'14',
      ),
    'mphone_short'=>array(
      'type'=>'%s',
      'label'=>t('虚拟短号'),
      'description'=>t('如果您办理了相应服务商的校园网虚拟短号，请在这里填写，方便联系，但一定确保前面服务商选择无误'),
      'display'=>!empty($field_session)?$field_session['mphone_short']:FALSE,
      'weight'=>'15',
      ),
    'reg_year'=>array(
      'type'=>'%d',
      'label'=>t('注册学年'),
      'description'=>t('注册学年'),
      'display'=>!empty($field_session)?$field_session['reg_year']:TRUE,
      'weight'=>'3',
      ),
    'quit_time'=>array(
      'type'=>'%d',
      'label'=>t('退会日期'),
      'description'=>t('退会日期'),
      'display'=>!empty($field_session)?$field_session['quit_time']:TRUE,
      'weight'=>'4',
      ),
    'current_state'=>array(
      'type'=>'%d',
      'label'=>t('当前状态'),
      'description'=>t('当前状态'),
      'display'=>!empty($field_session)?$field_session['current_state']:TRUE,
      'weight'=>'5',
      ),
  );
  return $fields;
}

/**
 * sxjmusers status define.
 *
 * @return array
 *  sxjmusers status array
 */
function sxjmusers_options() {
  $filters = array();

  $genders = array(
    '0' => '男',
    '1' => '女',
  );

  $filters['genders'] = array(
    'title' => t('性别'),
    'where' => "su.gender = %d",
    'options' => $genders,
  );

  $titles = sxjmusers_titles();

  $filters['title'] = array(
    'title' => t('身份'),
    'where' => "stu.tid = %d",
    'options' => $titles,
  );

  $colleges = sxjmusers_get_colleges();

  $filters['college'] = array(
    'title' => t('学院'),
    'where' => "su.college = %d",
    'options' => $colleges,
  );

  $mphone_services = array(
    '0' => '移动',
    '1' => '联通',
    '2' => '电信',
  );

  $filters['mphone_services'] = array(
    'title' => t('手机接入'),
    'where' => "su.mphone_service = %d",
    'options' => $mphone_services,
  );

  $years = sxjmusers_get_years(10);

  $filters['reg_years'] = array(
    'title' => t('注册学年'),
    'where' => "su.reg_year = %d",
    'options' => $years,
  );

  $current_state = array(
    SXJMUSERS_STATE_BLOCK => '已脱离',
    SXJMUSERS_STATE_REVIEW => '待完善',
    SXJMUSERS_STATE_CONFIRM => '待审核',
    SXJMUSERS_STATE_ACTIVE => '活跃中',
    SXJMUSERS_STATE_PERMANENT => '永久会员',
  );

  $filters['current_state'] = array(
    'title' => t('会员状态'),
    'where' => "su.current_state = %d",
    'options' => $current_state,
  );
  return $filters;
}

/**
 * sxjmusers search define.
 *
 * @return array
 *  sxjmusers search array
 */
function sxjmusers_searchs() {
  $searchs = array();
  $searchs['username'] = array (
    'title' => '学号',
    'where' => "u.name LIKE '%s'"
  );
  $searchs['realname'] = array (
    'title' => '姓名',
    'where' => "su.realname LIKE '%s'"
  );
  $searchs['birthday'] = array (
    'title' => '生日',
    'where' => "su.birthday LIKE '%s'"
  );
  $searchs['major'] = array (
    'title' => '专业',
    'where' => "su.major LIKE '%s'"
  );
  $searchs['email'] = array (
    'title' => '邮箱',
    'where' => "u.mail LIKE '%s'"
  );
  $searchs['phone'] = array (
    'title' => '电话',
    'where' => "su.phone LIKE '%s'"
  );
  $searchs['address'] = array (
    'title' => '地址',
    'where' => "su.address LIKE '%s'"
  );
  $searchs['mphone_long'] = array (
    'title' => '长号',
    'where' => "su.mphone_long LIKE '%s'"
  );
  $searchs['mphone_short'] = array (
    'title' => '短号',
    'where' => "su.mphone_short LIKE '%s'"
  );
  $searchs['quit_time_min'] = array (
    'title' => '',
    'where' => "su.quit_time >= %d"
  );
  $searchs['quit_time_max'] = array (
    'title' => '',
    'where' => "su.quit_time <= %d"
  );
  return $searchs;
}

/**
 * sxjmusers opertions handler.
 *
 * @param array $form_state
 *
 * @return aray
 *  sxjmusers opertions define array
 */
function sxjmusers_sxjmusers_operations($form_state = array()) {
  $operations = array(
    'block' => array(
      'label' => t('封禁会员'),
      'callback' => 'sxjmusers_operations_block',
    ),
    'unblock' => array(
      'label' => t('激活会员'),
      'callback' => 'sxjmusers_operations_unblock',
    ),
    'extend' => array(
      'label' => t('延长期限'),
      'callback' => 'sxjmusers_operations_extend',
    ),
    'decrease' => array(
      'label' => t('缩短期限'),
      'callback' => 'sxjmusers_operations_decrease',
    ),
    'permanent' => array(
      'label' => t('永久会员'),
      'callback' => 'sxjmusers_operations_permanent',
    ),
    'review' => array(
      'label' => t('需要完善'),
      'callback' => 'sxjmusers_operations_review',
    ),
    'confirm' => array(
      'label' => t('通过审核'),
      'callback' => 'sxjmusers_operations_confirm',
    ),
    'delete' => array(
      'label' => t('删除账号'),
    ),
  );

  return $operations;
}

/**
 * Callback function for admin mass blocking users.
 */
function sxjmusers_operations_block($accounts) {
  foreach ($accounts as $uid) {
    $account = user_load(array('uid' => (int)$uid));
    if ($account !== FALSE && $account->current_state >= SXJMUSERS_STATE_ACTIVE) {
      user_save($account, array('current_state' =>  SXJMUSERS_STATE_BLOCK),'个人资料');
    }
    //取消和用户身份相应的系统角色，从而限制用户的权限
    sxjmusers_title_perms_remove($uid);
  }
}

/**
 * Callback function for admin mass unblocking users.
 */
function sxjmusers_operations_unblock($accounts) {
  foreach ($accounts as $uid) {
    $account = user_load(array('uid' => (int)$uid));
    if ($account !== FALSE && $account->current_state == SXJMUSERS_STATE_BLOCK) {
      user_save($account, array('current_state' =>  SXJMUSERS_STATE_ACTIVE),'个人资料');
    }
    //根据用户的身份，赋予一定的角色，从而具有相应的权限
    sxjmusers_title_perms_rebuild($uid);
  }
}

/**
 * Callback function for extend mass users time limit.
 */
function sxjmusers_operations_extend($accounts) {
  foreach ($accounts as $uid) {
    $account = user_load(array('uid' => (int)$uid));
    user_save($account, array('quit_time' => $account->quit_time + 3600*24*365*variable_get('sxjmusers_time_limit',1)),'个人资料');
  }
}

/**
 * Callback function for descrease mass users time limit.
 */
function sxjmusers_operations_decrease($accounts) {
  foreach ($accounts as $uid) {
    $account = user_load(array('uid' => (int)$uid));
    user_save($account, array('quit_time' => $account->quit_time - 3600*24*365*variable_get('sxjmusers_time_limit',1)),'个人资料');
  }
}

/**
 * Callback function for make mass users to review their account information.
 */
function sxjmusers_operations_review($accounts) {
  foreach ($accounts as $uid) {
    $account = user_load(array('uid' => (int)$uid));
    if ($account !== FALSE) {
      user_save($account, array('current_state' =>  SXJMUSERS_STATE_REVIEW),'个人资料');
    }
    //取消和用户身份相应的系统角色，从而限制用户的权限
    sxjmusers_title_perms_remove($uid);
  }
}

/**
 * Callback function for confirm mass users regesition.
 */
function sxjmusers_operations_confirm($accounts) {
  foreach ($accounts as $uid) {
    $account = user_load(array('uid' => (int)$uid));
    if ($account !== FALSE && $account->current_state ==  SXJMUSERS_STATE_CONFIRM) {
      user_save($account, array('current_state' =>  SXJMUSERS_STATE_ACTIVE),'个人资料');
    }
    //根据用户的身份，赋予一定的角色，从而具有相应的权限
    sxjmusers_title_perms_rebuild($uid);
  }
}

/**
 * Callback function for make mass users permanent.
 */
function sxjmusers_operations_permanent($accounts) {
  foreach ($accounts as $uid) {
    $account = user_load(array('uid' => (int)$uid));
    if ($account !== FALSE && $account->current_state >=  SXJMUSERS_STATE_ACTIVE) {
      user_save($account, array('current_state' =>  $account->current_state | SXJMUSERS_STATE_PERMANENT),'个人资料');
    }
  }
}

/**
 * Drupal delete confirm form
 *
 * @param array $form_state
 *
 * @return
 */
function sxjmusers_multiple_delete_confirm(&$form_state) {
  $edit = $form_state['post'];

  $form['accounts'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);

  // array_filter() returns only elements with TRUE values.
  foreach (array_filter($edit['accounts']) as $uid => $value) {
    $user = db_result(db_query('SELECT name FROM {users} WHERE uid = %d', $uid));
    $form['accounts'][$uid] = array('#type' => 'hidden', '#value' => $uid, '#prefix' => '<li>', '#suffix' => check_plain($user) ."</li>\n");
  }

  $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');

  return confirm_form($form,t('你确定要删除这些用户么?'),'sxjm/user', t('这个操作不可恢复。'),t('全部删除'), t('取消'));
}

/**
 * Drupal confirm form submit
 *
 * @param array $form
 * @param array $form_state
 */
function sxjmusers_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    foreach ($form_state['values']['accounts'] as $uid => $value) {
      user_delete($form_state['values'], $uid);
    }
    drupal_set_message(t('所选用户已全部删除。'));
  }
  $form_state['redirect'] = 'sxjm/user';
  return;
}

/**
 * Theme sxjmusers filter fom.
 *
 * @param array $form
 * @return string
 *  form html string
 */
function theme_sxjmusers_filters($form) {
  $quit_time_html = '<div id="sxjmusers-admin-filters-search-quittime"><label>退会时期:</label>';
  $quit_time_html .= drupal_render($form['search']['quit_time_min']);
  $quit_time_html .= '<div id="sxjmusers-admin-filters-search-quittime-seperator">至</div> ';
  $quit_time_html .= drupal_render($form['search']['quit_time_max']);
  $quit_time_html .= '</div>';
  $form['search']['quit_time']['#value'] = $quit_time_html;
  $output = '<div id="sxjmusers-admin-filters-status">';
  $output .= drupal_render($form['status']);
  $output .= '</div><div id="sxjmusers-admin-filters-search">';
  $output .= drupal_render($form['search']);
  $output .= '</div><div id="sxjmusers-admin-filters-fields">';
  $output .= drupal_render($form['fields']);
  $output .= '</div><div id="sxjmusers-admin-filters-categories">';
  $output .= drupal_render($form['categories']);
  $output .= '</div><div id="sxjmusers-admin-filters-buttons">'. drupal_render($form['buttons']) .'</div>';
  return $output;
}

/**
 * Theme user administration overview.
 *
 * @ingroup themeable
 */
function theme_sxjmusers_accounts($form) {
  $print = $form['print']['#value'];

  $fields = sxjmusers_fields();

  if(!$print) $header[] = theme('table_select_header_cell');
  foreach ($fields as $key => $value) {
    if (!$value['display']) continue;

    if ($key == 'name') {
      $header[] = array('data' => '学号','field' => 'u.' . $key);
    } elseif ($key == 'mail') {
      $header[] = array('data' => '邮箱','field' => 'u.' . $key);
    } elseif ($key == 'tid') {
      $header[] = array('data' => '身份','field' => 'st.' . $key);
    } else {
      $header[] = array('data' => $fields[$key]['label'],'field' => 'su.' . $key);
    }
  }
  if(!$print) $header[] = t('操作');

  if(!$print) $output = drupal_render($form['options']);

  if (isset($form['name']) && is_array($form['name'])) {
    foreach (element_children($form['name']) as $name) {
      $row = array();

      if(!$print) $row[] = drupal_render($form['accounts'][$name]);
      foreach($fields as $key => $value) {
        if (!$value['display']) continue;
        $row[] = drupal_render($form[$key][$name]);
      }

      if(!$print) {
        $str = drupal_render($form['operations_edit'][$name]);
        $row[] = $str;
      }

      $rows[] = $row;
    }
  }
  else {
    $counter = 0;
    foreach($fields as $key => $value) {

      if (!$value['display']) continue;
      $counter++;
    }
    $counter = $counter + 2;
    $rows[] = array(array('data' => t('暂无用户信息'), 'colspan' => $counter));
  }

  $output .= theme('table', $header, $rows, array('id' => 'sxjmusers-admin'));

  if($print) {
    print theme('sxjmusers_accounts_html','数学建模会员信息',$output);
    exit;
  } else {
    if ($form['pager']['#value']) {
      $output .= drupal_render($form['pager']);
    }
    $output .= drupal_render($form);
    return $output;
  }

}

/**
 * Process variables for sxjmusers-admin-account-html.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $title
 * - $contents
 *
 * @see sxjmusers-admin-account-html.tpl.php
 */
function template_preprocess_sxjmusers_accounts_html(&$variables) {
  global $base_url, $language;

  $variables['title'] = check_plain($variables['title']);
  $variables['base_url'] = $base_url;
  $variables['language'] = $language;
}
