<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function hitsa_school_form_install_configure_form_alter(&$form, $form_state)
{
    // Pre-populate the site name with the server name.
    $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}


function hitsa_school_install_tasks()
{
    $tasks['choose_school_type'] = array(
    'display_name' => st('Select enabled languages'),
    'display' => true,
    'type' => 'form',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
    'function' => 'school_type_form',
    );

    $tasks['set_hitsa_defaults'] = array(
    'display_name' => st('Setting website default settings'),
    'display' => true,
    'type' => 'normal',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
    'function' => 'hitsa_set_system_defaults',
    );

    return $tasks;
}

function school_type_form($form, &$form_state)
{
    $form = array();
    $form['enabled_languages'] = array(
    '#type' => 'checkboxes',
    '#title' => st('Languages'),
    '#default_value' => array('en', 'ru'),
    '#options' => array('en' => st('English'), 'ru' => st('Russian')),
    '#description' => st('Select additional enabled languages'),
    );

    $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Save & Continue'),
    );

    return $form;
}

function school_type_form_submit($form, &$form_state)
{
    $enabled_languages = $form_state['values']['enabled_languages'];
    foreach($enabled_languages as $lang => $enabled) {
    db_update('languages')
      ->fields(array(
        'enabled' => empty($enabled) ? 0 : 1,
      ))
      ->condition('language', $lang)
      ->execute();
    }

}

function hitsa_school_profile_details()
{
    $details['language'] = "et";
    return $details;
}

function hitsa_set_system_defaults()
{
    hitsa_set_default_language();
    hitsa_set_language_detection_rules();
    hitsa_translate_webform();
}

function hitsa_set_default_language()
{
    $langs = language_list(); // Note: No argument
    $langcode = 'et';
    variable_set('language_default', $langs[$langcode]);

    // Set default language settings
    db_update('languages')
    ->fields(
        array(
        'prefix' => 'en',
        'weight' => -9,
        )
    )
    ->condition('language',  'en')
    ->execute();

    // Disable "Language None" option
    module_load_include('inc', 'entity_translation', 'entity_translation.admin');
    entity_translation_settings_init('node', array('exclude_language_none' => true));
}

function hitsa_set_language_detection_rules()
{
    include_once DRUPAL_ROOT . '/includes/language.inc';

    $weighted_provider_list = array(
    1 => LOCALE_LANGUAGE_NEGOTIATION_URL,
    10 => LANGUAGE_NEGOTIATION_DEFAULT,
    );
    $all_negotiation_providers = language_negotiation_info();
    $negotiation = array();
    foreach ($weighted_provider_list as $weight => $id) {
        $negotation[$id] = $all_negotiation_providers[$id];
        $negotation[$id]['weight'] = $weight;
    }
    language_negotiation_set(LANGUAGE_TYPE_INTERFACE, $negotation);
}

function hitsa_school_install_tasks_alter(&$tasks, $install_state){
    $tasks['install_select_locale']['function'] = '_hitsa_school_locale_selection';
}

// local callback function
function _hitsa_school_locale_selection(&$install_state){
    $install_state['parameters']['locale'] = 'en';
}

function hitsa_translate_webform() {
    $webform_nid = variable_get('hitsa_contacts_contact_us_webform_nid');

	$node = node_load($webform_nid);

	foreach($node->webform['components'] as &$component) {
		webform_localization_component_update_translation_strings($component);
	}
	webform_localization_translate_strings($node);
	node_save($node);

	$translations = array(
		1 => array(
			'en' => 'First and surname',
			'ru' => 'Имя и фамилия',
		),
		2 => array(
			'en' => 'E-mail',
			'ru' => 'Эл. почта',
		),
		3 => array(
			'en' => 'Message',
			'ru' => 'Сообщение',
		),
	);

	// Add translations
	foreach($node->webform['components'] as $delta => $component) {
		$context = 'webform:' . $node->nid . ':' . $delta . ':#title';
		i18n_string_translation_update($context, $translations[$delta]['en'], 'en');
		i18n_string_translation_update($context, $translations[$delta]['ru'], 'ru');
	}
	i18n_string_translation_update('webform:' . $node->nid . ':3:#description', '* Marked fields are required', 'en' );
	i18n_string_translation_update('webform:' . $node->nid . ':3:#description', '* Отмеченные поля обязательны для заполнения', 'ru');
	
	i18n_string_translation_update('webform:' . $node->nid . ':confirmation', "Thank you! We've received your message.", 'en' );
	i18n_string_translation_update('webform:' . $node->nid . ':confirmation', 'Спасибо! Мы получили ваше сообщение.', 'ru' );

	variable_set('hitsa_contacts_translations_added', TRUE);
}