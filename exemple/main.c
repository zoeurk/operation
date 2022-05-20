#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
/*BUFFER > 1*/
const unsigned long int BUFFER = 56;
#ifdef _MATH_H
char *cosinus(char *arg, char *format,unsigned long internal_buflen){
	char pi[512], npi[512], *pi_ = NULL, *temp, *t = NULL, *mul, buffer[internal_buflen], *pbuf, *form;
	long double val, format_;
	form = format+2;
	format_ = strtold(form,NULL);
		//fprintf(stderr, "Echec :%.0Lf < %lu (internal_buflen)\n", format_, internal_buflen);
	if(format_ > internal_buflen){
		fprintf(stderr, "Echec :%.0Lf > %lu (internal_buflen)\n", format_, internal_buflen);
		exit(EXIT_FAILURE);
	}
	memset(buffer, 0, internal_buflen);
	sprintf(pi,"%.54Lf", 8*atanl(1));
	sprintf(npi,"-%.54Lf", 8*atanl(1));
	t = multiplication(arg,"1");
	if(equal(arg,"0") > 0){
		mul = division(arg, pi, 0,0);
		pi_ = multiplication(pi, mul);
		temp = soustraction(t, pi_);
		free(mul);
		free(pi_);
		free(t);
		t = temp;
	}else{
		if(equal(arg, "0") < 0){
			mul = division(arg, pi, 0, 0);
			pi_ = multiplication(npi, mul);
			temp = addition(t, pi_);
			free(mul);
			free(pi_);
			free(t);
			t = temp;
		}
	}
	val = cosl(strtold(t,NULL));
	snprintf(buffer,  internal_buflen,format, val);
	if(buffer[internal_buflen-1] != 0){
		fprintf(stderr, "Tampon interne trop petit\n");
		exit(0);
	}
	pbuf = multiplication(buffer,"1");
	free(t);
	return pbuf;
}
#endif

#define POWER(fn) \
	if(equal(num1, "0") < 0){\
		free(n1);\
		free(n2);\
		if((n1 = calloc(5,sizeof(char))) == NULL){\
			perror("calloc()");\
			exit(EXIT_FAILURE);\
		}\
		strcpy(n1, "-nan");\
		return n1;\
	}\
	if((v_ = calloc(strlen(n2)+2,sizeof(char))) == NULL){\
		perror("calloc()");\
		exit(EXIT_FAILURE);\
	}\
	strcpy(v_+1, v);\
	*v_ = '0';\
	*v = 0;\
	pseudo = buffer;\
	do{\
		pseudo_ = strtold(n1, NULL);\
		sprintf(buffer, format, pseudo_);\
		if((eq = equal(n1, pseudo)) > 0){\
			n1_ = racine_carree(n1, virgule,approximation);\
			free(n1);\
			n1 = n1_;\
			i_ = addition(i, "1");\
			free(i);\
			i = i_;\
		}\
	}while(eq > 0);\
	pdot_ = strchr(format,'.');\
	if((dot_ = calloc(strlen(format), sizeof(char))) == NULL){\
		perror("calloc()");\
		exit(EXIT_FAILURE);\
	}\
	strcpy(dot_, pdot_+1);\
	pdot_ = strchr(dot_, 'L');\
	/**dot_ = '0';*/\
	*pdot_ = 0;\
	if((p = strchr(v_,'.')) != NULL && strlen(p+1) > (unsigned long int)atol(dot_)){\
		fprintf(stderr,"Warning `%s`:\n\tTrop de chiffre apres la virgule.\n\tUtilisation de la valeur: ", v_);\
		fprintf(stderr, format, strtold(v_, NULL)); \
		fprintf(stderr,"\n");\
	}\
	free(dot_);\
	pseudo_ = powl(strtold(n1_, NULL), strtold(v_, NULL));\
	snprintf(buffer, internal_buflen, format, pseudo_);\
	if(buffer[internal_buflen-1] != 0){\
		fprintf(stderr, "buffer interne trop court\n");\
		exit(EXIT_FAILURE);\
	}\
	if(equal(i,"0") != 0){\
		while(equal(i,"0") != 0){\
			if(set == 0){ \
				pseudo = multiplication(buffer, buffer);\
				set = 1;\
			}else{\
				p = pseudo;\
				pseudo = multiplication(p, buffer);\
				free(p);\
			}\
			i_ = soustraction(i, "1");\
			free(i);\
			i = i_;\
		}\
	}else pseudo = multiplication(buffer,"1");\
	free(n1_);\
	while(equal(n2, "0") != 0){\
		n1_ = multiplication(pseudo, num1);\
		free(pseudo);\
		pseudo = n1_;\
		n1_ = NULL;\
		n2_ = fn(n2, "1");\
		free(n2);\
		n2 = n2_;\
	}\
	n1_ = pseudo;\
	pseudo = NULL;\
	free(v_);\
	free(i);\
	i = NULL;\
	if(pseudo)\
		free(pseudo);


#define POW(fn)\
	n1_ = multiplication(n1,num1);\
	free(n1);\
	n1 = n1_;\
	n2_ = fn(n2, "1");\
	free(n2);\
	n2 = n2_;

void *puissance(void *num1, void *num2, unsigned long int internal_buflen, char *format, unsigned long int virgule, int approximation){
	char *n1 = multiplication(num1,"1"), *n2 = multiplication(num2,"1"),
		buffer[internal_buflen], *v, 
		*n1_ = n1, *n2_ = n2,
		*i = multiplication("1","0");
#ifdef _MATH_H
	char *i_, *v_, *pseudo = NULL, *p, *dot_, *pdot_;
	long double pseudo_;
	int eq, set = 0;
#endif
	memset(buffer, 0, internal_buflen);
	//unsigned long int i_ = 0;
	if(equal(num2, "0") == 0){
		free(n1);
		free(n2);
		n1 = multiplication("1","1");
		return n1;
	}
	if((v = strchr(n2, '.')) != NULL){
#ifdef _MATH_H
		if(*((char *)num2) != '-'){
				POWER(soustraction);
		}else{
				POWER(addition);
				free(n2_);
				n2_ = n1_;
				n1_ = division("1", n2_, virgule, approximation);
		}
#else
		fprintf(stderr, "Erreur puissance scalaire non pris en charge\n");\
		exit(EXIT_FAILURE);
#endif
	}else{
		if(equal(n2, "0") > 0){
			while(equal(n2,"1") != 0){
				POW(soustraction);
			}
		}else{
			while(equal(n2,"-1") != 0){
				POW(addition);
			}
			n1_ = division("1", n1, virgule, approximation);
			free(n1);
		}
	}
	if(i != NULL)
		free(i);
	if(n2_)
		free(n2_);
	return n1_;
}
int main(int argc, char **argv){
	int ret, i, v;
	unsigned long int sz = 56;
	char *r, *check, format[16];
	if(argc < 4){
		fprintf(stderr, "usage:\n\t%s num1 num2 virgule(>= 0) [internal_buflen(default = 56)]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	v = atoi(argv[3]);
	if(argc > 4)
		sz = atoi(argv[4]);
	if(v < 0){
		fprintf(stderr, "usage:\n\t%s num1 num2 virgule(>= 0) [internal_buflen(default = 56)]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if(v > 0){
		strcpy(format,"%.");
		if(strlen(argv[3]) > 5){
			fprintf(stderr,"Erreur: format trop long.\n");
			exit(EXIT_FAILURE);
		}
		strcat(format,argv[3]);
		strcat(format,"Lf");
	}else strcpy(format,"%Lf"); 
	for(i = 1; i < 3; i++)
		if((ret = strtype(argv[i])) != 0)
			switch(ret){
				case 1: case 2:
					fprintf(stderr, "Donnee invalide\n");
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
	r = modulo(argv[1], argv[2], 0);
	if(r){
		printf("modulo:%s\n", (char *)r);
		free(r);
	}
	r = modulo(argv[1], argv[2], atoi(argv[3]));
	if(r){
		printf("modulo etendu:%s\n",  (char *)r);
		free(r);
	}
	//No warrenty
#ifdef _MATH_H
	printf("++++++++++++++++++\n");
	r = cosinus(argv[1], format, sz);
	if(r){
		printf("cosinus de \'%s\':%s\n", argv[1],r);
		free(r);
	}
	r = cosinus(argv[2], format, sz);
	if(r){
		printf("cosinus de \'%s\':%s\n", argv[2], r);
		free(r);
	}
	printf("++++++++++++++++++\n");
#endif
	if(equal(argv[1],"0") < 0)
		fprintf(stderr, "Racine carree non applicable sur un nombre negatif:%s\n", argv[1]);
	else{
		r = racine_carree(argv[1], atoi(argv[3]),1);
		if(r){
			check = multiplication(r, r);
			printf("racine carree aproximatif de '%s': %s\n", argv[1], r);
			printf("Verification:%s\n", check);
			free(r);
			free(check);
		}
		r = racine_carree(argv[1], atoi(argv[3]),0);
		if(r){
			check = multiplication(r, r);
			printf("racine carree de '%s': %s\n", argv[1], r);
			printf("Verification:%s\n", check);
			free(r);
			free(check);
		}
	}
	if(equal(argv[2], "0") < 0)
		fprintf(stderr, "Racine carree non applicable sur un nombre negatif:%s\n", argv[2]);
	else{
		r = racine_carree(argv[2], atoi(argv[3]),1);
		if(r){
			check = multiplication(r, r);
			printf("racine carree aproximatif de '%s': %s\n", argv[2], r);
			printf("Verification:%s\n", check);
			free(r);
			free(check);
		}
		r = racine_carree(argv[2], atoi(argv[3]),0);
		if(r){
			check = multiplication(r, r);
			printf("racine carree de '%s': %s\n", argv[2], r);
			printf("Verification:%s\n", check);
			free(r);
			free(check);
		}
	}
	r = puissance(argv[1],argv[2], sz, format,atoi(argv[3]), 1);
	if(r){
		printf("%s^%s  = %s\n", argv[1], argv[2], r);
		free(r);
	}
	return 0;
}
