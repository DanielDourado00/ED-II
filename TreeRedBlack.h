#ifndef TREEREDBLACK_H
#define TREEREDBLACK_H
#include <stdio.h>

#define RED 0
#define BLACK 1

struct TreeRedBlackNode
{
    int id;
    int cor;
    struct TreeRedBlackNode *esq;   
    struct TreeRedBlackNode *dir;   
    struct TreeRedBlackNode *pai;   // ponteiro para o no pai, esta struct é auto referenciada 
};

typedef struct TreeRedBlackNode TreeRedBlackNode; // typedef para simplificar a chamada NODE

struct rbtree
{
    TreeRedBlackNode *raiz; // ponteiro para o no raiz da arvore
    size_t tam; // tamanho da arvore  size_t = unsigned int que significa o tamanho de um objeto
};

typedef struct rbtree rbtree; // typedef para simplificar a chamada TREE



TreeRedBlackNode *criarNo(int id, int cor, TreeRedBlackNode *esq, TreeRedBlackNode *dir, TreeRedBlackNode *pai);
rbtree *criarArvore();
void inserirNo(rbtree *arvore, int id);
void inserirFixup(rbtree *arvore, TreeRedBlackNode *novoNo);
void rotacaoEsquerda(rbtree *arvore, TreeRedBlackNode *no);
void rotacaoDireita(rbtree *arvore, TreeRedBlackNode *no);
TreeRedBlackNode *buscarNo(rbtree *arvore, int id);
void removerNo(rbtree *arvore, int id);
void removerFixup(rbtree *arvore, TreeRedBlackNode *no, TreeRedBlackNode *pai);
int alturaArvore(TreeRedBlackNode *no);
int alturaNegra(TreeRedBlackNode *no);
void printarNos(TreeRedBlackNode *no);
float percentagemNegra(TreeRedBlackNode *no);   // funcao para calcular a porcentagem de nos negros
float percentagemVermelha(TreeRedBlackNode *no);    // funcao para calcular a porcentagem nos rubros
double custoMedioBusca(rbtree *arvore, int id);
void gerarDOT(TreeRedBlackNode *no, FILE *arquivoDOT);
void visualizarArvoreDot(rbtree *arvore);

#endif // TREEREDBLACK_H