principal:
	g++ src/main.cpp -o bin/main -g -O2 -Wall -Iinclude -std=c++11
	@	 echo ">> Compilación terminada."

clean: 
	rm bin/main
	@   echo ">> Datos de compilación borrados."
