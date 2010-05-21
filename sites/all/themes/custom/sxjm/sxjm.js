if (Drupal.jsEnabled) {
  $(document).ready(function() {
    if($("div.preview")) {
      $("div.content-tabs-primary").insertBefore('form#node-form')
    };
  })
}
