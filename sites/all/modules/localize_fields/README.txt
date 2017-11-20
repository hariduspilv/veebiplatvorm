(Drupal Localize Fields module)

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Implementation
 * How to test when already using i18n field
 * Localize Fields vs. I18n Field
 * Import/conversion of existing translations
 * Installation
 * Notes


INTRODUCTION
------------

Translates field labels in all contexts - forms, validation and view:
 * title and description of all core fields and date fields
 * prefix and suffix of numeric fields
 * decimal separator according to instance settings (validation)
 * option labels of list types

The original impulse for creating the module was that label translation of
fields created via Features doesn't work, neither by core nor by using the
i18n_field module.
The main problem being i18n_field's use of translation textgroup - a concept
which BTW has been abandoned for Drupal 8 (see
https://drupal.org/node/1188430).


IMPLEMENTATION
--------------
Simple implementations of form, field and validation hooks.
A drush script and at batch job for converting/updating features field files
and copying translations from/to i18n_field.


LOCALIZE FIELDS AND TOKEN
-------------------------
Don't use tokens in multi-value'd fields' help text; cannot be translated due a
limitation in the Form API's handling of multi-value'd fields.


HOW TO TEST WHEN ALREADY USING I18N FIELD
-----------------------------------------

Initially:
Do NOT _uninstall_ i18n_field ('Field translation'), because then all
translations created via i18n_field will get lost forever.
Do at the most _disable_ i18n_field.

Installing/enabling Localize Fields via Drush:
 * translations created via i18n_field will automatically be copied by Localize
Fields

Installing/enabling Localize Fields via module GUI:
 * after enabling, go to this page:
/admin/config/regional/localize_fields/copy_i18n_field

Later:
When all translation created via i18n_field has been copied to Localize Fields,
it's advisable - for performance reasons - to uninstall i18n_field
('Field translation').


LOCALIZE FIELDS VERSUS I18N_FIELD
---------------------------------

Scope:
i18n_field is great for GUI-based configuration in a one-off site. And
i18n_field works pretty good for viewing, but not so good for editing.
Localize Fields is great for site install profiles, because it extends Features
and respects the limitations of .po files (no textgroup). And Localize Fields
works equally good for editing and viewing, because it consistently translates
labels used in validation.

Translation textgroup:
i18n_field uses translation textgroup; Localize Fields doesn't because .po
syntax includes no support for a textgroup property.

i18n_field doesn't translate:
 * fields created via Features
 * field labels used in validation (neither #element_validate nor
hook_field_validate()) implementations
 * prefix/suffix of number fields
 * decimal separator of decimal/float values (in validation and viewing)

i18n_field doesn't work well with potx .po export:
 * .po doesn't support textgroup

i18n_field doesn't work well with automated .po use during site install:
 * .po (gettext) doesn't support textgroup

Translation context:
i18n_field _always_ uses translation context whereas for localize_fields it's
an option.

i18n_field discovers and creates source of all labels at module installation;
Localize Fields doesn't, because there's no benefit in doing that.
A translation source should only be created if/when a translation (target) is
available.

Structure of contexts:
 * label and description:
 - i18n_field: [field name]:[bundle]:label
 - Localize Fields: field_instance:[bundle]-[fieldname]:label
(Localize Fields's bundle-field pattern matches the format of Features
field_instance declarations, making it easy to find field by context in a
Features field_instance file.
 * list options
 - i18n_field: [field name]:#allowed_values:[option value]
 - Localize Fields (same for every value): field:[field name]:allowed_values
 * number prefix/suffix
 - i18n_field: N/A
 - Localize Fields (suffix for suffix):
field_instance:[bundle]-[fieldname]:prefix


IMPORT/CONVERSION OF EXISTING TRANSLATIONS
------------------------------------------

Fields created via Features:
drush localize-fields --help

i18n_field translations:
Admin page /admin/config/regional/localize_fields/copy_i18n_field


INSTALLATION
------------

Additionally enables the sub module Localize Fields UI - an extension to the
core Field user interface - if Field UI is enabled.
If the 118n_field module is enabled, that module's weight will be modified (set
lower than Localise Field's weight).
Copies translations (drush installation only) from 118n_field if that module is (or previously was) enabled.
For GUI-based installation there's an admin page for copying translations from/to i18n_field.


NOTES
-----

Variable i18n_string_source_language
is the only way of setting another source language than English.

Doesn't translate integers.

Translation context is optional.
And reversible for fields created via Features (drush script).


MAINTAINER
----------
Jacob Friis Mathiasen <jacob.friis@simple-complex.net>
