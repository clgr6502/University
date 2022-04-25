Creazione libreria statica:  
&ensp; ar rvs libtokenizer.a tokenizer_lib.o  

Creazione libreria dinamica:  
&ensp; gcc tokenizer_lib.c -c -fPIC  
&ensp; gcc -shared tokenizer_lib.o

Compilazione:  
&ensp; gcc tokenizer_main.c -L . -ltokenizer
