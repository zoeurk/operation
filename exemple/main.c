#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation.h"

void cosinus(char *arg){
	char pi[512], npi[512],*pi_, *npi_ ,*temp, *t;
	sprintf(npi,"-%.56Lf", 8*atanl(1));
	sprintf(pi,"%.56Lf", 8*atanl(1));
	pi_ = multiplication(pi, "2");
	npi_ = multiplication(pi,"-2");
	if(equal(arg, "0") == 1){
		t = division(arg, pi_ , 0, 0);
		free(t);
		t = multiplication(arg, "1");
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
	printf("cosinus  de \'%s\': %.56Lf\n", arg, cosl(strtold(arg, NULL)));
	free(pi_);
	free(npi_);
}
char *find(char *i, char *result, unsigned long int virgule, int approximation){
	char *i_ = multiplication(i,"1"), k, end = 0,
		*temp = multiplication(i,i), *ppt, *pt,*t, *dot = NULL,
		*add = NULL, *padd;
	unsigned long int len = 0, l = 0, dotlen = 0;
	padd = allocation((void **)&add, strlen(i)+1, sizeof(char));
	memset(add, '0', strlen(i));
	add[0] = '1';
	if((dot = strchr(i,'.')) != NULL){
		len = strlen(i);
		l = len-strlen(dot);
		add[l] = '.';
	}
	while(equal(temp, result) < 0 && dotlen < virgule && end == 0){
		for(k = 57; k > 47;k--){
			t = multiplication(add,&k);
			pt = addition(i_,t);
			ppt = multiplication(pt, pt);
			if(equal(ppt, result) < 0){
				if((padd = strchr(pt,'.')) != NULL){
					if(strlen(padd) > virgule){
						if(approximation){
							if(strlen(pt)-1 > virgule){
								l = virgule;
								padd = dot = allocation((void **)&dot, virgule+3, sizeof(char));
								strcpy(dot,"0.");
								for(l = 0, padd += 2; l < virgule-2; l++, padd++){
									*padd = '0';
								}
								*padd = '1';
								padd = addition(pt,dot);
								free(pt);
								free(dot);
								pt = padd;
								pt[strlen(pt)-1] = 0;
							}else pt[strlen(pt)-1] = 0;
						}else pt[strlen(pt)-1] = 0;
						free(ppt);
						dotlen = virgule;
						end = 1;
						free(i_);
						i_ = pt;
						free(t);
						break;
					}
				}
				free(i_);
				free(ppt);
				i_ = pt;
				free(t);
			}else{
				free(t);
				free(pt);
				free(ppt);
			}
		}
		padd = add;
		add = division(add,"10",virgule,0);
		free(padd);
	}
	free(temp);
	free(add);
	return i_;
}
char *racine_carree(char *argv, unsigned long int virgule, int approximation){
	char *r, *i = addition(argv, "0"),*i_ = NULL, *j = NULL, *result = multiplication("1", argv);
	do{
		i_ = division(i, "2", 0, 1);
		j = multiplication(i_,i_);
		if(equal(j, result) <= 0){
			break;
		}
		free(i);
		i = i_ ;
		free(j);
	}while(1);
	if(equal(j, result) != 0){
		r = find(i_, result, virgule+1, approximation);
		free(i_);
	}else r = i_;
	free(i);
	free(j);
	free(result);
	return r;
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
	cosinus(argv[1]);
	cosinus(argv[2]);
	printf("++++++++++++++++++\n");
	r = racine_carree(argv[1], 16, 1);
	check = multiplication(r, r);
	printf("Racine carree (arrondie) de \'%s\':%s\n",argv[1], r);
	printf("Verification: %s\n", check);
	free(r);
	free(check);
	r = racine_carree(argv[1], 16, 0);
	check = multiplication(r, r);
	printf("Racine carree de \'%s\':%s\n",argv[1], r);
	printf("Verification: %s\n", check);
	free(r);
	free(check);
	r = racine_carree(argv[2], 16, 1);
	check = multiplication(r, r);
	printf("Racine carree (arrondie) de \'%s\':%s\n",argv[2], r);
	printf("Verification: %s\n", check);
	free(r);
	free(check);
	r = racine_carree(argv[2], 16, 0);
	check = multiplication(r, r);
	printf("Racine carree de \'%s\':%s\n",argv[2], r);
	printf("Verification: %s\n", check);
	free(r);
	free(check);
	return 0;
}
