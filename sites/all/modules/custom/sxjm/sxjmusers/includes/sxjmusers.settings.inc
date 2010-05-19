<?php
// $Id: sxjmusers.settings.inc$
//TODO还需要配置默认user系统的一些设定
function sxjmusers_settings($form_state) {
  //延长期限的控制
  //是否开放注册的控制
  $form['settings'] = array(
    '#title' => '用户设置',
    '#type'=>'fieldset',
    '#collasible'=>FALSE,
    '#collapsed'=>FALSE,
  );
  //TODO默认不开放注册，如果开放注册，需要确认legal已经设置。
  $form['settings']['sxjmusers_reg_status']=array(
    '#title' => '开放注册',
    '#type' => 'select',
    '#options' => array('0'=>'否','1'=>'是'),
  );
  $form['settings']['sxjmusers_time_limit']=array(
    '#title' => '会员期限',
    '#type' => 'select',
    '#options' => array('1'=>'1年','2'=>'2年','3'=>'3年'),
  );
  $form['submit'] = array(
    '#type'=>'submit',
    '#value'=>'保存',
  );
  $form['#theme'] = 'system_settings_form';
  $form['#submit'][] = 'system_settings_form_submit';
  return $form;
}


function sxjmusers_settings_submit($form, &$form_state) {
  return;
}


function sxjmusers_settings_validate($form, &$form_state) {
  if(!in_array($form_state['values']['sxjmusers_reg_status'],array(0,1))) {
    form_set_error('sxjmusers_reg_status','错误的表单值');
  }
  if(!in_array($form_state['values']['sxjmusers_time_limit'],array(1,2,3))) {
    form_set_error('sxjmusers_time_limit','错误的表单值');
  }
}
