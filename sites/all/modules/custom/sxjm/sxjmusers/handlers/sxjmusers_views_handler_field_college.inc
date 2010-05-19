<?php
/**
 * Field handler to show college.
 *
 * @ingroup views_field_handlers
 */
class sxjmusers_views_handler_field_college extends views_handler_field {
  function render($values) {
    $colleges = sxjmusers_get_colleges();
    return $colleges[$values->{$this->field_alias}];
  }
}
