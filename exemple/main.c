#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
int main(int argc, char **argv){
	int ret;
	char *r, pi[51], *pi_, *temp, *temp_, *temp__;
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
	r = division(argv[1], argv[2], 56);
	if(r){
		printf("division:%s\n", (char *)r);
		free(r);
	}
	//printf("++++++++++++++++++\n");
	x = strtold(argv[1], NULL);
	//printf("%.48Lf\n", (long double)2*M_PI);
	//printf("%.48Lf\n%.48Lf\n%.48Lf\n", x-2*M_PI, cosl(x-2*M_PI), cosl(x));
	pi_ = multiplication(pi, "2");
	if(equal(argv[1], pi_) > 0){
		temp = division(argv[1], pi_, 48);
		temp_ = strchr(temp, '.');
		*temp_ = 0;
		temp__ = multiplication(temp, pi_);
		*temp_ = '.';
		temp_ = soustraction(argv[1], temp__);
		x = strtold(temp_, NULL);
		printf("Cosinus arbitraire de \'%s\': %.48Lf\n", argv[1], cosl(x));
		free(temp);
		free(temp_);
		free(temp__);
	}else{
		x = strtold(argv[1], NULL);
		printf("Cosinus arbitraire de \'%s\': %.48Lf\n", argv[1], cosl(x));
	}
	x = strtold(argv[1], NULL);
	printf("Cosinus  de \'%s\': %.48Lf\n", argv[1], cosl(x));
	if(equal(argv[2], pi_) > 0){
		temp = division(argv[2], pi_, 48);
		temp_ = strchr(temp, '.');
		*temp_ = 0;
		temp__ = multiplication(temp, pi_);
		*temp_ = '.';
		temp_ = soustraction(argv[1], temp__);
		x = strtold(temp_, NULL);
		printf("Cosinus arbitraire de \'%s\': %.48Lf\n", argv[2], cosl(x));
		free(temp);
		free(temp_);
		free(temp__);
	}else{
		x = strtold(argv[2], NULL);
		printf("Cosinus arbitraire de \'%s\': %.48Lf\n", argv[2], cosl(x));
	}
	x = strtold(argv[2], NULL);
	printf("Cosinus  de \'%s\': %.48Lf\n", argv[2], cosl(x));
	free(pi_);
	return 0;
}
