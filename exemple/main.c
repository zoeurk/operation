#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"

void cosinus(char *arg){
	char pi[60], npi[60],*pi_, *npi_ ,*temp, *t;
	long double x;
	sprintf(npi,"-%.56Lf", (long double)M_PI);
	sprintf(pi,"%.56Lf", (long double)M_PI);
	pi_ = multiplication(pi, "2");
	npi_ = multiplication(pi,"-2");
	if(equal(arg, "0") == 1){
		t = division(arg, pi_ , 0, 0);
		temp = multiplication(t,pi_);
		free(t);
		t = soustraction(arg, temp);
		free(temp);
		printf("cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(strtold(t,NULL)));
		free(t);
	}else{
		if(equal(arg, "0") == -1){
			t = division(arg, npi_ , 0, 0);
			temp = multiplication(t,npi_);
			free(t);
			t = soustraction(arg, temp);
			free(temp); 
			printf("cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(strtold(t,NULL)));
			free(t);
		}
	}
	x = strtold(arg, NULL);
	printf("cosinus  de \'%s\': %.56Lf\n", arg, cosl(strtold(arg, NULL)));
	free(pi_);
	free(npi_);
}
void racine_carree(char *i, unsigned long int virgule, unsigned long long int coefficient){
	char *eq = NULL, *pi,*j, *pj,rc[60], m[21];
	long double r1;
	unsigned long long int  max = coefficient;
	if(equal(i, "0") < 0){
		printf("ERREUR: Valeur: %s < 0\n", i);
		return;
	}
	memset(m,0,21);
	sprintf(m,"%llu", max);
	sprintf(rc, "%.56Lf", sqrtl(max));
	pi = multiplication(i,"1");
	pj = multiplication("1","1");
	while(equal(pi,m) > 0){
		/*if(pi && strchr(pi,'.') && strlen(strchr(pi,'.')) > 6){
			j = pj;
			pj = multiplication("10", pj);
			free(j);
			j = pi;
			pi = division(j,"100",virgule,1);
			free(j);
			j = pi;
		}else{*/
			j = pj;
			pj = multiplication(rc, pj);
			free(j);
			j = pi;
			pi = division(j,m, virgule,0);
			//printf("%s\n", pi);
			//printf("%s\n", pi);
			free(j);
			j = pi;
		//}
	}
	j = pj;
	r1 = strtold(pi, NULL);
	r1 = sqrtl(r1);
	sprintf(rc, "%.56Lf", r1);
	j = multiplication(pj,rc);
	free(pj);
	free(pi);
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
	r = division(argv[1], argv[2], atoi(argv[3]),1);
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
