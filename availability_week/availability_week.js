(function($) {
	
  Drupal.availability_edit_protection = {};
  var click = false; // Allow Submit/Edit button
  var edit = false; // Dirty form flag
  
  Drupal.behaviors.availability_week = {
    attach: function (context, settings) {

      //code starts
      var control_wrappers = $('div.availability-wrapper');
    
      // Find the cell containers in the availability grid whose hidden input elements
      // are set to "yes" and invoke the "available" CSS class
      var yes_wrappers = control_wrappers.filter( function() {
        return ($(this).children().val() == 3);
      });
      yes_wrappers.removeClass("not-available maybe-available");
      yes_wrappers.addClass("available");
    
      // Find the cell containers in the availability grid whose hidden input elements
      // are set to "maybe" and invoke the "maybe" CSS class
      var maybe_wrappers = control_wrappers.filter( function() {
        return ($(this).children().val() == 2);
      });
      maybe_wrappers.removeClass("not-available available");
      maybe_wrappers.addClass("maybe-available");
     
      // Find the cell containers in the availability grid whose hidden input elements
      // are set to "no" and invoke the "no" CSS class
      var no_wrappers = control_wrappers.filter( function() {
        return ($(this).children().val() == 1);
      });
      no_wrappers.removeClass("maybe-available available");
      no_wrappers.addClass("not-available");
    
      // Set cursor to a pointer over the tiles containing hidden input elements
      control_wrappers.css('cursor', 'pointer');
    
      // Set up click listeners for the tri-state cycle keeping both
      // the CSS class and the hidden input element value in sync
      control_wrappers.click(function(){
        edit = true;
        var element_value = $(this).children().val();
        switch(element_value) {
          case '1':
            $(this).removeClass("not-available maybe-available");
            $(this).addClass("available");
            element_value = 3;
            break;
          case '2':
            $(this).removeClass("maybe-available available");
            $(this).addClass("not-available");
            element_value = 1;
            break;
          default:
            $(this).removeClass("not-available available");
            $(this).addClass("maybe-available");
            element_value = 2;
        }
        
        $( this ).children(0).val(element_value);
      });
    }
  }
})(jQuery);

