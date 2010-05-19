<?php
/**
 * Field handler to show a user gender.
 *
 * @ingroup views_field_handlers
 */
class sxjmusers_views_handler_field_gender extends views_handler_field {
  function render($values) {
    $genders = sxjmusers_get_genders();
    return $genders[$values->{$this->field_alias}];
  }
}
