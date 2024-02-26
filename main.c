#include "libs.h"
#include "TreeRedBlack.h"

//usando a arvore que esta implementada no arquivo TreeRedBlack.c
//para rodar com gcc o comando no terminal é: gcc main.c TreeRedBlack.c -o main
int main()
{
    rbtree *arvore = criarArvore(); // criando uma arvore rubro negra - red black
    int opcao = 0; // variavel para armazenar a opcao do usuario
    int id = 0; // variavel para armazenar o id do no que o usuario quer inserir

   do
    {
        printf("1 - Inserir no\n  4 - Sair\n"); // menu de opcoes
        scanf("%d", &opcao); // lendo a opcao do usuario
        switch (opcao) // switch case para as opcoes
        {
        case 1: // caso a opcao seja 1
            system("clear"); // limpando a tela
            printf("Digite o id do no que deseja inserir: "); // pedindo para o usuario digitar o id do no que ele quer inserir
            scanf("%d", &id); // lendo o id do no que o usuario quer inserir
            inserirNo(arvore, id); // chamando a funcao para inserir um no na arvore
            break; // saindo do switch case

        case 4: // caso a opcao seja 4
            system("clear"); // limpando a tela
            printf("Saindo...\n"); // mensagem de saida
            break; // saindo do switch case
        }

    }  while (opcao != 4); // enquanto a opcao for diferente de 4

    visualizarArvoreDot(arvore); // funcao do graphviz para visualizar a arvore passando por parametro a arvore
    return 0; // retornando 0
}
