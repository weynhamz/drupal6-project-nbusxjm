Drupal.behaviors.sxjm = function (context) {
  $("div.preview").ready( function () {
     $("div.content-tabs-primary").insertBefore('form#node-form');
  })
}
