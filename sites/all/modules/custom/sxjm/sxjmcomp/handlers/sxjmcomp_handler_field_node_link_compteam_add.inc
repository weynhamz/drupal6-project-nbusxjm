<?php
// $Id: sxjmcomp_handler_field_node_link_compteam_add.inc,v 1.1 2008/09/03 19:21:29 merlinofchaos Exp $
/**
 * Field handler to present a link node edit.
 */
class sxjmcomp_handler_field_node_link_compteam_add extends views_handler_field_node_link {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['title'] = 'title';
    $this->additional_fields['format'] = array('table' => 'node_revisions', 'field' => 'format');
    $this->additional_fields['comp_state'] = array('table'=>'content_type_sxjmcomp','field'=>'field_comp_state_value');
  }

  function render($values) {
    // ensure user has access to edit this node.
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->uid = $values->{$this->aliases['uid']};
    $node->type = $values->{$this->aliases['type']};
    $node->title = $values->{$this->aliases['title']};
    $node->format = $values->{$this->aliases['format']};
    $node->comp_state = $values->{$this->aliases['comp_state']};
    $node->status = 1; // unpublished nodes ignore access control

    $text = !empty($this->options['text']) ? $this->options['text'] : t('添加团队');
    if($node->comp_state == SXJMCOMP_OPENING) {
      $output = l($text, "comp/$node->title/add/team", array('query' => drupal_get_destination()));
    } else {
      $output = '<em>' . $text . '</em>';
    }

    return $output;
  }
}
