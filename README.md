#operation  
Petite librairie de calcule mathematique.  
La librairie est libre d'utilisation, de modification et de (re)distribution  
n'oubliez par de faire un:  

Pour installer la librairie:  
	aclocal  
	autoreconf --install  
	./configure --prefix=/usr --exec-prefix=/usr  
	make  
	make install (en super utilisateur)  
  
Pour l'exemple: 
patch pour ne pas utiliser la librairie <math.h>  
patch -i math.patch main.c
