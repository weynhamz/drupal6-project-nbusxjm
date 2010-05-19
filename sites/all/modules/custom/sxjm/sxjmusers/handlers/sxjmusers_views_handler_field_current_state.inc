<?php
/**
 * Field handler to show a user current state.
 *
 * @ingroup views_field_handlers
 */
class sxjmusers_views_handler_field_current_state extends views_handler_field {
  function render($values) {
    return sxjmusers_state_current($values->{$this->field_alias});
  }
}
