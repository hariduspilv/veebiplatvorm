<?php
// $Id$

/**
 * @file
 * Plugin to provide a google reverse geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Google Reverse Geocoder"),
  'description' => t('Reverse Geocodes via google reverse geocoder'),
  'callback' => 'geocoder_reverse_google',
  'terms_of_service' => 'http://code.google.com/apis/maps/documentation/geocoding/#Limits',
);

/**
 * Process Markup
 */
function geocoder_reverse_google($lat, $long, $options = array()) {
  try {
    geophp_load();

    $orig_location = new Point($long, $lat);

    $query = array(
      'latlng' => "$lat,$long",
      'sensor' => 'false',
    );

    // add language if exist
    if (isset($options['language'])) {
      $query['language'] = $options['language'];
    }

    $url = url("http://maps.googleapis.com/maps/api/geocode/json", array('query' => $query));
    $result = drupal_http_request($url);

    if (isset($result->error)) {
      $args = array(
        '@code' => $result->code,
        '@error' => $result->error,
      );
      $msg = t('HTTP request to google API failed.\nCode: @code\nError: @error', $args);
      throw new Exception($msg);
    }

    $data = json_decode($result->data);

    if ($data->status != 'OK') {
      $args = array('@status' => $data->status);
      $msg = t('Google API returned bad status.\nStatus: @status', $args);
      throw new Exception($msg);
    }

    $addresses = array();

    foreach ($data->results as $item) {
      // Check if we should reject these results
      if (isset($options['reject_results'])) {
        if (in_array($item->geometry->location_type, $options['reject_results'], TRUE)) {
          continue;
        }
      }

      // Reject this result if it is too far
      $address = new Point($item->geometry->location->lng, $item->geometry->location->lat);
      $distance = $orig_location->distance($address);
      if (isset($options['reject_distance']) && $distance > $options['reject_distance']) {
          continue;
      }

      $address->address = $item->formatted_address;

      // Add additional metadata to the geometry - it might be useful!
      $address->data = array();
      $address->data['geocoder_accuracy'] = $item->geometry->location_type;
      $address->data['geocoder_formatted_address'] = $item->formatted_address;
      $address->data['geocoder_address_components'] = $item->address_components;
      $address->data['distance'] = $distance;

      $addresses[] = $address;
    }

    if (empty($addresses)) {
      return;
    }

    // The connonical geometry is the first result (best guesse)
    $result = array_shift($addresses);

    // If there are any other addresses, these are auxiliary addresses that represent "alternatives"
    if (count($addresses)) {
      $result->data['geocoder_alternatives'] = $addresses;
    }

    return $result;
  } catch (Exception $e) {
    watchdog_exception('geocoder', $e);
    return FALSE;
  }
}
