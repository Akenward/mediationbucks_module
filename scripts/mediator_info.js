(function($) {
	
 /** 
  *  JQuery script to hide notes and meeting commitments in mediators block 
  *  except when the cursor hovers over the corresponding mediator name
  *  
  */ 
 Drupal.behaviors.availability = {
    attach: function (context) {
      // Initial conditions: all notes and commitments hidden
      $("div").filter(".mediator-notes").addClass("hide-element");
      $("div").filter(".mediator-commitments").addClass("hide-element");
      $("div.availability-notes-title").addClass('hide-element');
      $("div.mediator-commitments-title").addClass("hide-element");
      // Function to set hover and un-hover handlers
      $("div.mediator-name").hover(
      function() {
      	// Hover handler enables visibility of corresponding notes and commitments info while
      	// cursor is over the corresponding mediator name
        mediator_name = $(this).attr('id').replace("box-", "");
        if ($("span.selected-mediator-name").length == 0) {
          $("div#mediator-list").append('<span class="selected-mediator-name"><br/><h2>Addition information for ' + mediator_name.replace("-", " ") + '</h2></span>');
        }
        $("div").filter(".mediator-notes").filter("#notes-" + mediator_name).removeClass("hide-element");
        $("div").filter(".mediator-commitments").filter("#commitments-" + mediator_name).removeClass("hide-element");
        if ($("div").filter(".mediator-notes").filter("#notes-" + mediator_name).length > 0) {
          $("div.availability-notes-title").removeClass('hide-element');
        }
        if ($("div").filter(".mediator-commitments").filter("#commitments-" + mediator_name).length > 0) {
          $("div.mediator-commitments-title").removeClass("hide-element");
        }
      },
      function() {
      	// Un-hover handler removes visibility of all notes and commitments info
      	$("span.selected-mediator-name").remove();
        $("div").filter(".mediator-notes").addClass("hide-element");
        $("div").filter(".mediator-commitments").addClass("hide-element");
        $("div.availability-notes-title").addClass('hide-element');
        $("div.mediator-commitments-title").addClass("hide-element");
      }
    );
  },
};
}(jQuery));
