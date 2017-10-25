# https://www.drupal.org/project/admin_menu
drush dl admin_menu
drush en admin_menu
drush en admin_menu_toolbar
drush dis toolbar

# https://www.drupal.org/project/devel
drush dl devel
drush en admin_devel
drush en devel_generate

# https://www.drupal.org/project/ctools
drush dl ctools
drush en ctools

# https://www.drupal.org/project/drupalforfirebug
drush dl drupalforfirebug
drush en drupalforfirebug_preprocess
drush en drupalforfirebug

# https://www.drupal.org/project/adminimal_theme
drush dl adminimal_theme
drush en adminimal
drush vset admin_theme adminimal

# https://www.drupal.org/project/module_filter
drush dl module_filter
drush en module_filter

# Clear cache
drush cc all