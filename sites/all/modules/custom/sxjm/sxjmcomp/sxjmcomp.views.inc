<?php
/**
 * Implementation of hook_views_data().
 */
function sxjmcomp_views_data() {
  $data['node']= array (
    'compques_nid' => array(
      'argument' => array(
        'real field' => 'nid',
        'help' => t('得到数模论文所有可以关联的数模竞赛。'),
        'title' => t('关联竞赛'),
        'handler' => 'sxjmcomp_handler_argument_compques',
      ),
    ),
    'add_compques' => array(
      'field' => array(
        'help' => t('为数模竞赛添加竞赛赛题。'),
        'title' => t('添加赛题'),
        'handler' => 'sxjmcomp_handler_field_node_link_compques_add',
      ),
    ),
    'add_compteam' => array(
      'field' => array(
        'help' => t('为数模竞赛添加参赛团队。'),
        'title' => t('添加团队'),
        'handler' => 'sxjmcomp_handler_field_node_link_compteam_add',
      ),
    ),
    'start_sxjmcomp' => array(
      'field' => array(
        'help' => t('开始数学建模竞赛。'),
        'title' => t('开始竞赛'),
        'handler' => 'sxjmcomp_handler_field_node_link_sxjmcomp_start',
      ),
    ),
    'start_sxjmcomp_cancel' => array(
      'field' => array(
        'help' => t('取消开始数学建模竞赛。'),
        'title' => t('取消开始竞赛'),
        'handler' => 'sxjmcomp_handler_field_node_link_sxjmcomp_start_cancel',
      ),
    ),
    'stop_sxjmcomp' => array(
      'field' => array(
        'help' => t('结束数学建模竞赛。'),
        'title' => t('结束竞赛'),
        'handler' => 'sxjmcomp_handler_field_node_link_sxjmcomp_stop',
      ),
    ),
    'stop_sxjmcomp_cancel' => array(
      'field' => array(
        'help' => t('取消结束数学建模竞赛。'),
        'title' => t('取消结束结赛'),
        'handler' => 'sxjmcomp_handler_field_node_link_sxjmcomp_stop_cancel',
      ),
    ),
    'process_sxjmcomp' => array(
      'field' => array(
        'help' => t('处理数模竞赛组队。'),
        'title' => t('组队处理'),
        'handler' => 'sxjmcomp_handler_field_node_link_sxjmcomp_process',
      ),
    ),
    'process_sxjmcomp_cancel' => array(
      'field' => array(
        'help' => t('取消处理数模竞赛组队。'),
        'title' => t('取消组队处理'),
        'handler' => 'sxjmcomp_handler_field_node_link_sxjmcomp_process_cancel',
      ),
    ),
    'publish_sxjmcomp' => array(
      'field' => array(
        'help' => t('发布数模竞赛竞赛结果。'),
        'title' => t('发布结果'),
        'handler' => 'sxjmcomp_handler_field_node_link_sxjmcomp_publish',
      ),
    ),
    'download_comppaper' => array(
      'field' => array(
        'help' => t('下载特定竞赛的所有参赛论文。'),
        'title' => t('下载论文'),
        'handler' => 'sxjmcomp_handler_field_node_link_comppaper_download',
      ),
    ),
    'packaging_comppaper' => array(
      'field' => array(
        'help' => t('打包特定竞赛的所有参赛论文。'),
        'title' => t('打包论文'),
        'handler' => 'sxjmcomp_handler_field_node_link_comppaper_packaging',
      ),
    ),
  );
  $data['og']['compteam_join'] = array(
    'title' => t('Compteam: Join link'),
    'help' => t('Displays a link for joining a group when a user is not already a member.'),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_join',
    ),
  );
  $data['og']['compteam_quit'] = array(
    'title' => t('Compteam: Quit link'),
    'help' => t('Displays a link for quiting a group when a user is already a member.'),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_quit',
    ),
  );
  $data['og']['compteam_invite'] = array(
    'title' => t('Compteam: Invite link'),
    'help' => t('Displays a link for inviting users to a group.'),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_invite',
    ),
  );
  $data['og']['compteam_members'] = array(
    'title' => t('Compteam: Members list'),
    'help' => t('Dispalys members of a compteam.'),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_members',
    ),
  );
  $data['og']['compteam_members_count'] = array(
    'title' => t('Compteam: Members count'),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_members_count',
      'click sortable' => TRUE,
      'help' => t('Number of members for a group. Excludes memberships which are pending approval.'),
    ),
  );
  $data['og_uid']['compteam_is_admin'] = array(
    'real field' => 'is_admin',
    'title' => t('Compteam: Is admin or member.'),
    'help' => t('Wether a user is an admin or a member.'),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_is_admin',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'og_views_handler_filter_og_is_admin',
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );
  $data['og_uid']['compteam_is_manager'] = array(
    'real field' => 'uid',
    'title' => t('Compteam: Is manager.'),
    'help' => t('Wether a user is a manager.'),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_is_manager',
    ),
  );
  $data['og_uid']['compteam_is_active'] = array(
    'real field' => 'is_active',
    'title' => t('Comptram: Is membership approved'),
    'help' => t("Appends <em>approval needed</em> if user's membership request is pending."),
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_is_active',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Approved'),
      'type' => 'yes-no',
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );
  $data['og_uid']['compteam_managelink'] = array(
    'title' => t('Compteam: Approve/Deny/Remove membership link'),
    'help' => t('A link to approve/deny/remove a group member.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_managelink',
      'click sortable' => FALSE,
    ),
  );
  $data['og_uid']['compteam_managelinkadmin'] = array(
    'title' => t('Compteam: Admin manage link'),
    'help' => t('A link to the <em>Admin create or remove</em> page.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'sxjmcomp_handler_field_compteam_managelinkadmin',
      'click sortable' => FALSE,
    ),
  );
  $data['og_ancestry_1']['table']['group']  = t('Organic groups');
  $data['og_ancestry_1']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'group_nid',
      'table' => 'og_ancestry',
    ),
  );
  $data['og_ancestry_1']['nid'] = array(
    'title' => t('Post: Nid'),
    'help' => t('The node ID of the node.'),
    'field' => array(
      'handler' => 'views_handler_field_node',
    ),
    'relationship' => array(
      'title' => t('Group posts'),
      'help' => t("Bring in information about the group posts based on the group it belogs to."),
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function sxjmcomp_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'sxjmcomp') .'/handlers',
    ),
    'handlers' => array(
      //field
      'sxjmcomp_handler_field_node_link_compques_add' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_compteam_add' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_sxjmcomp_stop' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_sxjmcomp_stop_cancel' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_sxjmcomp_start' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_sxjmcomp_start_cancel' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_sxjmcomp_process' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_sxjmcomp_process_cancel' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_sxjmcomp_publish' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_comppaper_download' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_node_link_comppaper_packaging' => array(
        'parent' => 'views_handler_field_node_link',
       ),
      'sxjmcomp_handler_field_compteam_quit' => array(
        'parent' => 'views_handler_field',
      ),
      'sxjmcomp_handler_field_compteam_join' => array(
        'parent' => 'views_handler_field',
      ),
      'sxjmcomp_handler_field_compteam_invite' => array(
        'parent' => 'views_handler_field',
      ),
      'sxjmcomp_handler_field_compteam_members' => array(
        'parent' => 'views_handler_field_prerender_list',
      ),
      'sxjmcomp_handler_field_compteam_members_count' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'sxjmcomp_handler_field_compteam_is_admin' => array(
        'parent' => 'og_views_handler_field_og_uid',
      ),
      'sxjmcomp_handler_field_compteam_is_active' => array(
        'parent' => 'og_views_handler_field_og_uid',
      ),
      'sxjmcomp_handler_field_compteam_is_manager' => array(
        'parent' => 'og_views_handler_field_og_uid',
      ),
      'sxjmcomp_handler_field_compteam_managelink' => array(
        'parent' => 'og_views_handler_field_og_uid',
      ),
      'sxjmcomp_handler_field_compteam_managelinkadmin' => array(
        'parent' => 'og_views_handler_field_og_uid',
      ),
      'sxjmcomp_handler_argument_compques' => array(
        'parent' => 'views_handler_argument_many_to_one',
      ),
    ),
  );
}
