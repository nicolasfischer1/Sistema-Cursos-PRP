/**
 * Biblioteca "Manipulacao_Turmas.h".
 * Implementação das funções que tratam da manipulação e curadoria dos dados das turmas.
 * Criado em: 29/10/2020.
 * Última modificação por Nicolas Fischer no dia 08/12/2020.
*/

// Inclusão de bibliotecas padrões da linguagem
#include <stdio.h>  // Biblioteca padrão de entrada e saída
#include <stdlib.h> // Biblioteca padrão para manipulação de memória com uso dinâmico
#include <windows.h>
#include <string.h>

#include "Tipos_Registros.h" // Inclusão da biblioteca interna (criada para o projeto)
                             // Traz os dados primitivos e definição de registros e tipos

//  Protótipos das funções
int entrada_dados_turma(Turma *nova_turma);
Turma busca_turma(int aux);
int cadastro_turma(void);
void cria_lista_espera(void);
void imprime_turma(Turma aux);
void imprime_todas_turmas(void);
int qtd_turmas_cadastradas(void);
void excluir_turma(int codigo);
void editar_turma(int codigo);
void imprime_cabecalho_turma(void);
void imprime_fim_turma(void);

/**
* Função que preenche dados de uma turma, como entrada, fazendo todas as validações necessárias.
* Entrada (parâmetro(s)): <Turma *nova_turma> é a turma que receberá os dados captados (em ponteiro).
* Saída (retorno(s)): <int>, 0 para validação falsa, 1 para validação verdadeira.
* Saída: Serve como atribuição de retorno lógico.
*/
int entrada_dados_turma(Turma *nova_turma)
{
    printf("C%cdigo: ", 162);         // Questionando código
    fflush(stdin);                    // Limpando buffer do teclado
    scanf("%d", &nova_turma->codigo); // Armazenando código na variável de parâmetro

    Turma validador = busca_turma((*nova_turma).codigo); // Declaração e inicialização de variável auxiliar que busca uma possível turma com o código existente

    if ((validador.codigo != nova_turma->codigo) && (nova_turma->codigo >= 0)) // Caso não exista turma com esse código e nem ele seja menor que zero (0)
    {
        printf("Curso: ");                  // Questiona curso
        fflush(stdin);                      // Limpando buffer do teclado
        wscanf(L"%ls", &nova_turma->curso); // Armazenando curso na variável de parâmetro

        printf("Turno:\n[m] para manh%c\n[t] para tarde\n[n] para noite\n>> ", 198);          // Questiona turno
        fflush(stdin);                                                                        // Limpando buffer do teclado
        wscanf(L"%lc", &nova_turma->turno);                                                   // Armazenando turno na variável de parâmetro
        if (nova_turma->turno == 'm' || nova_turma->turno == 't' || nova_turma->turno == 'n') // Validando se o turno informado é valido
        {
            printf("Quantidade limite de alunos: "); // Questiona quantidade limite de alunos
            fflush(stdin);                           // Limpando buffer do teclado
            scanf("%d", &nova_turma->qtd_limite);    // Armazenando quantidade limite de alunos na variável de parâmetro
            if (nova_turma->qtd_limite > 0)          // Verificando se foi digitado nº positivo
                return 1;                            // Retornando inteiro lógico 1, dando sinal de que ocorreu tudo certo!
            else
                printf("Quantidade de alunos inv%clida!\n", 160);
        }
        else // Turno inválido
        {
            printf("\nTurno inv%clido!\n", 160);
        }
    }
    else // Código inválido
    {
        printf("\nN%co %c poss%cvel criar uma turma com esse c%cdigo!\n", 198, 130, 161, 162);
    }
    return 0; //  Retorno falso de processo não efetuado
}

/**
* Função que cadastra uma nova turma, incluíndo-a no arquivo correspondente.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois modifica direto componentes específicos.
* Saída (retorno(s)): <int>, 0 para validação falsa, 1 para validação verdadeira.
* Saída: Serve como atribuição de retorno lógico.
*/
int cadastro_turma(void)
{
    FILE *arquivo_turmas = fopen("Turmas.bin", "a+b"); //  Abre o arquivo 'Turmas.bin' e posiciona o ponteiro no final dele (abertura para gravação de dados)

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
    putchar(186);

    for (int i = 0; i < 74; i++)
    {

        if (i != 9 && i != 45 && i != 55 && i != 64)
            putchar(32);
        else
            putchar(186);
    }

    putchar(186);
    putchar(10);

    putchar(186);

    if (aux.turno == 'm')
        printf("%9d%c%-35ls%c  Manh%c  %c%8d%c%9d%c\n", aux.codigo, 186, aux.curso, 186, 198, 186, aux.qtd_alunos, 186, aux.qtd_limite, 186);
    else if (aux.turno == 't')
        printf("%9d%c%-35ls%c  Tarde  %c%8d%c%9d%c\n", aux.codigo, 186, aux.curso, 186, 186, aux.qtd_alunos, 186, aux.qtd_limite, 186);
    else
        printf("%9d%c%-35ls%c  Noite  %c%8d%c%9d%c\n", aux.codigo, 186, aux.curso, 186, 186, aux.qtd_alunos, 186, aux.qtd_limite, 186);

    putchar(186);

    for (int i = 0; i < 74; i++)
    {

        if (i != 9 && i != 45 && i != 55 && i != 64)
            putchar(32);
        else
            putchar(186);
    }
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

            if (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
            {
                imprime_cabecalho_turma();
                fseek(arquivo_turmas, 0, SEEK_SET);
            }

            while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
            {
                if (turma_aux.codigo >= 0)
                {
                    imprime_turma(turma_aux);
                    if (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
                    {
                        imprime_fim_turma();
                        fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);
                    }
                }
            }

            imprime_fim_turma();

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
    FILE *arquivo_turmas = fopen("Turmas.bin", "rb"); //  Abre o arquivo 'Turmas.bin'
    Turma turma_aux;                                  // Variável auxiliar

    if (arquivo_turmas) // Se arquivo foi aberto
    {
        while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas)) // Vare arquivo turma a turma
        {
            if (turma_aux.codigo == aux) // Se turma encontrada (comparação feita através do código)
            {
                fclose(arquivo_turmas); // fecha arquivo
                return turma_aux;       // retorna turma
            }
        }
        // caso não ocorra retorno antes (turma não encontrada)
        fclose(arquivo_turmas); // fecha o arquivo
    }
    else // Se arquivo não aberto
        printf("Problema no arquivo 'Turmas.bin'\n");

    turma_aux.codigo = -2; // coloca marcador lógico no código de retorno para eventuais verificações
    return turma_aux;      // retorna turma com marcação lógica
}

/**
* Função que conta a quantidade de turmas cadastradas, fora a lista de espera (que é um tipo especial de turma).
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois acessa direto componentes específicos.
* Saída (retorno(s)): <int> é o número de turmas contabilizado.
* Saída: Caso não encontre a turma, irá retornar registro com código de marcação lógica igual a -2.
*/
int qtd_turmas_cadastradas(void)
{
    FILE *arquivo_turmas = fopen("Turmas.bin", "rb"); //  Abre o arquivo 'Turmas.bin'
    int contador = 0;                                 // Variável auxiliar
    if (arquivo_turmas)                               // Se arquivo foi aberto
    {
        Turma turma_aux;                                            // Variável auxiliar
        while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas)) // Vare arquivo turma a turma
        {
            if (turma_aux.codigo != -1) // Caso não seja a lista de espera
                contador++;             // Incrementa contador
        }
        fclose(arquivo_turmas); // Fecha arquivo
    }
    else // Se arquivo não aberto
        printf("Problema no arquivo 'Turmas.bin'\n");
    return contador; // retorna contador
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

/**
* Função que exclui uma turma com base em uma dada matrícula.
* Entrada (parâmetro(s)): <int> código da turma a ser excluída.
* Saída (retorno(s)):  <void> sem retorno.
*/
void excluir_turma(int codigo)
{

    char escolha = '\0';

    printf("Excluir a turma acarretar%c tamb%cm na exclus%co de seus alunos.\nDeseja continuar? (S/N): ", 160, 130, 198);

    fflush(stdin);

    scanf("%c", &escolha);

    if (escolha == 'S' || escolha == 's')
    {
        FILE *arquivo_turmas = fopen("Turmas.bin", "r+b");

        if (arquivo_turmas)
        {

            Turma turma_aux;

            fseek(arquivo_turmas, 0, SEEK_SET);
            fseek(arquivo_turmas, 0, SEEK_END);

            int tamanho_maximo_turmas = ftell(arquivo_turmas);

            fseek(arquivo_turmas, 0, SEEK_SET);

            while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
            {

                if (turma_aux.codigo == codigo)
                {

                    if (ftell(arquivo_turmas) < tamanho_maximo_turmas)
                    {

                        while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
                        {

                            fseek(arquivo_turmas, sizeof(Turma) * -2, SEEK_CUR);

                            fwrite(&turma_aux, sizeof(Turma), 1, arquivo_turmas);

                            fseek(arquivo_turmas, sizeof(Turma), SEEK_CUR);
                        }

                        fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);
                    }
                    else
                        fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);

                    int tamanho = ftell(arquivo_turmas); //Obtém a posição do novo final

                    fclose(arquivo_turmas); //Fecha o arquivo

                    //Esta parte trunca o arquivo
                    HANDLE arquivo = CreateFileW(L"Turmas.bin", GENERIC_WRITE, 0, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL); //Abre o arquivo

                    SetFilePointer(arquivo, tamanho, NULL, 0); //Modifica a posição do cursor

                    SetEndOfFile(arquivo); //Trunca o arquivo, modificando a posição de seu final

                    CloseHandle(arquivo); //Fecha o arquivo

                    printf("A turma foi exclu%cda, bem como seus alunos!\n", 161);

                    break;
                }
            }

            FILE *arquivo_alunos = fopen("Alunos.bin", "r+b");

            if (arquivo_alunos)
            {

                Aluno aluno_aux;

                fseek(arquivo_alunos, 0, SEEK_SET);
                fseek(arquivo_alunos, 0, SEEK_END);

                int tamanho_maximo_alunos = ftell(arquivo_alunos);

                fseek(arquivo_alunos, 0, SEEK_SET);

                while (fread(&aluno_aux, sizeof(Aluno), 1, arquivo_alunos))
                {

                    if (aluno_aux.turma == codigo)
                    {

                        if (ftell(arquivo_alunos) < tamanho_maximo_alunos)
                        {

                            while (fread(&aluno_aux, sizeof(Aluno), 1, arquivo_alunos))
                            {

                                fseek(arquivo_alunos, sizeof(Aluno) * -2, SEEK_CUR);

                                fwrite(&aluno_aux, sizeof(Aluno), 1, arquivo_alunos);

                                fseek(arquivo_alunos, sizeof(Aluno), SEEK_CUR);
                            }
                        }
                        else
                            fseek(arquivo_alunos, sizeof(Aluno) * -1, SEEK_CUR);

                        int tamanho = ftell(arquivo_alunos); //Obtém a posição do novo final

                        fclose(arquivo_alunos); //Fecha o arquivo

                        //Esta parte trunca o arquivo
                        HANDLE arquivo = CreateFileW(L"Alunos.bin", GENERIC_WRITE, 0, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL); //Abre o arquivo

                        SetFilePointer(arquivo, tamanho, NULL, 0); //Modifica a posição do cursor

                        SetEndOfFile(arquivo); //Trunca o arquivo, modificando a posição de seu final

                        CloseHandle(arquivo); //Fecha o arquivo

                        tamanho_maximo_alunos -= sizeof(Aluno);

                        arquivo_alunos = fopen("Alunos.bin", "r+b");

                        continue;
                    }
                }

                fclose(arquivo_alunos);
            }
            else
                printf("Problema no arquivo 'Alunos.bin'\n");
        }
        else
            printf("Problema no arquivo 'Turmas.bin'\n");
    }
}

/**
* Função que edita uma turma com base em uma dada matrícula.
* Entrada (parâmetro(s)): <int> código da turma a ser editada.
* Saída (retorno(s)):  <void> sem retorno.
*/
void editar_turma(int codigo)
{

    char escolha = '\0';

    printf("Editar a turma acarretar%c na edi%c%co de todos os seus alunos.\nDeseja continuar? (S/N): ", 160, 135, 198);

    fflush(stdin);

    scanf("%c", &escolha);

    if (escolha == 'S' || escolha == 's')
    {

        FILE *arquivo_turmas = fopen("Turmas.bin", "r+b");

        Turma editar;

        Turma turma_aux;

        entrada_dados_turma(&editar);

        if (editar.codigo)
        {

            if (arquivo_turmas)
            {

                while (fread(&turma_aux, sizeof(Turma), 1, arquivo_turmas))
                {

                    if (turma_aux.codigo == codigo)
                    {

                        editar.qtd_alunos = turma_aux.qtd_alunos;

                        fseek(arquivo_turmas, sizeof(Turma) * -1, SEEK_CUR);
                        fwrite(&editar, sizeof(Turma), 1, arquivo_turmas);

                        fclose(arquivo_turmas);

                        FILE *arquivo_alunos = fopen("Alunos.bin", "r+b");

                        if (arquivo_alunos)
                        {

                            Aluno aluno_aux;

                            while (fread(&aluno_aux, sizeof(Aluno), 1, arquivo_alunos))
                            {

                                if (aluno_aux.turma == codigo)
                                {

                                    fseek(arquivo_alunos, sizeof(Aluno) * -1, SEEK_CUR);

                                    aluno_aux.turma = editar.codigo;

                                    fwrite(&aluno_aux, sizeof(Aluno), 1, arquivo_alunos);
                                    fclose(arquivo_alunos);
                                    fopen("Alunos.bin", "r+b");
                                }
                            }

                            break;
                        }
                        else
                            printf("Problema no arquivo 'Alunos.bin'\n");

                        printf("A turma foi editada, bem como seus alunos!\n");
                    }
                }
            }
            else
                printf("Problema no arquivo 'Turmas.bin'\n");
        }
    }
}

/**
* Função que imprime o cabeçalho da tabela de turmas.
* Entrada (parâmetro(s)): <void> nenhum parâmetro é recebido, pois a função faz impressão estática.
* Saída (retorno(s)):  <void> sem retorno.
*/
void imprime_cabecalho_turma(void)
{

    putchar(201);

    for (int i = 0; i < 74; i++)
    {

        if (i != 9 && i != 45 && i != 55 && i != 64)
            putchar(205);
        else
            putchar(203);
    }

    putchar(187);
    putchar(10);

    putchar(186);

    for (int i = 0; i < 74; i++)
    {

        if (i != 9 && i != 45 && i != 55 && i != 64)
            putchar(32);
        else
            putchar(186);
    }

    putchar(186);
    putchar(10);

    printf("%c  C%cdigo %c               Curso               %c  Turno  %c Alunos %c  Limite %c\n", 186, 162, 186, 186, 186, 186, 186);

    putchar(186);

    for (int i = 0; i < 74; i++)
    {

        if (i != 9 && i != 45 && i != 55 && i != 64)
            putchar(32);
        else
            putchar(186);
    }

    putchar(186);
    putchar(10);

    putchar(204);

    for (int i = 0; i < 74; i++)
    {

        if (i != 9 && i != 45 && i != 55 && i != 64)
            putchar(205);
        else
            putchar(206);
    }

    putchar(185);
    putchar(10);
}

/**
* Função que imprime a parte inferior da linha de uma turma na tabela de impressão.
* Entrada (parâmetro(s)): <void> nenhum parâmetro é recebido, pois a função faz impressão estática.
* Saída (retorno(s)):  <void> sem retorno.
*/
void imprime_fim_turma(void)
{

    putchar(186);
    putchar(10);

    putchar(204);

    for (int i = 0; i < 74; i++)
    {

        if (i != 9 && i != 45 && i != 55 && i != 64)
            putchar(205);
        else
            putchar(206);
    }

    putchar(185);
    putchar(10);
}
