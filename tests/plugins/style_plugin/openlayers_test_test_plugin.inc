<?php
// $Id$

/**
 * @file
 * Test 
 */

// Define plugin for CTools
$plugin = array(
  'title' => t('Example Plugin'),
  'description' => t('Example style plugin for context styling.
    Sets a random fill opacity and point radius.'),
  'style_plugin' => array(
    'class' => 'openlayers_style_plugin_test_plugin',
    'parent' => 'openlayers_style_plugin',
  ),
);

/**
 * Style Plugin for testing purposes.
 */
class openlayers_style_plugin_test_plugin extends 
  openlayers_style_plugin {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'point_radius_low' => 2,
      'point_radius_high' => 10,
    );
  }
  
  /**
   * Options form.
   */
  function options_form($defaults = array()) {
    $form = array();
    
    // Allow use to pick the highest and lowest for random
    // point radius
    $form['point_radius_low'] = array(
      '#type' => 'textfield',
      '#title' => t('Lowest point radius'),
      '#description' => t('Lowest value for the random point radius.'),
      '#default_value' => isset($defaults['point_radius_low']) ?
        $defaults['point_radius_low'] : 2,
    );
    $form['point_radius_high'] = array(
      '#type' => 'textfield',
      '#title' => t('Highest point radius'),
      '#description' => t('Highest value for the random point radius.'),
      '#default_value' => isset($defaults['point_radius_high']) ?
        $defaults['point_radius_high'] : 10,
    );
    
    return $form;
  }

  /**
   * Get an array of style property callbacks
   */
  function get_context_properties() {
    return array(
      'fillOpacity' => 'getFillOpacity',
      'pointRadius' => 'getPointRadius',
    );
  }


  /**
   * Render function
   */
  function render() {
    // Add JS
    drupal_add_js(drupal_get_path('module', 'openlayers_test') .
      '/plugins/style_plugin/openlayers_test_test_plugin.js');
  }
}
