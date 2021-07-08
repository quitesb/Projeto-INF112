all:
	echo "alguma coisa"

compilar: main.cpp Arquivo.h Arquivo.cpp Pessoa.h Medico.h Medico.cpp Paciente.h Paciente.cpp Status.h Status.cpp Leito.h Leito.cpp
	g++ main.cpp Arquivo.cpp Medico.cpp Paciente.cpp Status.cpp Leito.cpp -o programa -pthread

executar_w:
	./programa.exe

executar_l:
	./programa

clear_w:
	del programa.exe

clear_l:
	rm programa	
	

