#ifndef _UTIL_H_   /* Include guard */
#define _UTIL_H_

# include "config.h"

/*Takes as input: an allocated unsigned char * and number of
random bytes to generate and outputs: an status/error/return code
side effect: ptr has num_bytes number of random bytes ....
*/
int getRandBytes(unsigned char * ptr, unsigned num_bytes){
        int ret = RAND_bytes(ptr, num_bytes) ;
        if(ret != 1) return -1 ;
        return ret ;
}


/*
The following function takes as input: a file name in the file_name char *
and checks to see whether the file already exists in the current directory.
Return values:
0 ===> File exists
1 ===> File does not exist
*/
int isFilePresent(unsigned char * file_name){
        if(access(file_name,F_OK) != -1)
                return 0 ;
        else
                return -1 ;
}

/*The following function takes as input: a file name in the file_name char *
and tries to create the file.
Return values:
0 ===> File created successfully ...
1 ===> File could not be created ...
*/
int createFile(unsigned char *file_name){
        FILE * fp = fopen(file_name,"a+") ;
        int ret_code = 0 ;
        if(!fp){
                ret_code = -1 ;
        }
        else{
                fclose(fp) ;
        }
        return ret_code ;
}


unsigned char hex_digit_to_decimal(unsigned char ch){
        if(ch >='0' && ch <='9'){
                return (unsigned) (ch-'0') ;
        }
        else if(ch>='A' && ch<='F'){
                return (unsigned)(ch-'A'+10);
        }
        else
        {
                printf("ERROR: HEX-TO-DECIMAL: UNKNOWN DIGIT %c\n",ch);
                assert(0);
                return 0;
        }
}


//It is required for both hex_string and  byte_array to be allocated with proper space ...
int hex_array_to_byte_array(unsigned char * hex_string, unsigned char * byte_array)
{
        if(!byte_array){
                printf("ERROR: Byte Array Not allocated ..\n");
                return -1 ;
        }
        int len = strlen(hex_string);
        if(len%2 !=0){
                printf("ERROR: BAD HEX STRING: ODD LENGTH\n");
                return -1;
        }
        // byte_array = (unsigned char *) malloc(sizeof(unsigned char) * (len/2) + 1) ;
        int i ;
        for(i=0;i<(len-1);i+=2){
                byte_array[i/2] = (unsigned char)((hex_digit_to_decimal(hex_string[i]) << 4) | hex_digit_to_decimal(hex_string[i+1])) ;

        }
        return (len/2);
}

//It is required that both byte_array and hex_string are already allocated with proper space ...
int byte_array_to_hex_array(unsigned char * byte_array, unsigned int num_bytes,  unsigned char* hex_string)
{
        if(!hex_string){
                printf("ERROR: Hex String not allocated ....");
                return -1 ;
        }
        int i , j = 0;
        unsigned char buff[1024];
        for(i=0;i<num_bytes;++i){
                sprintf(buff,"%02X",byte_array[i]);
                //printf("BUFF: %c-%c\n",buff[0],buff[1]);
                hex_string[2*i]=buff[0];
                hex_string[2*i+1]=buff[1];
        }
        hex_string[2*i] = (unsigned char)0 ;
}

#endif 
