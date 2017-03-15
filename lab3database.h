#include "lab3message.h"

#define MAX_PASSWORD 128
#define TOTAL_ACCOUNTS 4

struct lab3database {
    unsigned char username[MAX_NAME];
    unsigned char password[MAX_PASSWORD];
}

struct lab3database database[TOTAL_ACCOUNTS];

database[0].username = "a";
database[0].password = "1234";

database[1].username = "b";
database[1].password = "4567";

database[2].username = "c";
database[2].password = "7890";

database[3].username = "d";
database[3].password = "5678";
