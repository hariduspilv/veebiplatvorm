(function ($) {

Drupal.behaviors.ddf = {
  attach: function (context, settings) {
    if (!settings.ddf) {
      return;
    }

    $.each(settings.ddf, function(key, form_settings) {
      var id = form_settings['form_id'];
      var form = $('input[value="' + id + '"]', context).closest('form').not('.ddf-processed').addClass('ddf-processed');
      if (form.length === 1) {
        if (form_settings['dependent'] && form_settings['fields']) {
          ddfForm(form, id, form_settings['dependent'], form_settings['fields'], form_settings);
        }
      }
    });

    function ddfForm(form, form_id, dependent, fields, form_settings) {
      var controlling_elements = {};
      var dependent_selectors = {};

      $.each(dependent, function(field_name) {
        var element = form.find('[name="' + dependent[field_name] + '"],[name="' + dependent[field_name] + '[]"]');
        dependent_selectors[field_name] = '#' + form.attr('id') + ' [name="' + element.attr('name') + '"]';
        if ((element.length === 1) && (element.attr('id'))) {
          dependent_selectors[field_name] = '#' + element.attr('id');
        }
      });

      $.each(fields, function(field_name, name_attr) {
        var elements = form.find('[name="' + name_attr + '"],[name^="' + name_attr + '["]').not('.ddf-field-processed').addClass('ddf-field-processed');
        if (elements.length > 0) {
          controlling_elements[field_name] = elements;
          elements.each(function() {
            var element = $(this);
            var url = settings['basePath'] + settings['pathPrefix'] + 'ddf/update/' + field_name + '/' +
              ddfGetScalar(form_settings['entity_type']) + '/' +
              ddfGetScalar(form_settings['bundle']) + '/' +
              ddfGetScalar(form_settings['entity_id']);

            element.attr('autocomplete', 'off');
            var ajax = new Drupal.ajax(false, element, {event: 'change', url: url});
            ajax.beforeSerialize = ddfBeforeSerialize;
          });
        }
      });

      function ddfBeforeSerialize(element, options) {
        options.type = 'GET';
        options.data = {};
        options.data['form_build_id'] = form_id;

        $.each(controlling_elements, function(field_name, controlling_element) {
          var value = $(controlling_element).fieldValue();
          options.data[field_name] = (value.length > 0) ? value.join('+') : 'NULL';
        });

        $.each(dependent_selectors, function(field_name, selector) {options.data['dep:' + field_name] = selector;});
      }

      function ddfGetScalar(value) {
        return ($.isArray(value)) ? value[0] : value;
      }
    }
  }
};

/**
 * Command to insert new content into the DOM without wrapping in extra DIV element.
 */
Drupal.ajax.prototype.commands.ddf_insertnowrap = function (ajax, response, status) {
  // Get information from the response. If it is not there, default to
  // our presets.
  var wrapper = response.selector ? $(response.selector) : $(ajax.wrapper);
  var method = response.method || ajax.method;
  var effect = ajax.getEffect(response);

  // We don't know what response.data contains: it might be a string of text
  // without HTML, so don't rely on jQuery correctly interpreting
  // $(response.data) as new HTML rather than a CSS selector. Also, if
  // response.data contains top-level text nodes, they get lost with either
  // $(response.data) or $('<div></div>').replaceWith(response.data).
  var new_content_wrapped = $('<div></div>').html(response.data);
  var new_content = new_content_wrapped.contents();
  var settings = {};

  // If removing content from the wrapper, detach behaviors first.
  switch (method) {
    case 'html':
    case 'replaceWith':
    case 'replaceAll':
    case 'empty':
    case 'remove':
      settings = response.settings || ajax.settings || Drupal.settings;
      Drupal.detachBehaviors(wrapper, settings);
      break;
  }

  // Add the new content to the page.
  wrapper[method](new_content);

  // Immediately hide the new content if we're using any effects.
  if (effect.showEffect !== 'show') {
    new_content.hide();
  }

  // Determine which effect to use and what content will receive the
  // effect, then show the new content.
  if ($('.ajax-new-content', new_content).length > 0) {
    $('.ajax-new-content', new_content).hide();
    new_content.show();
    $('.ajax-new-content', new_content)[effect.showEffect](effect.showSpeed);
  }
  else if (effect.showEffect !== 'show') {
    new_content[effect.showEffect](effect.showSpeed);
  }

  // Attach all JavaScript behaviors to the new content, if it was successfully
  // added to the page, this if statement allows #ajax['wrapper'] to be
  // optional.
  if (new_content.parents('html').length > 0) {
    // Apply any settings from the returned JSON if available.
    settings = response.settings || ajax.settings || Drupal.settings;
    Drupal.attachBehaviors(wrapper, settings);
  }
};

})(jQuery);
