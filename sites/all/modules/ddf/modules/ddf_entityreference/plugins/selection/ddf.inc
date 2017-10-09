<?php

if (module_exists('views')) {
  $plugin = array(
    'title' => t('Views: Filter by an entity reference view with dynamic arguments'),
    'class' => 'EntityReference_SelectionHandler_DDF',
    'weight' => 100,
  );
}
