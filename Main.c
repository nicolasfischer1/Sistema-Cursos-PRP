#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Manipulacao_Alunos.h"

int main(void)
{
    int escolha;
    Aluno aux_a;
    //  Caso nao tenha sido criada a lista de espera
    Turma aux_t;
    aux_t = busca_turma(-1);
    if (aux_t.codigo != -1)
        cria_lista_espera();

    while (1)
    {
        int i = 0;
        int validador = qtd_alunos_cadastrados();

        printf("\n________________SISTEMA DE CURSOS______________\n");
        printf("\nTecle '-1' para saber mais sobre este programa!");
        printf("\nOu digite a op%c%co desejada:\n\n", 135, 198);
        printf("[0] Sair e encerrar o programa\n");
        printf("[1] Cadastrar turma\n");
        printf("[2] Cadastrar aluno na lista de espera\n");
        printf("[3] Ver lista de espera\n");

        if (qtd_turmas() > 1)
        {
            printf("[4] Ver dados das turmas\n");
            printf("[5] Buscar turma\n");
            printf("[6] Editar turma\n");
            printf("[7] Excluir turma\n");
            printf("[8] Quantidade de turmas cadastradas\n");
            printf("[9] Cadastrar aluno\n");
        }

        if (qtd_turmas() > 1 && validador > 0)
        {

            printf("[10] Ver os alunos por turma\n");
            printf("[11] Ver todos os alunos\n");
            printf("[12] Buscar aluno\n");
            printf("[13] Editar aluno\n");
            printf("[14] Desmatricular aluno\n");
            printf("[15] Quantidade de alunos cadastrados\n");
        }

        fflush(stdin);
        scanf("%d", &escolha);

        switch (escolha)
        {
        case -1:
            printf("Que bom que quer saber sobre n%cs =)\nEsse %c um projeto acad%cmico da disciplina de Programa%c%co para Resolu%c%co de Problemas (2/2020 da UNISC).\nDesenvolvido pelo Nicolas Fischer, Patrick Priebe e Bruno Bolzan; e orientado pelo Prof. Ivan S.\nO mesmo consiste num sistema de cursos onde pode-se manipular de variadas formas as turmas e alunos!\nS%co utilizadas estruturas de registro com grava%c%co dos dados em arquivos bin%crios (.bin).\nTamb%cm %c empregado conceitos das estruturas de dados como: listas lineares, filas e pilhas (n%co encadeadas).\nLinguagem: C 99.\n", 162, 130, 136, 135, 198, 135, 198, 198, 135, 198, 160, 130, 130, 198);
            break;
        case 0:
            printf("\nAt%c logo!!\n", 130);
            Sleep(5);
            exit(1);
        case 1:
            cadastro_turma();
            break;
        case 2:
            cadastrar_aluno_espera();
            break;
        case 3:
            imprime_lista_espera();
            break;
        }

        if (qtd_turmas() > 1)
        {

            switch (escolha)
            {

            case 4:
                imprime_todas_turmas();
                break;

            case 5:
                printf("C%cdigo: ", 162);
                fflush(stdin);
                scanf("%d", &i);
                aux_t = busca_turma(i);
                if (aux_t.codigo >= 0)
                    imprime_turma(aux_t);
                else
                    printf("\nTurma n%co encontrada\n", 198);
                break;
            /* case 6:
                editar_turma(i);
                break;*/
            /*case 7:
                printf("Digite o codigo da turma que deseja excluir: ");
                fflush(stdin);
                scanf("%d", &i);
                aux = busca_turma(i);
                if (aux.codigo >= 0)
                    excluir_turma(i);
                break;*/
            case 8:
                printf("Ha %d turma(s)!\n", qtd_turmas() - 1);
                break;

            case 9:
                cadastrar_aluno();
                break;
            }
        }

        if (qtd_turmas() > 1 && validador > 0)
        {
            switch (escolha)
            {
            case 10:
                printf("C%cdigo: ", 162);
                fflush(stdin);
                scanf("%d", &i);
                aux_t = busca_turma(i);
                if (aux_t.codigo >= 0)
                    imprime_alunos_turma(aux_t);
                else
                    printf("N%co foi poss%cvel encontrar essa turma!\n", 198, 161);
                break;
            case 11:
                imprimir_todos_alunos();
                break;
            case 12:
                printf("Matr%ccula: ", 161);
                fflush(stdin);
                scanf("%d", &i);
                aux_a = buscar_aluno(i);
                if (aux_a.matricula != -2)
                    imprime_aluno(aux_a);
                else
                    printf("Aluno n%co encontrado!\n", 198);
                break;
            case 13:
                printf("Matr%ccula: ", 161);
                fflush(stdin);
                scanf("%d", &i);
                editar_aluno(i);
                break;
            case 14:
                printf("Matr%ccula: ", 161);
                fflush(stdin);
                scanf("%d", &i);
                desmatricular_aluno(i);
                break;
            case 15:
                printf("Ha %d alunos cadastrados (incluindo os da lista de espera)!\n", qtd_alunos_cadastrados());
                break;
            }
        }
        if (escolha > 15 || escolha < -1)
            printf("Op%c%co inv%clida!\n", 135, 198, 160);

        fflush(stdin);
        getchar();
        system("cls");
    }
    return 0;
}
