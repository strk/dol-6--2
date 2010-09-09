// $Id$

/**
 * @file
 * File to hold custom context styling
 */

/**
 * Style plugin context class
 */
Drupal.openlayers.style_plugin.openlayers_test_rnd_fillOpacity = function (params) {
  this.params = params;
};

/**
 * Style plugin context class methods
 */
Drupal.openlayers.style_plugin.openlayers_test_test_plugin.prototype = {

  // Fill opacity context.  Sets random fill opacity.
  'getFillOpacity' : function(feature) {
    // Random fill opacity
    return Math.random();
  }

};
