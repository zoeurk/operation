#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"

int main(int argc, char **argv){
	int ret;
	unsigned long int count = 0;
	char *r, pi[51], *pi_, *temp, *temp_, *endptr;
	long double x;
	memset(pi, 0, 51);
	sprintf(pi,"%.48Lf", (long double)M_PI);
	if(argc != 3){
		fprintf(stderr, "usage:\n\t%s num1 num2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	ret = equal(argv[1],argv[2]);
	switch(ret){
		case 0:
			printf("%s == %s\n", argv[1], argv[2]);
			break;
		case 1:
			printf("%s > %s\n", argv[1], argv[2]);
			break;
		case -1:
			printf("%s < %s\n", argv[1], argv[2]);
			break;
	}
	r = addition(argv[1], argv[2]);
	if(r){
		printf("addition:%s\n", (char *)r);
		free(r);
	}
	r = soustraction(argv[1], argv[2]);
	if(r){
		printf("soustraction:%s\n", (char *)r);
		free(r);
	}
	r = multiplication(argv[1], argv[2]);
	if(r){
		printf("multiplication:%s\n", (char *)r);
		free(r);
	}
	r = division(argv[1], argv[2], 8);
	if(r){
		printf("division:%s\n", (char *)r);
		free(r);
	}
	printf("ARGV[1] = %s\n", argv[1]);
	temp = argv[1];
	pi_ = multiplication(pi, "2");
	if(equal(temp, "0") >= 0){
		while(equal(pi_, temp) < 0){
			temp_ = soustraction(temp, pi_);
			if(temp == argv[1])
				temp = temp_;
				else{
				free(temp);
				temp = temp_;
			}
			count++;
		}
	}else{
		while(equal(pi_, temp) > 0){
			temp_ = addition(temp, pi_);
			if(temp == argv[1])
				temp = temp_;
				else{
				free(temp);
				temp = temp_;
			}
			count++;
		}
	}
	printf("Count:\t\t\t%lu\n", count);
	x = strtold(temp, &endptr);
	printf("cosinus arbitraire:\t%.48Lf\n", cosl(x));
	x = strtold(argv[1], &endptr);
	printf("cosinus:\t\t%.48Lf\n", cosl(x));
	if(temp != argv[1])
		free(temp);
	printf("ARGV[2] = %s\n", argv[2]);
	temp = argv[2];
	count = 0;
	if(equal(temp, "0") >= 0){
		while(equal(pi_, temp) < 0){
			temp_ = soustraction(temp, pi_);
			if(temp == argv[2])
				temp = temp_;
			else{
				free(temp);
				temp = temp_;
			}
			count++;
		}
	}else{
		while(equal(pi_, temp) > 0){
			temp_ = addition(temp, pi_);
			if(temp == argv[2])
				temp = temp_;
			else{
				free(temp);
				temp = temp_;
			}
			count++;
		}
	}
	printf("Count:\t\t\t%lu\n", count);
	x = strtold(temp, &endptr);
	printf("cosinus arbitraire:\t%.48Lf\n", cosl(x));
	x = strtold(argv[2], &endptr);
	printf("cosinus:\t\t%.48Lf\n", cosl(x));
	if(temp != argv[2])
		free(temp);
	free(pi_);
	return 0;
}

