<?php
/**
 * Field handler to show if user is admin or not.
 *
 * @ingroup views_field_handlers
 */
class sxjmcomp_handler_field_compteam_is_active extends og_views_handler_field_og_uid {
  function render($values) {
    if (isset($values->{$this->field_alias})) {
      $is_active = $values->{$this->field_alias};
      if (!$is_active) {
        return '<em>('. t('需要确认'). ')</em>';
      }
    }
  }
}
