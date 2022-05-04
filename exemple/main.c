#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"
/*BUFFER > 1*/
const unsigned long int BUFFER = 2;
char *cosinus(char *arg, unsigned long internal_buflen){
	char pi[512], npi[512], *pi_ = NULL, *temp, *t = NULL, *mul, buffer[internal_buflen], *pbuf;
	long double val;
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
	sprintf(buffer, "%Lf", val);
	pbuf = multiplication(buffer,"1");
	free(t);
	return pbuf;
}
char *racine_carree(void *num1, unsigned long int virgule, int approximation){
	unsigned long int len, v = virgule+1;
	/*last pour eviter une boucle plus bas*/
	char *num1_ = NULL, *pnum1_,*dix = NULL, *pdix, buffer[32], *buf, *pbuf, *result, *presult, *check = NULL, *test/*, *last = NULL*/;
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
	len = strlen(num1_);
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
		if(check)
			free(check);
		if((test = strchr(presult,'.')) != NULL && *presult != '0'){
			if(strlen(test+1)>=v)
				*(test+1+v) = 0; 
		}
		check = multiplication(presult, presult);
		/*Possible boucle infinie*/
		/*if(last == NULL){
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
		}*/
	}while(equal(num1_, check) < 0);
	free(num1_);
	/*if(last)
		free(last);*/
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
void *puissance(void *num1, void *num2, unsigned long int virgule, unsigned long int internal_buflen, int approximation){
	char *n1 = multiplication(num1,"1"), *n2 = multiplication(num2,"1"),
		*n1_ = n1, *n2_ = n2,
		*v, *v_, *pseudo = NULL, *p;
	char buffer[internal_buflen];
	long double pseudo_;
	int eq, set = 0;
	unsigned long int i = 0;
	if((v = strchr(n2, '.')) != NULL){
		if(*((char *)num2) != '-'){
				if(equal(num1, "0") < 0){
					free(n1);
					free(n2);
					if((n1 = calloc(5,sizeof(char))) == NULL){
						perror("calloc()");
						exit(EXIT_FAILURE);
					}
					strcpy(n1, "-nan");
					return n1;
				}
				if((v_ = calloc(strlen(n2)+2,sizeof(char))) == NULL){
					perror("calloc()");
					exit(EXIT_FAILURE);
				}
				strcpy(v_+1, v);
				*v_ = '0';
				*v = 0;
				pseudo = buffer;
				do{
					pseudo_ = strtold(n1, NULL);
					sprintf(buffer, "%Lf", pseudo_);
					if((eq = equal(n1, pseudo)) > 0){
						n1_ = racine_carree(n1, virgule,approximation);
						free(n1);
						n1 = n1_;
						i++;
					}
				}while(eq > 0);
				pseudo_ = powl(strtold(n1_, NULL), strtold(v_, NULL));
				sprintf(buffer, "%Lf", pseudo_);
				if(i != 0){
					while(i != 0){
						if(set == 0){ 
							pseudo = multiplication(buffer, buffer);
							set = 1;
						}else{
							p = pseudo;
							pseudo = multiplication(p, buffer);
							free(p);
						}
						i--;
					}
				}else pseudo = multiplication(buffer,"1");
				free(n1_);
				while(equal(n2, "0") != 0){
					n1_ = multiplication(pseudo, num1);
					free(pseudo);
					pseudo = n1_;
					n1_ = NULL;
					n2_ = soustraction(n2, "1");
					free(n2);
					n2 = n2_;
				}
				n1_ = pseudo;
				pseudo = NULL;
				free(v_);
				if(pseudo)
					free(pseudo);
				free(n2_);
				n2_ = NULL;
		}else{
				if(equal(num1, "0") < 0){
					free(n1);
					free(n2);
					if((n1 = calloc(5,sizeof(char))) == NULL){
						perror("calloc()");
						exit(EXIT_FAILURE);
					}
					strcpy(n1, "-nan");
					return n1;
				}
				if((v_ = calloc(strlen(n2)+2,sizeof(char))) == NULL){
					perror("calloc()");
					exit(EXIT_FAILURE);
				}
				strcpy(v_+1, v);
				*v_ = '0';
				*v = 0;
				n2_ = multiplication(n2,"-1");
				free(n2);
				pseudo_ = powl(strtold(n1, NULL), strtold(v_, NULL));
				sprintf(buffer, "%Lf", pseudo_);
				if(equal(n2_,"-1") <= 0)
					pseudo = puissance(n1, n2_, virgule, internal_buflen, approximation);
				free(n2_);
				free(v_);
				if(pseudo)
					n1_ = multiplication(buffer, pseudo);
				else
					n1_ = multiplication(buffer, "1");
				free(n1);
				n2_ = division("1", n1_, virgule, 0);
				free(n1_);
				n1_ = n2_;
				n2_ = NULL;
				free(pseudo);
		}
	}else{
		if(equal(n2, "0") > 0){
			while(equal(n2,"1") != 0){
				n1_ = multiplication(n1,num1);
				free(n1);
				n1 = n1_;
				n2_ = soustraction(n2, "1");
				free(n2);
				n2 = n2_;
			}
		}else{
			if(equal(n2,"0") < 0){
				while(equal(n2,"-1") != 0){
					n1_ = multiplication(n1,num1);
					free(n1);
					n1 = n1_;
					n2_ = addition(n2, "1");
					free(n2);
					n2 = n2_;
				}
				n1_ = division("1", n1, virgule, 0);
				free(n1);
			}else{
			}
		}
	}
	if(n2_)
		free(n2_);
	return n1_;
}
int main(int argc, char **argv){
	int ret, i;
	char *r, *check;
	if(argc != 4){
		fprintf(stderr, "usage:\n\t%s num1 num2 virgule\n", argv[0]);
		exit(EXIT_FAILURE);
	}
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
	printf("++++++++++++++++++\n");
	r = cosinus(argv[1],0);
	if(r){
		printf("cosinus de \'%s\':%s\n", argv[1],r);
		free(r);
	}
	r = cosinus(argv[2], 0);
	if(r){
		printf("cosinus de \'%s\':%s\n", argv[2], r);
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
	r = puissance(argv[1],argv[2], atoi(argv[3]), 56, 0);
	if(r){
		printf("%s^%s  = %s\n", argv[1], argv[2], r);
		free(r);
	}
	return 0;
}
