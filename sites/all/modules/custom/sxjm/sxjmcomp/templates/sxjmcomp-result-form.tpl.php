<?php
// $Id: compteam-admin-display-form.tpl.php,v 1.3 2008/01/16 22:57:26 goba Exp
?>
<?php
  // Add table javascript.
  drupal_add_js('misc/tableheader.js');
  drupal_add_js(drupal_get_path('module', 'sxjmcomp') .'/templates/scripts/sxjmcomp.js');
  foreach ($result_options as $result => $award) {
    drupal_add_tabledrag('compteams', 'match', 'sibling', 'compteam-result-select', 'compteam-result-'. $result, NULL, FALSE);
  }
?>
<table id="compteams" class="sticky-enabled">
  <thead>
    <tr>
      <th>参赛团队</th>
      <th>团队成员</th>
      <th>竞赛成绩</th>
    </tr>
  </thead>
  <tbody>
    <?php $row = 0; ?>
    <?php foreach ($result_options as $result => $award): ?>
      <tr class="result result-<?php print $result?>">
        <td colspan="3" class="result"><?php print $award; ?></td>
      </tr>
      <tr class="result-message result-<?php print $result?>-message <?php print empty($result_listing[$result]) ? 'result-empty' : 'result-populated'; ?>">
        <td colspan="3"><em>没有团队获得这个成绩</em></td>
      </tr>
      <?php foreach ($result_listing[$result] as $delta => $data): ?>
      <tr class="draggable <?php print $row % 2 == 0 ? 'odd' : 'even'; ?><?php print $data->row_class ? ' '. $data->row_class : ''; ?>">
        <td class="compteam"><?php print $data->title; ?></td>
        <td class="compteam"><?php print $data->members; ?></td>
        <td><?php print $data->result; ?></td>
      </tr>
      <?php $row++; ?>
      <?php endforeach; ?>
    <?php endforeach; ?>
  </tbody>
</table>
<?php print $form_submit; ?>
