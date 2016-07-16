(function($) {
	
  Drupal.availability_edit_protection = {};
  var click = false; // Allow Submit/Edit button
  var edit = false; // Dirty form flag
  
  Drupal.behaviors.availability = {
    attach: function (context, settings) {
      //code starts
      $('#edit-number-weeks').spinner({ min: 0, max: 10 });
      
      // *** exit protection ***
      var exit_protect = Drupal.settings.availability.exit_protection_settings;
      // If they leave an input field, assume they changed it.
      $("#availability-form :input").each(function() {
        $(this).blur(function() {
          edit = true;
        })
      });
      
      $("#availability-form .availability-wrapper").each(function() {
        $(this).click(function() {
          edit = true;
        })
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

