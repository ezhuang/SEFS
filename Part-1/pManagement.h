#ifndef PMANAGEMENT_H_   /* Include guard */
#define PMANAGEMENT_H_

# include "config.h"
# include <stdio.h>
# include <stdlib.h>
# include <openssl/x509.h>
# include <openssl/evp.h>
# include <openssl/hmac.h>
# include <openssl/rand.h>
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


int valiadate_param(unsigned char *user, unsigned char *password, unsigned char *pFile){
        // valiadate username formate
        int i;
        int userLen = strlen(user); 
        if(userLen<5 || userLen>32)
                return ERROR ; 
        for (i = 0; i < userLen; i++){
                if((user[i] >= '0' && user[i]<='9')
                  ||(user[i] >= 'A' && user[i]<='Z')
                  ||(user[i] >= 'a' && user[i]<='z'))
                  continue;
                else
                  return ERROR;     
        }   
        // valiadate passwork formate
        int passLen = strlen(password); 
        if(passLen<5 || passLen>32)
                return ERROR ; 
        for (i = 0; i < passLen; i++){
                if((password[i] >= '0' && password[i]<='9')
                  ||(password[i] >= 'A' && password[i]<='Z')
                  ||(password[i] >= 'a' && password[i]<='z')
                  ||(password[i]=='@')
                ||(password[i]== '#')
                ||(password[i]== '$')
                ||(password[i]== '%')
                ||(password[i]== '&')
                ||(password[i]== '*') 
                ||(password[i]== '(')
                ||(password[i]== ')')
                ||(password[i]== '-') 
                ||(password[i]== '+')
                ||(password[i]== '='))
                  continue;
                else
                  return ERROR;     
        }


        return OKAY;
 
        }


int register_user(unsigned char *user, unsigned char *password, unsigned char *pFile){
             
         
       
       //write the body
       if(!valiadate_param(user, password, pFile)){printf("formate not right.\n");return ERROR;}   
       if(is_user_valid(user,pFile)==OKAY){printf("user exist.\n");return ERROR;}
       if(isFilePresent(pFile)!=0) createFile(pFile);
       FILE *fOut;
       fOut = fopen(pFile, "a");
       unsigned char *entry = (unsigned char*)malloc(1024 * sizeof(unsigned char));
       //unsigned char *salt = (unsigned char*)malloc(SALT_SIZE * sizeof(unsigned char));
       //unsigned char *hex_string = (unsigned char*)malloc(SALT_SIZE*2 * sizeof(unsigned char));
       //unsigned char *hex_hpass = (unsigned char*)malloc(HMAC_SIZE*2 * sizeof(unsigned char));
       //unsigned char *hPassword = (unsigned char*)malloc(HMAC_SIZE * sizeof(unsigned char));;
       strcat(entry, user);
       strcat(entry,":");
       unsigned char salt[SALT_SIZE];
       unsigned char hex_string[SALT_SIZE*2];
       unsigned char hex_hpass[HMAC_SIZE*2];
       unsigned char hPassword[1024];
       
       //making hash
       if(!getRandBytes(salt, SALT_SIZE)){
                printf("salt ERROR\n");
                return ERROR;
        }
        
       
        
        //printf("1.%s \n", hex_string);

        
        //printf("********||%s||********* \n", salt);
        PKCS5_PBKDF2_HMAC_SHA1 (password,strlen(password),(unsigned char*) salt,strlen(salt),20000 , 32+16 , hPassword);
        //printf("********||%s||********* \n", hPassword);
        hPassword[HMAC_SIZE] = (unsigned char) 0;
        byte_array_to_hex_array(salt, SALT_SIZE, hex_string);
        strcat(entry, hex_string);
        byte_array_to_hex_array(hPassword, HMAC_SIZE,hex_hpass);
        //printf("2.%s \n", hex_hpass);
        
        strcat(entry,":");
        strcat(entry,hex_hpass);
        strcat(entry,"\n");
        //printf("%s", entry);
        fputs(entry, fOut);
        fclose(fOut);
        free(entry);
        //free(salt);
        //free(hex_string);
        //free(hex_hpass);
        //free(hPassword);
        
        //Returns OKAY or ERROR
        printf("DEBUG: Called register_user function\n");
        return OKAY ;
}


/*NOW THIS FUNCTION ALSO TAKES THE USER PASSWORD AS ARGUMENT ... */
int delete_user(unsigned char *user, unsigned char * password, unsigned char *pFile){
        //write the body
        //Returns OKAY or ERROR
        if(isFilePresent(pFile)!=0){printf("file not exist!\n"); return ERROR;}
        FILE *in, *out;
        in = fopen(pFile, "r");
        char *temp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        temp = strdup(pFile);
        strcat(temp,"~");
        if(isFilePresent(temp)==0){remove(temp);}
        out = fopen(temp,"a");
        while ((read = getline(&line, &len, in)) != -1) {

           char *tempLine = strdup(line);
           char *name;
           //while ((token = strsep(&str_copy, ":")))
           name = strsep(&tempLine, ":");
           if(strcmp(name,user)==0){  
              //user name match    
              unsigned char *hexSalt = strsep(&tempLine, ":");
              unsigned char salt[SALT_SIZE]; 
              if(hex_array_to_byte_array(hexSalt, salt)==-1){printf("hex to byte error.\n"); return ERROR;}
              unsigned char hPassword[1024];
              unsigned char *hexHmac = strsep(&tempLine,"\n");
              unsigned char hmac[1024];
              PKCS5_PBKDF2_HMAC_SHA1 (password,strlen(password),(unsigned char*) salt,strlen(salt),20000 , 32 , hPassword);
              hPassword[HMAC_SIZE] = (unsigned char) 0;
              if(hex_array_to_byte_array(hexHmac, hmac)==-1){printf("hex to byte error.\n"); return ERROR;}
              hmac[HMAC_SIZE] = (unsigned char) 0;
              if(strcmp(hPassword,hmac)==0) {printf("delete %s!\n",line);}
              else{
                //password not right
                printf("password not correct!\n");
                fclose(in);
                fclose(out);
                remove(temp);
                return ERROR;
              };
            }else{
              fputs(line,out);
            }   
       }
       if (line) free(line);
       fclose(in);
       fclose(out);
       remove(pFile);
       rename(temp,pFile);
       printf("DEBUG: Called delete_user function\n");
       return OKAY ;
}


int is_user_valid(unsigned char *user, unsigned char *pFile){
        //write the body
        //see if user name already exist
       FILE * fp;
       char * line = NULL;
       size_t len = 0;
       ssize_t read;

       fp = fopen(pFile, "r");
       if (fp == NULL)
           return ERROR;

       while ((read = getline(&line, &len, fp)) != -1) {
           char *tempLine = strdup(line);
           char *name;
           //while ((token = strsep(&str_copy, ":")))
           name = strsep(&tempLine, ":");
           if(strcmp(name,user)==0)
                return OKAY;
           //free(tempLine);
       }
       fclose(fp);
       if (line) free(line);
       //Returns OKAY or ERROR
       printf("DEBUG: Called is_user_valid function\n");
       return ERROR;
}

int match_user(unsigned char *user, unsigned char * password, unsigned char *pFile){
        //write the body
        if(!valiadate_param(user, password, pFile)){printf("formate not right.\n");return ERROR;}   
        FILE * fp;
       char * line = NULL;
       size_t len = 0;
       ssize_t read;

       fp = fopen(pFile, "r");
       if (fp == NULL)
           return ERROR;

       while ((read = getline(&line, &len, fp)) != -1) {
           char *tempLine = strdup(line);
           char *name;
           //while ((token = strsep(&str_copy, ":")))
           name = strsep(&tempLine, ":");
           if(strcmp(name,user)==0){  
            //user name match    
            unsigned char *hexSalt = strsep(&tempLine, ":");
            unsigned char salt[SALT_SIZE]; 
            if(hex_array_to_byte_array(hexSalt, salt)==-1){printf("hex to byte error.\n"); return ERROR;}
            unsigned char hPassword[1024];
            unsigned char *hexHmac = strsep(&tempLine,"\n");
            unsigned char hmac[1024];
            PKCS5_PBKDF2_HMAC_SHA1 (password,strlen(password),(unsigned char*) salt,strlen(salt),20000 , 32 , hPassword);
            hPassword[HMAC_SIZE] = (unsigned char) 0;
            if(hex_array_to_byte_array(hexHmac, hmac)==-1){printf("hex to byte error.\n"); return ERROR;}
            hmac[HMAC_SIZE] = (unsigned char) 0;
            if(strcmp(hPassword,hmac)==0) {printf("hahaha!\n");return OKAY;}
            else return ERROR;

           }
           
       }
       fclose(fp);
       if (line) free(line);
       //Returns OKAY or ERROR
       printf("DEBUG: Called is_user_valid function\n");
       return ERROR;
        
        //Returns OKAY or ERROR
        printf("DEBUG: Called match_user function\n");
        return OKAY ;
}

int change_user_password(unsigned char *user, unsigned char * password_current, unsigned char * password_new, unsigned char *pFile){
        //write the body
        //Returns OKAY or ERROR
        if(isFilePresent(pFile)!=0){printf("file not exist!\n"); return ERROR;}
        FILE *in, *out;
        in = fopen(pFile, "r");
        char *temp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        temp = strdup(pFile);
        strcat(temp,"~");
        if(isFilePresent(temp)==0){remove(temp);}
        out = fopen(temp,"a");
        while ((read = getline(&line, &len, in)) != -1) {

           char *tempLine = strdup(line);
           char *name;
           unsigned char *entry = (unsigned char*)malloc(1024 * sizeof(unsigned char)); 
           //while ((token = strsep(&str_copy, ":")))
           name = strsep(&tempLine, ":");
           

           if(strcmp(name,user)==0){  
              //user name match
              strcat(entry,name);
              strcat(entry,":"); 
              unsigned char *hexSalt = strsep(&tempLine, ":");
              unsigned char salt[SALT_SIZE]; 
              if(hex_array_to_byte_array(hexSalt, salt)==-1){printf("hex to byte error.\n"); return ERROR;}
              strcat(entry,hexSalt);
              strcat(entry,":");
              unsigned char hPassword[1024];
              unsigned char newPassword[1024];
              unsigned char *hexHmac = strsep(&tempLine,"\n");
              unsigned char hmac[1024];
              PKCS5_PBKDF2_HMAC_SHA1 (password_current,strlen(password_current),(unsigned char*) salt,strlen(salt),20000 , 32 , hPassword);
              PKCS5_PBKDF2_HMAC_SHA1 (password_new,strlen(password_new),(unsigned char*) salt,strlen(salt),20000 , 32 , newPassword);
              hPassword[HMAC_SIZE] = (unsigned char) 0;
              if(hex_array_to_byte_array(hexHmac, hmac)==-1){printf("hex to byte error.\n"); return ERROR;}
              hmac[HMAC_SIZE] = (unsigned char) 0;
              if(strcmp(hPassword,hmac)==0) {
                unsigned char newPassHex[HMAC_SIZE*2];
                byte_array_to_hex_array(newPassword,HMAC_SIZE,newPassHex);
                strcat(entry,newPassHex);
                printf("add new line !%s \n",entry);
                fputs(entry,out);
              }else{
                //password not right
                printf("password not correct!\n");
                fclose(in);
                fclose(out);
                remove(temp);
                return ERROR;
              };
            }else{
              fputs(line,out);
            }   
            if (entry) free(entry);
       }
       if (line) free(line);

       fclose(in);
       fclose(out);
       remove(pFile);
       rename(temp,pFile);
       printf("DEBUG: Called change_user_password function\n");
       return OKAY ;
}

#endif
