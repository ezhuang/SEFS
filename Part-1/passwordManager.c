// # include "config.h"
# include "util.h"
# include "pManagement.h"


int main(){
        printf("Available commands:\n(1) register_user\n(2) delete_user\n(3) is_user_valid\n(4) match_user\n(5) change_user_password\n(6) quit\n\n\n");

        unsigned char command[1024];
        int operation_status ;
        while(1){
                printf("enter a command: ");
                scanf("%s",command) ;
                // printf("\n") ;
                operation_status = OKAY ;
                if(!strcmp(command,"register_user")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("password file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = register_user(username,password,pFile) ;
                }
                else if(!strcmp(command,"delete_user")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;

                        printf("password: ");
                        unsigned char password[1024];
                        scanf("%s",password) ;

                        printf("password file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = delete_user(username,password, pFile) ;

                }
                else if(!strcmp(command,"is_user_valid")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = is_user_valid(username,pFile) ;

                }
                else if(!strcmp(command,"match_user")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("password file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = match_user(username,password,pFile) ;

                }
                else if(!strcmp(command,"change_user_password")){
                        printf("username: ");
                        unsigned char username[1024];
                        scanf("%s",username) ;
                        printf("current password: ");
                        unsigned char password[1024] ;
                        scanf("%s",password) ;
                        printf("new password: ");
                        unsigned char npassword[1024] ;
                        scanf("%s",npassword) ;

                        printf("password file name: ");
                        unsigned char pFile[1024] ;
                        scanf("%s",pFile);

                        operation_status = change_user_password(username,password,npassword, pFile) ;

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
