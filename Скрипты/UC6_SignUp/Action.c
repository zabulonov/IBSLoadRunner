Action()
{
	char username[50];
	char password[50];
	char name[30];
	char surname[30];
	char address[50];
	char zip[6];
	char cardNumber[11];
	char expDate[4];
	FILE* pFile;
	
	// Реализация в globals.h
	generateRandomString(username, 30, "user");
	generateRandomString(password, 50, "password_");
	generateRandomString(name, 20, "name_");
	generateRandomString(surname, 20, "surname_");
	generateRandomString(address, 50, "address_");
	generateUnique(zip, 6, "");
	generateUnique(cardNumber, 11, "");
	generateUnique(expDate, 5, "");
	
    
    lr_save_string(username, "username");
	lr_save_string(password, "password");
	lr_save_string(name, "name");
	lr_save_string(surname, "surname");
	lr_save_string(address, "address");
	lr_save_string(zip, "zip");
	
	lr_output_message("The value of username is: %s", username);


	pFile = fopen("..\\data\\data.dat", "a+");  
	if (pFile != NULL) {
	    lr_output_message("Файл data.dat успешно открыт.");
	    if (fprintf(pFile, "%s,%s,%s,%s,%s,%s,%s,%s \n", username, password,name,surname,address,zip,cardNumber,expDate) > 0) {
	        lr_output_message("Данные успешно записаны в файл.");
	    } else {
	        lr_error_message("Ошибка записи данных в файл.");
	    }
	    fclose(pFile);
	} else {
	    lr_error_message("Не удалось открыть файл users.dat.");
	    return -1;
	}

	lr_start_transaction("UC6_SignUp");

	lr_start_transaction("Goto_Home");

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

	
	// Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);
	
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

	// Assertion
	web_reg_find("Text=<title>Web Tours</title>", LAST);
	
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

	// Assertion
	web_reg_find("Text=<title>Web Tours Navigation Bar</title>", LAST);
	
	web_url("nav.pl", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t3.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("Goto_Home",LR_AUTO);

	lr_start_transaction("Goto_SignUpNow");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	lr_think_time(5);
	
	// Assertion
	web_reg_find("Text=First time registering?", LAST);

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

	lr_end_transaction("Goto_SignUpNow",LR_AUTO);

	lr_start_transaction("Registration");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	lr_think_time(5);

	// Assertion
	web_reg_find("Text=Thank you, <b>{username}</b>", LAST);
	
	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t6.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={name}", ENDITEM, 
		"Name=lastName", "Value={surname}", ENDITEM, 
		"Name=address1", "Value={address}", ENDITEM, 
		"Name=address2", "Value={zip}", ENDITEM, 
		"Name=register.x", "Value=40", ENDITEM, 
		"Name=register.y", "Value=10", ENDITEM, 
		LAST);

	lr_end_transaction("Registration",LR_AUTO);
	
	lr_start_transaction("After_Registration");

	web_revert_auto_header("Sec-Fetch-User");

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("After_Registration",LR_AUTO);

	lr_end_transaction("UC6_SignUp",LR_AUTO);

	return 0;
}