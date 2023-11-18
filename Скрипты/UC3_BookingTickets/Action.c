Action()
{
	char* departChar;
	char* arriveChar;
	int count;
	char* randomOutboundFlight;
	
	lr_start_transaction("UC3_Buy_Ticket");
	
	lr_start_transaction("Goto_Home");
	
	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Google Chrome\";v=\"119\", \"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

	// Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);
	
	web_url("WebTours",
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t39.inf", 
		"Mode=HTTP", 
		LAST);

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");
	
	// Assertion
	web_reg_find("Text=<!-- Home Frame -->", LAST);
	
	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t42.inf", 
		"Mode=HTTP", 
		LAST);
	
//	Save user session
	
	web_reg_save_param("userSession",
	    "LB=name=\"userSession\" value=\"",
	    "RB=\"",
	    "Search=Body",
	    LAST);
	
    // Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);
	
	web_url("nav.pl", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t46.inf", 
		"Mode=HTTP", 
		LAST);
		
	lr_end_transaction("Goto_Home",LR_AUTO);

	lr_start_transaction("Login");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(5);

	// Assertion
	web_reg_find("Text=User password was correct", LAST);
		
	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t47.inf",
		"Mode=HTTP",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={username}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=71", ENDITEM,
		"Name=login.y", "Value=9", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

    // Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);
	
	web_url("nav.pl_2",
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t48.inf", 
		"Mode=HTTP", 
		LAST);

	// Assertion
	web_reg_find("Text=<title>Welcome to Web Tours</title>", LAST);
	web_reg_find("Text=Welcome, <b>{username}</b>, ", LAST);
	
	web_url("login.pl_2", 
		"URL=http://localhost:1080/cgi-bin/login.pl?intro=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t49.inf", 
		"Mode=HTTP", 
		LAST);
	
	lr_end_transaction("Login",LR_AUTO);

	lr_start_transaction("Goto_Flights");
	

	lr_think_time(5);

	// Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);
	
	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t52.inf", 
		"Mode=HTTP", 
		LAST);
	
	// Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);

	web_url("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t53.inf", 
		"Mode=HTTP", 
		LAST);
	
	// Assertion
	web_reg_find("Text=Flight Selections", LAST);
	
	web_url("reservations.pl",
		"URL=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t54.inf", 
		"Mode=HTTP", 
		LAST);


	lr_end_transaction("Goto_Flights",LR_AUTO);

	lr_start_transaction("Search_Flight");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	lr_think_time(5);

	
	web_reg_save_param("OutboundFlight",
	    "LB=<input type=\"radio\" name=\"outboundFlight\" value=\"",
	    "RB=\"",
	    "Ord=ALL",
	    LAST);
		
	
	departChar = lr_eval_string("{depart}");
	do {
    arriveChar = lr_eval_string("{arrive}");
	} while (strcmp(departChar, arriveChar) == 0);

	lr_save_string(departChar, "departUnique");
	lr_save_string(arriveChar, "arriveUnique");
	
	
	
	// Assertion
	web_reg_find("Text=<title>Flight Selections</title>", LAST);
	web_reg_find("Text=>Flight departing from <B>{departUnique}</B> to <B>{arriveUnique}</B> on <B>{departDate}</B>", LAST);
	
	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t55.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
		"Name=depart", "Value={departUnique}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arriveUnique}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefRandom}", ENDITEM, 
		"Name=seatType", "Value={seatTypeRandom}", ENDITEM, 
		"Name=findFlights.x", "Value=37", ENDITEM, 
		"Name=findFlights.y", "Value=10", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM,  
		LAST);

	lr_end_transaction("Search_Flight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("Select_Flight");
	

	count = atoi(lr_eval_string("{OutboundFlight_count}"));
	if (count > 0) {
	
	    int index = rand() % count + 1;
	
	    char paramName[64];
	    sprintf(paramName, "{OutboundFlight_%d}", index);
	
		randomOutboundFlight = lr_eval_string(paramName);
		lr_save_string(randomOutboundFlight, "randomOutboundFlight");
	    lr_output_message("Выбран случайный OutboundFlight: %s", randomOutboundFlight);
	}
	else{
		lr_error_message("Не смог найти OutboundFlight");
	 }

	// Assertion
	web_reg_find("Text=<title>Flight Reservation</title>", LAST);
	web_reg_find("Text={firstName}",LAST);
		
	web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t56.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={randomOutboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
		"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
		"Name=seatType", "Value={seatTypeRandom}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefRandom}", ENDITEM, 
		"Name=reserveFlights.x", "Value=45", ENDITEM, 
		"Name=reserveFlights.y", "Value=15", ENDITEM, 
		LAST);

	lr_end_transaction("Select_Flight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("Send_Payments");

	
	// Assertion
	web_reg_find("Text=<title>Reservation Made!</title>", LAST);
	web_reg_find("Text={firstName}", LAST);
	web_reg_find("Text={lastName}", LAST);
	web_reg_find("Text={creditCard}", LAST);
	web_reg_find("Text={departDate}", LAST);
	
	web_submit_data("reservations.pl_4", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t57.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value={randPassName} {randPassSurname}", ENDITEM, 
		"Name=pass3", "Value={randPassName} {randPassSurname}", ENDITEM, 
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
		"Name=seatType", "Value={seatTypeRandom}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefRandom}", ENDITEM, 
		"Name=outboundFlight", "Value={randomOutboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value={advanceDiscount}", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=35", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);

	lr_end_transaction("Send_Payments",LR_AUTO);
	
	lr_start_transaction("Goto_Itinerary");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
    web_reg_save_param("flight",
       	"LB=name=\"flightID\" value=\"",
       	"RB=\"",
       	"Ord=all",
       	"Notfound=warning",
       	LAST);
	
	// Assertion
	web_reg_find("Text=User wants the intineraries", LAST);
                  
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Goto_Itinerary",LR_AUTO);

	lr_start_transaction("Logout");

	web_revert_auto_header("Origin");

	lr_think_time(5);

	// Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);
	
	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t58.inf", 
		"Mode=HTTP", 
		LAST);

	// Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);
	
	web_url("nav.pl_4", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t59.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);

	lr_end_transaction("UC3_Buy_Ticket",LR_AUTO);

	return 0;
}