Action()
{
	int countFlight;
	int countFlightAfterDelete;

	lr_start_transaction("UC5_CancelTicket");

	lr_start_transaction("Goto Home");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Google Chrome\";v=\"119\", \"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");
	
	web_reg_save_param("userSession",
    "LB=name=\"userSession\" value=\"",
    "RB=\"",
    "Search=Body",
    LAST);
	
	// Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Goto Home",LR_AUTO);

	lr_start_transaction("Login");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	lr_think_time(5);
	
	// Assertion
	web_reg_find("Text=User password was correct", LAST);
	web_reg_find("Text={username}", LAST);

	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=body", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={userSession}", ENDITEM, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=login.x", "Value=65", ENDITEM, 
		"Name=login.y", "Value=6", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	lr_end_transaction("Login",LR_AUTO);

	lr_start_transaction("Goto Itinerary");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
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

	lr_end_transaction("Goto Itinerary",LR_AUTO);

	lr_start_transaction("Cancel one ticket");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(5);
	
	lr_save_int(atoi(lr_eval_string("{flight_count}")),"countFlight");
	
	countFlight = atoi(lr_eval_string("{countFlight}"));
	
	web_reg_save_param("flightAfterDelete",
   		"lb=name=\"flightID\" value=\"",
		"rb=\"",
        "ord=all",
        "Notfound=warning",
        LAST);
	
	if(countFlight<=2 && countFlight > 0)
	{
		int randNumber = rand() % countFlight + 1;
		lr_save_int(randNumber, "randNumber");
		
		// Assertion
		web_reg_find("Text=<title>Flights List</title>", LAST);
		
		web_submit_form("itinerary.pl",
		"Snapshot=t5.inf",
		ITEMDATA,
		"Name={randNumber}", "Value=on", ENDITEM, 
		"Name=removeFlights.x", "Value=72", ENDITEM,
		"Name=removeFlights.y", "Value=7", ENDITEM,
		LAST);
	}
	
	if(countFlight>=3)
	{
		int randNumber1 = rand() % countFlight + 1;
		int randNumber2;
		int randNumber3;
		
		do {
        	 randNumber2 = rand() % countFlight + 1;
    	} while (randNumber1 == randNumber2);

		do {
        	 randNumber3 = rand() % countFlight + 1;
    	} while (randNumber1 == randNumber3 || randNumber3 == randNumber2);

		lr_save_int(randNumber1, "randNumber1");
		lr_save_int(randNumber2, "randNumber2");
		lr_save_int(randNumber3, "randNumber3");
		
		// Assertion
		web_reg_find("Text=<title>Flights List</title>", LAST);
		
		web_submit_form("itinerary.pl",
		"Snapshot=t5.inf",
		ITEMDATA,
		"Name={randNumber1}", "Value=on", ENDITEM, 
		"Name={randNumber2}", "Value=on", ENDITEM, 
		"Name={randNumber3}", "Value=on", ENDITEM, 
		"Name=removeFlights.x", "Value=72", ENDITEM,
		"Name=removeFlights.y", "Value=7", ENDITEM,
		LAST);
	}
	
	countFlightAfterDelete = atoi(lr_eval_string("{flightAfterDelete}"));
	
	if(countFlightAfterDelete == countFlight){
		lr_error_message("������ ��������! ������ ����������.");
	}
    

	lr_start_transaction("Logout");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);

	lr_end_transaction("UC5_CancelTicket",LR_AUTO);

	return 0;
}