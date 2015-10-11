#ifndef PMANAGEMENT_H_   /* Include guard */
#define PMANAGEMENT_H_

# include "config.h"

/*FUNCTION STATUS CODE*/
# define OKAY   1
# define ERROR -1

/*
DO NOT FORGET TO CHECK WHETHER THE USERNAME AND THE PASSWORD ARE VALID IN THE
BEGINNING OF EACH FUNCTION. THAT IS CHECK WHETHER THEY ONLY CONTAIN
CHARACTERS FROM THE CLASSES OF CHARACTERS ALLOWED. CONSULT THE PROJECT DESCRIPTION
TO FIND THE VALID CHARACTER CLASSES. ALSO CHECK TO SEE WHETHER THE PASSWORD
FILE IS EXISTENT. FOR CHECKING FILE EXISTENCE YOU CAN USE THE "isFilePresent"
FUNCTION IN THE "util.h" HEADER FILE .... 
*/


int register_user(unsigned char *user, unsigned char *password, unsigned char *pFile){
        //write the body
        //Returns OKAY or ERROR
        printf("DEBUG: Called register_user function\n");
        return OKAY ;
}


/*NOW THIS FUNCTION ALSO TAKES THE USER PASSWORD AS ARGUMENT ... */
int delete_user(unsigned char *user, unsigned char * password, unsigned char *pFile){
        //write the body
        //Returns OKAY or ERROR
        printf("DEBUG: Called delete_user function\n");
        return OKAY ;
}


int is_user_valid(unsigned char *user, unsigned char *pFile){
        //write the body
        //Returns OKAY or ERROR
        printf("DEBUG: Called is_user_valid function\n");
        return OKAY ;
}

int match_user(unsigned char *user, unsigned char * password, unsigned char *pFile){
        //write the body
        //Returns OKAY or ERROR
        printf("DEBUG: Called match_user function\n");
        return OKAY ;
}

int change_user_password(unsigned char *user, unsigned char * password_current, unsigned char * password_new, unsigned char *pFile){
        //write the body
        //Returns OKAY or ERROR
        printf("DEBUG: Called change_user_password function\n");
        return OKAY ;
}

#endif
