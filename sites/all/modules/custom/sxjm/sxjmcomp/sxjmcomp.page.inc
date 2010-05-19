<?php
/**
 * Sxjmcomp config form.
 *
 * @param $form_state
 */
function sxjmcomp_config_form($form_state) {
  $form['sxjmcomp_intro'] = array(
    '#type' => 'textarea',
    '#title' => '数模竞赛介绍',
    '#description' => '关于数学建模竞赛的科普性介绍，会被显示在' . l('数模竞赛','comp') . '页面',
    '#default_value' => variable_get('sxjmcomp_intro',''),
    '#rows' => 10,
  );
  $form['sxjmcomp_team_process_category'] = array(
    '#type' => 'radios',
    '#title' => '组队处理策略',
    '#options' => array(
      '0' => '禁止不足或者超过三人的团队参赛',
      '1' => '自动处理不足或者超过三人的团队，这会破坏这些团队的现有用户关系',
    ),
    '#default_value' => '1',
  );
  $form['sxjmcomp_ques_paper_package_path'] = array(
    '#type' => textfield,
    '#title' => '论文压缩包的存放路径',
    '#default_value' => '/sxjm/comp/ques/papers',
  );
  return system_settings_form($form);
}

/**
 * Confirm form when the comp is going to start.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_confirm_start($form_state, $comp_title) {
  $form['sxjmcomp'] = array('#type' => 'value', '#value' => $comp_title);
  return confirm_form($form, '您确定要开始竞赛吗？','sxjm/comp/' . $comp_title,'竞赛开始后，将不再允许报名和添加赛题。','确定','取消');
}

/**
 * Confirm form submit handler.
 * @param $form
 * @param $form_state
 */
function sxjmcomp_confirm_start_submit($form, &$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);
  sxjmcomp_comp_set_state(SXJMCOMP_PROCESS,$comp_nid);
  $form_state['redirect'] = 'sxjm/comp/'. $form_state['values']['sxjmcomp'];
}

/**
 * Confirm form when a started comp is going to be canceled.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_confirm_start_cancel($form_state, $comp_title) {
  $form['sxjmcomp'] = array('#type' => 'value', '#value' => $comp_title);
  return confirm_form($form, '您确定要取消开始竞赛吗？','sxjm/comp/' . $comp_title,'您可能因为误操作而开始了竞赛。','确定','取消');
}

/**
 * Confirm form submit handler.
 * @param $form
 * @param $form_state
 */
function sxjmcomp_confirm_start_cancel_submit($form, &$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);
  sxjmcomp_comp_set_state(SXJMCOMP_PENDING,$comp_nid);
  $form_state['redirect'] = 'sxjm/comp/'. $form_state['values']['sxjmcomp'];
}

/**
 * Confirm form when the comp is going to stop.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_confirm_stop($form_state, $comp_title) {
  $form['sxjmcomp'] = array('#type' => 'value', '#value' => $comp_title);
  return confirm_form($form, '您确定要结束竞赛吗？','sxjm/comp/' . $comp_title,'竞赛结束后，将不能再提交参赛论文。','确定','取消');
}

/**
 * Confirm form submit handler.
 * @param $form
 * @param $form_state
 */
function sxjmcomp_confirm_stop_submit($form, &$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);
  sxjmcomp_comp_set_state(SXJMCOMP_REVIEWING,$comp_nid);
  $form_state['redirect'] = 'sxjm/comp/'. $form_state['values']['sxjmcomp'];
}

/**
 * Confirm form when a stoped comp is going to be canceled.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_confirm_stop_cancel($form_state, $comp_title) {
  $form['sxjmcomp'] = array('#type' => 'value', '#value' => $comp_title);
  return confirm_form($form, '您确定重新开始竞赛吗？','sxjm/comp/' . $comp_title,'您可能因为误操作而结束了竞赛。','确定','取消');
}

/**
 * Confirm form submit handler.
 * @param $form
 * @param $form_state
 */
function sxjmcomp_confirm_stop_cancel_submit($form, &$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);
  sxjmcomp_comp_set_state(SXJMCOMP_PROCESS,$comp_nid);
  $form_state['redirect'] = 'sxjm/comp/'. $form_state['values']['sxjmcomp'];
}

/**
 * Confirm form when the comp is going to process.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_confirm_process($form_state, $comp_title) {
  $form['sxjmcomp'] = array('#type' => 'value', '#value' => $comp_title);
  return confirm_form($form, '您确定要处理参赛团队吗？','sxjm/comp/' . $comp_title,'根据系统设置处理数学建模参赛团队，结束竞赛报名，准备开始竞赛。','确定','取消');
}

/**
 * Confirm form submit handler.
 * @param $form
 * @param $form_state
 */
function sxjmcomp_confirm_process_submit($form, &$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);
  sxjmcomp_process($comp_nid);
  sxjmcomp_comp_set_state(SXJMCOMP_PENDING,$comp_nid);
  $form_state['redirect'] = 'sxjm/comp/'. $form_state['values']['sxjmcomp'];
}

/**
 * Confirm form when a processing comp is going to be canceled.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_confirm_process_cancel($form_state, $comp_title) {
  $form['sxjmcomp'] = array('#type' => 'value', '#value' => $comp_title);
  return confirm_form($form, '您确定要重新开放竞赛报名吗？','sxjm/comp/' . $comp_title,'在竞赛开始前，您还可以重新开放竞赛报名。','确定','取消');
}

/**
 * Confirm form submit handler.
 * @param $form
 * @param $form_state
 */
function sxjmcomp_confirm_process_cancel_submit($form, &$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);
  sxjmcomp_comp_set_state(SXJMCOMP_OPENING,$comp_nid);
  //对于当前竞赛的所有组，全部设置为开放状态热爱
  $teams = sxjmcomp_comp_get_team($comp_nid);
  foreach($teams as $team) {
    sxjmcomp_team_set_state_og(OG_OPEN,$team['nid']);
  }
  $form_state['redirect'] = 'sxjm/comp/'. $form_state['values']['sxjmcomp'];
}

/**
 * Confirm form when a published comp is going to be republished.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_republish_confirm_form($form_state, $comp_title) {
  $form['sxjmcomp'] = array('#type' => 'value', '#value' => $comp_title);
  return confirm_form($form, '您已经发布过竞赛结果，确定要重新发布吗？','sxjm/comp/' . $comp_title,'您可能需要修改某些团队的竞赛成绩','确定','取消');
}

/**
 * Confirm form submit handler.
 * @param $form
 * @param $form_state
 */
function sxjmcomp_republish_confirm_form_submit($form,&$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);
  sxjmcomp_comp_set_state(SXJMCOMP_REVIEWING,$comp_nid);
  //make page redirect not to be overided by the destination setting
  unset($_REQUEST['destination']);
  $form_state['redirect'] = 'comp/'. $form_state['values']['sxjmcomp'] . '/publish';
}

/**
 * Generate main compteams administration form.
 *
 * @param $form_state
 * @param $comp_title
 */
function sxjmcomp_result_form(&$form_state, $comp_title) {
  $comp = node_load(sxjmcomp_comp_get_nid($comp_title));
  $teams = $comp->field_comp_team;
  $awards = sxjmcomp_result_get_options($comp);

  // Add CSS
  drupal_add_css(drupal_get_path('module', 'sxjmcomp') .'/templates/styles/sxjmcomp.css', 'module', 'all', FALSE);

  // Tree the form values
  $form = array(
    '#tree' => TRUE,
  );
  $form['sxjmcomp'] = array(
    '#type' => 'value',
    '#value' => $comp_title,
  );
  foreach ($teams as $i => $team) {
    $team = node_load($team['nid']);
    $key = 'compteam_'. $team->nid;
    $form[$key]['nid'] = array(
      '#type' => 'value',
      '#value' => $team->nid,
    );
    $form[$key]['title'] = array(
      '#value' => $team->title,
    );
    $form[$key]['members'] = array(
      '#value' => sxjmcomp_team_members_string($team->nid),
    );
    $form[$key]['result'] = array(
      '#type' => 'select',
      '#options' => $awards,
      '#default_value' => isset($team->field_team_score[0]['value'])?$team->field_team_score[0]['value']:-1,//use isset here for there is a 0 value.
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('保存结果'),
  );

  return $form;
}

/**
 * Process main compteams administration form submission.
 *
 * @param $form
 * @param $form_state
 */
function sxjmcomp_result_form_submit($form, &$form_state) {
  $comp_nid = sxjmcomp_comp_get_nid($form_state['values']['sxjmcomp']);

  foreach ($form_state['values'] as $compteam) {
    if(is_array($compteam) && !empty($compteam['nid'])) {
      $compteam_ = node_load($compteam['nid']);
      $compteam_->field_team_score[0]['value'] = $compteam['result'];
      node_save($compteam_);
    }
  }
  sxjmcomp_comp_set_state(SXJMCOMP_FINISHED,$comp_nid);
  drupal_set_message('团队竞赛成绩已保存');
  cache_clear_all();
  $form_state['redirect'] = 'sxjm/comp/';
}

/**
 * Process variables for compteam-result-form.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $form
 *
 * @see compteam-result-form.tpl.php
 * @see theme_compteam_result_form()
 */
function template_preprocess_sxjmcomp_result_form(&$variables) {
  $sxjmcomp_nid = sxjmcomp_comp_get_nid(arg(1));
  $sxjmcomp = node_load($sxjmcomp_nid);

  $compteams = $sxjmcomp->field_comp_team;
  $compawards = sxjmcomp_result_get_options($sxjmcomp);

  $variables['result_options'] = $compawards;

  foreach ($compawards as $key => $value) {
    $variables['result_listing'][$key] = array();
  }

  foreach (element_children($variables['form']) as $i) {
    $compteam = &$variables['form'][$i];

    // Only take form elements that are compteams.
    if (isset($compteam['title'])) {
      // Fetch result for current compteam.
      $result = $compteam['result']['#default_value'];
      // Set special classes needed for table drag and drop.
      $variables['form'][$i]['result']['#attributes']['class'] = 'compteam-result-select compteam-result-'. $result;
      // Add compteam per row
      $variables['result_listing'][$result][$i]->row_class = isset($compteam['#attributes']['class']) ? $compteam['#attributes']['class'] : '';
      $variables['result_listing'][$result][$i]->modified = isset($compteam['#attributes']['class']) && strpos($compteam['#attributes']['class'], 'modified') !== FALSE ? TRUE : FALSE;
      $variables['result_listing'][$result][$i]->nid =  drupal_render($compteam['nid']);
      $variables['result_listing'][$result][$i]->title =  drupal_render($compteam['title']);
      $variables['result_listing'][$result][$i]->result = drupal_render($compteam['result']);
      $variables['result_listing'][$result][$i]->members =  drupal_render($compteam['members']);
    }
  }

  $variables['form_submit'] = drupal_render($variables['form']);
}

/**
 * Theme the state field of a comp.
 *
 * @param $view
 * @param $options
 * @param $values
 */
function theme_views_view_field__sxjmcomp_admin__field_comp_state_value($view,$options,$values) {
  switch($values->node_data_field_comp_state_field_comp_state_value) {
    case SXJMCOMP_OPENING:
      $text = "报名中";
      break;
    case SXJMCOMP_PENDING:
      $text = "预备中";
      break;
    case SXJMCOMP_PROCESS:
      $text = "进行中";
      break;
    case SXJMCOMP_REVIEWING:
      $text = "评阅中";
      break;
    case SXJMCOMP_FINISHED:
      $text = "已结束";
      break;
  }
  return $text;
}

/**
 * Theme the selective field of a comp team.
 *
 * @param $view
 * @param $options
 * @param $values
 */
function theme_views_view_field__field_comp_team__default__selective($view,$options,$values) {
  switch($values->og_og_selective) {
    case OG_OPEN:
      $text = "开放";
      break;
    case OG_MODERATED:
      $text = "封闭";
      break;
    case OG_INVITE_ONLY:
      $text = "邀请";
      break;
    case OG_CLOSED:
      $text = "关闭";
      break;
  }
  if ($values->member_count == 3) {
    $text .= '<strong>[已满]</strong>';
  }
  if ($values->member_count > 3) {
    $text .= '<strong>[超员]</strong>';
  }
  return $text;
}
