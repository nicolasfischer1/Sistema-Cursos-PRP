/**
 * Arquivo com código-fonte de uma biblioteca: "Var_Types-INTERNAL.h".
 * Definição das estruturas de registro e tipos de variáveis criadas com base nelas.
 * Criado em: 29/10/2020.
 * Última modificação por Nicolas Fischer no dia 29/10/2020.
*/

struct aluno //  Estrutura (registro) "aluno"
{
    int matricula;
    char nome[30];
    int idade;
    int turma;
};

struct turma //   Estrutura (registro) "turma"
{
    int codigo;
    char curso[60];
    char turno;
    int qtd_alunos;
    int qtd_limite;
};

//  Definindo os tipos a partir das estruturas (registros)
typedef struct aluno aluno;
typedef struct turma turma;
