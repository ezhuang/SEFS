
#include <stdio.h>
#include <stdlib.h>

# include "config.h"


# define OKAY   1
# define ERROR -1




int file_hex_hmac(unsigned char *file, unsigned char *key, unsigned char* result){
	//usage: 
	//unsigned char result[1024];
    //file_hex_hmac("2000undersea","1234567",result);
    


    int state = OKAY;
    FILE *f = fopen(file, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *data = malloc(fsize + 1);
	fread(data, fsize, 1, f);
	fclose(f);

	data[fsize] = 0;
 
    unsigned char* digest;
    
    
    digest = HMAC(EVP_sha256(), key, strlen(key), (unsigned char*)data, strlen(data), NULL, NULL);    
 
    
 	state = byte_array_to_hex_array(digest, HMAC_SIZE,  result);
    printf("HMAC digest: %s\n", result);
 	free(data);
    return state;


} 