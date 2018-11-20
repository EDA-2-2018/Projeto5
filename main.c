#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * CONSTANTES
 */
#define MAX_FILE 40
#define MAX_TAM (1<<20)
#define ALTURA_MAX 1000

/*
 * STRUCTS
 */
typedef struct Arv {
    int info;
    struct Arv* esq;
    struct Arv* dir;
}Arv;

typedef struct Node { //Árvore auxiliar com os dados necessário para a showTree
    struct Node *esq, *dir;
    int info, galho, altura, tipo;
    char descricao[11];
}Node;

/*
 * VARIÁVEIS GLOBAIS
 */
Arv *Root = NULL;
int espaco = 3, imprimeProx;
int esq[ALTURA_MAX], dir[ALTURA_MAX];

/*
 * ASSINATURA DAS FUNÇÕES
 */
//FUNÇÕES OBRIGATÓRIAS
Arv* loadTreeFromFile(const char *file_name);  //[1]
void showTree(Arv *raiz);                      //[2]
int isFullTree(Arv* root);                     //[3]
Arv* searchValue(Arv* tree, int num);          //[4]
int getHeight(Arv *tree);                      //[5]
Arv* removeValue(Arv* r, int v);               //[6]
void printInOrder(Arv* a);                     //[7]
void printPreOrder(Arv* a);                    //[8]
void printPosOrder(Arv* a);                    //[9]
void balanceTree(Arv *root);                   //[10]
//OUTRAS FUNÇÕES
Arv* init(void);
void liberaArv(Arv *no);
Arv* insert(Arv* a, int v);
int getLevel(Arv *node, int info, int level);
int getParent(Arv *root, int value, int treeHeight);
int getBrother(Arv *root, int value, int treeHeight);
bool isBalanced(Arv *tree);
int readTree(Arv *presentNode,int max,int row,int col,int a[44][120]);
int menor_node(int x, int y);
int maior_node(int x, int y);
Node *criaNodeTree(Arv *n);
void liberaNodeTree(Node *no);
void preenche_galho(Node *no);
void imprimeLevel(Node *no, int x, int level);
void menorEsq(Node *no, int x, int y);
void maiorDir(Node *no, int x, int y);

/*
 * FUNÇÃO MAIN
 */
int main(){
  Arv *raiz = init();
  while(1){
      system("clear");
      printf("\n\n\n\n\t**********MENU**********\n\n\t 1 - loadTreeFromFile\n");
      printf("\t 2 - showTree\n");
      printf("\t 3 - isFull\n");
      printf("\t 4 - searchValue\n");
      printf("\t 5 - getHeight\n");
      printf("\t 6 - removeValue\n");
      printf("\t 7 - printInOrder\n");
      printf("\t 8 - printPreOrder\n");
      printf("\t 9 - printPostOrder\n");
      printf("\t 10- balanceTree\n");
      printf("\t 0 - QUIT\n\n");

      int opcao;
      printf("\t Option: ");
      scanf("%d", &opcao);
      getchar();

      if(opcao == 0)
          break;

      if(opcao == 1){
          system("clear");

          char load_file[17], file[10];
          int num_file;
          printf("Lista de arquivos:\n\t\t1) bst1.txt\n\t\t2) bst2.txt\n\t\t3) bst3.txt\n\t\t4) bst4.txt\n\t\t5) bst5.txt\n\t\t6) bst6.txt\n\t\t7) bst7.txt\n\t\t8) bst8.txt");

          printf("\n\n\t\tDigite o numero correspondente para carregar o arquivo: ");

          scanf("%d", &num_file);
          getchar();

          sprintf(load_file,"./BSTs/bst%d.txt",num_file);

          raiz = loadTreeFromFile(load_file);
          Root = raiz;

          sprintf(file, "bst%d.txt", num_file);

          printf("\nArquivo %s carregado!\n", file);
          getchar();
      }
      if(opcao == 2){
          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else {
              system("clear");
              showTree(raiz);
          }

          getchar();
      }
      if(opcao == 3) {
          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else
              if(isFullTree(raiz))
                  printf("\nArvore cheia!\n");
              else
                  printf("\nArvore nao cheia!\n");
          getchar();
      }
      if(opcao == 4){
          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else{
              int search_value;
              printf("\nDigite o valor de pesquisa: ");
              scanf("%d", &search_value);
              getchar();
              if(searchValue(raiz, search_value)) {
                  if(search_value == raiz->info)
                      printf("\n  Nivel : %d (raiz da arvore)\n", getLevel(raiz, search_value, 1));
                  else{
                      int brother = getBrother(raiz, search_value, getLevel(raiz, search_value, 1) - 1);
                      printf("\n  Nivel : %d\n", getLevel(raiz, search_value, 1));
                      printf("  Pai  : %d\n", getParent(raiz, search_value, getLevel(raiz, search_value, 1) - 1));
                      if(brother)
                          printf("  Irmao : %d\n", brother);
                      else
                          printf("  Irmao : Nao possui!\n");
                  }
              }
              else
                  printf("\nValor nao encontrado na arvore!\n");
          }
          getchar();
      }
      if(opcao == 5) {

          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else
              printf("\nAltura = %d\n", getHeight(raiz));

          getchar();
      }
      if(opcao == 6) {
          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else {
              int value;
              printf("\nDigite o valor que deseja remover: ");
              scanf("%d", &value);
              getchar();

              if(searchValue(raiz, value)) {
                  removeValue(raiz, value);
                  printf("\n%d removido!\n", value);
              }
              else
                  printf("\nValor nao encontrado na arvore!\n");
          }
          getchar();
      }
      if(opcao == 7){
          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else {
              printf("\n");
              printInOrder(raiz);
          }
          getchar();
      }
      if(opcao == 8){

          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else {
              printf("\n");
              printPreOrder(raiz);
          }
          getchar();
      }
      if(opcao == 9){
          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else {
              printf("\n");
              printPosOrder(raiz);
          }
          getchar();
      }
      if(opcao == 10){
          system("clear");
          if(!raiz)
              printf("\nArvore vazia ou nao carregada!\n");
          else
              if(isBalanced(raiz))
                  printf("\nArvore Balanceada!\n");
              else
                  printf("\nArvore nao balaceada!\n");

          getchar();
      }

  }/*Fim-while*/

  liberaArv(Root);

  return 0;
}/*Fim-main*/

/*
 * ESCOPO DAS FUNÇÕES
 */
//FUNÇÕES OBRIGATÓRIAS
Arv* loadTreeFromFile(const char *file_name) { //[1]
    Arv *arr = init();
    int num;
    FILE *arquivo = NULL;

    arquivo = fopen(file_name, "r");

    if (!arquivo) {
        printf("Falha ao carregar arquivo!\n");
        exit(1);
    }

    while((fscanf(arquivo, "%d", &num))!=EOF)
        arr = insert(arr, num);

    fclose(arquivo);
    return arr;
}/*Fim-loadTreeFromFile*/

void showTree(Arv *raiz) { //[2]
  system("clear");
  Root = raiz;
  if(!raiz){
      printf("Arvore nao carregada!!\n");
  }else{
    int i,j;
    int a[44][120];
    for(i=0;i<44;i++){
      for(j=0;j<120;j++){
        a[i][j]=0;
      }
    }

    if(-1!=readTree(raiz,16,0,60,a)){
      for(i=0;i<35;i++){
        for(j=0;j<100;j++){
          if(i==0||i==17||i==26||i==31||i==34||i==36){ //Linhas em que os números vão aparecer
            if(a[i][j]==0)
              printf(" ");
            else
              printf("%d",a[i][j]);
          }else{
            if((a[i][j]==0))
              printf(" ");
            else
              printf("%c",a[i][j]);
          }
        }
        printf("\n");
      }
    }else{
       Node *nodeRaiz;

       if (Root == NULL)
           return;
       nodeRaiz = criaNodeTree(Root);
       preenche_galho(nodeRaiz);

       for (int i = 0; i < nodeRaiz->altura && i < ALTURA_MAX; i++)
           esq[i] = MAX_TAM;

       menorEsq(nodeRaiz, 0, 0);
       int xmin = 0;

       for (int i = 0; i < nodeRaiz->altura && i < ALTURA_MAX; i++)
           xmin = menor_node(xmin, esq[i]);
       for (int i = 0; i < nodeRaiz->altura; i++) {
           imprimeProx = 0;
           imprimeLevel(nodeRaiz, -xmin, i);
           printf("\n");
       }

       liberaNodeTree(nodeRaiz);
    }
  }

  getchar();
}/*Fim-showTree*/

int isFullTree( Arv* root) { //[3]

    if (root == NULL)
        return 1;

    if (root->esq == NULL && root->dir == NULL)
        return 1;

    if ((root->esq) && (root->dir))
        return (isFullTree(root->esq) && isFullTree(root->dir));

    return 0;
}/*Fim-isFullTree*/

Arv* searchValue (Arv* tree, int num) { //[4]
    if (tree == NULL)
        return NULL;

    else if(tree->info > num)
            return searchValue(tree->esq, num);
    else if
        (tree->info < num)
            return searchValue(tree->dir, num);
    else
        return tree;
}/*Fim-searchValue*/

int getHeight(Arv* node) { //[5]
    if (node==NULL)
        return 0;

    else  {
        int laltura = getHeight(node->esq);
        int raltura = getHeight(node->dir);

        if (laltura > raltura) {
            return(laltura+1);
        }
        else
            return(raltura+1);
    }
}/*Fim-getHeight*/

Arv* removeValue(Arv* r, int v) { //[6]
    if (r == NULL)
        return NULL;

    else if(r->info > v)
        r->esq = removeValue(r->esq, v);

    else if(r->info < v)
        r->dir = removeValue(r->dir, v);

    else {
        if (r->esq == NULL && r->dir == NULL) {
            free (r);
            r = NULL;
        }
        else if (r->esq == NULL) {
            Arv* t = r;
            r = r->dir;
            free(t);
        }
        else if(r->dir == NULL) {
            Arv* t = r;
            r = r->esq;
            free (t);
        }
        else {
            Arv* f = r->esq;
            while(f->dir != NULL) {
                f = f->dir;
            }
            r->info = f->info;
            f->info = v;
            r->esq = removeValue(r->esq,v);
        }
    }
    return r;
}/*Fim-removeValue*/

void printInOrder (Arv* a) { //[7]

    if (a != NULL) {
        printInOrder(a->esq);
        printf("%d ", a->info);
        printInOrder(a->dir);
    }

}/*Fim-printInOrder*/

void printPreOrder(Arv* a) { //[8]
    if (a != NULL) {
        printf("%d ", a->info);
        printPreOrder(a->esq);
        printPreOrder(a->dir);
    }
}/*Fim-printPreOrder*/

void printPosOrder (Arv* a) { //[9]
    if (a != NULL) {
        printPosOrder(a->esq);
        printPosOrder(a->dir);
        printf("%d ", a->info);
    }
}/*Fim-printPosOrder*/

void balanceTree(Arv *root) { //[10]

  if(isBalanced(root) == false){ //Só balanceia se ne for necessário

  }/*Fim-if*/

}/*Fim-balanceTree*/

//OUTRAS FUNÇÕES
Arv* init () {
    return NULL;
}/*Fim-init*/

void liberaArv(Arv *no){
    if (no == NULL) return;
    liberaArv(no->esq);
    liberaArv(no->dir);
    free(no);
}/*Fim-liberaArv*/

Arv* insert(Arv* a, int v) {
    if (a==NULL) {
        a = (Arv*)malloc(sizeof(Arv));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else if(v < a->info)
        a->esq = insert(a->esq,v);
    else /* v < a->info */
        a->dir = insert(a->dir,v);

    return a;
}/*Fim-insert*/

int getLevel(Arv *node, int info, int level) {
    if (node == NULL)
        return 0;

    if (node->info == info)
        return level;

    int downlevel = getLevel(node->esq, info, level+1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevel(node->dir, info, level+1);
    return downlevel;
}/*Fim-getLevel*/

int getParent(Arv *root, int value, int treeHeight) {
    if((root->esq != NULL) && value < root->info){
        if(root->esq->info == value)
            return root->info;

        getParent(root->esq, value, treeHeight);
    }

    else if((root->dir != NULL)){
        if(root->dir->info == value)
            return root->info;

        getParent(root->dir, value, treeHeight);
    }
}/*Fim-getParent*/

int getBrother(Arv *root, int value, int treeHeight) {
    if((root->esq != NULL) && value < root->info){
        if(root->esq->info == value) {
            if(root->dir != NULL)
                return root->dir->info;
            else
                return 0;
        }
        getBrother(root->esq, value, treeHeight);
    }

    else if((root->dir != NULL)){
        if(root->dir->info == value) {
            if(root->esq != NULL)
                return root->esq->info;
            else
                return 0;

        }
        getBrother(root->dir, value, treeHeight);
    }
}/*Fim-getBrother*/

bool isBalanced(Arv *tree) {
   int lh;
   int rh;

   if(tree == NULL)
    return true;

   lh = getHeight(tree->esq);
   rh = getHeight(tree->dir);

   if( abs(lh-rh) <= 1 && isBalanced(tree->esq) && isBalanced(tree->dir))
    return true;

   return false;
}/*Fim-isBalanced*/

int readTree(Arv *presentNode,int max,int row,int col,int a[44][120]){ //insere a árvore em uma matriz
  int i = 0, m = 0, n = 0;
  int r = row;

  if(presentNode==NULL)
    return -1;

  if(max==1&&(presentNode->esq!=NULL||presentNode->dir!=NULL))
    return -1;

  a[row][col]=presentNode->info;

  if(presentNode->esq!=NULL){
    while(i++<max)
      a[++r][col-i]='/';
    m= readTree(presentNode->esq,max/2,r+1,col-max-1,a);
  }

  i = 0;
  r = row;
  if(presentNode->dir!=NULL){
    while(i++<max)
      a[++r][col+i]='\\';
    n= readTree(presentNode->dir,max/2,r+1,col+max+1,a);
  }
  if(m == -1 || n == -1) //[m == -1 || n == -1]-> árvore não cabe nas dimensões da matriz a[44][120]
    return -1;
  else
    return 0;
}/*Fim-readTree*/

int menor_node(int x, int y){
    if(x < y)
      return x;
    else
      return y;
}/*Fim-menor_node*/

int maior_node(int x, int y){
    if(x > y)
      return x;
    else
      return y;
}/*Fim-maior_node*/

Node *criaNodeTree(Arv *n){
  Node *no;
  if (n == NULL)
      return NULL;

  no = malloc(sizeof(Node));
  no->esq = criaNodeTree(n->esq);
  no->dir = criaNodeTree(n->dir);
  no->tipo = 0;

  if (no->esq != NULL)
      no->esq->tipo = -1;
  if (no->dir != NULL)
      no->dir->tipo = 1;

  sprintf(no->descricao, "%d", n->info);
  no->info = strlen(no->descricao);

  return no;
}/*Fim-criaNodeTree*/

void liberaNodeTree(Node *no){
    if (no == NULL) return;
    liberaNodeTree(no->esq);
    liberaNodeTree(no->dir);
    free(no);
}/*Fim-liberaNodeTree*/

void preenche_galho(Node *no){
    int alturaMin, delta;

    if (no == NULL)
        return;

    preenche_galho(no->esq);
    preenche_galho(no->dir);

    if (no->dir == NULL && no->esq == NULL)
        no->galho = 0;

    else {
        if (no->esq != NULL) {
            for (int i = 0; i < no->esq->altura && i < ALTURA_MAX; i++)
                dir[i] = -MAX_TAM;

            maiorDir(no->esq, 0, 0);
            alturaMin = no->esq->altura;
        }
        else
            alturaMin = 0;
        if (no->dir != NULL) {
            for (int i = 0; i < no->dir->altura && i < ALTURA_MAX; i++)
                esq[i] = MAX_TAM;

            menorEsq(no->dir, 0, 0);
            alturaMin = menor_node(no->dir->altura, alturaMin);
        }
        else
            alturaMin = 0;

        delta = 4;
        for (int i = 0; i < alturaMin; i++)
            delta = maior_node(delta, espaco + 1 + dir[i] - esq[i]);

        if (((no->esq != NULL && no->esq->altura == 1) ||
                    (no->dir != NULL && no->dir->altura == 1)) && delta > 4) {
            delta--;
        }

        no->galho = ((delta + 1) / 2) - 1;
    }

    int altura = 1;
    if (no->esq != NULL) {
        altura = maior_node(no->esq->altura + no->galho + 1, altura);
    }
    if (no->dir != NULL) {
        altura = maior_node(no->dir->altura + no->galho + 1, altura);
    }
    no->altura = altura;
}/*Fim-preenche_galho*/

void imprimeLevel(Node *no, int x, int level){
    if (no == NULL) return;
    int isesq = (no->tipo == -1);
    if (level == 0) {
        int i;
        for (i = 0; i < (x - imprimeProx - ((no->info - isesq) / 2)); i++)
            printf(" ");

        imprimeProx += i;
        printf("%s", no->descricao);
        imprimeProx += no->info;
    }
    else if (no->galho >= level) {
        if (no->esq != NULL) {
            int i;
            for (i = 0; i < (x - imprimeProx - (level)); i++)
                printf(" ");

            imprimeProx += i;
            printf("/");
            imprimeProx++;
        }
        if (no->dir != NULL) {
            int i;
            for (i = 0; i < (x - imprimeProx + (level)); i++)
                printf(" ");

            imprimeProx += i;
            printf("\\");
            imprimeProx++;
        }
    }
    else {
        imprimeLevel(no->esq, x - no->galho - 1, level - no->galho - 1);
        imprimeLevel(no->dir, x + no->galho + 1, level - no->galho - 1);
    }
}/*Fim-imprimeLevel*/

void menorEsq(Node *no, int x, int y){
    if (no == NULL)
        return;

    int isesq = (no->tipo == -1);
    esq[y] = menor_node(esq[y], x - ((no->info - isesq) / 2));

    if (no->esq != NULL) {
        for(int i = 1; i <= no->galho  && y + i < ALTURA_MAX; i++) {
            esq[y + i] = menor_node(esq[y + i], x - i);
        }
    }

    menorEsq(no->esq, x - no->galho - 1, y + no->galho + 1);
    menorEsq(no->dir, x + no->galho + 1, y + no->galho + 1);
}/*Fim-menorEsq*/

void maiorDir(Node *no, int x, int y){
    if (no == NULL)
        return;
    int ttesq = (no->tipo != -1);
    dir[y] = maior_node(dir[y], x + ((no->info - ttesq) / 2));

    if (no->dir != NULL) {
        for(int i = 1; i <= no->galho && y + i < ALTURA_MAX; i++) {
            dir[y + i] = maior_node(dir[y + i], x + i);
        }
    }

    maiorDir(no->esq, x - no->galho - 1, y + no->galho + 1);
    maiorDir(no->dir, x + no->galho + 1, y + no->galho + 1);
}/*Fim--maiorDir*/
