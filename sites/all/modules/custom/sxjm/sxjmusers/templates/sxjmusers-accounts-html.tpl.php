<?php
// $Id: sxjmusers-admin-account-html.tpl.php,v 1.1.2.1 2009/05/13 19:11:04 goba Exp $

/**
 * @file sxjmusers-admin-account-html.tpl.php
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language; ?>" xml:lang="<?php print $language->language; ?>">
  <head>
    <title><?php print $title; ?></title>
    <base href="<?php print $base_url; ?>" />
    <link type="text/css" rel="stylesheet" href="<?php print $base_url;print '/';print drupal_get_path('module','sxjmusers')?>/styles/sxjmusers.print.css" />
  </head>
  <body>
    <h1><?php print $title; ?></h1>
    <?php print $contents; ?>
  </body>
</html>
