// $Id: sxjmcomp.js$

/**
 * Move a compteam in the compteams table from one result to another via select list.
 *
 * This behavior is dependent on the tableDrag behavior, since it uses the
 * objects initialized in that behavior to update the row.
 */
Drupal.behaviors.compteamDrag = function(context) {
  var table = $('table#compteams');
  var tableDrag = Drupal.tableDrag.compteams; // Get the compteams tableDrag object.

  var checkEmptyresults = function(table, rowObject) {
    $('tr.result-message', table).each(function() {
      // If the dragged row is in this result, but above the message row, swap it down one space.
      if ($(this).prev('tr').get(0) == rowObject.element) {
        // Prevent a recursion problem when using the keyboard to move rows up.
        if ((rowObject.method != 'keyboard' || rowObject.direction == 'down')) {
          rowObject.swap('after', this);
        }
      }
      // This result has become empty
      if ($(this).next('tr').is(':not(.draggable)') || $(this).next('tr').size() == 0) {
        $(this).removeClass('result-populated').addClass('result-empty');
      }
      // This result has become populated.
      else if ($(this).is('.result-empty')) {
        $(this).removeClass('result-empty').addClass('result-populated');
      }
    });
  };

  // A custom message for the compteams page specifically.
  Drupal.theme.tableDragChangedWarning = function () {
    return '<div class="warning">' + Drupal.theme('tableDragChangedMarker') + ' ' + Drupal.t("The changes to these compteams will not be saved until the <em>Save compteams</em> button is clicked.") + '</div>';
  };

  // Add a handler so when a row is dropped, update fields dropped into new results.
  tableDrag.onDrop = function() {
    dragObject = this;
    if ($(dragObject.rowObject.element).prev('tr').is('.result-message')) {
      var resultRow = $(dragObject.rowObject.element).prev('tr').get(0);
      var resultName = resultRow.className.replace(/([^ ]+[ ]+)*result-([^ ]+)-message([ ]+[^ ]+)*/, '$2');
      var resultField = $('select.compteam-result-select', dragObject.rowObject.element);

      if (!resultField.is('.compteam-result-'+ resultName)) {
        resultField.val(resultName);
      }
    }
  };

  // Add a handler for when a row is swapped, update empty results.
  tableDrag.row.prototype.onSwap = function(swappedRow) {
    checkEmptyresults(table, this);
  };

  // Add the behavior to each result select list.
  $('select.compteam-result-select:not(.compteamresultselect-processed)', context).each(function() {
    $(this).change(function(event) {
      // Make our new row and select field.
      var row = $(this).parents('tr:first');
      var select = $(this);
      tableDrag.rowObject = new tableDrag.row(row);

      // Find the correct result and insert the row as the first in the result.
      $('tr.result-message', table).each(function() {
        if ($(this).is('.result-' + select[0].value + '-message')) {
          // Add the new row and remove the old one.
          $(this).after(row);
          // Manually update weights and restripe.
          tableDrag.updateFields(row.get(0));
          tableDrag.rowObject.changed = true;
          if (tableDrag.oldRowElement) {
            $(tableDrag.oldRowElement).removeClass('drag-previous');
          }
          tableDrag.oldRowElement = row.get(0);
          tableDrag.restripeTable();
          tableDrag.rowObject.markChanged();
          tableDrag.oldRowElement = row;
          $(row).addClass('drag-previous');
        }
      });

      // Modify empty results with added or removed fields.
      checkEmptyresults(table, row);
      // Remove focus from selectbox.
      select.get(0).blur();
    });
    $(this).addClass('compteamresultselect-processed');
  });
};
