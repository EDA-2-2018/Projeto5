#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILE 40

/*
 * STRUCTS
 */
typedef struct Arv {
    int info;
    struct Arv* esq;
    struct Arv* dir;
}Arv;

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
/*int esta_balanceada(No *raiz);*/
/*No* cria_no(int num);*/
/*void insere_no(No *no, int num);*/
Arv* init(void);
Arv* insert(Arv* a, int v);
//void printTree(Arv *root, int space);
//void print(Arv *root);
int getLevel(Arv *node, int info, int level);
int getParent(Arv *root, int value, int treeHeight);
int getBrother(Arv *root, int value, int treeHeight);
bool isBalanced(Arv *tree);
int readTree(Arv *presentNode,int max,int row,int col,int a[176][480]);
int printTree(Arv *presentNode);


/*
 * FUNÇÃO MAIN
 */
int main(){
    Arv *raiz = init();
    while(1) {
        system("clear");
        printf("\n\n 1 - loadTreeFromFile\n");
        printf(" 2 - showTree\n");
        printf(" 3 - isFull\n");
        printf(" 4 - searchValue\n");
        printf(" 5 - getHeight\n");
        printf(" 6 - removeValue\n");
        printf(" 7 - printInOrder\n");
        printf(" 8 - printPreOrder\n");
        printf(" 9 - printPostOrder\n");
        printf("10 - balanceTree\n");
        printf(" 0 - SAIR\n\n");

        int opcao;
        printf("option: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao == 0)
            break;

        if(opcao == 1){
            system("clear");
            char File_name[MAX_FILE], Nome_escolhido[MAX_FILE];

            printf("Lista de arquivos:\n\tbst1.txt\n\tbst2.txt\n\tbst3.txt\n\tbst4.txt\n\tbst5.txt\n\tbst6.txt\n\tbst7.txt\n\tbst8.txt");
            printf("\n\nDigite o nome de um dos arquivos acima: ");
            //File_name = "./BSTs/";
            strcpy(File_name , "./BSTs/");
            scanf("%s\n", Nome_escolhido);
            getchar();

            strncat(File_name, Nome_escolhido, MAX_FILE);


            raiz = loadTreeFromFile(File_name);

        }
        if(opcao == 2){
            if(!raiz)
                printf("\nArvore vazia ou nao carregada!\n");
            else {
                system("clear");
                printTree(raiz);
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


        if(opcao == 4) {

            if(!raiz)
                printf("\nArvore vazia ou nao carregada!\n");

            else {
                int search_value;
                printf("\nDigite o valor de pesquisa: ");
                scanf("%d", &search_value);
                getchar();

                if(searchValue(raiz, search_value)) {
                    if(search_value == raiz->info)
                        printf("\n  Nivel : %d\n", getLevel(raiz, search_value, 1) - 1);

                    else {
                        int brother = getBrother(raiz, search_value, getLevel(raiz, search_value, 1) - 1);
                        printf("\n  Nivel : %d\n", getLevel(raiz, search_value, 1) - 1);
                        printf("   Pai  : %d\n", getParent(raiz, search_value, getLevel(raiz, search_value, 1) - 1));
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
                    printf("\n%d removido...\n", value);
                }
                else
                    printf("\nValor nao encontrado na arvore!\n");
            }
            getchar();
        }

        if(opcao == 7) {
            if(!raiz)
                printf("\nArvore vazia ou nao carregada!\n");
            else {
                printf("\n");
                printInOrder(raiz);
            }
            getchar();
        }

        if(opcao == 8) {

            if(!raiz)
                printf("\nArvore vazia ou nao carregada!\n");
            else {
                printf("\n");
                printPreOrder(raiz);
            }
            getchar();
        }

        if(opcao == 9) {
            if(!raiz)
                printf("\nArvore vazia ou nao carregada!\n");
            else {
                printf("\n");
                printPosOrder(raiz);
            }
            getchar();
        }

        if(opcao == 10) {
            // system("clear");
            if(!raiz)
                printf("\nArvore vazia ou nao carregada!\n");
            else
                if(isBalanced(raiz))
                    printf("\nArvore Balanceada!\n");
                else
                    printf("\nArvore nao balaceada!\n");

            getchar();
        }

    }
    return 0;
}/*Fim-main*/

/*
 * ESCOPO DAS FUNÇÕES
 */
//FUNÇÕES OBRIGATÓRIAS
Arv* loadTreeFromFile(const char *file_name) { //[1]
    Arv *arr = init();
    int num;
    FILE *arquivo;

    arquivo = fopen(file_name, "r");

    while((fscanf(arquivo, "%d", &num))!=EOF)
        arr = insert(arr, num);

    fclose(arquivo);
    return arr;
}/*Fim-loadTreeFromFile*/

void showTree(Arv *raiz) { //[2]
    system("clear");
    if(!raiz)
        printf("Arvore nao carregada!!\n");
    else
        printf("Imprime arvore...\n");
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
        int lheight = getHeight(node->esq);
        int rheight = getHeight(node->dir);

        if (lheight > rheight) {
            return(lheight+1);
        }
        else
            return(rheight+1);
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

/*void printTree(Arv *root, int space) {
    if (root == NULL)
        return;

    space += 10;

    printTree(root->dir, space);

    printf("\n");
    for(int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->info);


    printTree(root->esq, space);
}*//*Fim-printTree*/

/*void print(Arv *root) {
   printTree(root, 10);
}*//*Fim-print*/

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
                // printf("This value doesn't have brother\n");

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

int readTree(Arv *presentNode,int max,int row,int col,int a[176][480]){// reads the tree into the array
  // a[44][120]; //a simulates the physical screen
  int i=0;
  int m=0,n=0; //flags for sending error signal
  int r=row; //r changes to the next row
  if(presentNode==NULL)// if the tree(not a subtree) doesn't have any elements at all
    return -1;

  if(max==1&&(presentNode->esq!=NULL||presentNode->dir!=NULL))//max denotes the number of
  //slashes to the next element. if it is zero and yet not a leaf then dont print the graphical tree
    return -1;
    a[row][col]=presentNode->info;//sets the value on the screen
    if(presentNode->esq!=NULL){
      while(i++<max)
        a[++r][col-i]='/';
      m= readTree(presentNode->esq,max/2,r+1,col-max-1,a);
    }

    i=0;
    r=row;
    if(presentNode->dir!=NULL){
      while(i++<max)
        a[++r][col+i]='\\';
      n= readTree(presentNode->dir,max/2,r+1,col+max+1,a);
    }
    if(m==-1||n==-1)
      return -1;
    else
      return 0;
}/*Fim-readTree*/

int printTree(Arv *presentNode){
    int i,j;
    int a[176][480];
    for(i=0;i<176;i++){
      for(j=0;j<480;j++){
        a[i][j]=0;
      }
    }

    if(-1!=readTree(presentNode,16,0,60,a)){// -1 means it cannot print graphical form of tree
      for(i=0;i<37;i++){
        for(j=0;j<100;j++){//not 120 so that spaces dont shoot off onto the next line
          if(i==0||i==17||i==26||i==31||i==34||i==36){
          //if(i==0||i==17||i==26||i==31||i==34||i==36){//only on these lines integers exist (other lines have only slashes)
            if(a[i][j]==0)
              printf(" ");	//print spaces for uninitialized elements
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
    }else
    printf("Cannot print graphical form due to insufficient screen size\n");
  }/*Fim-printTree*/
