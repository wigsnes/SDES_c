#include "SDES.h"

static int encrypt_flag;
static int decrypt_flag;
static int crack_flag;
static int triple_flag;
static int key_flag;
static int out_flag;
static int help_flag;
static int verbose_flag;

int main(int argc, char *argv[])
{
    int c = 0;
    uint8_t *byte = 0;
    uint16_t key = 0;

    static struct option long_options[] =
    {
        {"encrypt", required_argument, &encrypt_flag, 'e'},
        {"decrypt", required_argument, &decrypt_flag, 'd'},
        {"crack",   required_argument, &crack_flag,   'c'},
        {"key",     optional_argument, &key_flag,     'k'},
        {"out",     required_argument, &out_flag,     'o'},
        {"triple",  no_argument,       &triple_flag,  't'},
        {"help",    no_argument,       &help_flag,    'h'},
        {"verbose", no_argument,       &verbose_flag, 'v'},
        {0,         0,                 0,               0}
    };

    while((c = getopt_long(argc, argv, "e:d:c:ko:thv", long_options, NULL)) != -1)
    {
        switch(c)
        {
        case 'e':
            encrypt_flag = 1;
            byte = optarg;
            break;
        case 'd':
            decrypt_flag = 1;
            break;
        case 'c':
            crack_flag = 1;
            break;
        case 'k':
            key_flag = 1;
            uint8_t *byte = optarg;
            //printf("key %c", byte[0]);
            if(optarg != NULL)
                printf("key %c", *optarg);
                //key = atoi(optarg);
                //printf("key %c", *optarg);
            break;
        case 'o':
            out_flag = 1;
            break;
        case 't':
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

    test(*byte, key);

    if(help_flag)
    {
        printf("Help!");
        exit(0);
    }

    if(!(encrypt_flag || decrypt_flag || crack_flag))
    {
        printf("Choose, encrypt, decrypt or crack.\n");
        exit(0);
    }

    if(encrypt_flag && decrypt_flag || encrypt_flag && crack_flag || decrypt_flag && crack_flag)
    {
        printf("You can only do one at a time.\n");
        exit(0);
    }

    if(triple_flag)
    {
        if(encrypt_flag)
        {
            TripleSDES_Encrypt(byte);
        }
        else if(decrypt_flag)
        {
            TripleSDES_Decrypt(byte);
        }
        else if(crack_flag)
        {
            TripleSDES_Crack(byte);
        }
    }
    else
    {
        if(encrypt_flag)
        {
            SDES_Encrypt(byte, key);
        }
        else if(decrypt_flag)
        {
            SDES_Decrypt(byte);
        }
        else if(crack_flag)
        {
            SDES_Crack(byte);
        }
    }
    exit(0);
}

uint8_t SDES_Decrypt(uint8_t *byte)
{

}

uint8_t SDES_Encrypt(uint8_t *byte, uint16_t key)
{
    uint8_t k1 = 0, k2 = 0, d = 0;
    while(*byte != '\0')
    {
        k1 = LS_1(P10(key));
        k2 = P8(LS_2(k1));
        k1 = P8(k1);
        d = IP_1(f_k(SW(f_k(IP(*byte), k2)), k1));
        printf("%d ", d);
        byte++;
    }
    printf("\n");
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

uint8_t LS_1(uint8_t key)
{
    return (((key & 0x3E0) << 1) | key >> 4) & 0x3E0 | (((key << 1) | (key & 0x1F) >> 4) & 0x1F);
}

uint8_t LS_2(uint8_t key)
{
    return (((key & 0x3E0) << 2) | key >> 3) & 0x3E0 | (((key << 2) | (key & 0x1F) >> 3) & 0x1F);
}

uint8_t P4(uint8_t S)
{
    uint8_t perm[4] = {2,4,3,1};
    return permutate(S, 4, 4, perm);
}

uint8_t P8(uint8_t key)
{
    uint8_t perm[8] = {6,3,7,4,8,5,10,9};
    return permutate(key, 10, 8, perm);
}

uint16_t P10(uint16_t key)
{
    uint8_t perm[10] = {3,5,2,7,4,10,1,9,8,6};
    return permutate(key, 10, 10, perm);
}

uint8_t IP(uint8_t right)
{
    uint8_t perm[8] = {2,6,3,1,4,8,5,7};
    return permutate(right, 8, 8, perm);
}

uint8_t IP_1(uint8_t right)
{
    uint8_t perm[8] = {4,1,3,5,7,2,8,6};
    return permutate(right, 8, 8, perm);
}

uint8_t f(uint8_t right, uint8_t key)
{
    uint8_t data, valS1, valS2;
    data = EP(right) ^ key;
    valS1 = (data & 0xF0) >> 4;
    valS2 = (data & 0x0F);
    return P4(S1(valS1) << 2 | S2(valS2));
}

uint8_t f_k(uint8_t byte, uint8_t key)
{
    uint8_t left = (byte & 0xF0) >> 4;
    uint8_t right = byte & 0x0F;
    return ((f(right, key) ^ left) << 4 | right);
}

uint8_t SW(uint8_t right)
{
    uint8_t msb = ((right & 0xF0) >> 4);
    uint8_t lsb = ((right & 0x0F) << 4);
    return (lsb | msb);
}

uint8_t EP(uint8_t right)
{
    uint8_t perm[] = {4,1,2,3,2,3,4,1};
    permutate(right, 4, 8, perm);
}

uint8_t S1(uint8_t msb)
{
    uint8_t S1_Box[4][4] = {
        {1,0,3,2},
        {3,2,1,0},
        {0,2,1,3},
        {3,1,3,2}
    };
    return S1_Box[(bit(msb, 3) << 1) + bit(msb, 0)][(bit(msb, 2) << 1) + bit(msb, 1)];
}

uint8_t S2(uint8_t lsb)
{
    uint8_t S2_Box[4][4] = {
        {0,1,2,3},
        {2,0,1,3},
        {3,0,1,0},
        {2,1,0,3}
    };
    return S2_Box[(bit(lsb, 3) << 1) + bit(lsb, 0)][(bit(lsb, 2) << 1) + bit(lsb, 1)];
}

uint8_t bit(uint16_t byte, uint8_t n)
{
    if((byte & (1 << n)) != 0)
        return 1;
    return 0;
}

uint16_t permutate(uint16_t byte, uint8_t length, uint8_t indexLength, uint8_t *index)
{
    uint16_t value = 0;
    for(int i = 0;i < indexLength;i++)
    {
        value |= (bit(byte, length - *index) << (indexLength - (i + 1)));
        index++;
    }
    return value;
}

void test(uint8_t byte, uint8_t key)
{
    //printf("LS_2: %d = 2\n", LS_2(0x10));
    //printf("LS_1: %d = 1\n", LS_1(0x10));
    //printf("P4: %d = 3\n", P4(0x0A));
    //printf("P8: %d = 164\n", P8(0x38));
    //printf("P10: %d = 524\n", P10(0x282));
    //printf("IP: %d = 184\n", IP(0xF0));
    //printf("IP_1: %d = 27\n", IP_1(0x0F));
    //printf("SW: %d = 240\n", SW(0x0F));
    //printf("EP: %d = 195\n", EP(0x09));
    //printf("S1: %d = 2\n", S1(0x0F));
    //printf("S2: %d = 3\n", S2(0x0F));
    //int8_t perm[] = {8,7,6,5,4,3,2,1};
    //printf("permutate: %d = 15\n", permutate(0xF0, 8, 8, perm));
}