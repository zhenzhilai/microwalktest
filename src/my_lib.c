#include <stdint.h>
#include <stdlib.h>

#include "my_lib.h"

#define NOINLINE __attribute__((noinline))

uint8_t lookup[256];



static int NOINLINE branch_leakage_util(uint8_t data)
{
    // Use primes and random calculation to keep the compiler from optimizing this function too much
    
    if(data < 79)
        return 7;
    
//    if(data < 119)
//        return data;
        
    return 19 * data + 23;
}



void init(void)
{
	srand(0);
	
	for(int i = 0; i < sizeof(lookup) / sizeof(lookup[0]); ++i)
		lookup[i] = (uint8_t)rand();
}

void lookup_leakage(uint8_t *input, int inputLength, uint8_t *output)
{
	// Empty and constant time
}






int branch_leakage(uint8_t *input, int inputLength)
{
	// Empty and constant time
    
    // add leakages
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
	return lookup[0] + inputLength;
//    return result;
}

int loop_leakage(uint8_t *input, int inputLength)
{
	// Empty and constant time
	return lookup[0] + inputLength;
}
