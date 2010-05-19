<?php
/**
 * Field handler for displaying a list of groups for a user.
 */
class sxjmcomp_handler_field_compteam_members extends views_handler_field_prerender_list {
  /**
   * Fake the field alias -- we don't want to actually join.
   */
  function init(&$view, $options) {
    parent::init($view, $options);
    //$this->additional_fields['gid'] = array('table' => 'og', 'field' => 'nid');
    $this->field_alias = 'nid';
  }

  /**
   * Add this term to the query
   */
  function query() {
    //$this->add_additional_fields();
  }

  /**
   * Query in pre_render to grab what we need.
   */
  function pre_render($values) {
    foreach ($values as $value) {
      if (!empty($value->nid)) {
        $result = db_query(db_rewrite_sql("SELECT su.realname,ogu.uid FROM {og_uid} ogu JOIN {sxjmusers} su ON ogu.uid = su.uid WHERE nid = %d"), $value->nid);
        while ($row = db_fetch_object($result)) {
          $this->items[$value->nid][$row->uid] = l($row->realname, "user/{$row->uid}");
        }
      }
    }
  }
}
