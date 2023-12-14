#include <stdint.h>
#include <stdlib.h>

// #include "my_lib.h"

//#include "kyber512/indcpa.h"
// #include "kyber512/kem.h"
// #include "kyber512/params.h"
//#include "randombytes.h"
//#include "kyber512/symmetric.h"
//#include "kyber512/verify.h"

//#include "kyber512/compiletest.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "api.h"
#include "randombytes.h"

#define NTESTS 1


#define NOINLINE __attribute__((noinline))

uint8_t lookup[256];



#define PASTER(x, y) x##_##y
#define EVALUATOR(x, y) PASTER(x, y)
#define NAMESPACE(fun) EVALUATOR(PQCLEAN_NAMESPACE, fun)

#define CRYPTO_BYTES           NAMESPACE(CRYPTO_BYTES)
#define CRYPTO_PUBLICKEYBYTES  NAMESPACE(CRYPTO_PUBLICKEYBYTES)
#define CRYPTO_SECRETKEYBYTES  NAMESPACE(CRYPTO_SECRETKEYBYTES)
#define CRYPTO_CIPHERTEXTBYTES NAMESPACE(CRYPTO_CIPHERTEXTBYTES)

#define crypto_kem_keypair NAMESPACE(crypto_kem_keypair)
#define crypto_kem_enc NAMESPACE(crypto_kem_enc)
#define crypto_kem_dec NAMESPACE(crypto_kem_dec)



static int NOINLINE branch_leakage_util(uint8_t data)
{
    // Use primes and random calculation to keep the compiler from optimizing this function too much
    
    if(data < 79)
        return 7;
    
    if(data < 119)
        return data;
        
    return 19 * data + 23;
}



void init(void)
{
	srand(0);
	
	for(int i = 0; i < sizeof(lookup) / sizeof(lookup[0]); ++i)
		lookup[i] = (uint8_t)rand();
}



int branch_leakage(uint8_t *input, int inputLength)
{
//    int testint;
//    testint = test_fun();
    
        // uint8_t pk[KYBER_PUBLICKEYBYTES];
        // uint8_t sk[KYBER_SECRETKEYBYTES];
    
        // PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(pk, sk);
        // crypto_kem_keypair(pk, sk);
    uint8_t key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sendb[CRYPTO_CIPHERTEXTBYTES];
    uint8_t sk_a[CRYPTO_SECRETKEYBYTES];

    crypto_kem_keypair(pk, sk_a);
    
    
    
    
    // Empty and constant time
    
    // add leakages
    // volatile int result = 0;
	int result = 0;
        
        for(int i = 0; i < inputLength; ++i)
            result += branch_leakage_util(input[i]);
    
    
//    no leakage reported by follows
//    int result = 0;
//
//    for(int i = 0; i < inputLength; ++i){
//        if (input[i] <= 80)
//            break;
//    }
//	return lookup[0] + inputLength;
    return result;
}

// int main(void) {
//     uint8_t input[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};


//     int res = branch_leakage(input, 16);
//     printf("%d\n", res);
//     // uint8_t key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
//     // uint8_t pk[CRYPTO_PUBLICKEYBYTES];
//     // uint8_t sendb[CRYPTO_CIPHERTEXTBYTES];
//     // uint8_t sk_a[CRYPTO_SECRETKEYBYTES];

//     // crypto_kem_keypair(pk, sk_a);
//     // printf("success2\n");

//     // int i, j;
//     // for (i = 0; i < NTESTS; i++) {
//     //     // Key-pair generation
//     //     crypto_kem_keypair(pk, sk_a);

//     //     printbytes(pk, CRYPTO_PUBLICKEYBYTES);
//     //     printbytes(sk_a, CRYPTO_SECRETKEYBYTES);

//     //     // Encapsulation
//     //     crypto_kem_enc(sendb, key_b, pk);

//     //     printbytes(sendb, CRYPTO_CIPHERTEXTBYTES);
//     //     printbytes(key_b, CRYPTO_BYTES);

//     //     // Decapsulation
//     //     crypto_kem_dec(key_a, sendb, sk_a);
//     //     printbytes(key_a, CRYPTO_BYTES);

//     //     for (j = 0; j < CRYPTO_BYTES; j++) {
//     //         if (key_a[j] != key_b[j]) {
//     //             printf("ERROR\n");
//     //             return -1;
//     //         }
//     //     }
//     // }
//     return 0;
// }
