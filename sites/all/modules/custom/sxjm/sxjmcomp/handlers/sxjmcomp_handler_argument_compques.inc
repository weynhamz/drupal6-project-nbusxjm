<?php
class sxjmcomp_handler_argument_compques extends views_handler_argument_many_to_one {
  function init(&$view, $options) {
    parent::init($view, $options);
  }
  function query(){
    $compques = sxjmcomp_comp_get_ques(sxjmcomp_team_get_comp($this->argument));
    if (is_array($compques)) {
      foreach ($compques as $value) {
        $argument[] = $value['nid'];
      }
      $this->value = $argument;
      $this->helper->add_filter();
    }
  }
}
