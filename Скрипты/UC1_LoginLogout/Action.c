Action()
{	
	lr_start_transaction("UC1_LoginLogout");
	
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

	//Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);
	
	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t16.inf", 
		"Mode=HTTP", 
		LAST);

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	lr_think_time(5);

	// Assertion
	web_reg_find("Text=A Session ID has been created and loaded into a cookie called MSO.", LAST);
	
	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t17.inf", 
		"Mode=HTTP", 
		LAST);

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
		"Snapshot=t18.inf", 
		"Mode=HTTP", 
		LAST);
		
	lr_end_transaction("Goto_Home",LR_AUTO);

	lr_start_transaction("Login");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
	// Assertion
	web_reg_find("Text=User password was correct", LAST);
	
	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t19.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=userSession", "Value={userSession}", ENDITEM, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=login.x", "Value=37", ENDITEM, 
		"Name=login.y", "Value=2", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);


	// Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);
	
	web_url("nav.pl_2", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t20.inf", 
		"Mode=HTTP", 
		LAST);

	// Assertion
	web_reg_find("Text= Don't forget to sign off when", LAST);
	web_reg_find("Text=Welcome, <b>{username}</b>", LAST);
	
	web_url("login.pl_2", 
		"URL=http://localhost:1080/cgi-bin/login.pl?intro=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t21.inf", 
		"Mode=HTTP", 
		LAST);


	lr_end_transaction("Login",LR_AUTO);
	
	lr_start_transaction("Goto_Flights");

	// Assertion
	web_reg_find("Text=User has returned to the search page", LAST);
	
	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t21.inf", 
		"Mode=HTTP", 
		LAST);

	// Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);
	
	web_url("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t22.inf", 
		"Mode=HTTP", 
		LAST);

	// Assertion
	web_reg_find("Text=<title>Flight Selections</title>", LAST);
	
	web_url("reservations.pl", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t23.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("Goto_Flights",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("Logout");

	// Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);
	
	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t22.inf", 
		"Mode=HTTP", 
		LAST);

	// Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);
	
	web_url("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t23.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);

	lr_end_transaction("UC1_LoginLogout",LR_AUTO);

	return 0;
}