/**
 * Arquivo com c�digo-fonte de uma biblioteca: "Tipos_Registros.h".
 * Defini��o das estruturas de registro e tipos de vari�veis criadas com base nelas.
 * Criado em: 29/10/2020.
 * �ltima modifica��o por Nicolas Fischer no dia 29/10/2020.
*/

struct aluno //  Estrutura (registro) "aluno"
{
    int matricula;
    wchar_t nome[60];
    int idade;
    int turma;
};

struct turma //   Estrutura (registro) "turma"
{
    int codigo;
    wchar_t curso[60];
    wchar_t turno; // [M] para manh�; [T] para tarde; [N] para noite
    int qtd_alunos;
    int qtd_limite;
};

//  Definindo os tipos a partir das estruturas (registros)
typedef struct aluno Aluno;
typedef struct turma Turma;
