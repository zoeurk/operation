#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"

char *cosinus(char *arg){
	char pi[512], npi[512],*pi_, *npi_ ,*temp, *t = NULL;
	sprintf(npi,"-%.54Lf", 4*atanl(1));
	sprintf(pi,"%.54Lf", 4*atanl(1));
	pi_ = multiplication(pi, "2");
	npi_ = multiplication(pi,"-2");
	if(equal(arg, "0") == 1){
			t = division(arg, pi_ , 0, 0);
			temp = multiplication(t,pi_);
			free(t);
			t = soustraction(arg, temp);
			free(temp);
	}else{
		if(equal(arg, "0") == -1){
			t = division(arg, npi_ , 0, 0);
			temp = multiplication(t,npi_);
			free(t);
			t = soustraction(arg, temp);
			free(temp);
		}else{
			t = allocation((void *)&t, 2, sizeof(char));
			*t = '0';
		}
	}
	free(pi_);
	free(npi_);
	return t;
}
char *racine_carree(void *num1, unsigned long int virgule){
	unsigned long int len = strlen(num1)-(strchr(num1, '.') != NULL), v = virgule;
	char buffer[32], *buf, *pbuf, *result, *presult, *check = NULL, *test, *last = NULL;
	if((test = strchr(num1,'.')) != NULL){
		test++;
		if(virgule < strlen(test)){
			v = strlen(test)+1;
		}
	}
	sprintf(buffer,"%lu", len);
	buf = multiplication(buffer,"100");
	pbuf = division(num1, buf,virgule, 0);
	result = addition(buf, pbuf);
	free(buf);
	presult = multiplication(result,"0.5");
	//printf("%s\n", result);
	do{
		//printf("______\n");
		free(pbuf);
		free(result);
		test = strchr(presult,'.');
		/*if(test){
			if(strlen(test)> 1+v)
				test[1+v] = 0;
			//printf("%s:%lu,%lu\n", test+1, strlen(test+1),v/8);
		}*/
		pbuf = division(num1, presult, v, 0);
		result = addition(presult, pbuf);
		free(presult);
		presult = multiplication(result,"0.5");
		//printf("==============\n");
		if(check)
			free(check);
		//printf("%s\n",presult);
		if((test = strchr(presult,'.')) != NULL){
			if(strlen(test+1)>=v)
				*(test+1+v) = 0; 
		}
		check = multiplication(presult, presult);
		/*if(test && strlen(test+1) > v){
				*(test+v) = 0;
		}*/
		if(last == NULL){
			last = allocation((void **)&last,strlen(check)+1, sizeof(char));
			strcpy(last, check);
		}else{
			if(equal(last, check) == 0){
				free(last);
				last = NULL;
				break;
			}
			free(last);
			last = allocation((void **)&last,strlen(check)+1, sizeof(char));
			strcpy(last, check);
		}
		//printf("%s\n",check);
	}while(equal(num1, check) < 0);
	if(last)
		free(last);
	free(pbuf);
	free(result);
	free(check);
	if(presult[strlen(presult)-1] == '.')
		presult[strlen(presult)-1] = 0;
	return presult;
}
int main(int argc, char **argv){
	int ret;
	char *r, *check;
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
	r = cosinus(argv[1]);
	if(r){
		printf("cosinus de \'%s\':%.56Lf\n", argv[1],cosl(strtold(r,NULL)));
		free(r);
	}
	r = cosinus(argv[2]);
	if(r){
		printf("cosinus de \'%s\':%.56Lf\n", argv[2], cosl(strtold(r,NULL)));
		free(r);
	}
	printf("++++++++++++++++++\n");
	r = racine_carree(argv[1], atoi(argv[3]));
	if(r){
		check = multiplication(r, r);
		printf("racine carree de '%s': %s\n", argv[1], r);
		printf("Verification:%s\n", check);
		free(r);
		free(check);
	}
	r = racine_carree(argv[2], atoi(argv[3]));
	if(r){
		check = multiplication(r, r);
		printf("racine carree de '%s': %s\n", argv[2], r);
		printf("Verification:%s\n", check);
		free(r);
		free(check);
	}
	/*printf("%Lf\n", sqrtl(strtold(argv[1], NULL)));*/
	return 0;
}
