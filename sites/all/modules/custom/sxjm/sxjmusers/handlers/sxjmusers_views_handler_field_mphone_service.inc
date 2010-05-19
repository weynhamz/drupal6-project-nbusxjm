<?php
/**
 * Field handler to show a mobile phone service.
 *
 * @ingroup views_field_handlers
 */
class sxjmusers_views_handler_field_mphone_service extends views_handler_field {
  function render($values) {
    $mphone_services = sxjmusers_get_mobile_services();
    return $mphone_services[$values->{$this->field_alias}];
  }
}
