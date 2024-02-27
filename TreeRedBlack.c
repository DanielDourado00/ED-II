#include "libs.h"
#include "TreeRedBlack.h"

/* definindo cores da arvore rubro negra - red black */



/* ===================================CRIACAO=================================== */
/* funcao para criar um no da arvore rubro negra - red black */
TreeRedBlackNode *criarNo(int id, int cor, TreeRedBlackNode *esq, TreeRedBlackNode *dir, TreeRedBlackNode *pai)
{
    TreeRedBlackNode *novoNo = (TreeRedBlackNode *)malloc(sizeof(TreeRedBlackNode)); // alocando memoria para o novo no
    novoNo->id = id; // setando o id do novo no, este id vai ser digitado pelo usuario
    novoNo->cor = cor; // setando a cor do novo no
    novoNo->esq = esq; // setando o filho esquerdo do novo no
    novoNo->dir = dir; // setando o filho direito do novo no
    novoNo->pai = pai; // setando o pai do novo no
    return novoNo; // retornando o novo no
}

/* funcao para criar uma arvore rubro negra - red black */
rbtree *criarArvore()
{
    rbtree *novaArvore = (rbtree *)malloc(sizeof(rbtree)); // alocando memoria para a nova arvore (novaArvore é um ponteiro para rbtree onde tem tamanho e raiz)
    novaArvore->raiz = NULL; // setando a raiz da nova arvore como nula, lembrando que a raiz é negra
    novaArvore->tam = 0; // setando o tamanho da nova arvore como 0
    return novaArvore; // retornando a nova arvore
}

/* ===================================CRIACAO=================================== */


/* ===================================INSERCAO=================================== */

//funcao para inserir um no na arvore rubro negra - red black
void inserirNo(rbtree *arvore, int id)
{
    TreeRedBlackNode *novoNo = criarNo(id, RED, NULL, NULL, NULL); // criando um novo no com o id digitado pelo usuario, cor vermelha, sem filhos e sem pai
    TreeRedBlackNode *aux = NULL; // criando um no auxiliar para percorrer a arvore
    TreeRedBlackNode *aux2Raiz = arvore->raiz; // criando um no auxiliar 2 que vai ser a raiz da arvore
    while (aux2Raiz != NULL) // enquanto o no auxiliar 2 for diferente de nulo, ou seja, enquanto a arvore nao estiver vazia
    {
        aux = aux2Raiz; // o no auxiliar recebe o no auxiliar 2
        if (novoNo->id < aux2Raiz->id) // se o id do novo no for menor que o id do no auxiliar 2, onde aux2Raiz é a raiz
        {
            aux2Raiz = aux2Raiz->esq; // o no auxiliar 2 recebe o filho esquerdo do no auxiliar 2 (pensando na arvore binaria)
        }
        else // se o id do novo no for maior que o id do no auxiliar 2
        {
            aux2Raiz = aux2Raiz->dir; // o no auxiliar 2 recebe o filho direito do no auxiliar 2
        }
    }

    novoNo->pai = aux; // o pai do novo no recebe o no auxiliar, ou seja, o no que vai ser o pai do novo no

    if (aux == NULL) // se o no auxiliar for nulo, ou seja, se a arvore estiver vazia
    {
        arvore->raiz = novoNo; // a raiz da arvore recebe o novo no
    }
    else if (novoNo->id < aux->id) // se o id do novo no for menor que o id do no auxiliar, onde o auxiliar é o pai do novo no
    {
        aux->esq = novoNo; // o filho esquerdo do no auxiliar recebe o novo no, ou seja, o novo no vai ser o filho esquerdo do no auxiliar
        //printf("O no %d foi inserido com sucesso!\n", novoNo->id); 
    }
    else // se o id do novo no for maior que o id do no auxiliar
    {
        aux->dir = novoNo; // o filho direito do no auxiliar recebe o novo no
    }
    novoNo->esq = NULL; // o filho esquerdo do novo no recebe nulo
    novoNo->dir = NULL; // o filho direito do novo no recebe nulo
    novoNo->cor = RED; // a cor, pq o novo no é vermelho
    arvore->tam++; // o tamanho da arvore aumenta
    inserirFixup(arvore, novoNo); // chamando a funcao para corrigir a arvore
}

//*funcao para concertar a arvore rubro negra - red black

void inserirFixup(rbtree *arvore, TreeRedBlackNode *novoNo) 
{
    while (novoNo->pai != NULL && novoNo->pai->cor == RED) // enquanto o pai do novo no for diferente de nulo e a cor do pai do novo no for vermelha
    {
        //*caso 1e
        if (novoNo->pai == novoNo->pai->pai->esq) // se o pai do novo no for igual ao filho esquerdo do avo do novo no
        {
            TreeRedBlackNode *tio = novoNo->pai->pai->dir; // criando um no tio que vai ser o filho direito do avo do novo no
           //if para verificar o tio
            if (tio != NULL && tio->cor == RED) // se o tio for diferente de nulo e a cor do tio for vermelha
            {
                novoNo->pai->cor = BLACK; // a cor do pai do novo no recebe preto
                printf("O pai do no %d foi pintado de preto\n", novoNo->id); 
                tio->cor = BLACK; // a cor do tio recebe preto
                printf("O tio do no %d foi pintado de preto\n", novoNo->id); 
                novoNo->pai->pai->cor = RED; // a cor do vo do novo no recebe vermelho
                printf("O vo do no %d foi pintado de vermelho\n", novoNo->id); 
                novoNo = novoNo->pai->pai; // o novo no recebe o vo do novo no, portanto o novo no vai subir na arvore
                printf("O no %d subiu na arvore e sua cor foi alterada para vermelho\n", novoNo->id); 
            }
            
            else //a cor do tio for preta
            {
                //*caso 2DE direita esquerda
                if (novoNo == novoNo->pai->dir) // se o novo no for igual ao filho direito do pai do novo no, ou seja o novo no é um filho direito
                {
                    novoNo = novoNo->pai; // o novo no recebe o pai do novo no
                    printf("O no %d recebeu o pai do no %d\n", novoNo->id, novoNo->id); 
                    printf("faço rotacao a esquerda\n");
                    rotacaoEsquerda(arvore, novoNo); // chamando a funcao para rotacionar a arvore para a esquerda

                } //*caso 3E filho esquerda
                novoNo->pai->cor = BLACK; // a cor do pai do novo no recebe preto
                printf("O pai do no %d foi pintado de preto\n", novoNo->id); 
                novoNo->pai->pai->cor = RED; // a cor do vo do novo no recebe vermelho
                printf("O vo do no %d foi pintado de vermelho\n", novoNo->id); 
                printf("rotaciono o vo a direita\n");
                rotacaoDireita(arvore, novoNo->pai->pai); // chamando a funcao para rotacionar a arvore para a direita
            }
        } //nesse if o pai e filho esquerdo e vermelho



        else // *entao o pai é rubro direita
        {
            TreeRedBlackNode *tio = novoNo->pai->pai->esq; // criando um no tio que vai ser o filho esquerdo do vo do novo no
            //*tio vermelho esquerda
            if (tio != NULL && tio->cor == RED) // se o tio for diferente de nulo e a cor do tio for vermelha
            {
                novoNo->pai->cor = BLACK; // a cor do pai do novo no recebe preto
                printf("O pai do no %d foi pintado de preto\n", novoNo->id); 
                tio->cor = BLACK; // a cor do tio recebe preto
                printf("O tio do no %d foi pintado de preto\n", novoNo->id); 
                novoNo->pai->pai->cor = RED; // a cor do pai do pai do novo no recebe vermelho
                printf("O vo do no %d foi pintado de vermelho\n", novoNo->id); 
                novoNo = novoNo->pai->pai; // o novo no recebe o vo do novo no, portanto o novo no vai subir na arvore e a cor do novo no vai ser vermelha
                printf("O no %d subiu na arvore (virou vo) e sua cor foi alterada para vermelho\n", novoNo->id); 
            }
            //*caso 2ed = V é um filho da esquerda, cujo pai é um filho rubro e cujo tio é negro esquerdista;
            else // se o tio for nulo ou a cor do tio for preta
            {
                if (novoNo == novoNo->pai->esq) // verifico se nonovo(filho do pai da esquerda) 
                {
                    novoNo = novoNo->pai; // o novo no recebe o pai do novo no
                    printf("O no %d recebeu o pai do no %d\n", novoNo->id, novoNo->id); 

                    printf("faço rotacao a direita\n");
                    rotacaoDireita(arvore, novoNo); // chamando a funcao para rotacionar a arvore para a direita
                }
                //*caso 3d
                novoNo->pai->cor = BLACK; // a cor do pai do novo no recebe preto
                printf("O pai do no %d foi pintado de preto\n", novoNo->id); 
                novoNo->pai->pai->cor = RED; // a cor do pai do pai do novo no recebe vermelho
                printf("vo do no %d fica rubro\n", novoNo->id);
                printf("rotaciono o vo a esquerda\n");
                rotacaoEsquerda(arvore, novoNo->pai->pai); // chamando a funcao para rotacionar a arvore para a esquerda //caso 3E
            }
        }
    }
    arvore->raiz->cor = BLACK; // a cor da raiz da arvore recebe preto
}

/* ===================================INSERCAO=================================== */

/* ===================================ROTACAO=================================== */
//ESQUERDA  

void rotacaoEsquerda(rbtree *arvore, TreeRedBlackNode *no) {
    if (no == NULL || no->dir == NULL) {
        return; // Verifica se o nó ou o seu filho direito são nulos
    }
    TreeRedBlackNode *aux = no->dir;

    // Atualiza ponteiros dos nós pai
    aux->pai = no->pai;
    if (no->pai == NULL) {
        arvore->raiz = aux;
        printf("A raiz da arvore recebeu o no %d\n", aux->id);
    } else if (no == no->pai->esq) {
        no->pai->esq = aux;
        printf("O filho esquerdo do pai do no %d recebeu o no %d\n", no->id, aux->id);
    } else {
        no->pai->dir = aux;
        printf("O filho direito do pai do no %d recebeu o no %d\n", no->id, aux->id);
    }

    no->dir = aux->esq;
    printf("O filho direito do no %d recebeu o filho esquerdo do no %d\n", no->id, aux->id);
    if (aux->esq != NULL) {
        aux->esq->pai = no;
        printf("O pai do filho esquerdo do no %d recebeu o no %d\n", aux->esq->id, no->id);
    }
    no->pai = aux;
    printf("O pai do no %d recebeu o no %d\n", no->id, aux->id);
    aux->esq = no;
    printf("O filho esquerdo do no %d recebeu o no %d\n", aux->id, no->id);
}


//DIREITA

void rotacaoDireita(rbtree *arvore, TreeRedBlackNode *no) {
    if (no == NULL || no->esq == NULL) {                                // Verifica se o nó ou o seu filho esquerdo são nulos, se forem, a função retorna, pois não é possível fazer a rotação e acaba ocasionando em segmentation fault
        return; // Verifica se o nó ou o seu filho esquerdo são nulos
    }
    TreeRedBlackNode *aux = no->esq; // Cria um nó auxiliar que recebe o filho esquerdo do nó que será rotacionado

    no->esq = aux->dir;
    printf("O filho esquerdo do no %d recebeu o filho direito do no %d\n", no->id, aux->id);
    if (aux->dir != NULL) {
        aux->dir->pai = no;
        printf("O pai do filho direito do no %d recebeu o no %d\n", aux->dir->id, no->id);
    }

    aux->pai = no->pai;
    printf("O pai do no %d recebeu o pai do no %d\n", aux->id, no->id);
    if (no->pai == NULL) {
        arvore->raiz = aux;
        printf("A raiz da arvore recebeu o no %d\n", aux->id);
    } else if (no == no->pai->dir) {
        no->pai->dir = aux;
        printf("O filho direito do pai do no %d recebeu o no %d\n", no->id, aux->id);
    } else {
        no->pai->esq = aux;
        printf("O filho esquerdo do pai do no %d recebeu o no %d\n", no->id, aux->id);
    }

    aux->dir = no;
    printf("O filho direito do no %d recebeu o no %d\n", aux->id, no->id);
    no->pai = aux;
    printf("O pai do no %d recebeu o no %d\n", no->id, aux->id);
}



/* ===================================ROTACAO=================================== */

/* ===================================Buscar NO=================================== */
//busacar no buscarNo
TreeRedBlackNode *buscarNo(rbtree *arvore, int id)
{
    TreeRedBlackNode *aux = arvore->raiz; // criando um no auxiliar que vai ser a raiz da arvore
    while (aux != NULL && aux->id != id) // enquanto o no auxiliar for diferente de nulo e o id do no auxiliar for diferente do id que o usuario digitou
    {
        if (id < aux->id) // se o id que o usuario digitou for menor que o id do no auxiliar
        {
            aux = aux->esq; // o no auxiliar recebe o filho esquerdo do no auxiliar
        }
        else // se o id que o usuario digitou for maior que o id do no auxiliar
        {
            aux = aux->dir; // o no auxiliar recebe o filho direito do no auxiliar
        }
    }
    return aux; // retornando o no auxiliar
}

//Acrescente um método que calcule o custo médio de uma busca (O custo da busca é o número de comparações de chaves).
//funcao para calcular o custo medio de uma busca:
double custoMedioBusca(rbtree *arvore, int id)
{
    TreeRedBlackNode *aux = arvore->raiz; // criando um no auxiliar que vai ser a raiz da arvore
    int comp = 0; // criando uma variavel comp que vai ser o numero de comparacoes de chaves
    while (aux != NULL && aux->id != id) // enquanto o no auxiliar for diferente de nulo e o id do no auxiliar for diferente do id que o usuario digitou
    {
        comp++; // o numero de comparacoes de chaves aumenta
        if (id < aux->id) // se o id que o usuario digitou for menor que o id do no auxiliar
        {
            aux = aux->esq; // o no auxiliar recebe o filho esquerdo do no auxiliar
        }
        else // se o id que o usuario digitou for maior que o id do no auxiliar
        {
            aux = aux->dir; // o no auxiliar recebe o filho direito do no auxiliar
        }
    }
    return comp; // retornando o numero de comparacoes de chaves
}


/* ===================================Buscar NO=================================== */

/* ===================================REMOCAO=================================== */

//segundo os 4 casos que estao em remocaoideias.txt, esta é a funcao de delete da arvore rb
void deleteno(rbtree *arvore, TreeRedBlackNode *no) {
    TreeRedBlackNode *aux = NULL;
    TreeRedBlackNode *aux2 = NULL;
    if (no->esq == NULL || no->dir == NULL) {           // Se o nó tem menos de dois filhos 
        aux = no;
    } else {                                            // Se o nó tem dois filhos
        aux = no->dir;
        while (aux->esq != NULL) {                      // Enquanto o filho esquerdo do nó não for nulo
            aux = aux->esq;
            //printf("O no %d recebeu o filho esquerdo do no %d\n", aux->id, no->id);
        }
    }
    if (aux->esq != NULL) {                             // Se o filho esquerdo do nó não for nulo
        aux2 = aux->esq;
    } else {                                            
        aux2 = aux->dir;
    }
    if (aux2 != NULL) {                                 // Se o filho direito do nó não for nulo
        aux2->pai = aux->pai;               
    }
    if (aux->pai == NULL) {                             // Se o pai do nó for nulo
        arvore->raiz = aux2;
    } else {                                                         
        if (aux == aux->pai->esq) {                 // Se o nó for igual ao filho esquerdo do pai do nó
            aux->pai->esq = aux2;                   // O filho esquerdo do pai do nó recebe o filho direito do nó
        } else {
            aux->pai->dir = aux2;                   // O filho direito do pai do nó recebe o filho direito do nó
        }
    }
    if (aux != no) {                                // Se o nó aux for diferente do nó
        no->id = aux->id;                           // O id do nó recebe o id do nó aux
    }
    if (aux->cor == BLACK) {                        // Se a cor do nó aux for preta
        removerFixup(arvore, aux2, aux->pai);       // Chama a função removerFixup
    }
    free(aux);
}

void removerFixup(rbtree *arvore, TreeRedBlackNode *no, TreeRedBlackNode *pai) {
    TreeRedBlackNode *aux = NULL; //aux null pq é o nó que vai ser removido
    while ((no == NULL || no->cor == BLACK) && no != arvore->raiz) {                // Enquanto o nó for nulo ou a cor do nó for preta e o nó for diferente da raiz
        if (no == pai->esq) {                                                        // Se o nó for igual ao filho esquerdo do pai
            aux = pai->dir;                                                         // O nó aux recebe o filho direito do pai


            if (aux->cor == RED) {                                                                                   //*caso 1
            printf("Caso 1\n");
                aux->cor = BLACK;
                printf("O irmao vermelho %d foi pintado de preto\n", aux->id);                   
                pai->cor = RED;             
                printf("O pai %d foi pintado fica rubro\n", pai->id);
                printf("rotaciono o pai a esquerda\n");
                rotacaoEsquerda(arvore, pai);
                aux = pai->dir;
                printf("O no %d recebeu o filho direito do pai %d\n", aux->id, pai->id);
            }


            
            if ((aux->esq == NULL || aux->esq->cor == BLACK) && (aux->dir == NULL || aux->dir->cor == BLACK)) {     //*caso 2
                aux->cor = RED;
                printf("Irmao direita %d foi pintado de vermelho\n", aux->id);
                printf("O irmao direito %d foi pintado de vermelho\n", aux->id);
                no = pai;
                printf("O no %d recebeu o pai %d\n", no->id, pai->id);
                pai = no->pai;
                printf("O pai %d recebeu o avo %d\n", pai->id, no->pai->id);





            } else {
                if (aux->dir == NULL || aux->dir->cor == BLACK) {                                                   //*caso 3       
                    printf("Caso 3\n");
                    if (aux->esq != NULL) {
                        aux->esq->cor = BLACK;
                        printf("O filho esquerdo do no %d foi pintado de preto\n", aux->esq->id);
                    }
                    aux->cor = RED;
                    printf("O irmao %d foi pintado de vermelho\n", aux->id);
                    printf("Rotaciona o irmao a direita\n");
                    rotacaoDireita(arvore, aux);
                    aux = pai->dir;
                    printf("O no %d recebeu o filho direito do pai %d (atualiza irmao)\n", aux->id, pai->id);
                }                                                                                                   //*caso 4
                printf("Caso 4\n");
                aux->cor = pai->cor;
                printf("O irmao %d recebeu a cor do pai %d\n", aux->id, pai->id);
                pai->cor = BLACK;
                printf("O pai %d foi pintado de preto\n", pai->id);
                if (aux->dir != NULL) {
                    aux->dir->cor = BLACK;
                    printf("O filho direito do no %d foi pintado de preto\n", aux->dir->id);
                }
                printf("Rotaciona o pai a esquerda\n");
                rotacaoEsquerda(arvore, pai);
                no = arvore->raiz;
            }


        } else {                                                                            //*Se o nó for igual ao filho direito do pai
            aux = pai->esq;                                                                 // O nó aux recebe o filho esquerdo do pai
            if (aux->cor == RED) {                                                          //*caso 1
            printf("Caso 1\n");
                aux->cor = BLACK;
                printf("O irmao vermelho %d foi pintado de preto\n", aux->id);
                pai->cor = RED;
                printf("O pai %d foi pintado de vermelho\n", pai->id);
                printf("Rotaciona o pai a direita\n");
                rotacaoDireita(arvore, pai);
                aux = pai->esq;
                printf("O no %d recebeu o filho esquerdo do pai %d\n", aux->id, pai->id);
            }
            if ((aux->dir == NULL || aux->dir->cor == BLACK) && (aux->esq == NULL || aux->esq->cor == BLACK)) {     //*caso 2
            printf("Caso 2\n");
                aux->cor = RED;
                printf("O irmao %d foi pintado de vermelho\n", aux->id);
                no = pai;
                printf("O no %d recebeu o pai %d\n", no->id, pai->id);
                pai = no->pai;
                printf("O pai %d recebeu o avo %d\n", pai->id, no->pai->id);
            } else {                                                                                                //*caso 3
            printf("Caso 3\n");
                if (aux->esq == NULL || aux->esq->cor == BLACK) {
                    if (aux->dir != NULL) {
                        aux->dir->cor = BLACK;
                        printf("O filho direito do no %d foi pintado de preto\n", aux->dir->id);
                    }
                    aux->cor = RED;
                    printf("O irmao %d foi pintado de vermelho\n", aux->id);
                    printf("rotaciona o irmao a esquerda\n");
                    rotacaoEsquerda(arvore, aux);
                    aux = pai->esq;
                    printf("O no %d recebeu o filho esquerdo do pai %d (atualiza irmao)\n", aux->id, pai->id);
                }   
                printf("Caso 4\n");                                                                                                //*caso 4
                aux->cor = pai->cor;
                printf("O irmao %d recebeu a cor do pai %d\n", aux->id, pai->id);
                pai->cor = BLACK;
                printf("O pai %d foi pintado de preto\n", pai->id);
                if (aux->esq != NULL) {
                    aux->esq->cor = BLACK;
                    printf("O filho esquerdo do no %d foi pintado de preto\n", aux->esq->id);
                }
                printf("Rotaciona o pai a direita\n");
                rotacaoDireita(arvore, pai);
                no = arvore->raiz;
                printf("O no %d recebeu a raiz da arvore\n", no->id);
            }
        }
    }
    if (no != NULL) {
        no->cor = BLACK;
        printf("O no %d foi pintado de preto\n", no->id);
    }
}


/* ===================================REMOCAO=================================== */

/* =================================== print nos com suas infos=================================== */
void printarNos(TreeRedBlackNode *no){
    if (no != NULL) // se o no for diferente de nulo
    {
        printf("No: %d, Cor: %s, Pai: %d, Filho Esquerdo: %d, Filho Direito: %d\n", no->id, (no->cor == RED) ? "Vermelho (RED)" : "Preto (BLACK)", (no->pai != NULL) ? no->pai->id : -1, (no->esq != NULL) ? no->esq->id : -1, (no->dir != NULL) ? no->dir->id : -1);
        printarNos(no->esq); // chamando a funcao para printar os nos da arvore esquerda
        printarNos(no->dir); // chamando a funcao para printar os nos da arvore direita
    }
}

/*======================================== Calcular alturaS======================================== */
int alturaArvore(TreeRedBlackNode *no){ //funcao para calcular a altura da arvore ela recebe a raiz da arvore, ignora os nos nulos e conta a raiz como primeiro nivel
    if (no == NULL) // se o no for nulo
        return 0; // retorna 0
    else // se o no nao for nulo
    {
        int esq = alturaArvore(no->esq); // a altura da arvore esquerda recebe a funcao para calcular a altura da arvore esquerda de maneira recursiva
        int dir = alturaArvore(no->dir); // a altura da arvore direita recebe a funcao para calcular a altura da arvore direita
        if (esq > dir) // se a altura da arvore esquerda for maior que a altura da arvore direita
            return esq + 1; // retorna a altura da arvore esquerda + 1
        else // se a altura da arvore esquerda nao for maior que a altura da arvore direita
            return dir + 1; // retorna a altura da arvore direita + 1
    }
}

int alturaNegra(TreeRedBlackNode *no) { //calcula nos negros, as folhas nulas nao contam como nos negros
    if (no == NULL) { // se o no for nulo
        return 0; // retorna 0
    } else {
        int esq = alturaNegra(no->esq); // a altura negra da arvore esquerda recebe a funcao para calcular a altura negra da arvore esquerda de maneira recursiva
        int dir = alturaNegra(no->dir); // a altura negra da arvore direita recebe a funcao para calcular a altura negra da arvore direita
        if (no->cor == BLACK) { // se o no for preto
            return esq + dir + 1; // retorna a soma das alturas negras da arvore esquerda e direita + 1
        } else { // se o no for vermelho
            return (esq + dir)-1; // retorna a soma das alturas negras da arvore esquerda e direita
        }
    }
}


/*======================================== Calcular altuaS======================================== */

/*======================================== Calcular porcentagem======================================== */

int contaNos(TreeRedBlackNode *no) {
    if (no == NULL) {
        return 0;
    } else {
        int esq = contaNos(no->esq);
        int dir = contaNos(no->dir);
        return esq + dir + 1;
    }
}

int contarNosVermelhos(TreeRedBlackNode *no) {
    if (no == NULL) {
        return 0;
    } else {
        int esq = contarNosVermelhos(no->esq);
        int dir = contarNosVermelhos(no->dir);
        if (no->cor == RED) {
            return esq + dir + 1;
        } else {
            return esq + dir;
        }
    }
}

int contaNosNegros(TreeRedBlackNode *no) {
    if (no == NULL) {
        return 0;
    } else {
        int esq = contaNosNegros(no->esq);
        int dir = contaNosNegros(no->dir);
        if (no->cor == BLACK) {
            return esq + dir + 1;
        } else {
            return esq + dir;
        }
    }
}


float percentagemNegra(TreeRedBlackNode *no){ //desce a arvore contando nivel a nivel quantas apariçoes de nos negros tem, divide pelo total de nos da arvore faz a porcentagem
    int totalNos = contaNos(no); // função para contar o número total de nós na árvore
    int nosNegros = contaNosNegros(no); // função para contar o número de nós negros na árvore
    return ((float)nosNegros / (float)totalNos) * 100; // retorna a porcentagem de nós negros
}

float percentagemVermelha(TreeRedBlackNode *no){ //desce a arvore contando nivel a nivel quantas apariçoes de nos vermelhos tem e divide pelo tamanho total de nos da arvore para fazer porcentagem
    int totalNos = contaNos(no); // função para contar o número total de nós na árvore
    int nosVermelhos = contarNosVermelhos(no); // função para contar o número de nós vermelhos na árvore
    return ((float)nosVermelhos / (float)totalNos) * 100; // retorna a porcentagem de nós vermelhos
}


/* =============================Plot .dot =============================*/
//funcao para o arquivo .dot do graphviz

void gerarDOT(TreeRedBlackNode *no, FILE *arquivoDOT) {
    if (no != NULL) {
        fprintf(arquivoDOT, "%d [label=\"%d\", color=%s];\n", no->id, no->id, (no->cor == RED) ? "red" : "black");
        if (no->esq != NULL) {
            fprintf(arquivoDOT, "%d -> %d;\n", no->id, no->esq->id);
            gerarDOT(no->esq, arquivoDOT);
        }
        if (no->dir != NULL) {
            fprintf(arquivoDOT, "%d -> %d;\n", no->id, no->dir->id);
            gerarDOT(no->dir, arquivoDOT);
        }
    }
}

void visualizarArvoreDot(rbtree *arvore) {
    FILE *arquivoDOT;
    arquivoDOT = fopen("arvore.dot", "w");
    if (arquivoDOT == NULL) {
        printf("Erro ao abrir o arquivo DOT.");
        return;
    }

    fprintf(arquivoDOT, "digraph ArvoreRubroNegra {\n");
    if (arvore->raiz != NULL) {
        gerarDOT(arvore->raiz, arquivoDOT);
    }
    fprintf(arquivoDOT, "}\n");

    fclose(arquivoDOT);
}