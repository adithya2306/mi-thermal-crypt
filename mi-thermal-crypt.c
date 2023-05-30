#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include "cmdline.h"

// taken from https://stackoverflow.com/a/24899425
/**
 * Encrypt or decrypt, depending on flag 'should_encrypt'
 */
void en_de_crypt(int should_encrypt, FILE *ifp, FILE *ofp, unsigned char *ckey, unsigned char *ivec) {

    const unsigned BUFSIZE=4096;
    unsigned char *read_buf = malloc(BUFSIZE);
    unsigned char *cipher_buf;
    unsigned blocksize;
    int out_len;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_CIPHER_CTX_init(ctx);
    EVP_CipherInit(ctx, EVP_aes_128_cbc(), ckey, ivec, should_encrypt);
    blocksize = EVP_CIPHER_CTX_block_size(ctx);
    cipher_buf = malloc(BUFSIZE + blocksize);

    while (1) {

        // Read in data in blocks until EOF. Update the ciphering with each read.

        int numRead = fread(read_buf, sizeof(unsigned char), BUFSIZE, ifp);
        EVP_CipherUpdate(ctx, cipher_buf, &out_len, read_buf, numRead);
        fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);
        if (numRead < BUFSIZE) { // EOF
            break;
        }
    }

    // Now cipher the final block and write it out.

    EVP_CipherFinal(ctx, cipher_buf, &out_len);
    fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);

    // Free memory

    EVP_CIPHER_CTX_free(ctx);
    free(cipher_buf);
    free(read_buf);
}

int main(int argc, char *argv[]) {

    struct gengetopt_args_info ai;
    unsigned char ckey[] = "thermalopenssl.h";
    unsigned char ivec[] = "thermalopenssl.h";
    FILE *fIN, *fOUT;

    if (cmdline_parser(argc, argv, &ai) != 0) {
        exit(1);
    }

    fIN = fopen(ai.infile_arg, "rb");
    fOUT = fopen(ai.outfile_arg, "wb");

    en_de_crypt(ai.encrypt_flag, fIN, fOUT, ckey, ivec);

    return 0;
}
