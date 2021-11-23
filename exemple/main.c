#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
void cosinus(char *arg){
	char pi[60], npi[60],*pi_, *npi_ ,*temp;
	long double x;
	//memset(npi, 0, 51);
	sprintf(npi,"-%.56Lf", (long double)M_PI);
	//memset(pi, 0, 51);
	sprintf(pi,"%.56Lf", (long double)M_PI);
	pi_ = multiplication(pi, "2");
	npi_ = multiplication(npi, "-2");
	temp = multiplication(arg,"1");
	if(equal(temp, pi_) > 0){
		temp = modulo(arg, pi_);
		x = strtold(modulo(arg,pi_), NULL);
		printf("Cosinus arbitraire de \'%s\': %.56Lf\n", arg, cosl(x));
		free(temp);
	}else{
		if(equal(arg, npi_) < 0){
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
#define MIN 64
#define Q_MIN "64"
void racine_carree(char *i){
	//printf("%s\n", i);
	char *pi,*j, *pj,rc[60], arrondi[58], m[21];
	long double r1;
	char t[2] = { 0, 0 };
	unsigned long long int  max = MIN;
	if(equal(i, "0") < 0){
		printf("ERREUR: Valeur: %s < 0\n", i);
		return;
	}
	memset(m,0,21);
	sprintf(m,"%llu", max);
	sprintf(rc, "%.56Lf", sqrtl(max));
	memset(arrondi,'0',58);
	arrondi[57] = 0;
	arrondi[1] = '.';
	arrondi[56] = '1';
	//printf("%s\n", rc);
	pi = multiplication(i,"1");
	pj = multiplication("1","1");
	while(equal(pi,m) > 0){
		//printf("*\n");
		//printf("%s\n", rc);
		j = pj;
		pj = multiplication(rc, pj);
		free(j);

		j = pi;
		/*pl = multiplication(j, j);
		if(equal(i, pl) < 0)
			break;*/
		pi = division(j,m,1024);
		free(j);
		j = pi;
	}
	j = pj;
	r1 = strtold(pi, NULL);
	r1 = sqrtl(r1);
	sprintf(rc, "%.56Lf", r1);
	j = multiplication(pj,rc);
	//printf("==>%s\n", pj);
	free(pj);
	free(pi);
	pj = multiplication(j,j);
	//printf("==>%s\n", pj);
	free(pj);
	if((j = strchr(pj, '.'))){
		if(strlen(j+1) > 56){
				t[0] = *(j+56);
				if(atoi(t) >= 5){
					pj = j;
					j = addition(pj, arrondi);
					free(pj);
					pj = strchr(j, '.');
					*(pj+57) = 0;
				}else
					*(pj+57) = 0;
		}
	}
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
	/*printf("++++++++++++++++++\n");
	cosinus(argv[1]);
	cosinus(argv[2]);
	printf("++++++++++++++++++\n");
	racine_carree(argv[1]);
	racine_carree(argv[2]);*/
	return 0;
}
