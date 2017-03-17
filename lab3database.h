#include "lab3message.h"

#define MAX_PASSWORD 128
#define TOTAL_ACCOUNTS 4

struct lab3database {
    unsigned char username[MAX_NAME];
    unsigned char password[MAX_PASSWORD];
};

struct lab3database database[TOTAL_ACCOUNTS] = {{"a", "1234"},{"b", "4321"},{"c", "5678"},{"d", "7890"}};
