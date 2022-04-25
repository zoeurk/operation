#ifndef OPERATION_H
#define OPERATION_H

int strtype(void *str);
void *allocation(void **ptr, size_t members, unsigned long int size);
void *reallocation(void **ptr, unsigned long int size);
int equal(void *num1, void *num2);
void *addition(void *num1, void *num2);
void *soustraction(void *num1, void *num2);
void *multiplication(void *num1, void *num2);
void *division(void *num1, void *num2, unsigned long int virgule);
void *modulo(void *num1, void *num2);
#endif
