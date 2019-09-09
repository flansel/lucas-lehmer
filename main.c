#include <stdbool.h>
//all of the mpz stuff comes from gmp.h 
#include <gmp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "lucas.h"


/* *
 * This program is design to use the Lucas-Lehmer Primality test
 * to determine the primality of mersenne primes( primes of the order 2^p -1
 * this allows for the user input of an exponent and can calculate numbers much larger than
 * the standard C types allow for by using the gmp
 *
 *
 * As far as I know this only works on linux and using gmp.h
 * It may work on minGW or cygwin but I am unsure if gmp is supported 
 * */

int main(int argc, char* argv[]){
	lucasSetup();
	return 0;
}

/* *
 * this is a simple up to rt(n) prime check for the exponents of the mersenne 
 * this is because a mersenne cannot be prime unless the exponent is prime hence the
 * fomula 2^p -1 for mersennes
 * */
int checkPrimeFaster(int num){
	if(num == 0 || num == 1){
    	return 1;
	}
  double root = sqrt((double)num);
  root = (int) root;
  int i;
  for(i = 2; i<=root; i++){
  	if(num % i == 0){
    	return 1;
  	}
  }
  return 0;
}

/* *
 * takes in the exp and creates the mpz "integer" to send into the LL sequence
 * after this is reprompts the user to get another exponenent
 * */
bool lucasLehmer(int exp){
	printf("Starting Lucas Lehmer\n");
	mpz_t n;
	int flag;
	mpz_init(n);
	mpz_set_ui(n,0);
	flag = mpz_set_str(n,"2", 10);
	if(flag != 0){
		printf("Failed\n");
		exit(0);
	}
	mpz_pow_ui(n,n,exp);
	mpz_sub_ui(n,n,1);
	printf ("Mersenne =");
  	mpz_out_str(stdout,10,n);
  	printf ("\n");
	size_t size = mpz_sizeinbase(n,10);
	clock_t start, end;
	double cpu_time;
	start = clock();
	bool lucasNum = findLucasLehmerNumber(exp, n);
	if(lucasNum){	
		printf("2^%d is Prime\n",exp);
		printf("The length of this prime is ");
		printf("%zu",size);
		printf(" digits!\n");
	}else{
		mpz_out_str(stdout,10,n);
		printf(" is definitly not prime\n");
	}
	end = clock();
	cpu_time  = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("that calculation took %f seconds\n", cpu_time);
	return 0;
}
/* *
 *Takes in the exp(the index of the lucas number in this case) and the full number as the modulus
 *Goes through the sequence up until the index of the exp -2 and returns the index mod the full n
 *umber. We Mod throught the whole sequence, to keep at n bits where n is the length of mod
 * */
bool findLucasLehmerNumber(int exp, mpz_t mod){
	printf("Starting Lucas-Lehmer Sequence\n");
    mpz_t n;
    int flag;
    mpz_init(n);
    mpz_set_ui(n,0);
    flag = mpz_set_str(n,"4",10);
    if(flag != 0){
    	printf("Lucas-Lehmer Sequence creation FAILED\n");
        exit(0);
    }
    int i;
    for(i = 0;i<exp-2;i++){         
    	mpz_pow_ui(n,n,2);
        mpz_sub_ui(n,n,2);
        mpz_mod(n,n,mod);
    }       
    printf("Found Lucas Number-->");
    mpz_out_str(stdout,10,n);
    printf("\n\n");
    if(mpz_cmp_ui(n,0) == 0)
    	return true;
    return false;
}
/* *
 * Gets the exponent from the user and sends it to be proccessed
 * When the processing is done it prints whether or not the number is prime
 * based on the lucas number
 * */
void lucasSetup(){
	char exp [32];
    printf("Enter the power of the Mersenne Prime\n");
    scanf("%32s",exp);
    int expNum = atoi(exp);
    if(checkPrimeFaster(expNum) == 0){
    	lucasLehmer(expNum);
    }else{
        printf("Aborting --> exp not prime\n");
       	printf("2^%d-1",expNum);
	   	printf (" is definitly not prime \n");
   	}
	printf("Choose another exp, [y/n]");
	char checkAgian[32];
	scanf("%31s",checkAgian);
	if(*checkAgian == 'y' || *checkAgian == 'Y'){
		lucasSetup();
	}
}


