/**
 * Arquivo com código-fonte de uma biblioteca: "Tipos_Registros.h".
 * Definição das estruturas de registro e tipos de variáveis criadas com base nelas.
 * Criado em: 29/10/2020.
 * Última modificação por Nicolas Fischer no dia 29/10/2020.
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
    wchar_t turno; // [M] para manhã; [T] para tarde; [N] para noite
    int qtd_alunos;
    int qtd_limite;
};

//  Definindo os tipos a partir das estruturas (registros)
typedef struct aluno Aluno;
typedef struct turma Turma;
