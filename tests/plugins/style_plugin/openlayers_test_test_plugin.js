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
  this.params.point_radius_high = parseInt(this.params.point_radius_high);
  this.params.point_radius_low = parseInt(this.params.point_radius_low);
};

/**
 * Style plugin context class methods
 */
Drupal.openlayers.style_plugin.openlayers_test_test_plugin.prototype = {

  // Private methods (not copied to final style context object)
  'prv' : {
    'random' : function(low, high) {
      return Math.floor(Math.random() * (high-low+1)) + low;
    }
  },
  
  // Fill opacity context.  Sets random fill opacity.
  'getFillOpacity' : function(feature) {
    // Random fill opacity
    return this.prv.random(1, 100)/100;
  },
  
  // Point radius context.  Given paramters, gets a random
  // pointRadius.
  'getPointRadius' :  function(feature) {
    var high = this.params.point_radius_high;
    var low = this.params.point_radius_low;
    return this.prv.random(low, high);
  }
};
