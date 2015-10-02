Natal, 24/setembro/2015

# Identificação #
	
	* Instituição: Universidade Federal do Rio Grande do Norte (UFRN)
	* Disciplina:  Linguagem de Programação 1 (IMD0030)

	* Aluno:       Vinícius Campos Tinoco Ribeiro
	* Matrícula:   2014025284

	* Aluno:       Vitor Rodrigues Greati
	* Matrícula:   2015034967

# Introdução #

O projeto consiste no desenvolvimento do jogo Game of Life, idealizado 
pelo matemático Horton Conway em 1970. A ideia do jogo é simular a vida
de um grupo celular que se perpetua de acordo com algumas regras de 
sobrevivência.

# Regras #

	* Regra 1 - Se uma célula está viva, mas o número de vizinhos vivos é 
	menor ou igual a um, na próxima geração a célula morrerá de solidão.

	* Regra 2 - Se uma célula está viva e tem quatro ou mais vizinhos vivos, 
	na próxima geração a célula morrerá sufocada devido a supepopulação.

	* Regra 3 - Uma célula viv com dois ou três vizinhos, na próxima geração permanecerá viva.

	* Regra 4 - Se uma celula está morta, então na próxima geração ela 
	se tornará viva se possuir exatamente três vizinhos vivos. Se possuir uma quantidade de 
	vizinhos vivos diferente de três, a célula permanecerá morta.
	
	* regra 5 - Todos os nascimentos e mortes acontecem exatamente ao mesmo tempo, portanto
	células que estão morrendo podem ajudar outras a nascer, mas não podem prevenir a
	morte de outros pela redução da superpopulação; da mesma forma, células que estão
	nascendo não irão preservar ou matar células vivas na geração anterior.

# Estrutura #

O projeto está sub-dividido em 6 pastas:
	
	* bin: Possui os executáveis do projeto
	* data: Possui arquivos que servem como entrada para a execução do programa
	* documentation: Possui toda a documentação do projeto com doxygen
	* game: Possui as pastas relacionadas a parte gráfica do jogo
		* bin: Possui os executáveis do projeto(GRÁFICO)
		* img: Possui as imagens utilizadas no jogo(GRÁFICO)
		* lib: Possui os objetos do jogo(GRÁFICO)
		* src: Possui o driver do projeto(GRÁFICO)
	* include: Possui o arquivo de cabeçalho da classe GameOfLife.
	* src: Possui o arquivo de implementação dos métodos da classe GameOfLife e o driver que é o teste do projeto. 
	* saida: Possui os arquivos de histórico das gerações

# Guia de utilização(MODO TEXTO) - Linux #
	
	1 - Descompactar o projeto na pasta de preferência
	1 - Abra o terminal
	2 - Desloque-se até pasta do projeto, conwaygameoflife.
	3 - Digite os seguintes comandos de compilação: 
		g++ -Wall -std=c++11 -I include/ src/driver.cpp -o bin/<nome_do_executavel>
		Obs: <nome_do_executavel> é o nome que deseja por para ser o executavel do projeto
	4 - Para executar, tem-se duas maneiras:
		./bin/<nome_executavel> /data/<arquivo_de_entrada>
		- O comando acima apenas executa o programa com a entrada de arquivos.
		ou 
		./bin/<nome_executavel> /data/<arquivo_de_entrada> /saida/<arquivo_de_saida>
		- O comando acima apenas executa o programa com a entrada de arquivos e salva na pasta de saida

		Obs: <arquivo_de_entrada> é um arquivo de texto com uma entrada da matriz
			 <arquivo_de_saida> será o arquivo que armazenará o histórico de gerações

# Guia de utilização(MODO GRÁFICO) - Linux #
	
	1 - Descompactar o projeto na pasta de preferência
	1 - Abra o terminal
	2 - Desloque-se até pasta do projeto, conwaygameoflife.
	3 - Digite os seguintes comandos de compilação: 
		cd game/lib
		g++ -I ../../include/ ../src/driver.cpp -c -std=c++11
		g++ driver.o -o ../bin/<nome_do_executavel> -lsfml-graphics -lsfml-window -lsfml-system -std=c++11 -g
		cd ../bin
		Obs: <nome_do_executavel> é o nome que deseja por para ser o executavel do projeto
	4 - Para executar, tem-se duas maneiras:
		./<nome_executavel> ../../data/<arquivo_de_entrada>
		- O comando acima apenas executa o programa com a entrada de arquivos.
		ou 
		./bin/<nome_executavel> ../../data/<arquivo_de_entrada> ../../saida/<arquivo_de_saida>
		- O comando acima apenas executa o programa com a entrada de arquivos e salva na pasta de saida

		Obs: <arquivo_de_entrada> é um arquivo de texto com uma entrada da matriz
			 <arquivo_de_saida> será o arquivo que armazenará o histórico de gerações

# Erros tratados
	* Quando não se informa o arquivo de entrada ou um caminho inválido para ele
	* Quando não se informa um caminho válido para o arquivo de saída

# Resultado no valgrind(MODO TEXTO) #

	* O projeto passou no valgrind sem vazamento de memória,
	resposta no terminal ao fim de uma execução: 

	y==2595== 
	==2595== HEAP SUMMARY:
	==2595==     in use at exit: 0 bytes in 0 blocks
	==2595==   total heap usage: 151 allocs, 151 frees, 13,471 bytes allocated
	==2595== 
	==2595== All heap blocks were freed -- no leaks are possible
	==2595== 
	==2595== For counts of detected and suppressed errors, rerun with: -v
	==2595== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
