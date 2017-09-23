#include "SDES.h"

static int encrypt_flag;
static int decrypt_flag;
static int crack_flag;
static int triple_flag;
static int out_flag;
static int help_flag;
static int verbose_flag;

void main(int argc, char *argv[])
{
    int c = 0;

    static struct option long_options[] =
    {
        {"encrypt", required_argument, &encrypt_flag, 'e'},
        {"decrypt", required_argument, &decrypt_flag, 'd'},
        {"crack",   required_argument, &crack_flag,   'c'},
        {"out",     required_argument, &out_flag,     'o'},
        {"triple",  no_argument,       &triple_flag,  't'},
        {"help",    no_argument,       &help_flag,    'h'},
        {"verbose", no_argument,       &verbose_flag, 'v'},
        {0,         0,                 0,               0}
    };

    while((c = getopt_long(argc, argv, "e:d:c:o:thv", long_options, NULL)) != -1)
    {
        switch(c)
        {
        case 'e':
            encrypt_flag = 1;
            break;
        case 'd':
            decrypt_flag = 1;
            break;
        case 'c':
            crack_flag = 1;
            break;
        case 'o':
            out_flag = 1;
            break;
        case 'ot':
            triple_flag = 1;
            break;
        case 'h':
            help_flag = 1;
            break;
        case 'v':
            verbose_flag = 1;
            break;
        default:
            abort();
        }
    }

    if(help_flag)
    {
        printf("Help!");
        exit(0);
    }

    if(!(encrypt_flag || decrypt_flag || crack_flag))
    {
        printf("Choose, encrypt, decrypt or crack.");
        exit(0);
    }

    if(encrypt_flag && decrypt_flag || encrypt_flag && crack_flag || decrypt_flag && crack_flag)
    {
        printf("You can only do one at a time");
        exit(0);
    }

    if(encrypt_flag)
    {
        if(verbose_flag)
        {
            if(triple_flag)
            {
                TripleSDES_Encrypt(uint8_t *byte)
            }
            else
            {
                SDES_Encrypt(uint8_t *byte)
            }
        }
        else
        {
            if(triple_flag)
            {
                TripleSDES_Encrypt(uint8_t *byte)
            }
            else
            {
                SDES_Encrypt(uint8_t *byte)
            }
        }
    }
    else if(decrypt_flag)
    {
        if(verbose_flag)
        {
            if(triple_flag)
            {
                TripleSDES_Decrypt(uint8_t *byte)
            }
            else
            {
                SDES_Decrypt(uint8_t *byte)
            }
        }
        else
        {
            if(triple_flag)
            {
                TripleSDES_Decrypt(uint8_t *byte)
            }
            else
            {
                SDES_Decrypt(uint8_t *byte)
            }
        }
    }
    else if(crack_flag)
    {
        if(verbose_flag)
        {
            if(triple_flag)
            {
                TripleSDES_Crack(uint8_t *byte)
            }
            else
            {
                SDES_Crack(uint8_t *byte)
            }
        }
        else
        {
            if(triple_flag)
            {
                TripleSDES_Crack(uint8_t *byte)
            }
            else
            {
                SDES_Crack(uint8_t *byte)
            }
        }
    }

    exit(0);
}

uint8_t SDES_Decrypt(uint8_t *byte)
{
    
}

uint8_t SDES_Encrypt(uint8_t *byte)
{

}

uint8_t SDES_Crack(uint8_t *byte)
{
}

uint8_t TripleSDES_Decrypt(uint8_t *byte)
{
}

uint8_t TripleSDES_Encrypt(uint8_t *byte)
{
}

uint8_t TripleSDES_Crack(uint8_t *byte)
{
}