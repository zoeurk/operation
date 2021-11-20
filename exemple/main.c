#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
void cosinus(char *arg){
	int ret;
	char pi[51], npi[52],*pi_, *npi_ ,*temp, *temp_, *temp__;
	long double x;
	memset(npi, 0, 51);
	sprintf(npi,"-%.48Lf", (long double)M_PI);
	memset(pi, 0, 51);
	sprintf(pi,"%.48Lf", (long double)M_PI);
	pi_ = multiplication(pi, "2");
	npi_ = multiplication(npi, "-2");
	if(equal(arg, pi_) > 0){
		temp = division(arg, pi_, 56);
		ret = 0;
		if((temp_ = strchr(temp, '.')) != NULL){
			*temp_ = 0;
			ret = 1;
		}else	temp = temp;
		temp__ = multiplication(temp, pi_);
		if(ret == 1){
			*temp_ = '.';
			ret = 0;
		}
		temp_ = soustraction(arg, temp__);
		x = strtold(temp_, NULL);
		printf("Cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(x));
		free(temp);
		free(temp_);
		free(temp__);
	}else{
		if(equal(arg, npi_) < 0){
			temp = division(arg, npi_, 56);
			ret = 0;
			if((temp_ = strchr(temp, '.')) != NULL){
				*temp_ = 0;
				ret = 1;
			}else	temp = temp;
			temp__ = multiplication(temp, pi_);
				if(ret == 1){
				*temp_ = '.';
				ret = 0;
			}
			temp_ = soustraction(arg, temp__);
			x = strtold(temp_, NULL);
			printf("Cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(x));
			free(temp);
			free(temp_);
			free(temp__);
		}
		//x = strtold(arg, NULL);
		//printf("Cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(x));
	}
	x = strtold(arg, NULL);
	printf("Cosinus  de \'%s\': %.56Lf\n", arg, cosl(x));
	free(pi_);
	free(npi_);
}
void racine_carree(char *i){
	//printf("Racine carree arbitraire de \'%s\': %s\n", i, pk);
	printf("Racine carree de \'%s\': %.56Lf\n", i, powl(strtold(i, NULL),0.5));
	//free(pk);
}
int main(int argc, char **argv){
	int ret;
	char *r;
	if(argc != 4){
		fprintf(stderr, "usage:\n\t%s num1 num2 virgule\n", argv[0]);
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
	r = division(argv[1], argv[2], atoi(argv[3]));
	if(r){
		printf("division:%s\n", (char *)r);
		free(r);
	}
	r = modulo(argv[1], argv[2]);
	if(r){
		printf("modulo:%s\n", (char *)r);
		free(r);
	}
	printf("++++++++++++++++++\n");
	cosinus(argv[1]);
	cosinus(argv[2]);
	printf("++++++++++++++++++\n");
	racine_carree(argv[1]);
	racine_carree(argv[2]);
	return 0;
}
