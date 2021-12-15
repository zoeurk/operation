#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "operation.h"

char *cosinus(char *arg){
	char pi[512], npi[512],*pi_, *npi_ ,*temp, *t = NULL;
	sprintf(npi,"-%.56Lf", 8*atanl(1));
	sprintf(pi,"%.56Lf", 8*atanl(1));
	pi_ = multiplication(pi, "2");
	npi_ = multiplication(pi,"-2");
	if(equal(arg, "0") == 1){
		t = division(arg, pi_ , 0, 0);
		free(t);
		t = multiplication(arg, "1");
	}else{
		if(equal(arg, "0") == -1){
			t = division(arg, npi_ , 0, 0);
			temp = multiplication(t,npi_);
			free(t);
			t = soustraction(arg, temp);
			free(temp);
		}
	}
	free(pi_);
	free(npi_);
	return t;
}
char *find(char *i, char *result, unsigned long int virgule, int approximation){
	char *i_ = multiplication(i,"1"), k, end = 0, end_ = 0,
		*ppt, *pt,*t, *dot = NULL,
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
	while(dotlen <= virgule && end == 0){
		for(k = 57, end_ = 0; end_ == 0 && k > 47;k--){
		//printf("%i::%lu\n", end, dotlen);
			t = multiplication(add,&k);
			//printf("}}}>%s\n", t);
			pt = addition(i_,t);
			//printf("###>%s\n", pt);
			ppt = multiplication(pt, pt);
			if(strchr(pt,'.') && strlen(strchr(pt,'.')+1) > virgule)
				*(strchr(pt,'.')+1+virgule) = 0;
			//printf("~~~>%s\n", ppt);
			//printf("%s::%s\n", pt, ppt);
			if(equal(ppt, result) < 0){
				end_ = 1;
				if((padd = strchr(pt,'.')) != NULL){
					if(strlen(padd) >= virgule){
						//printf("%c",k);
						//printf("ok\n");
						if(approximation){
							if(strlen(pt) > virgule && virgule > 1){
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
								pt[strlen(pt)] = 0;
							}else{
								if(virgule == 1){
									l = virgule;
									padd = dot = allocation((void **)&dot, 2, sizeof(char));
									*padd = '1';
									padd = addition(pt,dot);
									free(pt);
									free(dot);
									pt = padd;
								}
								pt[strlen(pt)] = 0;
							}
						}else pt[strlen(pt)] = 0;
						free(ppt);
						dotlen = virgule;
						end = 1;
						free(i_);
						i_ = pt;
						free(t);
						if((ppt = strchr(pt, '.')) != NULL){
							for(pt = &i_[strlen(pt)-1];pt != i && (*pt == '0' && *pt != '.'); pt--)
								*pt = 0;
							if(*pt == '.')
								*pt = 0;
						}
						break;
					}
				}
				free(i_);
				free(ppt);
				i_ = pt;
				free(t);
				//if(end_ )printf("\n");
			}else{
				free(t);
				free(pt);
				free(ppt);
			}
			//printf("\n");
		}
		padd = add;
		add = division(add,"10",virgule,0);
		free(padd);
		if(virgule == 1)
			break;
	}
	free(add);
	return i_;
}
char *racine_carree(char *argv, unsigned long int virgule, int approximation){
	char *r, *i = multiplication(argv,"1"),*i_ = NULL, *j = NULL, *result = multiplication("1", argv),
		*tableau[4] = {"7", "5", "3", "2"}, *mod = NULL;
	int z = 0;
	//printf("%s::%s\n", argv, i);
	//exit(0);
	//printf("%s\n", (char *)modulo(i, tableau[0]));
	while(mod == NULL && z != 3){
		mod = modulo(argv, tableau[z]);
		if(mod && equal(mod,"0") == 0){
			free(mod);
			break;
		}
		free(mod);
		mod = NULL;
		z++;
	}
	do{
		i_ = division(i, tableau[z], 0, 1);
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
	long double t = 0;
	unsigned long int i = 0;
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
	/*printf("%lu;%Lf\n", sizeof(long double),LDBL_MAX);
	for(r = (char *)&t, i = 0; i < sizeof(long double);i++, r++){
		*r = ~1;
		if(i + 1 == sizeof(long double))
			*r = 0;
		//printf("%Lf, %i\n",t,*r);
	}*/
	//r = (char *)&t;
	//printf("%.100000000Lf::%s\n", t, r);
	//exit(0);
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
		printf("cosinus de \'%s\':%Lf\n", argv[1],cosl(strtold(r,NULL)));
		free(r);
	}
	r = cosinus(argv[2]);
	if(r){
		printf("cosinus de \'%s\':%Lf\n", argv[2], cosl(strtold(r,NULL)));
		free(r);
	}
	printf("++++++++++++++++++\n");
	r = racine_carree(argv[1], atoi(argv[3]), 1);
	if(r){
		check = multiplication(r, r);
		printf("Racine carree arbitraire (arrondie) de \'%s\':%s\n",argv[1], r);
		printf("Verification: %s\n", check);
		free(r);
		free(check);
	}
	/*r = racine_carree(argv[1], atoi(argv[3]), 0);
	check = multiplication(r, r);
	printf("Racine carree arbitraire de \'%s\':%s\n",argv[1], r);
	printf("Verification: %s\n", check);
	free(r);
	free(check);
	r = racine_carree(argv[2], atoi(argv[3]), 1);
	check = multiplication(r, r);
	printf("Racine carree (arrondie) de \'%s\':%s\n",argv[2], r);
	printf("Verification: %s\n", check);
	free(r);
	free(check);
	r = racine_carree(argv[2], atoi(argv[3]),0);
	check = multiplication(r, r);
	printf("Racine carree de \'%s\':%s\n",argv[2], r);
	printf("Verification: %s\n", check);
	free(r);
	free(check);*/
	printf("%Lf\n", sqrtl(strtold(argv[1], NULL)));
	return 0;
}
