<?php
// $Id$

/**
 * @file
 * Test 
 */

// Define plugin for CTools
$plugin = array(
  'title' => t('TEST: random fill opacity'),
  'description' => t('Example style plugin for context styling.
    Sets a random fill opacity.'),
  'style_plugin' => array(
    'class' => 'openlayers_test_rnd_fillOpacity',
    'parent' => 'openlayers_style_plugin',
  ),
);

/**
 * Style Plugin for testing purposes.
 */
class openlayers_test_rnd_fillOpacity extends 
  openlayers_style_plugin {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
    );
  }
  
  /**
   * Options form.
   */
  function options_form($defaults = array()) {
    $form = array();
    return $form;
  }

  /**
   * Get an array of style property callbacks
   */
  function get_context_properties() {
    return array(
      'fillOpacity' => 'getFillOpacity',
    );
  }


  /**
   * Render function
   */
  function render() {
    // Add JS
    drupal_add_js(drupal_get_path('module', 'openlayers_test') .
      '/plugins/style_plugin/openlayers_test_rnd_fillOpacity.js');
  }
}
