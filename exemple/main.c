#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
int main(int argc, char **argv){
	int ret;
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
	r = division(argv[1], argv[2], 56);
	if(r){
		printf("division:%s\n", (char *)r);
		free(r);
	}
	pi_ = multiplication(pi, "2");
	//printf("%s, %s\n", pi_, pi);
	//printf("%s\n", argv[1]);
	//exit(0);
	if((temp = division(argv[1], pi_, 48)) == NULL){
		temp = argv[1];
		x = strtold(temp, &endptr);
	}else{
		//printf("%s\n", temp);
		if((temp_ = strchr(temp, '.')) != NULL){
			//printf("%s\n", temp);
			temp_--;
			*temp_ = '0';
			endptr = multiplication(pi_,temp_);
			temp = endptr;
			x = strtold(temp, &endptr);
		}else{
			free(temp);
			temp = argv[1];
			x = 0;
		}
	}
	if(temp != argv[1])
		free(temp);
	endptr = NULL;
	if(endptr && strlen(endptr)>0)
		fprintf(stderr, "Erreur: <%s>\n", endptr);
	printf("cosinus arbitraire de \'%s\':\t%.48Lf\n", argv[1],cosl(x));
	endptr = NULL;
	x = strtold(argv[1], &endptr);
	if(endptr && strlen(endptr)>0)
		fprintf(stderr, "Erreur: <%s>\n", endptr);
	printf("cosinus de \'%s\':", argv[1]);
	if(equal(argv[1], "0") < 0){
		printf("\t\t%.48Lf\n", cosl(x));
	}else{
		printf("\t\t\t%.48Lf\n", cosl(x));
	}
	if((temp = division(argv[2], pi_, 48)) == NULL){
		temp = argv[2];
		x = strtold(temp, &endptr);
	}else{
		//printf("%s\n", temp);
		if((temp_ = strchr(temp, '.')) != NULL){
			//printf("%s\n", temp);
			temp_--;
			*temp_ = '0';
			endptr = multiplication(pi_,temp_);
			temp = endptr;
			x = strtold(temp, &endptr);
		}else{
			free(temp);
			temp = argv[2];
			x = 0;
		}
	}
	if(temp != argv[2])
		free(temp);
	endptr = NULL;
	if(endptr && strlen(endptr)>0)
		fprintf(stderr, "Erreur: <%s>\n", endptr);
	printf("cosinus arbitraire de \'%s\':\t%.48Lf\n", argv[2],cosl(x));
	endptr = NULL;
	x = strtold(argv[2], &endptr);
	if(endptr && strlen(endptr)>0)
		fprintf(stderr, "Erreur: <%s>\n", endptr);
	printf("cosinus de \'%s\':", argv[2]);
	if(equal(argv[2], "0") < 0){
		printf("\t\t%.48Lf\n", cosl(x));
	}else{
		printf("\t\t\t%.48Lf\n", cosl(x));
	}
	free(pi_);
	return 0;
}
