/**
 * @file
 * Localize Fields test Javascript behaviors.
 */

/*jslint browser: true, continue: true, indent: 2, newcap: true, nomen: true, plusplus: true, regexp: true, white: true, ass: true*/
/*global alert: false, confirm: false, console: false*/
/*global jQuery: false, Drupal: false*/

(function ($) {
  'use strict';

  Drupal.behaviors.localizeFieldsTest = {
    attach: function (context) {
      var elms, le, i, type, s, em, k, n = 0, m, p, rgx = /(LOCALIZE_FIELDS_UNTRANSLATED)/g, rgxToken = /\[current\-date:short\]/, nErrors = {
        label: 0,
        description: 0,
        'allowed values': 0,
        prefix: 0,
        suffix: 0
      };

      type = 'allowed values';
      le = (elms = $('label.option').get()).length;
      m = 0;
      for (i = 0; i < le; i++) {
        if ((s = elms[i].innerHTML).indexOf('LOCALIZE_FIELDS_UNTRANSLATED') > -1) {
          console.log(type + '(' + (++m) + ')' + ': ' + s);
          $(elms[i]).html(s.replace(rgx, '<span class="localize-fields-test">UNTRANSLATED</span>'));
          ++n;
          ++nErrors[type];
        }
      }

      type = 'label';
      le = (elms = $('label,fieldset > legend > span.fieldset-legend').get()).length;
      m = 0;
      for (i = 0; i < le; i++) {
        if ((s = elms[i].innerHTML).indexOf('LOCALIZE_FIELDS_UNTRANSLATED') > -1) {
          console.log(type + '(' + (++m) + ')' + ': ' + s);
          $(elms[i]).html(s.replace(rgx, '<span class="localize-fields-test">UNTRANSLATED</span>'));
          ++n;
          ++nErrors[type];
        }
      }

      type = 'description';
      le = (elms = $('div.description,div.fieldset-description').get()).length;
      m = p = 0;
      for (i = 0; i < le; i++) {
        if ((s = elms[i].innerHTML).indexOf('LOCALIZE_FIELDS_UNTRANSLATED') > -1) {
          console.log(type + '(' + (++m) + ')' + ': ' + s);
          $(elms[i]).html(s = s.replace(rgx, '<span class="localize-fields-test">UNTRANSLATED</span>'));
          ++n;
          ++nErrors[type];
        }
        if (s.indexOf('[current-date:short]') > -1) {
          $(elms[i]).html(s.replace(rgxToken, '<span class="localize-fields-test">TOKEN</span>'));
          ++p;
        }
      }

      type = 'prefix';
      le = (elms = $('span.field-prefix').get()).length;
      m = 0;
      for (i = 0; i < le; i++) {
        if ((s = elms[i].innerHTML).indexOf('LOCALIZE_FIELDS_UNTRANSLATED') > -1) {
          console.log(type + '(' + (++m) + ')' + ': ' + s);
          $(elms[i]).html(s.replace(rgx, '<span class="localize-fields-test">UNTRANSLATED</span>'));
          ++n;
          ++nErrors[type];
        }
      }

      type = 'suffix';
      le = (elms = $('span.field-suffix').get()).length;
      m = 0;
      for (i = 0; i < le; i++) {
        if ((s = elms[i].innerHTML).indexOf('LOCALIZE_FIELDS_UNTRANSLATED') > -1) {
          console.log(type + '(' + (++m) + ')' + ': ' + s);
          $(elms[i]).html(s.replace(rgx, '<span class="localize-fields-test">UNTRANSLATED</span>'));
          ++n;
          ++nErrors[type];
        }
      }

      if (n) {
        em = 'Untranslated label(s) found:';
        for (k in nErrors) {
          if (nErrors.hasOwnProperty(k)) {
            em += "\n- " + k + ': ' + nErrors[k];
          }
        }
        alert(em);
      }
      else {
        console.log('Found no Localize Fields translation errors.');
      }
      if (!p) {
        console.log('Found no Token replacement errors.');
      }
      else {
        console.log('Token replacement errors: ' + p + '.');
      }
    }
  };
}(jQuery));
