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
        printf("1 - Inserir \n2 - Buscar\n3 - Remover\n4 - Altura Total da arvore\n5 - Altura Negra\n6 - Vizualizar info nos\n7 -Percento Negro\n8 - Percento Rubro\n9 - Custo de busca \n0 - Sair\n"); // menu de opcoes
        scanf("%d", &opcao); // lendo a opcao do usuario
        switch (opcao) // switch case para as opcoes
        {
        case 1: // caso a opcao seja 1
            system("clear"); // limpando a tela
            printf("Digite o id do no que deseja inserir: \n"); // pedindo para o usuario digitar o id do no que ele quer inserir
            scanf("%d", &id); // lendo o id do no que o usuario quer inserir
            //id tem necessariamente precisa conter 4 digitos, indo de 0001 ate 9999 e o id nao pode ser repetido
            if (id < 10000 && id > 999 && !buscarNo(arvore, id)) // se o id for valido e nao existir na arvore
            {
                inserirNo(arvore, id); // inserindo o no na arvore
                visualizarArvoreDot(arvore); // funcao do graphviz para visualizar a arvore passando por parametro a arvore

                printf("No inserido com sucesso!\n"); // mensagem de sucesso
            }
            else // se o id nao for valido ou ja existir na arvore
            {
                printf("Id invalido ou ja existente!\nSo aceitamos matricular entre 1000 e 9999\n"); // mensagem de erro
            }
            break; // saindo do switch case
        case 2: // caso a opcao seja 2
            system("clear"); // limpando a tela
            printf("Digite o id do no que deseja buscar: "); // pedindo para o usuario digitar o id do no que ele quer buscar
            scanf("%d", &id); // lendo o id do no que o usuario quer buscar
            if (buscarNo(arvore, id)) // se o no existir na arvore
            {
                printf("No encontrado!\n"); // mensagem de sucesso
            }
            else // se o no nao existir na arvore
            {
                printf("No nao encontrado!\n"); // mensagem de erro
            }
            break; // saindo do switch case
        case 3: // caso a opcao seja 3
            system("clear"); // limpando a tela
            printf("Digite o id do no que deseja remover: "); // pedindo para o usuario digitar o id do no que ele quer remover
            scanf("%d", &id); // lendo o id do no que o usuario quer remover
            if (buscarNo(arvore, id)) // se o no existir na arvore
            {
                removerNo(arvore, id); // removendo o no da arvore
                visualizarArvoreDot(arvore); // funcao do graphviz para visualizar a arvore passando por parametro a arvore

                printf("No removido com sucesso!\n"); // mensagem de sucesso
            }
            else // se o no nao existir na arvore
            {
                printf("No nao encontrado!\n"); // mensagem de erro
            }
            break; // saindo do switch case
        case 4: // caso a opcao seja 4
            system("clear"); // limpando a tela
            printf("Altura total da arvore: %d\n", alturaArvore(arvore->raiz)); // imprimindo a altura total da arvore
            break; // saindo do switch case
        case 5: // caso a opcao seja 
            system("clear"); // limpando a tela
            printf("Altura total Negra da arvore: %d\n", alturaNegra(arvore->raiz));
            break; // saindo do switch
        case 6: // caso a opcao seja 6
            system("clear"); // limpando a tela
            printarNos(arvore->raiz); // imprimindo os nos da arvore
            break; // saindo do switch case
        case 7: // caso a opcao seja 7
            system("clear"); // limpando a tela
            printf("Considerando a as folhas como negras:\n");
            printf("A Percentagem de nos negros é de: %f", percentagemNegra(arvore->raiz));
            break;
        case 8:
            system("clear");
            printf("Considerando a as folhas como negras:\n");
            printf("A Percentagem de nos Rubros é de: %f\n", percentagemVermelha(arvore->raiz));
            break;
        case 9:
            system("clear");
            printf("O custo medio de busca é: %f", custoMedioBusca(arvore, id));  //numero de comparacao de chaves
            break;
        case 0: // caso a opcao seja 4
            system("clear"); // limpando a tela
            printf("Saindo...\n"); // mensagem de saida
            break; // saindo do switch case
        }

    }  while (opcao != 0); // enquanto a opcao for diferente de 4
    return 0; // retornando 0

   
}