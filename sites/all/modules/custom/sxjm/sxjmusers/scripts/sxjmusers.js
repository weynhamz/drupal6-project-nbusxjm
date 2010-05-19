Drupal.behaviors.sxjmusers = function (context) {
  //字段显示策略定义
  $('input[type=radio][name=categories]', context).bind ('click',function(){
    var current = $('input[type=radio][name=categories]:checked').val();
    switch(current) {
      default:
      case '0':
        var sxjmusers_fields_set = [0,2,3,4,13,14,15];
        break;
      case '1':
        var sxjmusers_fields_set = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15];
        break;
      case '2':
        var sxjmusers_fields_set = [0,2,3,4,5,6,7];
        break;
      case '3':
        var sxjmusers_fields_set = [0,1,3,8,9,10,11,12];
        break;
    }
    var sxjmusers_fields = $('#sxjmusers-admin-filters-fields input[type=checkbox]');
    for(key in sxjmusers_fields) {
      sxjmusers_fields[key].checked = '';
    }
    for(key in sxjmusers_fields_set) {
      field_set = sxjmusers_fields_set[key];
      sxjmusers_fields[field_set].checked = 'checked';
    }
  });
}
