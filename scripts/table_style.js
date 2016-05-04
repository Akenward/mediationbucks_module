(function($) {
	
 /** jQuery implementation of Drupal.behaviours receiving two arrays, link_array and meeting_array as settings from availability.block.views
  *  @link_array contains all availability data and meeting commitments organised by mediator, period of the week and w/c Monday
  *  Used to produce a list of mediators available in a side block for any period or week displayed in an availability table 
  *  and to display availability notes and/or meeting details for a mediator as a mouseover feature.
  *  @meeting_array contains meeting data organised by period of the week and w/c Monday.  Used to highlight periods in the availability table.
  *  This script applies to the views "Mediator availability" and "Availability by mediator".
    */ 
Drupal.behaviors.availability = {
  attach: function (context, settings) {
  	//set up variables for the two arrays passed as settings
  	var link_array = Drupal.settings.availability.mediators;
  	var meeting_array = Drupal.settings.availability.meetings;
  	// set up a variable with main function scope for the placeholder div that will hold the mediator list
  	var mediator_list = $('#mediator-list');
  	
  	// Set up array to help convert month names to a number
    
    var month_convert = {'January': 0, 'February': 1, 'March': 2, 'April': 3, 'May': 4, 'June': 5, 'July': 6, 'August': 7, 'September': 8, 'October': 9, 'November': 10, 'December':11};
    
    /** Views uses column labels for a generic week e.g. "Mon am".  We need to insert the actual day of the month
    *   e.g. "mon 27 am".  This is done by finding the weekday number (0 - 4) from the label and the date 
    *   for the Monday starting the week from the table caption e.g. 27th October 2014".  This is reformatted
    *   to produce a date object.  The date object is then adjusted to the cell date by adding the appropriate number of days.
    *   Then the day of the month (e.g. 27) is inserted into the column label.
    */ 
    var elts = $("th.views-field");
    $.each(elts, function( index, value) {
      var label_bits = $(this).html().trim().split(' ');
      var week_day = {'Mon': 0, 'Tue': 1, 'Wed': 2, 'Thur': 3, 'Fri': 4}[label_bits[0]];
      var table_caption = $(this).parent().parent().parent().children().filter('caption').html();
      var date_bits = table_caption.split(' ');
      date_bits[1] = month_convert[date_bits[1]];
      date_bits[0] = date_bits[0].substr(0, date_bits[0].length - 2);
      var start_monday = new Date(date_bits[2], date_bits[1], date_bits[0]);
      start_monday.setDate(start_monday.getDate() + week_day);
      $(this).html(label_bits[0] + '<br>' + start_monday.getDate() + '<br>' + label_bits[1]);
    });
    
    /** Highlight cells in the availability table affected by a meeting 
    *   We need to work through the meeting list retrieving the cell (if displayed) that matches week period and w/c Monday 
    *   and add the class that will highlight it as affected by a meeting.
    */ 
    $.each(meeting_array, function( index, value ) {
      var meeting_monday = value.monday;
      var meeting_d = value.day;
      var meeting_t = value.time;
      $('td.views-field-' + meeting_d + '-' + meeting_t).filter( function() {
       	return($(this).parent().parent().parent().children().filter('caption').html() == meeting_monday);
      }).addClass('meeting-date');
    });
    
    $("td.views-field").hover(
      function() {
      $(this).addClass('highlight-cell');
      },
      function() {
      $(this).removeClass('highlight-cell');
      }
    );
  	
  	/** Set click watchers on the view cells showing aggregate mediator availability.  These create a list of mediators
  	*   making up the total shown in the table plus any not showing availability but committed to a meeting. 
    *   The mediators are formatted to distinguish available, maybe available and affected by a meeting. 
    */ 
  	$("td.views-field").click(function(){
  		
  	  // clear any mediator list already set up
  	  mediator_list.empty();
  	  
  	  // find the period of the week for the cell being clicked by picking out the character pattern in the class list
  	  // keep a 'underscore' version to match the period name used in Views and link_array as well as hyphen version to use in DOM elements
  	  var position = ($(this).attr('class').search(/(mo|tu|we|th|fr)\-(m|a|e)/));
  	  if (position != -1) {
  	  	var click_period = $(this).attr('class').substring(position, position + 4);
  	  	var click_period_underscore = click_period.replace(/-/g, '_');
  	    
  	  }
  	  // Find the w/c Monday by working upwards through the DOM to the caption for the current week's table and reading the mark-up
  	  //  and then reformat from e.g. Monday 27th November to 2014-11-27 for link_array references and to build a date object to which a day value
  	  // can be added to get the date of the clicked cell.  This is used in a preface to the list of mediators.
  	  var table_caption = $(this).parent().parent().parent().children().filter('caption').html();
      var date_bits = table_caption.split(' ');
      month_code = ('0' + (1 + month_convert[date_bits[1]])).slice(-2);
      date_code = ('0' + (date_bits[0].substr(0, date_bits[0].length - 2))).slice(-2);
      var start_monday = date_bits[2] + '-' + month_code + '-' + date_code;
      var date_monday = new Date(date_bits[2], month_code - 1, date_code);
      week_day = {'mo': 0, 'tu': 1, 'we': 2, 'th': 3, 'fr': 4}[click_period.split('-')[0]];
      day_period = click_period.split('-')[1];
      date_monday.setDate(date_monday.getDate() + week_day);
      var day_script = 'for the ' + {'m': 'morning', 'a':'afternoon', 'e':'evening'}[day_period] + ' of ';
      day_script += ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'][date_monday.getDay() - 1] + ' ';
      day_script += ordinal_suffix_of(date_monday.getDate()) + ' ';
      day_script += Object.keys(month_convert)[date_monday.getMonth()];
      mediator_list.append('<p>' + day_script + '</p>');
   
  	  // check each mediator element in link_array, selecting those with availability showing for the clicked w/c Monday and period of the week
  	  // Add each qualifying name to the list of mediators in the mediator list <div> formatted using class according to whether they have 
  	  // definite or maybe availability.
  	  $.each(link_array, function( index, value) {
  	  	var mediator_name_clear = value['name'];
  	  	var mediator_name = mediator_name_clear.replace(/\s/g,'-');
  	  	var name_shown = false;
  	  	if (value.hasOwnProperty(start_monday)) {
  	  	  if (value[start_monday].hasOwnProperty('available')) {
  	  	  	if (value[start_monday]['available'].hasOwnProperty(click_period_underscore)) {
  	  	  	  if (value[start_monday]['available'][click_period_underscore] == '1.0') {
  	  	  	    mediator_list.append('<div id = "box-' + mediator_name + '-' + start_monday + '-' + click_period + '" class = "mediator-name mediator-name-yes">' + mediator_name_clear + '</div>');
  	  	  	  }
  	  	  	  else {
  	  	  	  	mediator_list.append('<div id = "box-' + mediator_name + '-' + start_monday + '-' + click_period + '" class = "mediator-name mediator-name-maybe">' + mediator_name_clear + '</div>');
  	  	  	  }
  	  	  	  name_shown = true;
  	  	  	}
  	  	  }
  	  	  // then check if there's meeting data in the mediator element of link_array.  If there is and we've already included the mediator, change the class
  	  	  // to format as affected by a meeting.  If the mediator is affected by a meeting but is not showing availability then add them to the list
  	  	  // with a class for meeting format.
  	  	  if (value[start_monday].hasOwnProperty('meeting')) {
  	  	    if (value[start_monday]['meeting'].hasOwnProperty(click_period_underscore)) {
  	  	      if (name_shown) {
  	  	      	$("#box-" + mediator_name + '-' + start_monday + '-' + click_period).removeClass("mediator-name-yes mediator-name-maybe");
  	  	      	$("#box-" + mediator_name + '-' + start_monday + '-' + click_period).addClass("mediator-name-meeting");
  	  	      }
  	  	      else {
  	  	      	mediator_list.append('<div id = "box-' + mediator_name + '-' + start_monday + '-' + click_period + '" class = "mediator-name mediator-name-meeting">' + mediator_name_clear + '</div>');
  	  	      }
  	  	      name_shown = true;
  	  	    }
  	  	  }
  	  	}
  	  });
  	  
  	  // If the view contains an autocomplete box for a user (mediator) implying that it is the "availability by mediator" view and this box is non-empty,
  	  // identify mediators listed but not included in the autocomplete list and give them a class that makes them disappear, so the list matches the total 
  	  // availability in the View aggregate cell plus any additional mediators with meetings.
  	  if ($(".form-autocomplete").filter("#edit-uid").attr("value")) {
        var selected_mediators = $(".form-autocomplete").filter("#edit-uid").attr("value").split(', ');
        if (selected_mediators.length > 0) {
          $(".mediator-name").filter(function() {
      	    return($.inArray($(this).html(), selected_mediators) == -1);
          }).addClass('mediator-name-hidden');
        }
      }
  	  // clear the placeholder div for mediator notes update the mouseover watchers that display notes for the new mediator list
  	  $("#mediator-notes").html('');
  	  mouse_over_update();
  	  
  	  // include an explanatory note if the mediator list is empty.
  	  if ($(".mediator-name").length == 0) {
  	  	mediator_list.append('<p>No mediators meet these criteria<\p>');
  	  }
  	});
  	
  	/** Set up the mouseover watchers to display mediator meeting details for the period and avaiability notes
    * for the relevant week when the cursor is held over that mediator's name.  Shuffle classes
    * so that the text colour for notes matches the mediator background colour
    */ 
    function mouse_over_update() {
      $("div.mediator-name-yes").mouseover(function(){
        $("#mediator-notes").removeClass("mediator-notes-maybe mediator-notes-meeting");
        $("#mediator-notes").addClass("mediator-notes");
        $("#mediator-notes").html(write_mediator_notes($(this)));
      });
    
      $("div.mediator-name-maybe").mouseover(function(){
   	    $("#mediator-notes").removeClass("mediator-notes mediator-notes-meeting");
        $("#mediator-notes").addClass("mediator-notes-maybe");
        $("#mediator-notes").html(write_mediator_notes($(this)));
      });
   
      $("div.mediator-name-meeting").mouseover(function(){
   	    $("#mediator-notes").removeClass("mediator-notes mediator-notes-maybe");
        $("#mediator-notes").addClass("mediator-notes-meeting");
        $("#mediator-notes").html(write_mediator_notes($(this)));
      });
    }
    
    /** Helper function to compose availability notes and meeting details
    * @mediator_div: the DOM div element for the mediator name containing relevant details in the id tag
    * @is_meeting: boolean value - are meeting details required?
    */ 
    function write_mediator_notes(mediator_div) {
      var mediator_notes = '';
      var box_info = $(mediator_div).attr('id');
      var info_bits = box_info.split('-');
      var mediator_name = info_bits[1] + ' ' + info_bits[2];
      var start_monday = info_bits[3] + '-' + info_bits[4] + '-' + info_bits[5];
      var click_period = info_bits[6] + '_' + info_bits[7]
      $.each(link_array, function( index, value) {
      	if (value['name'] == mediator_name) {
      	  if (value[start_monday].hasOwnProperty('notes')) {
      	  	mediator_notes = (value[start_monday]['notes'].length > 0) ? ('<p>"' + value[start_monday]['notes'] + '"</p>') : '' ;
      	  }
      	  // for a mediator affected by a meeting we also need to include meeting details - and there may be more than one
      	  if (mediator_div.hasClass("mediator-name-meeting")) {
      	    $.each(value[start_monday]['meeting'][click_period], function( index, value) {
      	  	  mediator_notes += '<p>' + value.title + ' ' + value.time + '</p>';
      	    });
          }
      	}
      });
      return ('<strong>' + mediator_name + '</strong>' + mediator_notes);	
    }
    
    function ordinal_suffix_of(i) {
      var j = i % 10,
        k = i % 100;
      if (j == 1 && k != 11) {
        return i + "st";
      }
      if (j == 2 && k != 12) {
        return i + "nd";
      }
      if (j == 3 && k != 13) {
        return i + "rd";
      }
      return i + "th";
    }
  }
};
})(jQuery);