#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
void cosinus(char *arg){
	char pi[60], npi[60],*pi_, *npi_ ,*temp;
	long double x;
	sprintf(npi,"-%.56Lf", (long double)M_PI);
	sprintf(pi,"%.56Lf", (long double)M_PI);
	pi_ = multiplication(pi, "2");
	npi_ = multiplication(npi, "-2");
	temp = multiplication(arg,"1");
	if(equal(temp, pi_) > 0){
		free(temp);
		temp = modulo(arg, pi_);
		x = strtold(temp, NULL);
		printf("Cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(x));
		free(temp);
	}else{
		if(equal(arg, npi_) < 0){
			free(temp);
			temp = modulo(arg, npi_);
			x = strtold(temp, NULL);
			printf("Cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(x));
			free(temp);
		}
	}
	x = strtold(arg, NULL);
	printf("Cosinus  de \'%s\': %.56Lf\n", arg, cosl(x));
	free(pi_);
	free(npi_);
}
void racine_carree(char *i, unsigned long int virgule, unsigned long long int coefficient){
	//printf("%s\n", i);
	char *t, *pi,*j, *pj,rc[60], m[21];
	long double r1;
	unsigned long long int  max = coefficient;
	if(equal(i, "0") < 0){
		printf("ERREUR: Valeur: %s < 0\n", i);
		return;
	}
	memset(m,0,21);
	sprintf(m,"%llu", max);
	sprintf(rc, "%.56Lf", sqrtl(max));
	//printf("%s\n", rc);
	pi = multiplication(i,"1");
	pj = multiplication("1","1");
	while(equal(pi,m) > 0){
		if(pi && strchr(pi,'.') && strlen(strchr(pi,'.')) > 6){
			j = pj;
			pj = multiplication("10000", pj);
			free(j);
			j = pi;
			pi = division(j,"100000000",virgule);
			free(j);
			j = pi;		
		}else{
			j = pj;
			pj = multiplication(rc, pj);
			free(j);
			j = pi;
			pi = division(j,m,virgule);
			//printf("%s\n", pi);
			free(j);
			j = pi;
		}
	}
	j = pj;
	r1 = strtold(pi, NULL);
	r1 = sqrtl(r1);
	sprintf(rc, "%.56Lf", r1);
	j = multiplication(pj,rc);
	free(pj);
	free(pi);
	//printf("%s\n", (char *)multiplication(j,j));
	printf("Racine carree arbitraire pour \'%s\':%s\n" , i,j);
	printf("Racine carree pour \'%s\':%.56Lf\n", i, sqrtl(strtold(i, NULL)));
	free(j);
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
	
	//No warrenty
	printf("++++++++++++++++++\n");
	cosinus(argv[1]);
	cosinus(argv[2]);
	printf("++++++++++++++++++\n");
	racine_carree(argv[1], 56, 4);
	racine_carree(argv[2], 56, 4);
	return 0;
}
