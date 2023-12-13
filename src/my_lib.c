#include <stdint.h>
#include <stdlib.h>

#include "my_lib.h"

//#include "kyber512/indcpa.h"
#include "kyber512/kem.h"
#include "kyber512/params.h"
//#include "randombytes.h"
//#include "kyber512/symmetric.h"
//#include "kyber512/verify.h"
#include <stddef.h>
#include <string.h>

//#include "kyber512/compiletest.h"


#define NOINLINE __attribute__((noinline))

uint8_t lookup[256];



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
    
        uint8_t pk[KYBER_PUBLICKEYBYTES];
        uint8_t sk[KYBER_SECRETKEYBYTES];
    
        PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(pk, sk);
    
    
    
    
    
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

