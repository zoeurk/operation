#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
/*BUFFER > 1*/
const unsigned long int BUFFER = 2;
char *cosinus(char *arg){
	char pi[512], npi[512], *pi_ = NULL, *temp, *t = NULL, *mul;
	//unsigned long int i = 0;
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
	return t;
}
char *racine_carree(void *num1, unsigned long int virgule, int approximation){
	unsigned long int len = strlen(num1)-(strchr(num1, '.') != NULL), v = virgule+1;
	/*last pour eviter une boucle plus bas*/
	char *num1_ = NULL, *pnum1_,*dix = NULL, *pdix, buffer[32], *buf, *pbuf, *result, *presult, *check = NULL, *test, *last = NULL;
	num1_ = multiplication(num1, "1");
	while(strchr(num1_,'.') != NULL){
		pnum1_ = multiplication(num1_,"100");
		free(num1_);
		num1_ = pnum1_;
		if(dix == NULL)
			dix = multiplication("1", "10");
		else{
			pdix = multiplication(dix, "10");
			free(dix);
			dix = pdix;
		}
	}
	len = strlen(num1_)-(strchr(num1_, '.') != NULL);
	if((test = strchr(num1_,'.')) != NULL){
		test++;
		if(virgule < strlen(test)){
			v = strlen(test)+1;
		}
	}
	sprintf(buffer,"%lu", len);
	buf = multiplication(buffer,"100");
	pbuf = division(num1_, buf,virgule, 0);
	result = addition(buf, pbuf);
	free(buf);
	presult = multiplication(result,"0.5");
	do{
		free(pbuf);
		free(result);
		test = strchr(presult,'.');
		pbuf = division(num1_, presult, v, 0);
		result = addition(presult, pbuf);
		free(presult);
		presult = multiplication(result,"0.5");
		//printf("%s\n", presult);
		if(check)
			free(check);
		if((test = strchr(presult,'.')) != NULL && *presult != '0'){
			if(strlen(test+1)>=v)
				*(test+1+v) = 0; 
		}
		//printf("%s\n", presult);
		check = multiplication(presult, presult);
		/*Possible boucle infinie*/
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
	}while(equal(num1_, check) < 0);
	free(num1_);
	if(last)
		free(last);
	free(pbuf);
	free(result);
	free(check);
	if((result = strchr(presult, '.'))){
		if(!approximation)
			result[virgule+1] = 0;
		else{
			if(presult[strlen(presult)-1] >= '5'){
				test = allocation((void **)&test, 3, sizeof(char));
				strcpy(test,"0.");
				if(v == 1){
					check = reallocation((void **)&test,4);
					strcat(test, "1");
					check = addition(presult, test);
					free(presult);
					presult = check;
				}else{
					while(strlen(test) +1 <= v){
						check = reallocation((void **)&test,strlen(test)+2);
						strcat(test, "0");
						check = addition(presult, test);
						free(presult);
						presult = check;
					}
					check = reallocation((void **)&test,strlen(test)+2);
					test[strlen(test)] = '1';
					check = addition(presult, test);
					free(presult);
					presult = check;
					if(strlen(presult) > virgule+1)
						presult[strlen(presult) - 1] = 0;
					else
						presult[strlen(presult)-1] = 0;
				}
				free(test);
			}else presult[strlen(presult)-1] = 0;
			for(result = &presult[strlen(presult)-1]; *result == '0'; *result = 0, result--);;
		}
	}
	if(dix){
		result = division(presult, dix,virgule, approximation);
		free(presult);
		presult = result;
		free(dix);
	}
	if((result = strchr(presult,'.')) && strlen(result) > virgule){
		result[virgule+1] = 0;
		for(result = &presult[strlen(presult)-1]; *result == '0'; *result = 0, result--);;
	}
	if(presult[strlen(presult)-1] == '.')
		presult[strlen(presult)-1] = 0;
	return presult;
}
int main(int argc, char **argv){
	int ret, i;
	char *r, *check;
	if(argc != 4){
		fprintf(stderr, "usage:\n\t%s num1 num2 virgule\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/*for(i = 1; i < 3; i++)
		if((ret = strtype(argv[i])) != 0)
			switch(ret){
				case 1: case 2:
					fprintf(stderr, "Donnee invalide\n");
					exit(EXIT_FAILURE);
			}*/
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
	return 0;
}
