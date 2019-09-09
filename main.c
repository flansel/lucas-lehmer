#include <stdbool.h>
#include <gmp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "lucas.h"

int main(int argc, char* argv[]){
	lucasSetup();
	return 0;
}

int checkPrimeFaster(int num){
	if(num == 0 || num == 1){
    	return -1;
	}
  double root = sqrt((double)num);
  root = (int) root;
  int i;
  for(i = 2; i<=root; i++){
  	if(num % i == 0){
    	return i;
  	}
  }
  return 0;
}


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
	bool lucasNum = findLucasLehmerNumber(exp, n);
	if(lucasNum){	
  		mpz_out_str(stdout,10,n);
		printf(" is  prime\n");
	}else{
		mpz_out_str(stdout,10,n);
		printf(" is definitly not prime\n");
	}
	return 0;
}

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
    printf("Found Lucas Number-->\n");
    mpz_out_str(stdout,10,n);
    printf("\n\n");
    if(mpz_cmp_ui(n,0) == 0){
    	return true;
    }else{
       	return false;
    }
    return 0;
}

void lucasSetup(){
	char exp [32];
    printf("Enter the power of the Mersenne Prime\n");
    scanf("%32s",exp);
    int expNum = atoi(exp);
    if(checkPrimeFaster(expNum) == 0){
    	lucasLehmer(expNum);
    }else{
        printf("Aborting --> exp not prime\n");
        mpz_t n;
        int flag;
        mpz_init(n);
        mpz_set_ui(n,0);
        flag = mpz_set_str(n,"2", 10);
        if(flag != 0){
        	printf("Failed\n");
            exit(0);
        }       
       	mpz_pow_ui(n,n,expNum);
        mpz_sub_ui(n,n,1);
        mpz_out_str(stdout,10,n);
        printf (" is definitly not prime \n");
   	}
}

