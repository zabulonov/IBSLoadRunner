# IBSLoadRunner

## Некоторые критерии и их решения

- [x] **Данные для параметров информации о пользователе (логин, пароль, Имя,
Фамилия, адрес и т.д.) должны хранится и вызываться из одного файла для
всех скриптов.**

` ../data/data.dat`

- [x] **Решена вероятная проблема выбора одинакового пункта вылета и прилета.**

```c
departChar = lr_eval_string("{depart}");
do {
  arriveChar = lr_eval_string("{arrive}");
} while (strcmp(departChar, arriveChar) == 0);
```

- [x] **Реализован шаг покупки билета для нескольких пассажиров (от 3ех).**

```
...
"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
"Name=pass2", "Value={randPassName} {randPassSurname}", ENDITEM, 
"Name=pass3", "Value={randPassName} {randPassSurname}", ENDITEM,
...
```
randPassName и randPassSurname будут разные см. параметры

- [x] **Реализован шаг удаления нескольких броней (1-3, рандом).**

```c
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
		lr_error_message("Ошибка удаления! Билеты остуствуют.");
	}
```
- [x] **Реализован шаг выбора рандомного рейса из списка**

```c
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

```

- [x] **Реализован скрипт регистрации новых пользователей с автоматической генерацией
тестовых данных, сценарий включен в профиль тестирования (нельзя использовать
цифры для генерации тестовых даных).**

```c
void generateUnique(char* buffer, int length, char* prefix) {
    long t = time(NULL);
    int random_number = rand() % 100000;  
    snprintf(buffer, length, "%s%ld%d", prefix, t, random_number);
}

void generateRandomString(char *str, int length, char* prefix) {
	
	int prefixLength = strlen(prefix);
	int i;
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	
    strcpy(str,prefix);
    
    for (i = prefixLength; i < length; ++i) {
        int index = rand() % (sizeof(alphabet) - 2); 
        str[i] = alphabet[index]; 
    }
    str[length - 1] = '\0'; 
}
```
Использование:
```c
	// Реализация в globals.h
	generateRandomString(username, 30, "user");
	generateRandomString(password, 50, "password_");
	generateRandomString(name, 20, "name_");
	generateRandomString(surname, 20, "surname_");
	generateRandomString(address, 50, "address_");
	generateUnique(zip, 6, "");
	generateUnique(cardNumber, 11, "");
	generateUnique(expDate, 4, "");
```


