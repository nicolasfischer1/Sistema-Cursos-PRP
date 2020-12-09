/**
 * Biblioteca "Manipulacao_Turmas.h".
 * Implementação das funções que tratam da manipulação e curadoria dos dados das turmas.
 * Criado em: 29/10/2020.
 * Última modificação por Nicolas Fischer no dia 08/12/2020.
*/

// Inclusão de bibliotecas padrões da linguagem
#include <stdio.h>  // Biblioteca padrão de entrada e saída
#include <stdlib.h> // Biblioteca padrão para manipulação de memória com uso dinâmico

#include "Tipos_Registros.h" // Inclusão da biblioteca interna (criada para o projeto)
                             // Trás os dados primitivos e definição de registros e tipos

//  Protótipos das funções
int entrada_dados_turma(Turma *nova_turma);
Turma busca_turma(int aux);
int cadastro_turma(void);
void cria_lista_espera(void);
void imprime_turma(Turma aux);
void imprime_todas_turmas(void);
int qtd_turmas_cadastradas(void);

/**
* Função que preenche dados de uma turma, como entrada, fazendo todas as validações necessárias.
* Entrada (parâmetro(s)): <Turma *nova_turma> é a turma que receberá os dados captados (em ponteiro).
* Saída (retorno(s)): <int>, 0 para validação falsa, 1 para validação verdadeira.
* Saída: Serve como atribuição de retorno lógico.
*/
int entrada_dados_turma(Turma *nova_turma)
{
    //  Questionando o usuário as informações da turma, limpando buffer do teclado, lendo e armazenando-as no registro passado como parâmetro
    printf("C%cdigo: ", 162);
    fflush(stdin);
    scanf("%d", &nova_turma->codigo);

    Turma validador = busca_turma((*nova_turma).codigo);

    if ((validador.codigo != nova_turma->codigo) && (nova_turma->codigo >= 0))
    {
        printf("Curso: ");
        fflush(stdin);
        wscanf(L"%ls", &nova_turma->curso);

        printf("Turno:\n[m] para manh%c\n[t] para tarde\n[n] para noite\n>> ", 198);
        fflush(stdin);
        wscanf(L"%lc", &nova_turma->turno);

        printf("Quantidade limite de alunos: ");
        fflush(stdin);
        scanf("%d", &nova_turma->qtd_limite);
        if (nova_turma->qtd_limite > 0)
            return 1;
        else
        {
            printf("\nQuantidade insuportada!\n");
            return 0;
        }
    }
    else
    {
        printf("\nN%co %c poss%cvel criar uma turma com esse c%cdigo!\n", 198, 130, 161, 162);
        return 0;
    }
}

/**
* Função que cadastra uma nova turma, incluíndo-a no arquivo correspondente.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois modifica direto componentes específicos.
* Saída (retorno(s)): <int>, 0 para validação falsa, 1 para validação verdadeira.
* Saída: Serve como atribuição de retorno lógico.
*/
int cadastro_turma(void)
{
    FILE *arquivo_turmas = fopen("Turmas.bin", "a+b"); //  Abre/Cria o arquivo 'Turmas.bin' e posiciona o ponteiro no final dele (abertura para gravação de dados)

    if (arquivo_turmas != NULL) //  Se for possível abrir/criar o arquivo 'Turmas.bin'
    {
        Turma nova_turma; //  Criando registro temporário (visível apenas dentro desta condicional)
        if (entrada_dados_turma(&nova_turma) == 1)
        {
            nova_turma.qtd_alunos = 0;                             //  Inicializa a quantidade de alunos da turma com 0;
            fwrite(&nova_turma, sizeof(Turma), 1, arquivo_turmas); //  "Escreve" o registro dentro do arquivo
            fclose(arquivo_turmas);                                //  Salva as alterações, limpando o buffer e fechando o arquivo
            system("cls");                                         //  Limpa tela depois que grava os dados no registro
            printf("\nTurma cadastrada com sucesso!\n");
            getchar();
            return 1; //  Retorno verdadeiro de processo bem sucedido
        }
    }
    else //  Caso não seja possível abrir o arquivo 'Turmas.bin'
    {
        printf("Problema no arquivo 'Turmas.bin'\n");
        return 0; //  Retorno falso de processo não efetuado
    }
}

/**
* Função que imprime uma turma em formatação já tabelada, mas sem cabeçalho indicando os dados.
* Entrada (parâmetro(s)): <Turma aux> é a turma na qual os dados serão impressos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_turma(Turma aux)
{

    printf("*****************************************************\n");
    printf("Turma: %d\t Curso: %ls\t Turno: %lc\n", aux.codigo, aux.curso, aux.turno);
    printf("Alunos na turma: %d\t Limite de alunos: %d\n", aux.qtd_alunos, aux.qtd_limite);
}

/**
* Função que imprime todas as turmas cadastradas, exceto a lista de espera (que é um tipo especial de turma).
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
void imprime_todas_turmas(void)
{
    if (qtd_turmas_cadastradas() > 0)
    {
        FILE *arquivo_turmas = fopen("Turmas.bin", "rb");
        if (arquivo_turmas)
        {
            Turma turma_aux;
            while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
            {
                if (turma_aux.codigo >= 0)
                    imprime_turma(turma_aux);
                else
                    continue;
            }
            fclose(arquivo_turmas);
        }
        else //  Caso não seja possível abrir o arquivo 'Turmas.bin'
        {
            printf("Problema no arquivo 'Turmas.bin'\n");
        }
    }
    else
    {
        printf("N%co h%cturma cadastrada.\n", 198, 160);
    }
}

/**
* Função que busca uma turma na base de dados.
* Entrada (parâmetro(s)): <int> é o código da turma, um número inteiro
* Saída (retorno(s)): retorna uma variável do tipo <Turma> (registro) com o que foi encontrado.
* Saída: Caso não encontre a turma, irá retornar registro com código de marcação lógica igual a -2.
*/
Turma busca_turma(int aux)
{
    FILE *arquivo_turmas = fopen("Turmas.bin", "rb");
    Turma turma_aux;

    if (arquivo_turmas)
    {
        while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
        {
            if (turma_aux.codigo == aux)
            {
                fclose(arquivo_turmas);
                return turma_aux;
            }
        }
        turma_aux.codigo = -2;
        fclose(arquivo_turmas);
        return turma_aux;
    }
    else
    {
        printf("Problema no arquivo 'Turmas.bin'\n");
        return turma_aux;
    }
}

/**
* Função que conta a quantidade de turmas cadastradas, fora a lista de espera (que é um tipo especial de turma).
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <int> é o número de turmas contabilizado.
* Saída: Caso não encontre a turma, irá retornar registro com código de marcação lógica igual a -2.
*/
int qtd_turmas_cadastradas(void)
{
    FILE *arquivo_turmas = fopen("Turmas.bin", "rb");
    int contador = 0;
    if (arquivo_turmas)
    {
        Turma turma_aux;
        while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
        {
            contador++;
        }
        fclose(arquivo_turmas);
        return contador;
    }
    else
    {
        printf("Problema no arquivo 'Turmas.bin'\n");
        return 0;
    }
}

/**
* Função que cria a lista de espera (tipo especial de turma) na qual tem código igual a -1.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)):  <void> sem retorno.
*/
void cria_lista_espera(void)

{
    FILE *arquivo_turmas = fopen("Turmas.bin", "a+b"); //  Abre/Cria o arquivo 'Turmas.bin' e posiciona o ponteiro no final dele (abertura para gravação de dados)

    if (arquivo_turmas != NULL) //  Se for possível abrir/criar o arquivo 'Turmas.bin'
    {
        Turma nova_turma; //  Criando registro temporário (visível apenas dentro desta condicional)
        nova_turma.codigo = -1;
        nova_turma.qtd_alunos = 0; //  Inicializa a quantidade de alunos da turma com 0;
        nova_turma.qtd_limite = nova_turma.qtd_alunos + 1;
        fwrite(&nova_turma, sizeof(Turma), 1, arquivo_turmas); //  "Escreve" o registro dentro do arquivo
        fclose(arquivo_turmas);
    }
    else //  Caso não seja possível abrir o arquivo 'Turmas.bin'
    {
        printf("Problema no arquivo 'Turmas.bin'\n");
        getchar();
    }
}