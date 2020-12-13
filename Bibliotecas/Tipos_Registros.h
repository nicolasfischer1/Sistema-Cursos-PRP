/**
 * Biblioteca "Tipos_Registros.h".
 * Definição das estruturas de registro e tipos de variáveis criadas com base nelas.
 * Criado em: 29/10/2020.
 * Última modificação por Nicolas Fischer no dia 08/10/2020.
*/

struct aluno //  Estrutura (registro) "aluno"
{
    int matricula;
    wchar_t nome[60];
    int idade;
    int turma;
    int aux;
};

struct turma //   Estrutura (registro) "turma"      // Lista de espera é um tipo especial de turma, na qual tem código lógico para encontro, que é igual a -1.
{
    int codigo;
    wchar_t curso[60];
    wchar_t turno; // [m] para manhã; [t] para tarde; [n] para noite
    int qtd_alunos;
    int qtd_limite;
};

//  Definindo os tipos a partir das estruturas (registros)
typedef struct aluno Aluno;
typedef struct turma Turma;
