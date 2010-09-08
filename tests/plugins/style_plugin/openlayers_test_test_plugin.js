// $Id$

/**
 * @file
 * File to hold custom context styling
 */

/**
 * Style plugin context class
 */
Drupal.openlayers.style_plugin.openlayers_test_test_plugin = function (params) {
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
  },
  
  // Point radius context.  Given paramters, gets a random
  // pointRadius.
  'getPointRadius' :  function(feature) {
    var high = parseInt(this.params.point_radius_high);
    var low = parseInt(this.params.point_radius_low);
    return Math.floor(Math.random() * (high-low+1)) + low
  }
};
