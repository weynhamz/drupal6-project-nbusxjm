Drupal.behaviors.sxjmusers = function (context) {
  // 生日选择使用 jqury.ui.datepicker
  $('input.datepicker').datepicker({
    showOn: 'both',
    dateFormat: 'yy-mm-dd',
    startDate:'10/01/1949',
    changeYear: true, //加年份选择菜单
    changeMonth: true, //加月份选择菜单
    buttonText: 'Choose a date', //日历图标的文字信息
    buttonImage: Drupal.settings.basePath + Drupal.settings.sxjmusers.path + '/images/calendar.gif',
    buttonImageOnly: true, //关于加日历图标的信息
  });
  $('input.datepicker').datepicker($.datepicker.regional['zh-CN']);
  //禁止input的浏览器记录，以免影响到datepicker的效果
  $('input.datepicker').focus(function(){
    $(this).blur();
  });
}
