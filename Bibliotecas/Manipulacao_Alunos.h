/**
 * Biblioteca "Manipulacao_Alunos.h".
 * Implementação das funções que tratam da manipulação e curadoria dos dados dos alunos.
 * Criado em: 29/11/2020.
 * Última modificação por Patrick Cauan Priebe no dia 09/12/2020.
*/

// Inclusão de bibliotecas padrões da linguagem.
#include <stdio.h>	 // Biblioteca padrão de entrada e saída.
#include <stdlib.h>	 // Biblioteca padrão para manipulação de memória com uso dinâmico.
#include <windows.h> // Biblioteca padrão para manipulação de API.

#include "Manipulacao_Turmas.h" // Inclusão da biblioteca para manipulação das turmas.

//  Protótipos das funções.
void cadastrar_aluno_espera(void);
void cadastrar_aluno(void);
void imprime_lista_espera(void);
void imprime_alunos_turma(Turma aux);
void imprimir_todos_alunos(void);
Aluno buscar_aluno(int matricula);
void editar_aluno(int matricula);
void desmatricular_aluno(int matricula);
int qtd_alunos_cadastrados(void);
int entrada_dados_aluno(Aluno *novo_aluno);
void imprime_aluno(Aluno aluno_aux, int escolha);
void atualizar_lista_espera(void);
void imprime_cabecalho_aluno(void);
void imprime_fim_aluno(void);
void imprime_fim_tabela_aluno(void);

/**
* Função que busca um aluno na base de dados.
* Entrada (parâmetro(s)): <int> é a matrícula do aluno, um número inteiro.
* Saída (retorno(s)): retorna uma variável do tipo <Aluno> (registro) com o que foi encontrado.
* Saída: Caso não encontre a matrícula, irá retornar registro com código de marcação lógica igual a -2.
*/
Aluno buscar_aluno(int matricula)
{

	FILE *arquivo_alunos = fopen("Alunos.bin", "rb"); //  Abre/cria o arquivo 'Alunos.bin' "rb" (abertura para leitura de dados)

	if (arquivo_alunos != NULL) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
	{
		Aluno buscar;												  //  Criando registro temporário (visível apenas dentro desta condicional)
		while (fread(&buscar, sizeof(Aluno), 1, arquivo_alunos) == 1) // Loop enquanto for possível ler uma linha do arquivo alunos
		{
			if (matricula == buscar.matricula) // Compara as matrículas
				return buscar;				   // Retorna o aluno
		}
		buscar.matricula = -2;	// Caso não encontre retorna -2
		fclose(arquivo_alunos); //  Salva as alterações, limpando o buffer e fechando o arquivo
		return buscar;			// Retorna que o aluno não está cadastrado
	}
	else //  Se não for possível abrir/criar o arquivo 'Alunos.bin'
		printf("Problema no arquivo 'Alunos.bin'\n");
}

/**
* Função que cadastra o aluno na lista de espera (tipo especial de turma) na qual tem código igual a -1.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)):  <void> sem retorno.
*/
void cadastrar_aluno_espera(void)
{

	FILE *arquivo_alunos = fopen("Alunos.bin", "a+b"); //  Abre/cria o arquivo 'Alunos.bin' "a+b" (abertura para leitura e escrita de dados)

	if (arquivo_alunos != NULL) // Se for posssível abrir/criar o arquivo 'Alunos.bin'
	{
		Aluno aluno_espera;									//  Criando registro temporário (visível apenas dentro desta condicional)
		int validador = entrada_dados_aluno(&aluno_espera); // Validador recebe a entrada de dados passando como argumento o aluno
		aluno_espera.aux = aluno_espera.turma;				// O aux desse aluno recebe o código da turma
		aluno_espera.turma = -1;							// A turma desse aluno é alterada para -1 (referente a lista de espera)

		if (validador != 0) // Se o validador for diferente de 0 (matrícula inválida ou já existente)
		{
			fwrite(&aluno_espera, sizeof(Aluno), 1, arquivo_alunos); // Escreve o registro dentro do arquivo

			FILE *arquivo_turmas = fopen("Turmas.bin", "r+b"); //  Abre/cria o arquivo 'Turmas.bin' "r+b" (abertura para leitura e escrita de dados)
			if (arquivo_turmas)								   //  Se for possí­vel abrir/criar o arquivo 'Turmas.bin'
			{
				Turma aux;											  //  Criando registro temporário (visível apenas dentro desta condicional)
				while (fread(&aux, sizeof(Turma), 1, arquivo_turmas)) // Loop enquanto for possível ler uma linha dentro do arquivo turmas
				{
					if (aux.codigo == -1) // Se o código aux do aluno for -1
					{
						fseek(arquivo_turmas, (sizeof(Turma) * -1), SEEK_CUR); // Reposiciona o indicador de posição do fluxo em função do deslocamento -1
						aux.qtd_alunos++;									   // Acresce a quantidade de alunos da turma
						fwrite(&aux, sizeof(Turma), 1, arquivo_turmas);		   // Escreve as alterações no arquivo turmas
						printf("\nAluno cadastrado com sucesso na lista de espera!\n");
						break; // Término do laço
					}
				}
				fclose(arquivo_turmas); //  Salva as alterações, limpando o buffer e fechando o arquivo
			}
			else //  Se não for possí­vel abrir/criar o arquivo 'Turmas.bin'
				printf("Problema no arquivo 'Turmas.bin'\n");
		}
	}
	else //  Se não for possível abrir/criar o arquivo 'Alunos.bin'
		printf("Problema no arquivo 'Alunos.bin'\n");

	fclose(arquivo_alunos); //  Salva as alterações, limpando o buffer e fechando o arquivo
}

/**
* Função que preenche dados de um aluno, como entrada, fazendo todas as validações necessárias.
* Entrada (parâmetro(s)): <Aluno *novo_aluno> é o aluno que receberá os dados captados (em ponteiro).
* Saída (retorno(s)): <int>, 0 para matrícula inválida, 1 para cadastro realizado e 2 para turma lotada.
* Saída: Serve como atribuição de retorno lógico.
*/
int entrada_dados_aluno(Aluno *novo_aluno)
{

	printf("Digite a matr%ccula: ", 161); // Inserção da matrícula do aluno
	fflush(stdin);						  // Limpa o buffer
	scanf("%d", &novo_aluno->matricula);  // Guarda a matrícula no campo correspondente

	Aluno a_validador = buscar_aluno(novo_aluno->matricula); // Verifica se a matrícula já existe

	if (novo_aluno->matricula >= 0 && a_validador.matricula == -2) // Caso a matrícula seja maior ou igual a 0 e o validador tenha retornado -2 (matrícula inexistente)
	{
		printf("Nome: ");				   // Inserção do nome do aluno
		fflush(stdin);					   // Limpa o buffer
		wscanf(L"%ls", &novo_aluno->nome); // Guarda o nome no campo correspondente

		if (novo_aluno->nome[0] != '\0' && novo_aluno->nome[0] != ' ' && novo_aluno->nome[0] > 64) // Caso o nome na posição 0 seja diferente de um espaço e seja um caracter do alfabeto
		{
			printf("Idade: ");				 // Inserção da idade do aluno
			fflush(stdin);					 // Limpa o buffer
			scanf("%d", &novo_aluno->idade); // Guarda a turma no campo correspondente

			if (novo_aluno->idade > 0 && novo_aluno->idade < 150) // Se a idade do aluno for maior que 0 e menor que 150
			{
				printf("Turma (ou c%cdigo de espera): ", 162); // Inserção da turma do aluno
				fflush(stdin);								   // Limpa o buffer
				scanf("%d", &novo_aluno->turma);			   // Guarda a turma no campo correspondente

				Turma validador = busca_turma(novo_aluno->turma); // Validador para verificar se a turma existe
				if (validador.codigo != -2)						  // Caso a turma exista
				{
					if (validador.qtd_alunos < validador.qtd_limite) // Verifica se tem espaço na turma
					{
						printf("\nDados cadastrados!\n");
						return 1;
					}
					else // Caso a turma estiver lotada
						printf("\nTurma lotada!\n");
					return 2;
				}
				else // Caso a turma não seja encontrada
				{
					printf("\nTurma n%co encontrada!\n", 198);
					return 2;
				}
			}
			else // Caso a idade seja inválida
				printf("\nIdade inv%clida\n", 160);
		}
		else // Caso o nome seja inválido
			printf("\nNome inv%clido!\n", 160);
	}
	else // Caso a matrícula seja inválida ou inexistente
		printf("\nMatr%ccula inv%clida ou j%c existente!\n", 161, 160, 160);
	return 0;
}

/**
* Função que cadastra um aluno em determinada turma(caso ela esteja cheia, será redirecionado para a lista de espera).
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)):  <void> sem retorno.
*/
void cadastrar_aluno(void)
{

	Aluno novo_aluno;								  // Criando registro temporário (visível apenas dentro desta condicional)
	int validador = entrada_dados_aluno(&novo_aluno); // Valida se o aluno foi cadastrado
	if (validador == 1)								  // Caso o aluno não esteja cadastrado
	{
		FILE *arquivo_turmas = fopen("Turmas.bin", "r+b"); // Abre/cria o arquivo 'Turmas.bin' "r+b" (abertura para leitura e escrita de dados)
		if (arquivo_turmas)								   // Se for posssível abrir/criar o arquivo 'Turmas.bin'
		{
			Turma aux;											  // Criando registro temporário (visí­vel apenas dentro desta condicional)
			while (fread(&aux, sizeof(Turma), 1, arquivo_turmas)) // Loop enquanto for possível ler uma linha dentro do arquivo turmas
			{
				if (aux.codigo == novo_aluno.turma) // Caso o código da turma seja igual ao código da turma do aluno
				{
					fseek(arquivo_turmas, (sizeof(Turma) * -1), SEEK_CUR); // Reposiciona o indicador de posição do fluxo em função do deslocamento -1
					aux.qtd_alunos++;									   // Acresce a quantidade de alunos da turma
					fwrite(&aux, sizeof(Turma), 1, arquivo_turmas);		   // Escreve as alterações no arquivo turmas
					break;												   // Término do laço
				}
			}
			fclose(arquivo_turmas); //  Salva as alterações, limpando o buffer e fechando o arquivo
		}
		else //  Se não for possível abrir/criar o arquivo 'Turmas.bin'
		{
			printf("Problema no arquivo 'Turmas.bin'\n");
			return;
		}

		FILE *arquivo_alunos = fopen("Alunos.bin", "a+b"); //  Abre/cria o arquivo 'Alunos.bin' "a+b" (abertura para leitura e escrita de dados)
		if (arquivo_alunos)								   // Se for posssível abrir/criar o arquivo 'Alunos.bin
		{
			fwrite(&novo_aluno, sizeof(Aluno), 1, arquivo_alunos); // Escreve as alterações no arquivo turmas

			printf("\nAluno cadastrado!\n");
			fclose(arquivo_alunos); // Salva as alterações, limpando o buffer e fechando o arquivo
		}
		else // Se não for possível abrir/criar o arquivo 'Turmas.bin'
		{
			printf("\nProblema no arquivo 'Alunos.bin'\n");
			return;
		}
	}
	else // Caso o aluno já esteja cadastrado
		printf("\nAluno n%co cadastrado!\n", 198);
}

/**
* Função que imprime somente a turma da lista de espera.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_lista_espera(void)
{
	Turma aux = busca_turma(-1); // Criando registro temporário (visível apenas dentro desta condicional) recebendo a função busca turma (lista de espera)
	if (aux.qtd_alunos != 0)	 // Se a quantidade de alunos da lista de espera for diferente de 0
	{
		FILE *arquivo_alunos = fopen("Alunos.bin", "rb"); //  Abre/Cria o arquivo 'Alunos.bin' "rb"(abertura para leitura de dados)

		if (arquivo_alunos != NULL) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
		{
			Aluno aluno_espera; // Criando registro temporário (visível apenas dentro desta condicional)

			int ocorrencias = 0; // Variável para guardar o número de ocorrências de alunos da turma de espera

            while(fread(&aluno_espera, sizeof(Aluno), 1, arquivo_alunos)) // Percorrer o arquivo
                if(aluno_espera.turma == aux.codigo) // Se encontrar um aluno com a turma de espera
                    ocorrencias++; // Incrementa o número de ocorrências

			fseek(arquivo_alunos, 0, SEEK_SET); // Reposiciona o indicador de posição do fluxo em função do deslocamento

			puts("\n");

			imprime_cabecalho_aluno(); // Imprime o cabeçalho do aluno

			while (fread(&aluno_espera, sizeof(Aluno), 1, arquivo_alunos) == 1) //  Vai rodar enquanto ela conseguir retornar uma linha válida
			{
				if (aluno_espera.turma == -1)
				{ // Se for a lista de espera

					imprime_aluno(aluno_espera, 1);
					ocorrencias--; // Decrementa o número de ocorrências

					if(ocorrencias != 0) // Se houverem mais ocorrências de alunos na turma de espera
                        imprime_fim_aluno(); // Imprime o fim da linha do aluno
                    else{ // Se não houverem mais ocorrências de alunos na turma de espera
                        imprime_fim_tabela_aluno(); // Imprime o fim da tabela
                        break; // Sai do laço
                    }
				}
			}

			Turma verificador = busca_turma(-1); // Criando registro temporário que recebe a função busca turma -1 (lista de espera)
			if (verificador.qtd_alunos == 0)	 // Caso a quantidade de alunos seja igual a 0
				printf("\nLista de espera vazia\n");
			fclose(arquivo_alunos); //  Salva as alterações, limpando o buffer e fechando o arquivo
		}
		else // Se não for possível abrir/criar o arquivo 'Alunos.bin'
			printf("Problema no arquivo 'Alunos.bin'\n");
	}
	else // Se a lista de espera estiver vazia
	{
		printf("\nLista de espera vazia!\n");
	}
}

/**
* Função que imprime todos os alunos cadastrados em todas as turmas.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprimir_todos_alunos(void)
{
	FILE *arquivo_alunos = fopen("Alunos.bin", "rb"); //  Abre/Cria o arquivo 'Alunos.bin' "rb"(abertura para leitura de dados)

	if (arquivo_alunos != NULL) // Se for possível abrir/criar o arquivo 'Alunos.bin'
	{
		Aluno todos_alunos; // Criando registro temporário (visível apenas dentro desta condicional)

		fseek(arquivo_alunos, 0, SEEK_END); // Reposiciona o indicador de posição do fluxo em função do deslocamento

		int tamanho_total = ftell(arquivo_alunos); // Conta o tamanho (bytes) do arquivo alunos

		fseek(arquivo_alunos, 0, SEEK_SET); // Reposiciona o indicador de posição do fluxo em função do deslocamento

		if (fread(&todos_alunos, sizeof(Aluno), 1, arquivo_alunos))
		{ // Se for possível ler uma linha válida

			puts("\n");

			imprime_cabecalho_aluno(); // Imprime o cabeçalho aluno

			fseek(arquivo_alunos, 0, SEEK_SET); // Reposiciona o indicador de posição do fluxo em função do deslocamento

			while (fread(&todos_alunos, sizeof(Aluno), 1, arquivo_alunos) == 1) // Vai rodar enquanto ela conseguir retornar uma linha válida
			{

				imprime_aluno(todos_alunos, 0); // Imprime o aluno

				if (ftell(arquivo_alunos) == tamanho_total){ // Se o tamanho do arquivo aluno for igual ao tamanho total
					imprime_fim_tabela_aluno();
					break;									// Término do laço
				}

				imprime_fim_aluno(); // Imprime o fechamento de linha do aluno
			}

		}
		else // Caso não haja aluno
			printf("\nN%co h%c alunos!\n", 198, 160);

		fclose(arquivo_alunos); //  Salva as alterações, limpando o buffer e fechando o arquivo
	}
	else // Se não for possível abrir/criar o arquivo 'Alunos.bin'
		printf("Problema no arquivo 'Alunos.bin'\n");
}

/**
* Função que imprime os alunos de uma determinada turma.
* Entrada (parâmetro(s)): <Turma aux> é a turma na qual os dados serão impressos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_alunos_turma(Turma aux)
{
	FILE *arquivo_alunos = fopen("Alunos.bin", "rb"); //  Abre/Cria o arquivo 'Alunos.bin' "rb"(abertura para leitura de dados)

	if (arquivo_alunos != NULL) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
	{
		Aluno aluno_turma; // Criando registro temporário (visível apenas dentro desta condicional)

		int ocorrencias = 0; // Variável para guardar o número de ocorrências de alunos da turma especificada

		while(fread(&aluno_turma, sizeof(Aluno), 1, arquivo_alunos)) // Percorrer o arquivo
            if(aluno_turma.turma == aux.codigo) // Se encontrar um aluno com a turma especificada
                ocorrencias++; // Incrementa o número de ocorrências

        fseek(arquivo_alunos, 0, SEEK_SET); // Volta ao início do arquivo

		Turma auxiliar = busca_turma(aux.codigo); // Criando registro temporário que recebe a função busca turma passando como argumento o código do aux

		if (auxiliar.codigo != -2 && auxiliar.qtd_alunos > 0)
		{ // Se o código for diferente de -2 e a quantidade de alunos for maior que 0

			puts("\n");

			imprime_cabecalho_aluno(); // Imprime cabeçalho do aluno
		}

		fseek(arquivo_alunos, 0, SEEK_SET); // Reposiciona o indicador de posição do fluxo em função do deslocamento

		while (fread(&aluno_turma, sizeof(Aluno), 1, arquivo_alunos)) //  Vai rodar enquanto ela conseguir retornar uma linha válida
		{
			if (aux.codigo == aluno_turma.turma){ // Se o código do aux for igual ao da turma
				imprime_aluno(aluno_turma, 0); // Imprime o aluno
				ocorrencias--; // Decrementa o número de ocorrências
				if(ocorrencias != 0) // Se houverem mais ocorrências
                    imprime_fim_aluno(); // Imprime o fim de linha
                else // Se não houverem mais ocorrências
                    imprime_fim_tabela_aluno(); // Imprime o fechamento de tabela
			}
		}

		fclose(arquivo_alunos); //  Salva as alterações, limpando o buffer e fechando o arquivo
	}
	else // Se não for possível abrir/criar o arquivo 'Alunos.bin'
		printf("Problema no arquivo 'Alunos.bin'\n");
}

/**
* Função que edita os dados de um aluno com base em uma daterminada matrícula.
* Entrada (parâmetro(s)): <int> matrícula do aluno a ser editado.
* Saída (retorno(s)):  <void> sem retorno.
*/
void editar_aluno(int matricula)
{

	FILE *arquivo_alunos = fopen("Alunos.bin", "r+b"); //  Abre/Cria o arquivo 'Alunos.bin' "r+b"(abertura para leitura e escrita de dados)

	if (arquivo_alunos != NULL) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
	{
		Aluno editar = buscar_aluno(matricula); // Criando registro temporário que recebe a função buscar aluno passando como argumento a matrícula

		if (editar.matricula != -2) // Caso ele encontre o aluno
		{
			printf("***********************************\n");
			printf("\nAluno encontrado!\n\n");

			puts("\n");

			imprime_cabecalho_aluno(); // Imprime o cabeçalho do aluno

			imprime_aluno(editar, 0); // Imprime o aluno

			puts("\n");

			int turma_antiga = editar.turma; // Salva a turma anterior

			while (1) // Laço para validar a entrada de dados do aluno
			{
				if (entrada_dados_aluno(&editar) == 1)
					break;
			}

			fseek(arquivo_alunos, sizeof(Aluno) * -1, SEEK_CUR); // Reposiciona o indicador de posição do fluxo em função do deslocamento
			fwrite(&editar, sizeof(Aluno), 1, arquivo_alunos);	 // Escreve as alterações no arquivo alunos
			fclose(arquivo_alunos);								 //  Salva as alterações, limpando o buffer e fechando o arquivo

			int turma_nova = editar.turma; // Salva a turma nova

			if (turma_antiga != turma_nova) // Se a turma anterior for diferente da turma nova
			{

				FILE *arquivo_turmas = fopen("Turmas.bin", "r+b"); //  Abre/Cria o arquivo 'Alunos.bin' "r+b"(abertura para leitura e escrita de dados)

				if (arquivo_turmas) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
				{

					Turma turma_aux; // Criando registro temporário

					while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas)) // Enquanto for possível ler uma linha válida
					{

						if (turma_aux.codigo == turma_antiga) // Se o código da turma aux for igual a da turma antiga
						{

							turma_aux.qtd_alunos--;								  // Decrementa a quantidade de alunos
							fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);  // Reposiciona o indicador de posição do fluxo em função do deslocamento
							fwrite(&turma_aux, sizeof(Turma), 1, arquivo_turmas); // Escreve as alterações no arquivo turmas
							fseek(arquivo_turmas, 0, SEEK_SET);					  // Reposiciona o indicador de posição do fluxo em função do deslocamento
							break;												  // Término do laço
						}
					}

					fseek(arquivo_turmas, 0, SEEK_SET); // Reposiciona o indicador de posição do fluxo em função do deslocamento

					while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas)) // Enquanto for possível ler uma linha válida
					{

						if (turma_aux.codigo == turma_nova) // Se o código da turma aux for igual ao da turma nova
						{

							turma_aux.qtd_alunos++;								  // Acresce a quantidade de alunos
							fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);  // Reposiciona o indicador de posição do fluxo em função do deslocamento
							fwrite(&turma_aux, sizeof(Turma), 1, arquivo_turmas); // Escreve as alterações no arquivo turmas
							fseek(arquivo_turmas, 0, SEEK_SET);					  // Reposiciona o indicador de posição do fluxo em função do deslocamento
							break;												  // Término do laço
						}
					}

					fclose(arquivo_turmas); //  Salva as alterações, limpando o buffer e fechando o arquivo
					printf("Aluno editado e turma atualizada!\n");
				}
				else // Se não for possí­vel abrir/criar o arquivo 'Turmas.bin'
					printf("Problema no arquivo 'Turmas.bin'\n");
			}
		}
		else // Se o aluno não for encontrado
			printf("Aluno n%co encontrado!\n", 198);
	}
	else // Se não for possível abrir/criar o arquivo 'Alunos.bin'
		printf("Problema no arquivo 'Alunos.bin'\n");

	fclose(arquivo_alunos); //  Salva as alterações, limpando o buffer e fechando o arquivo
}

/**
* Função que serve para desmatricular um aluno com base em uma determinada matrícula.
* Entrada (parâmetro(s)): <int> matrícula do aluno a ser excluído.
* Saída (retorno(s)):  <void> sem retorno.
*/
void desmatricular_aluno(int matricula)
{

	FILE *arquivo_a = fopen("Alunos.bin", "r+b"); //  Abre/Cria o arquivo 'Alunos.bin' "r+b"(abertura para leitura e escrita de dados)

	int aluno_foi_encontrado = 0; //Variável booleana para aluno encontrado

	if (arquivo_a != NULL) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
	{
		//Obtém o tamanho do arquivo
		fseek(arquivo_a, 0, SEEK_END);		   //Vai até o final
		int tamanho_maximo = ftell(arquivo_a); //Obtém a posição em bytes em relação ao começo
		fseek(arquivo_a, 0, SEEK_SET);		   //Volta o cursor do arquivo para o início

		Aluno desmatricular; //Variável para procurar o aluno a ser desmatriculado
		Aluno aux;			 //Variável para o deslocamento dos registros no arquivo

		int codigo; //Variável para salvar a turma em que o aluno estava

		while (fread(&desmatricular, sizeof(Aluno), 1, arquivo_a)) //Percorre o arquivo procurando pelo aluno a ser desmatriculado
		{
			if (desmatricular.matricula == matricula) //Se encontrar o aluno a ser desmatriculado
			{

				codigo = desmatricular.turma; //Salva a turma do aluno a ser desmatriculado

				if (ftell(arquivo_a) < tamanho_maximo)
				{ //Se o aluno não era o último do arquivo

					while (fread(&aux, sizeof(Aluno), 1, arquivo_a)) //Percorre o arquivo deslocando a lista
					{
						fseek(arquivo_a, sizeof(Aluno) * -2, SEEK_CUR); //Volta dois alunos para deslocar os registros à esquerda corretamente

						fwrite(&aux, sizeof(Aluno), 1, arquivo_a); //Sobrescreve o registro

						fseek(arquivo_a, sizeof(Aluno), SEEK_CUR); //Passa para o próximo aluno a ser deslocado
					}

					fseek(arquivo_a, sizeof(Aluno) * -1, SEEK_CUR); //Ao final, volta um aluno para poder truncar o duplicado no final do arquivo
				}
				else												//Se o aluno era o último do arquivo
					fseek(arquivo_a, sizeof(Aluno) * -1, SEEK_CUR); //Volta um aluno para poder truncar o arquivo, removendo um aluno duplicado

				int tamanho = ftell(arquivo_a); //Obtém a posição do novo final

				fclose(arquivo_a); //Fecha o arquivo

				//Esta parte trunca o arquivo
				HANDLE arquivo = CreateFileW(L"Alunos.bin", GENERIC_WRITE, 0, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL); //Abre o arquivo

				SetFilePointer(arquivo, tamanho, NULL, 0); //Modifica a posição do cursor

				SetEndOfFile(arquivo); //Trunca o arquivo, modificando a posição de seu final

				CloseHandle(arquivo); //Fecha o arquivo

				aluno_foi_encontrado = 1; //Muda o estado da variável booleana para aluno encontrado

				break; //Sai do escopo do while
			}
		}

		if (aluno_foi_encontrado)
		{ //Se o aluno foi encontrado

			FILE *arquivo_turmas = fopen("Turmas.bin", "r+b"); //Abre o arquivo de turmas

			Turma turma_aux; //Estrutura Turma auxiliar

			while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
			{ //Percorre o arquivo

				if (turma_aux.codigo == codigo)
				{ //Se a turma do aluno desmatriculado foi encontrada

					turma_aux.qtd_alunos--; //Decrementa a quantidade de alunos

					fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR); //Retrocede uma turma

					fwrite(&turma_aux, sizeof(Turma), 1, arquivo_turmas); //Sobrescreve os dados da turma

					fclose(arquivo_turmas); //Fecha o arquivo

					break; //Sai do laço
				}
			}

			printf("\nAluno desmatriculado!\n"); //Informa que o aluno foi desmatriculado
		}

		else
		{											   //Se o aluno não foi encontrado
			printf("\nAluno n%co encontrado!\n", 198); //Informa que o aluno não foi encontrado
			fclose(arquivo_a);						   //Fecha o arquivo
		}
	}
	else											  //Se não foi possível abrir ou criar o arquivo
		printf("Problema no arquivo 'Alunos.bin'\n"); //Informa o problema
}

/**
* Função que informa a quantidade de alunos cadastrados em todas as turmas.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois modifica direto componentes específicos.
* Saída (retorno(s)): <int>, retorno do contador com o número de alunos cadastrados.
* Saída: Serve como atribuição de retorno lógico.
*/
int qtd_alunos_cadastrados(void)
{
	int contador = 0;

	FILE *arquivo = fopen("Alunos.bin", "r+b"); //  Abre/Cria o arquivo 'Alunos.bin' "r+b"(abertura para leitura e escrita de dados)

	if (arquivo != NULL) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
	{
		Aluno aluno_cad;									 // Criando registro temporário (visível apenas dentro desta condicional)
		while (fread(&aluno_cad, sizeof(Aluno), 1, arquivo)) // Vai rodar enquanto ela conseguir retornar uma linha válida
			contador += 1;									 // Contador vai marcar a quantidade de alunos cadastrados
	}
	else
	{
		arquivo = fopen("Alunos.bin", "w+b"); //  Abre/Cria o arquivo 'Alunos.bin' "w+b"(abertura para leitura e escrita de dados)
		if (arquivo == NULL)				  //  Se não for possível abrir/criar o arquivo 'Alunos.bin'
			printf("Problema no arquivo 'Alunos.bin'\n");
	}
	fclose(arquivo); //  Salva as alterações, limpando o buffer e fechando o arquivo
	return contador;
}

/**
* Função que serve para imprimir o o aluno.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_aluno(Aluno aluno_aux, int escolha)
{

	putchar(186); // Imprime caracter especial

	for (int i = 0; i < 72; i++)
	{ // Escreve uma linha inteira

		if (i != 11 && i != 56 && i != 64) // Coloca um caracter diferente como separador
			putchar(32);
		else
			putchar(186);
	}

	putchar(186);
	putchar(10);

	putchar(186);

	if (aluno_aux.turma != -1) // Se o código aux do aluno for diferente de -1 (não está na lista de espera)
		printf("%11d%c%-44ls%c%7d%c%7d%c\n", aluno_aux.matricula, 186, aluno_aux.nome, 186, aluno_aux.idade, 186, aluno_aux.turma, 186);
	else if (!escolha) // Se for igual 0
		printf("%11d%c%-44ls%c%7d%c%7d%c\n", aluno_aux.matricula, 186, aluno_aux.nome, 186, aluno_aux.idade, 186, aluno_aux.aux, 186);
	else // Se for difente de 0
		printf("%11d%c%-44ls%c%7d%cEspera!%c\n", aluno_aux.matricula, 186, aluno_aux.nome, 186, aluno_aux.idade, 186, 186);

	putchar(186);

	for (int i = 0; i < 72; i++)
	{

		if (i != 11 && i != 56 && i != 64)
			putchar(32);
		else
			putchar(186);
	}
}

/**
* Função que serve para atualizar a lista de espera após cadastrar uma turma ou desmatricular um aluno.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void atualizar_lista_espera(void)
{

	FILE *arquivo_alunos = fopen("Alunos.bin", "r+b"); // abrir o arquivo alunos
	FILE *arquivo_turmas = fopen("Turmas.bin", "r+b"); // abrir o arquivo turmas

	if (arquivo_alunos != NULL && arquivo_turmas != NULL) //  Se for possível abrir/criar o arquivo 'Alunos.bin'
	{
		Aluno aluno_aux;											// Criando registro temporário (visível apenas dentro desta condicional)
		Turma turma_aux;											// Criando registro temporário (visível apenas dentro desta condicional)
		while (fread(&aluno_aux, sizeof(Aluno), 1, arquivo_alunos)) // Enquanto for possível ler uma linha válida
		{
			if (aluno_aux.turma == -1) // Se o código aux da turma for igual a -1 (Lista de espera)
			{

				while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas)) // Enquanto for possível ler uma linha válida
				{
					if (turma_aux.codigo == aluno_aux.aux) // Se o código da turma for igual ao aux do aluno
					{
						if (turma_aux.qtd_alunos < turma_aux.qtd_limite) // Se tiver espaço na turma
						{
							aluno_aux.turma = turma_aux.codigo; // O aluno recebe o código da turma
							aluno_aux.aux = 0;					// O auxiliar do aluno é atualizado para 0

							turma_aux.qtd_alunos++;								  // Acresce a quantidade de alunos da turma
							fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);  // Reposiciona o indicador de posição do fluxo em função do deslocamento
							fwrite(&turma_aux, sizeof(Turma), 1, arquivo_turmas); // Reescrevendo a turma

							fseek(arquivo_alunos, sizeof(Aluno) * -1, SEEK_CUR);  // Reposiciona o indicador de posição do fluxo em função do deslocamento
							fwrite(&aluno_aux, sizeof(Aluno), 1, arquivo_alunos); // Reescrevendo o aluno

							fclose(arquivo_turmas);						 //  Salva as alterações, limpando o buffer e fechando o arquivo
							fclose(arquivo_alunos);						 //  Salva as alterações, limpando o buffer e fechando o arquivo
							arquivo_alunos = fopen("Alunos.bin", "r+b"); // abrir o arquivo alunos
							arquivo_turmas = fopen("Turmas.bin", "r+b"); // abrir o arquivo turmas

							fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas);  // Leitura das linhas do arquivo turmas
							fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);  // Reposiciona o indicador de posição do fluxo em função do deslocamento
							turma_aux.qtd_alunos--;								  // Decresce a quantidade de alunos da turma
							fwrite(&turma_aux, sizeof(Turma), 1, arquivo_turmas); // Escreve as alterações no arquivo turmas

							fclose(arquivo_turmas);						 // Salva as alterações, limpando o buffer e fechando o arquivo
							arquivo_turmas = fopen("Turmas.bin", "r+b"); // Abre/Cria o arquivo 'Alunos.bin' "r+b"(abertura para leitura e escrita de dados)
						}
						break; // Término do laço
					}
				}
			}
		}
		printf("\nA lista de espera foi atualizada!\n");
		fclose(arquivo_turmas); //  Salva as alterações, limpando o buffer e fechando o arquivo
		fclose(arquivo_alunos); //  Salva as alterações, limpando o buffer e fechando o arquivo
	}
	else // Se não for possível abrir/criar o arquivo 'Alunos.bin' e 'Turmas.bin'
		printf("Problema no arquivo 'Alunos.bin' ou 'Turmas.bin'\n");
}

/**
* Função que serve para imprimir o cabeçalho da tabela dos alunos.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_cabecalho_aluno(void)
{

	putchar(201); // Imprime caracter especial

	for (int i = 0; i < 72; i++)
	{ // Escreve uma linha inteira

		if (i != 11 && i != 56 && i != 64) // Coloca um caracter diferente como separador
			putchar(205);
		else
			putchar(203);
	}

	putchar(187);
	putchar(10);

	putchar(186);

	for (int i = 0; i < 72; i++)
	{ // Escreve uma linha inteira

		if (i != 11 && i != 56 && i != 64) // Coloca um caracter diferente como separador
			putchar(32);				   // Imprime um espaço
		else
			putchar(186); // Imprime caracter especial
	}

	putchar(186);
	putchar(10);

	putchar(186);

	printf(" Matr%ccula %c                    Nome                    %c Idade %c Turma ", 161, 186, 186, 186, 186);

	putchar(186);
	putchar(10);

	putchar(186);

	for (int i = 0; i < 72; i++)
	{ // Escreve uma linha inteira

		if (i != 11 && i != 56 && i != 64) // Coloca um caracter diferente como separador
			putchar(32);
		else
			putchar(186);
	}

	putchar(186);
	putchar(10);

	putchar(204);

	for (int i = 0; i < 72; i++)
	{ // Escreve uma linha inteira

		if (i != 11 && i != 56 && i != 64) // Coloca um caracter diferente como separador
			putchar(205);
		else
			putchar(206);
	}

	putchar(185);
	putchar(10);
}

/**
* Função que serve para imprimir o fim da tabela dos alunos.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_fim_aluno(void)
{

	putchar(186); // Imprime caracter especial
	putchar(10);

	putchar(204);

	for (int i = 0; i < 72; i++)
	{ // Escreve uma linha inteira

		if (i != 11 && i != 56 && i != 64) // Coloca um caracter diferente como separador
			putchar(205);
		else // Caso for igual aos caracteres
			putchar(206);
	}

	putchar(185);
	putchar(10);
}

/**
* Função que serve para imprimir conexões final do rodapé de encaixe da tabela.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_fim_tabela_aluno(void){

    putchar(186);
    putchar(10);

    putchar(200);

    for(int i = 0; i < 72; i++){

        if(i != 11 && i != 56 && i != 64)
            putchar(205);
        else
            putchar(202);

    }
    putchar(188);
    putchar(10);

}
