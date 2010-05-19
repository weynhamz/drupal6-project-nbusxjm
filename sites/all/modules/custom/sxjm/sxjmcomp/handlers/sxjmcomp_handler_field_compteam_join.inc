<?php
/**
 * Field handler to allow show 'join' link or empty if already member.
 *
 * @ingroup views_field_handlers
 */
class sxjmcomp_handler_field_compteam_join extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['og_selective'] = 'og_selective';
    $this->additional_fields['title'] = array('table'=>'node','field'=>'title');
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    global $user;
    if (!in_array($values->nid, array_keys($user->og_groups))) {
      switch ((int)$values->{$this->aliases['og_selective']}) {
        case OG_CLOSED:
          return '<em>'. t('关闭'). '</em>';
        case OG_INVITE_ONLY:
          return '<em>'. t('需要邀请'). '</em>';
        case OG_MODERATED:
          $txt = t('申请');
          break;
        case OG_OPEN:
          $txt = t('加入');
          break;
      }
      if(isset($txt) && sxjmusers_access('参加数学建模竞赛')) {
        //如果已经加入了改团队所属竞赛的某个团队，则忽略此加入链接
        $compteam = node_load($values->nid);
        $sxjmcomp_nid = $compteam->field_team_comp[0]['nid'];
        if(sxjmcomp_team_joined($sxjmcomp_nid)) {
          return '<em>'. $txt . '</em>';
        } else {
          return l($txt, 'comp/team/' . $values->{$this->aliases['title']} . '/join', array('attributes' => array('rel' => 'nofollow'), 'query' => drupal_get_destination()));
        }
      }
    }
  }
}
