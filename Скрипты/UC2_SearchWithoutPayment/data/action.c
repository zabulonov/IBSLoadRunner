Action()
{

	web_url("gts1c3.der", 
		"URL=http://pki.goog/repo/certs/gts1c3.der", 
		"Resource=1", 
		"RecContentType=application/pkix-cert", 
		"Referer=", 
		"Snapshot=t11.inf", 
		LAST);

	web_url("gtsr1.der", 
		"URL=http://pki.goog/repo/certs/gtsr1.der", 
		"Resource=1", 
		"RecContentType=application/pkix-cert", 
		"Referer=", 
		"Snapshot=t12.inf", 
		LAST);

	lr_think_time(58);

	lr_start_transaction("UC2_SearchWithoutPayment");

	web_url("gts1c3.der_2", 
		"URL=http://pki.goog/repo/certs/gts1c3.der", 
		"Resource=1", 
		"RecContentType=application/pkix-cert", 
		"Referer=", 
		"Snapshot=t13.inf", 
		LAST);

	web_url("gtsr1.der_2", 
		"URL=http://pki.goog/repo/certs/gtsr1.der", 
		"Resource=1", 
		"RecContentType=application/pkix-cert", 
		"Referer=", 
		"Snapshot=t14.inf", 
		LAST);

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

	lr_think_time(12);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t15.inf", 
		"Mode=HTTP", 
		LAST);

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t16.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("nav.pl", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t17.inf", 
		"Mode=HTTP", 
		LAST);

	lr_start_transaction("1_Login");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(8);

	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t18.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=userSession", "Value=137636.106763872HAHQzfHpctVzzzzHtctHHpQtDtf", ENDITEM, 
		"Name=username", "Value=jojo", ENDITEM, 
		"Name=password", "Value=bean", ENDITEM, 
		"Name=login.x", "Value=76", ENDITEM, 
		"Name=login.y", "Value=8", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_2", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t19.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("login.pl_2", 
		"URL=http://localhost:1080/cgi-bin/login.pl?intro=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t20.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("1_Login",LR_AUTO);

	lr_think_time(158);

	lr_start_transaction("2_GotoFlights");

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t21.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t22.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("reservations.pl", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t23.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("2_GotoFlights",LR_AUTO);

	lr_start_transaction("3_SearchFlights");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(296);

	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t24.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value=London", ENDITEM, 
		"Name=departDate", "Value=11/05/2023", ENDITEM, 
		"Name=arrive", "Value=Paris", ENDITEM, 
		"Name=returnDate", "Value=11/06/2023", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=on", ENDITEM, 
		"Name=seatPref", "Value=Window", ENDITEM, 
		"Name=seatType", "Value=Business", ENDITEM, 
		"Name=findFlights.x", "Value=63", ENDITEM, 
		"Name=findFlights.y", "Value=9", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("3_SearchFlights",LR_AUTO);

	lr_end_transaction("UC2_SearchWithoutPayment",LR_AUTO);

	return 0;
}