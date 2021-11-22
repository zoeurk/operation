#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <float.h>
#include "operation.h"
void cosinus(char *arg){
	int ret;
	char pi[51], npi[52],*pi_, *npi_ ,*temp, *temp_, *temp__;
	long double x;
	memset(npi, 0, 51);
	sprintf(npi,"-%.48Lf", (long double)M_PI);
	memset(pi, 0, 51);
	sprintf(pi,"%.48Lf", (long double)M_PI);
	pi_ = multiplication(pi, "4");
	npi_ = multiplication(npi, "-4");
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
#define MIN 4096
#define Q_MIN "4096"
void racine_carree(char *i){
	//printf("%s\n", i);
	char *pi,*j, *pj, rc[60], arrondi[58];
	long double r1;
	char t[2] = { 0, 0 };
	sprintf(rc, "%.56Lf", sqrtl(MIN));
	memset(arrondi,'0',58);
	arrondi[57] = 0;
	arrondi[1] = '.';
	arrondi[56] = '1';
	//printf("%s\n", rc);
	pi = multiplication(i,"1");
	pj = multiplication("1","1");
	while(equal(pi,Q_MIN) > 0){
		//printf("%s\n", rc);
		j = pj;
		pj = multiplication(rc, pj);
		free(j);
		if((j = strchr(pj, '.'))){
			if(strlen(j+1) > 56){
				t[0] = *(j+57);
				if(atoi(t) >= 5){
					j = pj;
					pj = addition(j, arrondi);
					free(j);
					j = strchr(pj, '.');
					*(j+57) = 0;
				}else
					*(j+57) = 0;
			}
		}
		j = pi;
		pi = division(pi,Q_MIN,56);
		free(j);
	}
	j = pj;
	r1 = strtold(pi, NULL);
	r1 = sqrtl(r1);
	sprintf(rc, "%.56Lf", r1);
	j = multiplication(pj,rc);
	free(pj);
	//printf("==>%s\n", pj);
//	free(pj);
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
	//printf("%.56Lf\n", LDBL_MAX);
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
