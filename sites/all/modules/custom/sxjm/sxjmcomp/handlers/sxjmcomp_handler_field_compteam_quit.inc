<?php
/**
 * Field handler to show 'leave' link.
 *
 * @ingroup views_field_handlers
 */
class sxjmcomp_handler_field_compteam_quit extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['og_selective'] = 'og_selective';
    $this->additional_fields['title'] = array('table'=>'node','field'=>'title');
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function render($values) {
    global $user;
    if (in_array($values->nid, array_keys($user->og_groups)) && sxjmusers_access('参加数学建模竞赛')) {
      $text = !empty($this->options['text']) ? $this->options['text'] : t('退出');
      switch ((int)$values->{$this->aliases['og_selective']}) {
        case OG_CLOSED:
          return;
        default:
          return l($text, 'comp/team/' . $values->{$this->aliases['title']} . '/quit', array('attributes' => array('rel' => 'nofollow'), 'query' => drupal_get_destination()));
      }
    }
  }
}
