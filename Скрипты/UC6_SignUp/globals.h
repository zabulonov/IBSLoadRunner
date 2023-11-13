#ifndef _GLOBALS_H 
#define _GLOBALS_H
#define THINK_TIME 10

//--------------------------------------------------------------------
// Include Files
#include "lrun.h"
#include "web_api.h"
#include "lrw_custom_body.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


//--------------------------------------------------------------------
// Global Variables

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


#endif  //_GLOBALS_H
