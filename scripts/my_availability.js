(function($) {
	
  Drupal.availability_edit_protection = {};
  var click = false; // Allow Submit/Edit button
  var edit = false; // Dirty form flag
  
  Drupal.behaviors.availability = {
    attach: function (context, settings) {
      //code starts
      var control_wrappers = $('div.availability-wrapper.hasnt-meeting');
    
      // Find the cell containers in the availability grid whose hidden input elements
      // are set to "yes" and invoke the "available" CSS class
      var yes_wrappers = control_wrappers.filter( function() {
        return ($(this).children().val() == "1.0");
      });
      yes_wrappers.removeClass("not-available maybe-available");
      yes_wrappers.addClass("available");
    
      // Find the cell containers in the availability grid whose hidden input elements
      // are set to "maybe" and invoke the "maybe" CSS class
      var maybe_wrappers = control_wrappers.filter( function() {
        return ($(this).children().val() == "1");
      });
      maybe_wrappers.removeClass("not-available available");
      maybe_wrappers.addClass("maybe-available");
     
      // Find the cell containers in the availability grid whose hidden input elements
      // are set to "no" and invoke the "no" CSS class
      var no_wrappers = control_wrappers.filter( function() {
        return ($(this).children().val() == "0");
      });
      no_wrappers.removeClass("maybe-available available");
      no_wrappers.addClass("not-available");
    
      control_wrappers.css('cursor', 'pointer');
    
      // Set up click listeners for the tri-state cycle keeping both
      // the CSS class and the hidden input element value in sync
      control_wrappers.click(function(){
        edit = true;
        var element_value = $(this).children().val();
        switch(element_value) {
          case "0":
            $(this).removeClass("not-available maybe-available");
            $(this).addClass("available");
            element_value = "1.0";
            break;
          case "1":
            $(this).removeClass("maybe-available available");
            $(this).addClass("not-available");
            element_value = "0";
            break;
          default:
            $(this).removeClass("not-available available");
            $(this).addClass("maybe-available");
            element_value = "1";
        }
        $( this ).children(0).val(element_value);
      });
      $('#edit-number-weeks').spinner({ min: 0, max: 10 });
    
      // *** edit protection ***
           
      var epValues = $('#exit_protection_values').attr('value').split(',');
      var record_exists = epValues[0];
      var exit_protect = epValues[1];
      if (!record_exists) edit = true;
            
      // If they leave an input field, assume they changed it.
      $("#availability-form :input").each(function() {
        $(this).blur(function() {
          edit = true;
        });
      });

      // Let all form submit buttons through
      $("#edit-submit-button").each(function() {
        $(this).addClass('availability-edit-protection-processed');
        $(this).click(function() {
          click = true;
        });
      });

      // Catch all links and buttons EXCEPT for "#" links
      $("a, button, input[type='submit']:not(.availability-edit-protection-processed)").each(function() {
        $(this).click(function() {
          // return when a "#" link is clicked so as to skip the
          // window.onbeforeunload function
          if (edit && $(this).attr("href") != "#") {
            return 0;
          }
        });
      });

      // Handle backbutton, exit etc.
      window.onbeforeunload = function() {   
        if (edit && !click) {
          click = false;
          if (exit_protect > 0) {
          	return (Drupal.t("You will lose all unsaved work."));
           }
        }
      };
    }
  }
})(jQuery);

