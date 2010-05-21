<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
<?php print $head ?>
<?php print $styles ?>
<?php print $scripts ?>
<title><?php print $head_title ?></title>
</head>

<body>

  <!-- wrapper -->
  <div id="wrapper">

  <!-- header -->
  <div id="header" class="clear-block">
    <?php print $header; ?>
    <?php
      print '<h1 id="title"><a href="'. check_url($front_page) .'" title="'. $site_title .'">';
      if ($logo) print '<span id="site-logo"><img src="'. check_url($logo) .'" alt="'. $site_title .'" /></span>';
      if ($site_name) $site_name = check_plain($site_name);
      if ($site_name) print '<span id="site-title">'  . $site_name .'</span>';
      if ($site_slogan) $site_slogan = check_plain($site_slogan);
      if ($site_slogan) print '<span id="site-slogan">'  . $site_slogan .'</span>';
      print '</a></h1>';
    ?>
   <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
   <?php if (!empty($search_box)): print '<div id="search-box">' . $search_box . '</div>'; endif; ?>
  </div> <!-- /header -->

  <!-- container -->
  <div id="container">

    <!-- container-header -->
    <div id="container-header">
      <?php if (!empty($primary_links)) :?>
      <div id="primary">
      <?php print theme('links', $primary_links, array('class' => 'links primary-links')); ?>
      </div>
      <?php endif; ?>
      <?php print $main_header ?>
      <!-- breadcrumb -->
      <?php if(!empty($breadcrumb)) :?>
      <div id="breadcrumb"><?php print $breadcrumb ?></div>
      <?php endif;?><!-- /breadcrumb -->
    </div> <!-- /container-header -->

    <!-- container-middle -->
    <div id="container-middle" class="clear-block">
      <div id="container-middle-left" class="clear-block">
        <?php print $main_left ?>
      </div>
      <div id="container-middle-right" class="clear-block">
        <?php print $main_right ?>
      </div>
      <div id="container-middle-main" class="clear-block">
        <?php if ($show_messages && $messages): print $messages; endif; ?>

        <div id="main-content" class="content">
          <?php if ($title): ?><h2 class="node-title"><?php print $title; ?></h2><?php endif; ?>
          <?php if ($tabs): print '<div class="content-tabs content-tabs-primary">'. $tabs .'</div>'; endif; ?>
          <?php if ($tabs2): print '<div class="content-tabs content-tabs-secondary">'. $tabs2 .'</div>'; endif; ?>
          <?php print $content ?>
          <?php print $main_main ?>
        </div>
      </div>
    </div> <!-- /container-middle -->

    <!-- container-footer -->
    <div id="container-footer" class="clear-block">
      <?php print $main_footer;?>
      <?php if (!empty($secondary_links)): ?>
      <div id="secondary">
      <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')); ?>
      </div>
      <?php endif; ?>
    </div> <!-- /container-footer -->

  </div> <!-- /container -->

  </div> <!-- /wrapper -->

  <!-- footer -->
  <div id="footer" class="clear-block">
    <div id="footer-msg"><?php print $footer_message?></div>
    <?php print $footer ?>
  </div> <!--/footer -->

<?php print $closure ?>

</body>
</html>
