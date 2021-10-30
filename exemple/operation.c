#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"
void *allocation(void **ptr, unsigned long int members, unsigned long int size){
	if(members == (unsigned long int)~0){
		fprintf(stderr,"Taille de la chaine trop longue pour le systeme.\n");
		exit(EXIT_FAILURE);
	}
	if((*ptr = calloc(members, size)) == NULL){
		perror("calloc()");
		exit(EXIT_FAILURE);
	}
	return *ptr;
}
void *reallocation(void **ptr, unsigned long int size){
	char *buf;
	unsigned long int i = 0, sz = 0;
	if(size == (unsigned long int)~0){
		fprintf(stderr,"Taille de la chaine trop longue pour le systeme.\n");
		free(*ptr);
		exit(EXIT_FAILURE);
	}
	if(size < strlen(*ptr) || size + 1 < size){
		fprintf(stderr,
			"Erreur interne:\n\tLe nombre actuel >= Au nouveu nombre\n");
		fprintf(stderr,
			"Erreur possible:\n\tLe nombre est trop longue pour le systeme.");
		free(*ptr);
		exit(EXIT_FAILURE);
	}
	if((*ptr = realloc(*ptr, size+1)) == NULL){
		perror("realloc()");
		exit(EXIT_FAILURE);
	}
	buf = (*ptr)+strlen(*ptr);
	sz = strlen(*ptr);
	for(i = 0; i <= sz; i++){
		buf[i] = 0;
	}
	return (*ptr)+strlen(*ptr);
}
int equal(void *num1, void *num2){
	char *n1 = num1, *n2 = num2,
		*dot1, *dot2,
		*val1, *val2,
		v1[2] = { 0, 0 }, v2[2] = { 0, 0 },
		neg1 = 0, neg2 = 0;
	unsigned long int dot1_len = 0, dot2_len = 0,
				val1_len = 0, val2_len = 0;
	long long ii = 0;
	for(val1 = n1; *val1 == '-' || *val1 == '+'; val1++)
		if(*val1 == '-')
			neg1 = !neg1;
	for(val2 = n2; *val2 == '-' || *val2 == '+'; val2++)
		if(*val2 == '-')
			neg2 = !neg2;
	DOT_INIT;
	if(dot1)dot1++;
	if(dot2)dot2++;
	val1_len = strlen(n1);
	val2_len = strlen(n2);
	val1_len = (dot1_len) ? val1_len - dot1_len -1: val1_len; 
	val2_len = (dot2_len) ? val2_len - dot2_len -1: val2_len;
	if(neg1 && !neg2)
		return -1;
	if(neg2 && !neg1)
		return 1;
	while(*val1 == '0' && *(val1+1) != '.'){
		val1_len--;
		val1++;
	}
	while(*val2 == '0' && *(val2+1) != '.'){
		val2_len--;
		val2++;
	}
	if(val1[strlen(val1)-1] == '.')
		val1_len--;
	if(val2[strlen(val2)-1] == '.')
		val2_len--;
	if(*val1 == '0'){
		while(*val1 == '0' && *(val1+1) != 0){
			val1_len--;
			val1++;
		}
	}
	if(*val2 == '0'){
		while(*val2 == '0' && *(val2+1) != 0){
			val2_len--;
			val2++;
		}
	}
	if(val1_len > val2_len){
		if(neg1 && neg2){
			return -1;
		}
		return 1;
	}else	if(val1_len < val2_len){
			if(neg1 && neg2)
				return 1;
			else	return -1;
		}
	for(val1 = val1, val2 = val2, ii = 0;ii < (long long int)val1_len; ii++, val1++, val2++){
		v1[0] = *val1;
		v2[0] = *val2;
		v1[0] = atoi(v1);
		v2[0] = atoi(v2);
		if(v1[0] > v2[0]){
			if(neg1 && neg2)
				return -1;
			return 1;
		}else	if(v1[0] < v2[0]){
				if(neg1 && neg2)
					return 1;
				return -1;
			}
	}
	if(dot1 && dot2){
		for(dot1 = dot1, dot2 = dot2;
			*dot1 != 0 && *dot2 !=0;
			dot1++, dot2++
		){
			if(*dot1 > *dot2){
				if(*n1 == '-' && *n2 == '-')
					return -1;
				return 1;
			}
			if(*dot1 < *dot2){
				if(*n1 == '-' && *n2 == '-')
					return 1;
				return -1;
			}
		}
	}
	if((!dot1 || *dot1 == 0 )&& dot2 && *dot2 != 0){
		for(dot2 = dot2; *dot2 != 0; dot2++)
			if(*dot2 > '0'){
				if(*n1 == '-' && *n2 == '-')
					return 1;
				return -1;
			}
	}
	if((dot1 && *dot1 != 0) && (!dot2 || *dot2 == 0)){
		for(dot1 = dot1; *dot1 != 0; dot1++)
			if(*dot1 > '0'){
				if(*n1 == '-' && *n2 == '-')
					return -1;
				return 1;
			}
	}
	return 0;
}
void *addition(void *num1, void *num2){
	char *n1 = num1, *n2 = num2,
		*dot1, *dot2,
		*val1, *val2,
		v1[2] = { 0, 0 }, v2[2] = { 0, 0 },
		*buffer, *pbuf, *ret, *pret,
		*ptr1 = NULL, *ptr2= NULL,
		result = 0, retenue = 0, neg = 0, neg1 = 0, neg2 = 0, set = 0;
	unsigned long int dot1_len = 0, dot2_len = 0,
				val1_len = 0, val2_len = 0,
				buflen = 0, z = 1;
	long long int ii = 0, ij = 0;
	NEG;
	if(neg1 || neg2){
		if(neg1 && neg2)
			neg = 1;
		else
			if(neg1 && !neg2)
				return soustraction(n2,n1);
			else
				if(!neg1 && neg2)
					return soustraction(n1, n2);
	}
	ZERO;
	if(strlen(n1) == 0 && strlen(n2) == 0){
		ret = allocation((void **)&ret, 2, sizeof(char));
		*ret = '0';
		return ret;
	}
	DOT_SEARCH(dot1, dot2, dot1_len, dot2_len, val1, val2);
	val1_len = strlen(n1);
	val2_len = strlen(n2);
	val1_len = (dot1_len) ? val1_len - dot1_len -1: val1_len; 
	val2_len = (dot2_len) ? val2_len - dot2_len -1: val2_len;
	pbuf = allocation((void **)&buffer,BUFFER, sizeof(char));
	if(dot1 != NULL && dot1_len == 0)
		val1_len--;
	if(dot2 != NULL && dot2_len == 0)
		val2_len--;
	if(dot1 && dot2){
		if(dot1_len > dot2_len){
			ii = dot1_len;
			ij = dot2_len;
			ptr1 = &dot1[dot1_len-1];
			ptr2 = &dot2[dot2_len-1];
		}else{
			ii = dot2_len;
			ij = dot1_len;
			ptr1 = &dot2[dot2_len-1];
			ptr2 = &dot1[dot1_len-1];
		}
		for(ii = ii, ptr1 = ptr1; ii != ij && ii > 0; ii--, ptr1--){
			v1[0] = *ptr1;
			if(buflen + 1 >= BUFFER){
				z++;
				buflen = 0;
				pbuf = reallocation((void **)&buffer, BUFFER*z);
			}
			sprintf(pbuf,"%c", v1[0]);
			pbuf++;
			buflen++;
		}
		for(ii = ii, ptr1 = ptr1, ptr2 = ptr2; ii > 0; ii--, ptr1--, ptr2--){
			v1[0] = *ptr1;
			v2[0] = *ptr2;
			v1[0] = atoi(v1);
			v2[0] = atoi(v2);
			result = v1[0] + v2[0] + retenue;
			if(result >= 10){
				retenue = 1;
				result -= 10;
			}else	retenue = 0;
			if(buflen + 1 >= BUFFER){
				z++;
				buflen = 0;
				pbuf = reallocation((void **)&buffer, BUFFER*z);
			}
			sprintf(pbuf, "%i", result);
			pbuf++;
			buflen++;
		}
	}else{
		if(dot1 && !dot2){
			ii = dot1_len;
			ptr1 = &dot1[dot1_len-1];
		}else{
			if(!dot1 && dot2){
				ii = dot2_len;
				ptr1 = &dot2[dot2_len-1];
			}
		}
		for(ii = ii, ptr1 = ptr1; ii > 0;ii--, ptr1--){
			if(buflen + 1 >= BUFFER){
				z++;
				buflen = 0;
				pbuf = reallocation((void **)&buffer, BUFFER*z);
			}
			sprintf(pbuf,"%c", *ptr1);
			pbuf++;
			buflen++;
		}
	}
	if(dot1_len || dot2_len){
		if(buflen + 1 >= BUFFER){
			z++;
			buflen = 0;
			pbuf = reallocation((void **)&buffer, BUFFER*z);
		}
		sprintf(pbuf,".");
		pbuf++;
		buflen++;
	}
	for(ptr1 = val1, ptr2 = val2, ii = val1_len, ij = val2_len;
		ii > 0 && ij > 0; ii--, ij--, ptr1--, ptr2--){
		v1[0] = *ptr1;
		v2[0] = *ptr2;
		v1[0] = atoi(v1);
		v2[0] = atoi(v2);
		result = v1[0] + v2[0] + retenue;
		if(result >= 10){
			retenue = 1;
			result -= 10;
		}else	retenue = 0;
		if(buflen + 1 >= BUFFER){
			z++;
			buflen = 0;
			pbuf = reallocation((void **)&buffer, BUFFER*z);
		}
		sprintf(pbuf,"%i", result);
		pbuf++;
		buflen++;
	}
	if(ii || ij){
		if(ij){
			ii = ij;
			ptr1 = ptr2;
		}
		for(ii = ii, ptr1 = ptr1; ii > 0; ii--,ptr1--){
			v1[0] = *ptr1;
			v1[0] = atoi(v1);
			result = v1[0] + retenue;
			if(result >= 10){
				retenue = 1;
				result -= 10;
			}else	retenue = 0;
			if(buflen + 1 >= BUFFER){
				z++;
				buflen++;
				pbuf = reallocation((void **)&buffer, BUFFER*z);
			}
			sprintf(pbuf,"%i", result);
			pbuf++;
			buflen++;
		}
	}
	if(retenue){
		if(buflen + 1 >= BUFFER){
			z++;
			buflen = 0;
			pbuf = reallocation((void **)&buffer, BUFFER*z);
		}
		sprintf(pbuf,"%i", retenue);
		pbuf++;
		buflen++;
	}
	pbuf = buffer;
	ii = 0;
	while(*pbuf == '0'){
		if(*(pbuf+1) == 0)
			break;
		set = 1;
		pbuf++;
	}
	ij = strlen(buffer);
	pret = allocation((void **)&ret, ij+1, sizeof(char));
	for(ii = ij-1, pret = pret; ii >= 0; ii--, pret++)
		*pret = buffer[ii];
	free(buffer);
	buffer = ret;
	set = 0;
	if(dot1 || dot2){
		while(*buffer == '0'&& *(buffer+1) == '0'){
			*buffer = 0;
			buffer++;
			set = 1;
		}
		if(set){
			pbuf = allocation((void **)&pbuf, strlen(buffer)+1, sizeof(char));
			strcpy(pbuf, buffer);
			memset(ret, 0, strlen(ret));
			strcpy(ret, pbuf);
			free(pbuf);
		}
	}
	pret = &ret[strlen(ret)-1];
	if(dot1 || dot2){
		while(*pret == '0' || *pret == '.'){
				*pret = 0;
				pret--;
		}
	}
	if(neg){
		if((ret = realloc(ret,strlen(ret)+2)) == NULL){
			perror("realloc()");
			exit(EXIT_FAILURE);
		}
		for(pret = &ret[strlen(ret)+1], ii = strlen(ret);pret != ret; pret--, ii--){
			*pret = ret[ii];
		}
		*ret = '-';
	}
	return ret;
}
void *soustraction(void *num1, void *num2){
	char *n1 = num1, *n2 = num2,
		*dot1, *dot2,
		*val1, *val2,
		v1[2] = { 0, 0 }, v2[2] = { 0, 0 },
		*buffer, *pbuf, *ret, *pret,
		*ptr1 = NULL, *ptr2= NULL,
		result = 0, retenue = 0, neg = 0, neg1 = 0, neg2 = 0;
	unsigned long int dot1_len = 0, dot2_len = 0,
				val1_len = 0, val2_len = 0,
				buflen = 0, z = 1;
	long long int ii = 0, ij = 0;
	NEG;
	if(neg1 || neg2){
		if(neg1 && neg2){
			return soustraction(n2, n1);
		}else{
			if(neg1 && !neg2){
				buffer = addition(n2, n1);
				buffer = realloc(buffer, strlen(buffer)+2);
				for(pbuf = &buffer[strlen(buffer)+1], ii = strlen(buffer); buffer != pbuf; pbuf--, ii--)
					*pbuf = buffer[ii];
				*buffer = '-';
				return buffer;
			}else{
				if(!neg1 && neg2)
					return addition(n1, n2);
			}
		}
	}
	switch(equal(num1,num2)){
		case 0:
			pbuf = allocation((void **)&buffer, 2, sizeof(char));
			*pbuf = '0';
			return pbuf;
		case -1:
			neg = 1;
			n1 = num2;
			n2 = num1;
			goto next;
		case 1:
			n1 = num1;
			n2 = num2;
			next:
			ZERO;
			DOT_SEARCH(dot1, dot2, dot1_len, dot2_len, val1, val2);
			val1_len = strlen(n1);
			val2_len = strlen(n2);
			val1_len = (dot1_len) ? val1_len - dot1_len: val1_len; 
			val2_len = (dot2_len) ? val2_len - dot2_len: val2_len;
			break;
		default: printf("ERROR\n");
			exit(0);
	}
	//printf("%lu::%lu\n", val1_len, val2_len);
	//exit(0);
	pbuf = allocation((void **)&buffer,BUFFER, sizeof(char));
	if(dot1 != NULL && dot1_len == 0)
		val1_len--;
	if(dot2 != NULL && dot2_len == 0)
		val2_len--;
	if(dot1_len > dot2_len){
		for(ii = (long long int)dot1_len; ii >= 0 && (unsigned long int)ii != dot2_len; ii--){
			if(buflen + 1 >= BUFFER){
				z++;
				buflen = 0;
				pbuf = reallocation((void **)&buffer,z*BUFFER);
			}
			sprintf(pbuf, "%c", dot1[ii-1]);
			pbuf++;
			buflen++;
		}
		for(ii = ii, ij = dot2_len; ii > 0 && ij > 0; ii--, ij--){
			v1[0] = dot1[ii-1];
			v2[0] = dot2[ij-1];
			v1[0] = atoi(v1);
			v2[0] = atoi(v2);
			if(v1[0] - retenue >= v2[0]){
				result = v1[0] - v2[0] - retenue;
				retenue = 0;
			}else{
				result = 10+v1[0] - v2[0] - retenue;
				retenue = 1;
			}
			if(buflen + 1 >= BUFFER){
				z++;
				buflen = 0;
				pbuf = reallocation((void **)&buffer,z*BUFFER);
			}
			sprintf(pbuf, "%i", result);
			pbuf++;
			buflen++;
		}
	}
	if(dot2_len > dot1_len){
		for(ii = dot2_len; ii > 0 && ii != (long long int)dot1_len; ii--){
			v1[0] = dot2[ii-1];
			v1[0] = atoi(v1);
			if(v1[0] - retenue > 0){
				result = 10 - v1[0] - retenue;
				retenue = 1;
			}else{
				retenue = 0;
			}
			if(buflen + 1 >= BUFFER){
				z++;
				buflen = 0;
				pbuf = reallocation((void **)&buffer,z*BUFFER);
			}
			sprintf(pbuf, "%i", result);
			pbuf++;
			buflen++;
		}
		for(ii = ii, ij = dot1_len; ii > 0 && ij > 0; ii--, ij--){
			v1[0] = dot1[ii-1];
			v2[0] = dot2[ij-1];
			v1[0] = atoi(v1);
			v2[0] = atoi(v2);
			if(v1[0] - retenue >= v2[0]){
				result = v1[0] - v2[0] - retenue;
				retenue = 0;
			}else{
				result = 10+v1[0] - v2[0] - retenue;
				retenue = 1;
			}
			if(buflen + 1 >= BUFFER){
				z++;
				buflen = 0;
				pbuf = reallocation((void **)&buffer,z*BUFFER);
			}
			sprintf(pbuf, "%i", result);
			pbuf++;
			buflen++;
		}
	}else{
		if(dot1_len == dot2_len){
			for(ii = dot1_len; ii > 0 && (unsigned long int)ii != dot2_len; ii--){
				v1[0] = dot1[ii-1];
				v1[0] = atoi(v1);
				if(v1[0] - retenue >= 0){
					result = 10 - v1[0] - retenue;
				}else{
					retenue = 0;
				}
				if(buflen + 1 >= BUFFER){
					z++;
					buflen = 0;
					pbuf = reallocation((void **)&buffer,z*BUFFER);
				}
				sprintf(pbuf, "%i", result);
				pbuf++;
				buflen++;
			}
			for(ii = ii, ij = dot2_len; ii > 0 && ij > 0; ii--, ij--){
				v1[0] = dot1[ii-1];
				v2[0] = dot2[ij-1];
				v1[0] = atoi(v1);
				v2[0] = atoi(v2);
				if(v1[0] - retenue >= v2[0]){
					result = v1[0] - v2[0] - retenue;
					retenue = 0;
				}else{
					result = 10+v1[0] - v2[0] - retenue;
					retenue = 1;
				}
				if(buflen + 1 >= BUFFER){
					z++;
					buflen = 0;
					pbuf = reallocation((void **)&buffer,z*BUFFER);
				}
				sprintf(pbuf, "%i", result);
				pbuf++;
				buflen++;
			}
		}
	}
	if(dot1_len || dot2_len){
		if(buflen + 1 >= BUFFER){
			z++;
			buflen = 0;
			pbuf = reallocation((void **)&buffer,z*BUFFER);
		}
		sprintf(pbuf, ".");
		pbuf++;
		buflen++;
		//printf("%s\n", buffer);
	}
	//fprintf(stderr,"===>%s::%s\n", (char *)n1, (char *)n2);
	//len = val2_len - val1_len;
	//printf("%lu::%lu::%lli\n", val1_len, val2_len, len);
	//exit(0);
	for(ptr1 = val1, ptr2 = val2, ii = val1_len - (neg1 == 1), ij = val2_len - (dot2_len > 0);
		ii > 0 && ij > 0; /*&&
		*ptr1 != 0 && 
		*ptr2 != 0;*/
		ii--, ij--, ptr1--, ptr2--
	){
		//printf("++++++++++++++++++++++\n");
		/*fprintf(stderr, "%s::%s\n",
			ptr1,
			ptr2
		);*/
		//printf("===>%lli::%lli\n", ii, ij);
		//exit(0);
		v1[0] = *ptr1;
		v2[0] = *ptr2 ;
		/*if(*(ptr2 +1) == 0 ){
			fprintf(stderr,"ERROR::%lli\n", ij);
		}*/
		v1[0] = atoi(v1);
		v2[0] = atoi(v2);
		if(v1[0] - retenue >= v2[0]){
			result = v1[0] - v2[0] - retenue;
			retenue = 0;
		}else{
			result = 10+v1[0] - v2[0] - retenue;
			retenue = 1;
		}
		if(buflen + 1 >= BUFFER){
			z++;
			buflen = 0;
			pbuf = reallocation((void **)&buffer,z*BUFFER);
		}
		sprintf(pbuf, "%i", result);
		pbuf++;
		buflen++;
	}
	//printf("==>%lli::%lli\n", ii, ij);
	//exit(0);
	for(ii = ii; ii > 0; ii--, ptr1--){
		if((ptr1 +1) == n1)break;
		v1[0] = *ptr1;
		v1[0] = atoi(v1);
		if(v1[0] - retenue >= 0){
			result = v1[0] - retenue;
			retenue = 0;
		}else{
			result = 10 - (v1[0] + retenue);
			if(result == 10)
				result = 0;
			retenue = 1;
		}
		if(buflen + 1 >= BUFFER){
			z++;
			buflen = 0;
			pbuf = reallocation((void **)&buffer,z*BUFFER);
		}
		sprintf(pbuf, "%i", result);
		pbuf++;
		buflen++;
	}
	for(ij = ij-1, ptr2 = ptr2; ij > 0; ij--, ptr2++){
		v2[0] = *ptr2;
		v2[0] = atoi(v2);
		if(v2[0] - retenue < 0){
			result = v2[0] - retenue;
			retenue = 0;
		}else{
			result = 10 - v2[0] - retenue;
			retenue = 1;
		}
		if(buflen + 1 >= BUFFER){
			z++;
			buflen = 0;
			pbuf = reallocation((void **)&buffer,z*BUFFER);
		}
		sprintf(pbuf, "%i", result);
		pbuf++;
		buflen++;
	}
	pbuf = (*(pbuf) == '.') ? pbuf +1: pbuf;
	while(buffer[strlen(buffer)-1] == '0'&& buffer[strlen(buffer)-2] != '.'){
		buffer[strlen(buffer)-1] = 0;
		pbuf = &buffer[strlen(buffer)-2];

	}
	pbuf--;
	buflen--;
	if(buflen + 1 >= BUFFER){
		z++;
		buflen = 0;
		pbuf = reallocation((void **)&buffer,z*BUFFER);
	}
	pbuf++;
	buflen++;
	if(neg){
		/*BUG POSSIBLE*/
		if(buflen + 1 >= BUFFER){
			z++;
			pbuf = reallocation((void **)&buffer,z*BUFFER);
		}
		pbuf = buffer+strlen(buffer);
		sprintf(pbuf,"-");
		pbuf++;
		buflen++;
	}
	pbuf = buffer;
	ij = strlen(pbuf);
	pret = allocation((void **)&ret, ij+1, sizeof(char));
	for(ii = ij-1, pret = pret; ii >= 0; ii--, pret++)
		*pret = pbuf[ii];
	if(equal("0",ret) == 0){
		strcpy(ret,"0");
	}
	while((dot1_len|| dot2_len) && (ret[strlen(ret)-1] == '0' || ret[strlen(ret)-1] == '.'))
		ret[strlen(ret)-1] = 0;
	free(pbuf);
	return ret;
}
void *multiplication(void *num1, void *num2){
	char *n1 = num1, *n2 = num2,
		*dot1, *dot2,
		v1[2] = { 0, 0 }, v2[2] = { 0, 0 }, temp[3] = { 0, 0, 0},
		*buffer,
		*resultat = NULL, 
		*result = NULL, *presult, *total = NULL,*pbuf,
		retenue = 0, neg = 0, neg1 = 0, neg2 = 0, z = 0;
	unsigned long int dot1_len = 0, dot2_len = 0,
				buflen = 0, iz = 1, zero = 0;
	long long int ii = 0, ij = 0,ii_ = 0,x = 0;
	NEG;
	NEG_TEST;
	if(equal("0", n1) == 0 || equal("0", n2) == 0){
		resultat = allocation((void **)&resultat, 2, sizeof(char));
		*resultat = '0';
		return resultat;
	}
	ZERO;
	dot1 = strchr(n1, '.');
	dot2 = strchr(n2, '.');
	dot1_len = (dot1) ? strlen(dot1) -1: 0;
	dot2_len = (dot2) ? strlen(dot2) -1: 0;
	pbuf = allocation((void **)&resultat, BUFFER, sizeof(char));
	for(n1 = n1,
		ii = strlen(n1);
		ii > 0; ii--,
		zero += (ii > 0 && n1[ii-1] != '.')
	){
		if(n1[ii-1] == '.')continue;
		v1[0] = n1[ii-1];
		v1[0] = atoi(v1);
		if(zero){
			for(x = 0; (unsigned long int)x < zero; x++){
				if(buflen+1 >= BUFFER){
					iz++;
					buflen = 0;
					pbuf = reallocation((void **)&resultat, BUFFER*iz);
				}
				sprintf(pbuf,"0");
				pbuf++;
				buflen++;
			}
		}
		for(n2 = n2, ij = strlen(n2); ij > 0;ij--){
			if(n2[ij-1] == '.')continue;
			v2[0] = n2[ij-1];
			v2[0] = atoi(v2);
			z = retenue/10;
			retenue = 0;
			if(v1[0]*v2[0] + z >= 10 && ii-1 > 0 && ij-1 > 0){
				do{
					retenue += 10;
				}while(v1[0]*v2[0]+ z - retenue >= 10);
				if(buflen+1 >= BUFFER){
					iz++;
					buflen = 0;
					pbuf = reallocation((void **)&resultat, BUFFER*iz);
				}
				sprintf(pbuf,"%i", v2[0]*v1[0]+z-retenue);
				pbuf++;
				buflen++;
			}else{
				if(ij-1 == 0 && v1[0]*v2[0]+ z - retenue >= 10){
					if(buflen+2 >= BUFFER){
						iz++;
						buflen = 0;
						pbuf = reallocation((void **)&resultat, BUFFER*iz+1);
						pbuf = &resultat[strlen(resultat)];
					}
					sprintf(pbuf,"%i", v2[0]*v1[0]+z-retenue);
					temp[0] = *(pbuf+1);
					temp[1] = *pbuf;
					*pbuf = temp[0];
					*(pbuf+1) = temp[1];
					result = allocation((void **)&result, strlen(resultat)+1, sizeof(char));
					for(presult = result,ii_ = strlen(resultat); ii_ > 0; ii_--,presult++)
						*presult = resultat[ii_-1];
					memset(resultat, 0, strlen(resultat));
					pbuf = reallocation((void **)&resultat,BUFFER);
					pbuf = resultat;
					if(total == NULL)
						total = result;
					else{
						presult = addition(total,result);
						free(total);
						free(result);
						total = presult;
					}
					iz = 1;
					buflen = 0;
				}else{
					if(v1[0]*v2[0] + z >= 10){
						do{
							retenue += 10;
						}while(v1[0]*v2[0]+ z - retenue >= 10);
						if(buflen+1 >= BUFFER){
							iz++;
							buflen = 0;
							pbuf = reallocation((void **)&resultat, BUFFER*iz);
						}
						sprintf(pbuf,"%i", v2[0]*v1[0]+z-retenue);
						pbuf++;
						buflen++;
					}else{
						if(ij - 1 > 0){
							if(buflen+1 >= BUFFER){
								iz++;
								buflen = 0;
								pbuf = reallocation((void **)&resultat, BUFFER*iz);
							}
							sprintf(pbuf,"%i", v2[0]*v1[0]+z-retenue);
							pbuf++;
							buflen++;
						}else{
							if(buflen+1 >= BUFFER){
								iz++;
								buflen = 0;
								pbuf = reallocation((void **)&resultat, BUFFER*iz);
							}
							sprintf(pbuf,"%i", v2[0]*v1[0]+z-retenue);
							pbuf++;
							buflen++;
							result = allocation((void **)&result, strlen(resultat)+1, sizeof(char));
							for(presult = result,ii_ = strlen(resultat); ii_ > 0; ii_--,presult++){
								*presult = resultat[ii_-1];
							}
							if(total == NULL){
								total = result;
							}else{
								presult = addition(total, result);
								free(result);
								free(total);
								total = presult;
							}
							pbuf = resultat;
							memset(resultat,0,BUFFER*iz);
							iz = 1;
							pbuf = reallocation((void **)&resultat, BUFFER);
						}
					}
				}
			}
		}
	}
	if(dot1_len + dot2_len > 0){
		pbuf = allocation((void **)&buffer, strlen(total)+2, sizeof(char));
		strcpy(pbuf, total);
		for(pbuf = &buffer[strlen(buffer)-1], ii = 0; (unsigned long int)ii != dot1_len + dot2_len;pbuf--, ii++){
			*(pbuf+1) = *(pbuf);
		}
		*(pbuf+1) = '.';
		free(total);
		free(resultat);
		for(pbuf = &buffer[strlen(buffer)-1];*pbuf == '0'; pbuf--)
			*pbuf = 0;
		pbuf = strchr(buffer, '.');
		if(pbuf && *(pbuf + 1) == 0)
			*pbuf = 0;
		if(*buffer == '.'){
			total = allocation((void **)&total,strlen(buffer)+2, sizeof(char));
			*total = '0';
			strcpy(&total[1], buffer);
			free(buffer);
			buffer = total;
		}
		if(neg){
			VALEUR_NEGATIVE(buffer, pbuf, ii);
		}
		return buffer;
	}
	if(neg){
		VALEUR_NEGATIVE(total, pbuf, ii);
	}
	free(resultat);
	return total;
}
void *division(void *num1, void *num2, unsigned long int virgule){
	char *n1 = num1, *n2 = num2,
		*quotient = NULL, *dividende = NULL, *diviseur = NULL, *reste = NULL, *preste,
		*temp = NULL, *temp_ = NULL, t[2] = {0, 0}, *result = NULL, *pr, point = 0,
		neg = 0, neg1 = 0, neg2 = 0;
	unsigned long int buflen = 0, qbuf = 1, len = 0, virgule_ = 0, zero = 0, nreste = 0, qreste = 1;
	long long int ii = 0;
	int x;
	if(equal(n2,"0") == 0){
		fprintf(stderr, "Erreur: Division par 0\n");
		exit(EXIT_FAILURE);
	}
	if(equal(n1,"0") == 0){
		 quotient = allocation((void **)&quotient,2,sizeof(char));
		*quotient = '0';
		return quotient;
	}
	NEG;
	NEG_TEST;
	//printf("%i\n", neg);
	ZERO;
	diviseur = allocation((void **)&diviseur, strlen(n2)+1, sizeof(char));
	dividende = allocation((void **)&dividende, strlen(n1)+1, sizeof(char));
	memcpy(diviseur, n2, strlen(n2));
	memcpy(dividende, n1, strlen(n1));
	do{
		if((n2 = strchr(diviseur,'.')) == NULL  && (n1 = strchr(dividende, '.')) == NULL)
				break;
		temp = multiplication(diviseur, "10");
		free(diviseur);
		diviseur = temp;
		temp = multiplication(dividende, "10");
		free(dividende);
		dividende = temp;
	}while(1);
	preste = allocation((void **)&reste, BUFFER, sizeof(char));
	pr = allocation((void **)&result, BUFFER, sizeof(char));
	len = strlen(dividende)-1;
	do{
		if(nreste +1 >= BUFFER){
			qreste++;
			nreste = 0;
			preste = reallocation((void **)&reste, qreste*BUFFER);
		}
		*preste = dividende[ii];
		preste[1] = 0;
		preste++;
		nreste++;
		ii++;
	}while((unsigned long int)ii < strlen(dividende) && equal(reste, diviseur) < 0);
	while(equal(reste, diviseur) < 0 && virgule_ <= virgule+1){
		temp = multiplication(reste, "10");
		free(reste);
		reste = temp;
		if(point == 0){
			if(buflen + 1 >= BUFFER){
				buflen = 0;
				qbuf++;
				pr = reallocation((void **)&result, qbuf * BUFFER);
			}
			*pr = '0';
			pr++;
			buflen++;
			if(buflen + 1 >= BUFFER){
				buflen = 0;
				qbuf++;
				pr = reallocation((void **)&result, qbuf * BUFFER);
			}
			*pr = '.';
			pr++;
			buflen++;
		}else{
			if(buflen + 1 >= BUFFER){
				buflen = 0;
				qbuf++;
				pr = reallocation((void **)&result, qbuf * BUFFER);
			}
			*pr = '0';
			pr++;
			buflen++;
			virgule_++;
		}
		point = 1;
		zero++;
	}
	for(x = 9; x >= 0;x--){
		sprintf(t,"%i", x);
		temp = multiplication(t, diviseur);
		temp_ = soustraction(reste, temp);
		if(equal(temp_,"0") >= 0){
			free(reste);
			free(temp);
			reste = temp_;
			break;
		}
		free(temp);
		free(temp_);
	}
	if(buflen + 1 >= BUFFER){
		buflen = 0;
		qbuf++;
		pr = reallocation((void **)&result, qbuf * BUFFER);
	}
	*pr = *t;
	pr++;
	buflen++;
	while(((unsigned long int)ii <= len || equal(reste,"0") != 0)){
		temp = multiplication(reste, "10");
		free(reste);
		reste = temp;
		if((unsigned long int)ii <= len){
			t[0] = dividende[ii];
			t[1] = 0;
			temp = addition(reste, t);
			free(reste);
			reste = temp;
		}else{
			if(point == 0){
				point = 1;
				if(buflen + 1 >= BUFFER){
					buflen = 0;
					qbuf++;
					pr = reallocation((void **)&result, qbuf * BUFFER);
				}
				*pr = '.';
				pr++;
				buflen++;
			}else
				virgule_++;
			if(virgule_ >= virgule+1)break;
		}
		for(x = 9; x >= 0; x--){
			sprintf(t, "%i", x);
			temp = multiplication(t, diviseur);
			temp_ = soustraction(reste, temp);
			if(equal(temp_,"0") >= 0){
				free(reste);
				free(temp);
				reste = temp_;
				break;
			}else{
				free(temp);
				free(temp_);
			}
		}
		if(buflen + 1 >= BUFFER){
			buflen = 0;
			qbuf++;
			pr = reallocation((void **)&result, qbuf * BUFFER);
		}
		*pr = *t;
		pr++;
		buflen++;
		ii++;
	}
	//printf("%s\n", result);
	if(neg){
		VALEUR_NEGATIVE(result, pr, ii);
	}
	//printf("%s\n", result);
	if((temp = strchr(result, '.')) != NULL){
		temp_ = &result[strlen(result)-1];
		if(virgule == 0){
			if(equal(temp_, "5")){
				if(!neg)
					temp_ = addition(result ,"1");
				else	temp_ = soustraction(result, "1");
				//temp_ = addition(result,"1");
				free(result);
				result = temp_;
				temp = strchr(result,'.');
				//exit(0);
				if(temp)
					*temp = 0;
			}
		}else{
			//printf("ici\n");
			//if(x == 0){
			//printf("==>%s::%i:%i\n", result, x, neg);
				if(strlen(strchr(result,'.') +1) >= virgule){
					//printf("%lu\n", virgule_);
					//printf("la\n");
					temp = allocation((void **)&temp, strlen(result)+1, sizeof(char));
					if(equal(temp_, "5") >= 0){
						//printf("OK\n");
						for(len = 0, temp_ = temp_;temp_ != result+1; temp_--){
							if(temp_ == &result[strlen(result)-1]){
								strcat(temp, "0.");
							}else{	if(temp_ == result+2){
									strcat(temp, "1");
								}else{	strcat(temp, "0");
								}
								//virgule_++;
							}
						}
						//printf("===>%s::%s\n",result, temp);
						free(reste);
						if(!neg)
							reste = addition(result ,temp);
						else	reste = soustraction(result, temp);
						free(result);
						result = reste;
						reste = temp;
						//if(virgule_ >= virgule -1){
						//	printf("==>%s::%lu;%lu\n", result, virgule_, virgule);
							//exit(0);
						//}
						//if(strlen(result) > 0)
							result[strlen(result)-1] = 0;
					}else	free(temp);
				}
			}
		//}
	}
	if((n1 = strchr(result,'.')) != NULL)
		for(n2 = &result[strlen(result) - 1]; *n2 == '.' || *n2 == '0' ; *n2 = 0, n2--);;
	//printf("%s\n", result);
	if(equal(result,"0") == 0 || equal(result,"-0") == 0){
		*result = '0';
		result[1] = 0;
	}
	free(reste);
	free(dividende);
	free(diviseur);
	return result;
}

