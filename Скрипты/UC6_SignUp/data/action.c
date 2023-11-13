Action()
{

	lr_start_transaction("UC6_SignUp");

	lr_start_transaction("Goto Home");

	web_add_auto_header("sec-ch-ua", 
		"\"Google Chrome\";v=\"119\", \"Chromium\";v=\"119\", \"Not?A_Brand\";v=\"24\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTTP", 
		LAST);

	web_add_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t2.inf", 
		"Mode=HTTP", 
		LAST);

	web_add_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	web_url("nav.pl", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t3.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("Goto Home",LR_AUTO);

	lr_start_transaction("Goto SignUpNow");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	lr_think_time(28);

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t4.inf", 
		"Mode=HTTP", 
		LAST);

	web_add_header("Sec-Fetch-Dest", 
		"script");

	web_url("profileValidate.js", 
		"URL=http://localhost:1080/WebTours/profileValidate.js", 
		"Resource=1", 
		"RecContentType=application/javascript", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t5.inf", 
		LAST);

	lr_end_transaction("Goto SignUpNow",LR_AUTO);

	lr_start_transaction("Registration");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	lr_think_time(93);

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t6.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=username", "Value=testuser", ENDITEM, 
		"Name=password", "Value=1234", ENDITEM, 
		"Name=passwordConfirm", "Value=1234", ENDITEM, 
		"Name=firstName", "Value=firstName1", ENDITEM, 
		"Name=lastName", "Value=lastName1", ENDITEM, 
		"Name=address1", "Value=Address 1", ENDITEM, 
		"Name=address2", "Value=000001", ENDITEM, 
		"Name=register.x", "Value=40", ENDITEM, 
		"Name=register.y", "Value=10", ENDITEM, 
		LAST);

	lr_end_transaction("Registration",LR_AUTO);

	lr_end_transaction("UC6_SignUp",LR_AUTO);

	return 0;
}