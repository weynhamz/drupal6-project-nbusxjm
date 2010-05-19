<?php
function sxjmusers_views_data() {
  $data['sxjmusers'] = array(
    'table' => array(
      'group' => '数模用户',
      'join' => array (
        'users' => array(
          'left_field' => 'uid',
          'field' => 'uid',
        ),
      ),
    ),
    'realname' => array(
      'title' => '姓名',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'gender' => array(
      'title' => '性别',
      'field' => array(
        'handler' => 'sxjmusers_views_handler_field_gender',
      ),
    ),
    'birthday' => array(
      'title' => '生日',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'college' => array(
      'title' => '学院',
      'field' => array(
        'handler' => 'sxjmusers_views_handler_field_college',
      ),
    ),
    'major' => array(
      'title' => '专业',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'phone' => array(
      'title' => '电话',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'address' => array(
      'title' => '地址',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'mphone_service' => array(
      'title' => '手机接入',
      'field' => array(
        'handler' => 'sxjmusers_views_handler_field_mphone_service',
      ),
    ),
    'mphone_long' => array(
      'title' => '手机长号',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'mphone_short' => array(
      'title' => '手机短号',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'reg_year' => array(
      'title' => '注册学年',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'quit_time' => array(
      'title' => '脱离日期',
      'field' => array(
        'handler' => 'views_handler_field_date',
      ),
    ),
    'current_state' => array(
      'title' => '当前状态',
      'field' => array(
        'handler' => 'sxjmusers_views_handler_field_current_state',
      ),
    ),
  );
  return $data;
}

function sxjmusers_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'sxjmusers') .'/handlers',
    ),
    'handlers' => array(
      'sxjmusers_views_handler_field_college' => array(
        'parent' => 'views_handler_field',
      ),
      'sxjmusers_views_handler_field_current_state' => array(
        'parent' => 'views_handler_field',
      ),
      'sxjmusers_views_handler_field_gender' => array(
        'parent' => 'views_handler_field',
      ),
      'sxjmusers_views_handler_field_mphone_service' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
