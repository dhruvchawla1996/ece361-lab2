#define MAX_NAME 128
#define MAX_DATA 1024

struct lab3message {
    unsigned int type;
    unsigned int size;
    unsigned char source[MAX_NAME];
    unsigned char data[MAX_DATA];
}
