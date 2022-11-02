#include <stdio.h>
#include <stdlib.h>

char* caesar(char* in, int key, int encrypt) {
    if (in == NULL)
        return NULL;

    const int len = strlen(in);
    if (len == 0)
        return NULL;
    char* out = (char*) malloc(sizeof(char) + len);
    for (int i = 0; i < len; ++i) {
        out[i] = *(in + i) + ((encrypt) ? (char) key : (char) -key);
    }
    out[len] = 0;
    return out;
}

char* shuffle(char* in, int key, int encrypt) {
    int l = strlen(in);
    if (l == 0) return NULL;
    const int len = key * (1 + ((l - 1) / key));

    char* out = (char*) malloc(sizeof(char) * len);
    if (encrypt == 0) key = len / key;
    int idx = 0;
    for (int i = 0; i < key; ++i) {
        for (int j = i; j < len; j += key) {
            out[idx++] = (*(in + j)) ? *(in + j) : (char) 'x';
        }
    }
    out[len] = '\0';
    return out;
}

int main() {
    char* msg = "thizizazecretmezzage";
    printf("%s \n", msg);
    char* encrypt = caesar(msg, 6, 1);
    printf("%s \n", encrypt);
    char* decrypt = caesar(encrypt, 6, 0);
    printf("%s \n", decrypt);

    char* s_encrypt = shuffle(decrypt, 6, 1);
    printf("%s \n", s_encrypt);
    char* s_decrypt = shuffle(s_encrypt, 6, 0);
    printf("%s \n", s_decrypt);
}
