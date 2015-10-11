#ifndef _EFSMANAGEMENT_H_   /* Include guard */
#define _EFSMANAGEMENT_H_

# include "config.h" 
# include "pManagement.h"
# include "util.h" 


# define OKAY 1 
# define ERROR -1 

//			FILL THE BODY OF THE FOLLOWING FUNCTION 


int create_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	return OKAY ; 
}
int delete_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	return OKAY ; 
}

int encrypt_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	return OKAY ; 
}

int  decrypt_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	return OKAY ; 
}

char* read_from_file(unsigned char *username, unsigned char* password, unsigned char * fileName, int offset, int length){
	return NULL ; 
}

int write_to_file(unsigned char *username, unsigned char* password, unsigned char * fileName, int offset, unsigned char * nContent){
	return OKAY ; 
}

int file_size(unsigned char *username, unsigned char* password, unsigned char * fileName){
	return ERROR ; 
}


int file_integrity_check(unsigned char *username, unsigned char* password, unsigned char * fileName){
	return OKAY ; 
}

int system_health_check(){
	return OKAY ; 
}




#endif
