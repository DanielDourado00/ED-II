#ifndef TREEREDBLACK_H
#define TREEREDBLACK_H
#include <stdio.h>

typedef struct TreeRedBlackNode TreeRedBlackNode; // typedef para simplificar a chamada NODE
typedef struct rbtree rbtree; // typedef para simplificar a chamada TREE
//file

TreeRedBlackNode *criarNo(int id, int cor, TreeRedBlackNode *esq, TreeRedBlackNode *dir, TreeRedBlackNode *pai);
rbtree *criarArvore();
void inserirNo(rbtree *arvore, int id);
void inserirFixup(rbtree *arvore, TreeRedBlackNode *novoNo);
void rotacaoEsquerda(rbtree *arvore, TreeRedBlackNode *no);
void rotacaoDireita(rbtree *arvore, TreeRedBlackNode *no);
TreeRedBlackNode *buscarNo(rbtree *arvore, int id);
void removerNo(rbtree *arvore, int id);
void removerFixup(rbtree *arvore, TreeRedBlackNode *no, TreeRedBlackNode *pai);

void gerarDOT(TreeRedBlackNode *no, FILE *arquivoDOT);
void visualizarArvoreDot(rbtree *arvore);

#endif // TREEREDBLACK_H