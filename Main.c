/**
 * Programa principal, arquivo com código fonte principal "Main.c".
 * Implementação das funções que tratam da manipulação e curadoria dos dados das turmas.
 * Criado em: 29/10/2020.
 * Última modificação por Nicolas Fischer no dia 08/12/2020.
*/

// Inclusão de bibliotecas padrões da linguagem
#include <stdio.h>   // Biblioteca padrão de entrada e saída
#include <stdlib.h>  // Biblioteca padrão para manipulação de memória com uso dinâmico
#include <windows.h> // Biblioteca padrão do Windows

#include "Manipulacao_Alunos.h" // Inclusão da biblioteca interna (criada para o projeto)
                                // Traz as funções de manipulação dos alunos
                                // As demais importações foram feitas nessa biblioteca, sendo nescessário refazer.

/**
* Função que possui o menu que exibe as opções de escolha ao usuário, captura a escolha e executa as funções.
* Entrada (parâmetro(s)): <void> sem parâmetro válido, pois modifica direto componentes específicos.
* Saída (retorno(s)): <void> sem retorno.
*/
int main(void)
{
    // Declaração de variáveis auxiliares
    Aluno aux_a;
    Turma aux_t;

    //  Caso nao tenha sido criada a lista de espera
    aux_t = busca_turma(-1);    // Buscando turma especial (lista de espera)
    if (aux_t.codigo != -1) // Caso não encontre a lista de espera (turma especial, com código -1)
        cria_lista_espera(); // É criada a lista de espera (inicializado os atributos)

    while (1)   // Laço continuo de seleção das opções
    {
        // Declaração de variáveis auxiliares
        int escolha;
        int i = 0;

        // Variável auxiliar que guarda a quantidade de alunos
        // Evita que a função seja chamada mais de uma vez em verificações naquele instante do laço
        int qtd_alunos = qtd_alunos_cadastrados();
        int qtd_turmas = qtd_turmas_cadastradas();

        // Menu principal, é exibido em todas as hipóteses
        printf("\n________________SISTEMA DE CURSOS______________\n");
        printf("\nTecle '-1' para saber mais sobre este programa!");
        printf("\nOu digite a op%c%co desejada:\n\n", 135, 198);
        printf("[0] Sair e encerrar o programa\n");
        printf("[1] Cadastrar turma\n");
        printf("[2] Cadastrar aluno na lista de espera\n");
        printf("[3] Ver lista de espera\n");

        if (qtd_turmas > 1)   // Menu de manipulação intermediário que é exibido se houver ao menos uma turma (não levando em consideração a lista de espera)
        {
            printf("[4] Ver dados das turmas\n");
            printf("[5] Buscar turma\n");
            printf("[6] Editar turma\n");
            printf("[7] Excluir turma\n");
            printf("[8] Quantidade de turmas cadastradas\n");
            printf("[9] Cadastrar aluno\n");
        }

        if (qtd_turmas > 1 && qtd_alunos > 0) // Menu de manipulação final, se tiver houver ao menos um aluno e ao menos uma turma
        {

            printf("[10] Ver os alunos por turma\n");
            printf("[11] Ver todos os alunos\n");
            printf("[12] Buscar aluno\n");
            printf("[13] Editar aluno\n");
            printf("[14] Desmatricular aluno\n");
            printf("[15] Quantidade de alunos cadastrados\n");
        }

        fflush(stdin);  // Limpa buffer do teclado
        scanf("%d", &escolha);  // Recebe e armazena a escola (opção digitada)

        switch (escolha)    // Estrutura de condição, evita ambiguidade na visibilidade das opções, ocorre todas as hipóteses
        {
        case -1:    // Rotina sobre
            printf("Que bom que quer saber sobre n%cs =)\nEsse %c um projeto acad%cmico da disciplina de Programa%c%co para Resolu%c%co de Problemas (2/2020 da UNISC).\nDesenvolvido pelo Nicolas Fischer, Patrick Priebe e Bruno Bolzan; e orientado pelo Prof. Ivan S.\nO mesmo consiste num sistema de cursos onde se pode manipular de variadas formas as turmas e alunos!\nS%co utilizadas estruturas de registro com grava%c%co dos dados em arquivos bin%crios (.bin).\nTamb%cm s%co empregados conceitos das estruturas de dados como: listas lineares, filas e pilhas (n%co encadeadas).\nLinguagem: C 99.\n", 162, 130, 136, 135, 198, 135, 198, 198, 135, 198, 160, 130, 198, 198);
            break;
        case 0: // Rotina saída
            printf("\nAt%c logo!!\n", 130);
            Sleep(5);
            exit(1);
        case 1: // Rotina cadastrar turma
            cadastro_turma();
            atualizar_lista_espera();
            break;
        case 2: // Rotina cadastrar aluno na lista de espera
            cadastrar_aluno_espera();
            break;
        case 3: // Rotina imprimir a lista de espera
            imprime_lista_espera();
            break;
        default:
            break;
        }

        if (qtd_turmas > 1) // Caso haja ao menos uma turma (não levando em consideração a lista de espera)
        {

            switch (escolha)    // Estrutura de condição, evita ambiguidade na visibilidade das opções
            {

            case 4: // Rotina imprimir todas as turmas
                imprime_todas_turmas();
                break;

            case 5: // Rotina imprime dados de uma turma
                printf("C%cdigo: ", 162);
                fflush(stdin);
                scanf("%d", &i);
                aux_t = busca_turma(i);
                if (aux_t.codigo >= 0){
                    imprime_cabecalho_turma();
                    imprime_turma(aux_t);
                    imprime_fim_tabela_turma();
                }
                else
                    printf("\nTurma n%co encontrada\n", 198);
                break;
              case 6: // Rotina editar dados de uma turma
                printf("Digite o codigo da turma que deseja editar: ");
                fflush(stdin);
                scanf("%d", &i);
                aux_t = busca_turma(i);
                if (aux_t.codigo >= 0)
                    editar_turma(i);
                else
                    printf("Turma n%co encontrada.\n", 198);
                break;
                break;
            case 7: // Rotina exclui uma turma
                printf("Digite o codigo da turma que deseja excluir: ");
                fflush(stdin);
                scanf("%d", &i);
                aux_t = busca_turma(i);
                if (aux_t.codigo >= 0)
                    excluir_turma(i);
                else
                    printf("Turma n%co encontrada.\n", 198);
                break;
            case 8: // Rotina quantidade de turmas
                printf("Ha %d turma(s)!\n", qtd_turmas - 1);
                break;

            case 9: // Rotina cadastrar aluno
                cadastrar_aluno();
                break;
            default:
                break;
            }
        }

        if (qtd_turmas > 1 && qtd_alunos > 0)   //Se houver ao menos um aluno e ao menos uma turma
        {
            switch (escolha)    // Estrutura de condição, evita ambiguidade na visibilidade das opções
            {
            case 10:    // Rotina imprime todos os alunos de uma turma
                printf("C%cdigo: ", 162);
                fflush(stdin);
                scanf("%d", &i);
                aux_t = busca_turma(i);
                if (aux_t.codigo >= 0 || aux_t.qtd_alunos != 0)
                    imprime_alunos_turma(aux_t);
                else
                    printf("N%co foi poss%cvel encontrar essa turma ou sem alunos nela!\n", 198, 161);
                break;
            case 11:    // Rotina imprimir todos os alunos
                imprimir_todos_alunos();
                break;
            case 12:    // Rotina buscar aluno
                printf("Matr%ccula: ", 161);
                fflush(stdin);
                scanf("%d", &i);
                aux_a = buscar_aluno(i);
                if (aux_a.matricula != -2){

                    puts("\n");

                    imprime_cabecalho_aluno();

                    imprime_aluno(aux_a, 0);

                    imprime_fim_tabela_aluno();

                }
                else
                    printf("Aluno n%co encontrado!\n", 198);
                break;
            case 13:    // Rotina editar aluno
                printf("Matr%ccula: ", 161);
                fflush(stdin);
                scanf("%d", &i);
                editar_aluno(i);
                break;
            case 14:    // Rotina excluir (desmatricular) aluno
                printf("Matr%ccula: ", 161);
                fflush(stdin);
                scanf("%d", &i);
                desmatricular_aluno(i);
                atualizar_lista_espera();
                break;
            case 15:    // Rotina quantidade de alunos
                printf("Ha %d alunos cadastrados (incluindo os da lista de espera)!\n", qtd_alunos_cadastrados());
                break;
            default:
                break;
            }
        }
        if (escolha > 15 || escolha < -1) // Caso não valide nenhuma escolha
            printf("Op%c%co inv%clida!\n", 135, 198, 160);

        fflush(stdin);  // Limpa buffer do teclado
        getchar();  // Parada de tela, espera digitar algo
        system("cls");  // Limpa tela
    }   // fim do while (1)
    return 0;   // Retorno da função principal
}
