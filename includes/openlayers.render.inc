<?php
// $Id: openlayers.render.inc,v 1.3.2.20 2010/10/05 13:55:37 strk Exp $

/**
 * @file
 * Processing functions for layers and behaviors
 * @ingroup openlayers
 */

/**
 * Initialize the layer array into an indexed array of layer objects
 *
 * @param $layers
 *   Array of layers to process
 * @param $map
 *   Map array
 * @return $layer_data
 *   Array of initialized layer objects
 */
function _openlayers_layers_process($layers = array(), &$map = array()) {
  $layer_data = array();

  $weight = 0;
  foreach ($layers as $layer) {
    if ($layer_object = openlayers_layer_load($layer)) {
      $layer_object->render($map);
      $layer_object->data['title'] = $layer_object->title;
      $layer_object->data['weight'] = ++$weight;
      $layer_data[$layer_object->name] = $layer_object->data;
    }
  }

  return $layer_data;
}

/**
 * Execute render() method for all enabled behaviors.
 *
 * @param $behaviors
 *   Array of behaviors to process
 * @param $map
 *   Map array
 * @return $rendered
 *  Indexed array of rendered behaviors
 */
function _openlayers_behaviors_render($behaviors = array(), &$map = array()) {
  $rendered = array();
  
  foreach (openlayers_behaviors() as $key => $plugin) {
    if (isset($behaviors[$key]) && $class = ctools_plugin_get_class($plugin, 'behavior')) {
      $behavior = new $class($behaviors[$key], $map);
      $rendered[$key] = $behavior->render($map);
    }
  }

  return $rendered;
}

/**
 * Process Styles
 *
 * Get full data for any styles
 *
 * @param $styles
 *   Array of map styles ( <style_role> : <style_name> | <style_array> )
 * @param $layer_styles
 *   Array of layer styles ( <layer_name> : <style_name> | <by_role_array> )
 *   The <by_role_array> is an array of <style_name> indexed by <style_role>
 * @param $map
 *   Map array
 * @return $processed
 *   Indexed array of processed styles ( <style_name> => <style_array> )
 */
function _openlayers_styles_process($styles = array(), 
  $layer_styles = array(), &$map = array()) {
  ctools_include('plugins');

  // Get styles info array
  $styles_info = openlayers_styles();

  // Process with handler if available.
  $used_plugins = array();
  foreach ($styles_info as $i => $style) {
    // Check for property plugins.
    foreach ($style->data as $prop => $propval) {
      if (is_array($propval)) {
        $plugname = $propval['plugin'];
        if (!empty($plugname)) {
          // the above should never happen, except
          // for cases in which the old style plugin 
          // system was used (for prop == 'plugins')
          $used_plugins[$plugname] = TRUE;
        }
      }
    }
  }

  if (!empty($used_plugins)) {
    $style_plugins = openlayers_style_plugins();
    foreach (array_keys($used_plugins) as $plugname) {
      $plug = $style_plugins[$plugname];
      $plugin_class = ctools_plugin_get_class($plug, 'style_plugin');
      if (isset($plugin_class)) {
        $plugin = new $plugin_class();
        $plugin->render();
      }
    }
  }


  // Go through styles
  $processed = array();
  foreach ($styles as $k => $style) {
    // Check if array, if array, just pass on
    if (is_array($style)) {
      $processed[$k] = $style;
    }
    elseif (!empty($styles_info[$style]) && $info = $styles_info[$style]->data) {
      $processed[$k] = $info;
    }
  }

  // Add layer styles
  foreach ($layer_styles as $stylename) {
    // UPGRADE NOTE:
    // Presets up to 6.x-2.x-alpha10 always had a single style
    // per layer specified. Newer ones have them splitted by role
    $stylenames = is_array($stylename) ? array_values($stylename)
      : array($stylename);
    foreach ($stylenames as $style) {
      if (!isset($processed[$style]) && 
          !empty($styles_info[$style]) && 
          $info = $styles_info[$style]->data) {
        $processed[$style] = $info;
      }
    }
  }

  // Run through theme function
  $processed = theme('openlayers_styles', $processed, $map);

  // Return processed
  return $processed;
}

/**
 * Create Map ID
 *
 * Create a unique ID for any maps that are not assigned an ID
 *
 * @note
 *   Technically someone can assign a map ID identical
 *   to the one that is created
 * @return
 *   New map id
 */
function _openlayers_create_map_id() {
  static $map_count = 0;
  $id = 'openlayers-map-auto-id-'. $map_count;
  $map_count++;
  return $id;
}
