<?php
/**
 * @file
 * localize_fields_test.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function localize_fields_test_taxonomy_default_vocabularies() {
  return array(
    'lclzflds' => array(
      'name' => 'lclzflds',
      'machine_name' => 'lclzflds',
      'description' => 'Localize Fields Test vocabulary.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
