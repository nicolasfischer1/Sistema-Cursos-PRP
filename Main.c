#include <stdio.h>
#include <stdlib.h>
#include "Bibliotecas/Manipulacao_Alunos.h"
#include "Bibliotecas/Manipulacao_Turmas.h"
#include "Bibliotecas/Tipos_Registros.h"

int main(void)
{
    int escolha;

    //  Caso não tenha sido criada a lista de espera
    Turma aux;
    aux = busca_turma(-1);
    if (aux.codigo != -1)
        cria_lista_espera();

    while (1)
    {
        printf("Digite o n%cmero correspondente %c op%c%co desejada:\n", 163, 133, 135, 198);
        printf("[0] Sair e encerrar o programa\n");
        printf("[1] Cadastrar nova turma\n");
        printf("[2] Cadastrar aluno na lista de espera\n");

        if (qtd_turmas() != 0)
        {
            printf("[3] Ver todas as turmas\n");
            printf("[4] Buscar turma\n");
            printf("[5] Editar turma\n");
            printf("[6] Excluir turma\n");
            printf("[7] Ver quantidade de turmas cadastradas\n");
            printf("[8] Cadastrar aluno\n");
        }

        /*
        if (qtd_alunos() != 0)
        {
            printf("[9] Ver lista de espera\n");
            printf("[10] Ver os alunos de uma turma\n");
            printf("[11] Ver todos os alunos\n");
            printf("[12] Buscar aluno pela matr%ccula\n", 161);
            printf("[13] Editar dados de um aluno\n");
            printf("[14] Desmatricular aluno\n");
            printf("[15] Ver quantidade de alunos cadastrados\n");
        }
*/

        fflush(stdin);
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            printf("\nAt%c logo!!\n", 130);
            sleep(5);
            exit(1);
        case 1:
            cadastro_turma();
            break;
        /*case 2:
            cadastrar_aluno_espera();
            break;*/
        }

        if (qtd_turmas() != 0)
        {
            switch (escolha)
            {
            case 3:
                imprime_todas_turmas();
                break;
            case 4:
                printf("Digite o código da turma para buscar: ");
                fflush(stdin);
                scanf("%d", &escolha);
                aux = busca_turma(escolha);
                if (aux.codigo >= 0)
                    imprime_turma(aux);
                break;
            /* case 5:
                editar_turma(escolha);
                break;
            case 6:
                printf("Digite o código da turma que deseja excluir: ");
                fflush(stdin);
                scanf("%d", &escolha);
                aux = busca_turma(escolha);
                if (aux.codigo >= 0)
                    excluir_turma(escolha);
                break;*/
            case 7:
                printf("Há %d turma (s)!\n", qtd_turmas());
                break;
            /*case 8:
                cadastrar_aluno();
                break;*/
            }
        }

    
     if (qtd_alunos() != 0)
     {
     switch (escolha)
            {
                case 9:
                    imprime_lista_espera();
                    break;
                /*case 10:
                    printf("Digite o código da turma que deseja ver: ");
                    fflush(stdin);
                    scanf("%d", &escolha);
                    aux = busca_turma(escolha);
                    if (aux.codigo >= 0)
                        imprimir_alunos_turma(escolha);
                    break;
                case 11:
                    imprimir_todos_alunos();
                    break;
                case 12:
                .
                .
                .
                .
                .
                .
                .
                .
                */
                default:
                    printf("Opção inválida!\n");
                    break;
            }
    }
    fflush(stdin);
    getchar();
    system("cls");
}
    return 0;
}
