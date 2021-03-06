# include "util.h"
/*# include "efsManagement.h" */
# include "pManagement.h"
# include "hmac.h"

unsigned char * master_encdec_key ;
unsigned char * master_hmac_key ;  
unsigned char * master_iv = "PURDUECS526CLASSFALL2015WLINUSA0"; 
unsigned char * password_file ; 
unsigned char * master_filelist ="master.filelist";; 


//			FILL THE BODY OF THE FOLLOWING FUNCTIONS 


int create_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	printf("DEBUG: CALLED CREATE_FILE FUNCTION\n"); 
	return OKAY ; 
}
int delete_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	printf("DEBUG: CALLED DELETE_FILE FUNCTION\n"); 
	return OKAY ; 
}

int encrypt_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	printf("DEBUG: CALLED ENCRYPT_FILE FUNCTION\n"); 
	return OKAY ; 
}

int  decrypt_file(unsigned char *username, unsigned char* password, unsigned char * fileName){
	printf("DEBUG: CALLED DECRYPT_FILE FUNCTION\n"); 
	return OKAY ; 
}

char* read_from_file(unsigned char *username, unsigned char* password, unsigned char * fileName, int offset, int length){
	printf("DEBUG: CALLED READ_FROM_FILE FUNCTION\n"); 
	return NULL ; 
}

int write_to_file(unsigned char *username, unsigned char* password, unsigned char * fileName, int offset, unsigned char * nContent){
	printf("DEBUG: CALLED WRITE_TO_FILE FUNCTION\n"); 
	return OKAY ; 
}

int file_size(unsigned char *username, unsigned char* password, unsigned char * fileName){
	printf("DEBUG: CALLED FILE_SIZE FUNCTION\n"); 
	return ERROR ; 
}


int file_integrity_check(unsigned char *username, unsigned char* password, unsigned char * fileName){
	printf("DEBUG: CALLED FILE_INTEGRITY_CHECK FUNCTION\n"); 
	return OKAY ; 
}

int system_health_check(){
	printf("DEBUG: CALLED SYSTEM_HEALTH_CHECK FUNCTION\n"); 
	return OKAY ; 
}



int main(int argc, char* argv[]){




        if(argc != 4){
                printf("ERROR: Missing command line arguments\nUsage: ./efsmanager master_password user_password_file date_and_time_of_last_change\n");
                return 1 ;
        }


	printf("Found master password: %s\n",argv[1]);
	printf("Found user password file: %s\n",argv[2]);
	printf("Found date of last change: %s\n",argv[3]);
	printf("Found master_iv: %s\n",master_iv);

	//copy argv[2] to password_file 
	

	
	/*
	use the master password and master IV to generate the master encryption 
	decryption key and master hmace key. Store the master encryption decryption 
	key in  master_encdec_key and store the master hmac key in master_hmac_key
	*/


        

        unsigned char command[1024];
        int operation_status ;
        while(1){
		printf("Available commands:\n(1) create_file\n(2) delete_file\n(3) encrypt_file\n(4) decrypt_file\n(5) read_from_file\n(6) write_to_file\n(7) file_size\n(8) file_integrity_check\n(9) system_health_check\n(10) quit\n\n\n");
                printf("enter a command: ");
                scanf("%s",command) ;
                // printf("\n") ;
                operation_status = OKAY ;
                if(!strcmp(command,"create_file")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = create_file(username,password,pFile) ;
                }
                else if(!strcmp(command,"delete_file")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = delete_file(username,password,pFile) ;
                }
                else if(!strcmp(command,"encrypt_file")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name to encrypt: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = encrypt_file(username,password,pFile) ;
                }
                else if(!strcmp(command,"decrypt_file")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name to decrypt: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = decrypt_file(username,password,pFile) ;

                }
                else if(!strcmp(command,"file_size")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = file_size(username,password,pFile) ;
                }
                else if(!strcmp(command,"file_integrity_check")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = file_integrity_check(username,password,pFile) ;
                }
                else if(!strcmp(command,"system_health_check")){
                        operation_status = system_health_check(); 
                }
                else if(!strcmp(command,"read_from_file")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);
			printf("position to read from: ");
			int offset ; scanf("%d",&offset); 
			printf("how many characters to read: "); 
			int len; scanf("%d",&len); 			


                        unsigned char *content = read_from_file(username,password,pFile,offset,len) ;
			if(content == NULL){
				printf("ERROR: Reading from file\n");
				continue;
			}
			else{
				printf("CONTENT:\n%s\n",content);
			}
                }
		
                else if(!strcmp(command,"write_to_file")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);
			printf("position to write to: ");
			int offset ; scanf("%d",&offset); 
			printf("Content to write:\n "); 
			char content[8192] ; 
			int i = 0 ; 
			while(1){
				char ch = getchar(); 
				if(ch == EOF) break ; 
				content[i] = ch ; 
				++i ; 
			}			

                        operation_status = write_to_file(username,password,pFile,offset,content) ;
                }

                else if(!strcmp(command,"quit")){
                        printf("INFO: Got the quit command\n");
                        printf("Program terminating\n");
                        break;
                }
                else{
                        printf("ERROR: Unknown command %s\n",command);
                        printf("INFO: Ignoring command\n") ;
                }

                if(operation_status == ERROR)
                        printf("Operation %s failed\n",command) ;
        }
        return 0;
}
