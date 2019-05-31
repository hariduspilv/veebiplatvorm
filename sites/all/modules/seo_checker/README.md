# SEO Complicance Checker

The SEO Compliance Checker is a [Drupal](http://drupa.org) module. It checks node content on search engine optimization upon its creation or modification. Whenever a publisher saves or previews a node, the module performs a set of checks and gives the user a feedback on the compliance of the rules. This module is supported by the [UFirst Group](http://www.ufirstgroup.com).
The module page can be found on [https://drupal.org/project/seo_checker](https://drupal.org/project/seo_checker).

## seo_checker.module

The core module seo_checker doesn't implement any checks. It introduces a hook to gather information about existing SEO checks in other modules. When you save or preview a node, the core module applies the discovered SEO checks, collects the results and displays them in form of a result table to the editor.

## Submodules

The module comes along with two submodules (basic_seo_rules.module and keyword_rules.module) that implement checks for some basic SEO rules. Any drupal module can define further SEO rules by implementing hook_register_seo_rules(). The function should return an array with the rule definitions such as their name, description and callback, similarly to hook_menu().

The submodule **keyword_rules.module** requires a text field on the node where you enter your keywords. It is recommended to use the [Meta Tags](http://drupal.org/project/nodewords "Meta Tags Module") (Drupal 6) respectively [Meta tags](http://drupal.org/project/metatag "Meta tags D7 Module") or [Meta tags quick](http://drupal.org/project/metatags_quick "Meta tags quick Module") module (Drupal 7). Alternatively, you can use CCK but you will have to create the field on your own.

If you have ideas for further SEO rules this module should check, feel free to post them to [#420312].

## Use jquery_ui for nice Sliders in Drupal 6

While **Drupal 7 comes with jQuery UI included**, Drupal 6 still requires you to install an additional module called [jquery_ui](http://www.drupal.org/project/jquery_ui). Once it is installed you will get nice [sliders](http://drupal.org/files/images/threshold_sliders.jpg) in the backoffice to adjust your rule thresholds. 
In order to get the sliders, you need a working combination of modules and JQuery libraries. See the list below to find out what setup you need.

### Preferred setup at the moment

*   SEO Compliance Checker **6.x-2.x**
*   [JQuery Update](http://drupal.org/project/jquery_update) **6.x-2.x**
*   [JQuery UI module](http://drupal.org/project/jquery_ui) with JQuery UI library **1.8.x**

### Setup using older versions

*   SEO Compliance Checker **6.x-1.x**
*   [JQuery Update](http://drupal.org/project/jquery_update) **6.x-1.x**
*   [JQuery UI module](http://drupal.org/project/jquery_ui) with JQuery UI library **1.6.x**