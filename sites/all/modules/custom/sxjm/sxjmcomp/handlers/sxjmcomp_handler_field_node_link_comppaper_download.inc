<?php
// $Id: sxjmcomp_handler_field_node_link_comppaper_download.inc,v 1.1 2008/09/03 19:21:29 merlinofchaos Exp $
/**
 * Field handler to present a link node edit.
 */
class sxjmcomp_handler_field_node_link_comppaper_download extends views_handler_field_node_link {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['title'] = 'title';
  }

  function render($values) {
    // ensure user has access to edit this node.
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->uid = $values->{$this->aliases['uid']};
    $node->type = $values->{$this->aliases['type']};
    $node->title = $values->{$this->aliases['title']};

    if(!is_null($node->nid) && sxjmusers_access('管理数学建模竞赛') && sxjmcomp_ques_paper_package_check($node->nid)) {
      $url = sxjmcomp_ques_paper_package_path($node->nid);
      $text = !empty($this->options['text']) ? $this->options['text'] : t('组队处理');
      $output = l($text, $url, array('query' => drupal_get_destination()));
      return $output;

    }
  }
}
