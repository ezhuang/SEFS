#ifndef _CONFIG_H_   /* Include guard */
#define _CONFIG_H_

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <math.h>
# include <openssl/hmac.h>
# include <openssl/x509.h>
# include <openssl/evp.h>
# include <openssl/rand.h>
# include <string.h>
# include <unistd.h>
# include <assert.h>

/*MAXIMUM SIZE OF DIFFERENT PARAMETERS*/
#define SALT_SIZE 32
#define HMAC_SIZE 32
#define UNAME_SIZE 32
#define PASSWORD_SIZE 32
#define MASTERKEY_SIZE 16
#define MASTERIV_SIZE  32


#endif
