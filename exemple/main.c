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
char *racine_carree(void *num1, unsigned long int virgule, int approximation){
	unsigned long int len = strlen(num1)-(strchr(num1, '.') != NULL), v = virgule+1;
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
	do{
		free(pbuf);
		free(result);
		test = strchr(presult,'.');
		pbuf = division(num1, presult, v, 0);
		result = addition(presult, pbuf);
		free(presult);
		presult = multiplication(result,"0.5");
		if(check)
			free(check);
		if((test = strchr(presult,'.')) != NULL){
			if(strlen(test+1)>=v)
				*(test+1+v) = 0; 
		}
		check = multiplication(presult, presult);
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
	if((result = strchr(presult, '.'))){
		if(!approximation)
			result[strlen(result)-1] = 0;
		else{
			test = allocation((void **)&test, 3, sizeof(char));
			strcpy(test,"0.");
			if(v == 1){
				check = reallocation((void **)&test,4);
				strcat(test, "1");
				check = addition(presult, test);
				free(presult);
				presult = check;
				//printf("%s::%s\n", check, test);
			}else{
				while(strlen(test) +1 <= v){
					check = reallocation((void **)&test,strlen(test)+1);
					strcat(test, "0");
					check = addition(presult, test);
					free(presult);
					presult = check;
					//printf("%s::%s\n", check, test);
				}
				//test[strlen(test)-1] = 0;
				check = reallocation((void **)&test,strlen(test)+2);
				test[strlen(test)] = '1';
				//printf("%s::%s\n", test, presult);
				check = addition(presult, test);
				//printf("==>%s::%s::%s\n", check, presult, test);
				free(presult);
				presult = check;
				//printf("%s::%s\n", check, test);
				presult[strlen(presult)-1] = 0;

			}
			free(test);
			//presult[strlen(presult)-1] = 0;
			for(result = &presult[strlen(presult)-1]; *result == '0'; *result = 0, result--);;
		}
	}
	/*if((test = strchr(presult, '.'))){
		printf("%s::%lu\n", test, virgule);
		*(test - virgule +1) = 0;
	}*/
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
	/*printf("%Lf\n", sqrtl(strtold(argv[1], NULL)));*/
	return 0;
}
