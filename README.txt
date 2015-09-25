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
	
	* bin: Possue os executáveis do projeto
	* data: Possue arquivos que servem como entrada para a execução do programa
	* documentation: Possue toda a documentação do projeto com doxygen
	* include: Possue o arquivo de cabeçalho da classe GameOfLife.
	* src: Possue o arquivo de implementação dos métodos da classe GameOfLife e o driver que é o teste do projeto. 
	* saida: Possue os arquivos de histórico das gerações

# Guia de utilização - Linux #
	
	1 - Descompactar o projeto na pasta de preferência
	1 - Abra o terminal
	2 - Desloque-se até pasta do projeto, conwaygameoflife.
	3 - Digite o seguinte comando de compilação: 
		g++ -Wall -std=c++11 -I include/ src/*.cpp -o bin/<nome_do_executavel>
		Obs: <nome_do_executavel> é o nome que deseja por para ser o executavel do projeto
	4 - Para compilar, tem-se duas maneiras:
		./bin/<nome_executavel> /data/<arquivo_de_entrada>
		ou 
		./bin/<nome_executavel> /data/<arquivo_de_entrada> /saida/<arquivo_de_saida>

		Obs: <arquivo_de_entrada> é um arquivo de texto com uma entrada da matriz
			 <arquivo_de_saida> será o arquivo que armazenará o histórico de gerações
