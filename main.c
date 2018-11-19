#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Arv {
    int info;
    struct Arv* esq;
    struct Arv* dir;
}Arv;

Arv* init(void);
Arv* searchValue(Arv* r, int v);
Arv* insere(Arv* a, int v);
Arv* loadTreeFromFile(const char *nome_arquivo);
int isFullTree( Arv* root); 
int height(Arv *tree);
Arv* removeValue(Arv* r, int v);
void printInOrder(Arv* a);
void printPreOrder(Arv* a);
void printPosOrder(Arv* a);
void showTree(Arv *b);
void print(Arv *root);
int getLevel(Arv *node, int info, int level); 
int getParent(Arv *root, int value, int treeHeight);
int getBrother(Arv *root, int value, int treeHeight);

int main() {
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

        if(opcao == 1)
            raiz = loadTreeFromFile("./BSTs/bst8.txt");        

        if(opcao == 2){
            system("clear");
            if(!raiz)
                printf("Arvore vazia ou nao carregada!\n");
            else
                print(raiz);

            getchar();
        }
        if(opcao == 3) {
            if(!raiz)
                printf("Arvore vazia ou nao carregada!\n");
            else
                if(isFullTree(raiz))
                    printf("\nArvore cheia!\n");
                else
                    printf("\nArvore nao cheia!\n");            
            getchar();
        }


        if(opcao == 4) {
            system("clear");

            if(!raiz)
                printf("Arvore vazia ou nao carregada!\n");
            
            else {
                int search_value;
                printf("Digite o valor de pesquisa: ");
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
                printf("Arvore vazia ou nao carregada!\n");
            else
                printf("\nAltura = %d\n", height(raiz));
            
            getchar();
        }

        if(opcao == 6) {
            system("clear");
            if(!raiz)
                printf("Arvore vazia ou nao carregada!\n");
            else {
                int value;
                printf("Digite o valor que deseja remover: ");
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
            system("clear"); 
            if(!raiz) 
                printf("Arvore vazia ou nao carregada!\n");
            else 
                printInOrder(raiz);
            getchar();
        }

        if(opcao == 8) {
            system("clear"); 
            if(!raiz) 
                printf("Arvore vazia ou nao carregada!\n");
            else 
                printPreOrder(raiz);
            getchar();
        }
    
        if(opcao == 9) {
            system("clear"); 
            if(!raiz) 
                printf("Arvore vazia ou nao carregada!\n");
            else 
                printPosOrder(raiz);
            getchar();
        }

        if(opcao == 10) {
            system("clear"); 
            if(!raiz) 
                printf("Arvore vazia ou nao carregada!\n");
            else 
                printPosOrder(raiz);
            getchar();
        }

    }
    return 0;
}

Arv* init (void) {
    return NULL;
}

void printInOrder (Arv* a) {
           
    if (a != NULL) {
        printInOrder(a->esq);
        printf("%d ", a->info);
        printInOrder(a->dir);
    }

}

void printPreOrder (Arv* a) {
    if (a != NULL) {
        printf("%d ", a->info);
        printPreOrder(a->esq);
        printPreOrder(a->dir);
    }
}

void printPosOrder (Arv* a) {
    if (a != NULL) {
        printPosOrder(a->esq);
        printPosOrder(a->dir);
        printf("%d ", a->info);
    }
}

Arv* searchValue (Arv* r, int v) {
    if (r == NULL) 
        return NULL;    
    
    else if(r->info > v) 
            return searchValue(r->esq, v);
    else if 
        (r->info < v) 
            return searchValue(r->dir, v);
    else 
        return r;
}

Arv* insere(Arv* a, int v) {
    if (a==NULL) {
        a = (Arv*)malloc(sizeof(Arv));
        a->info = v;
        a->esq = a->dir = NULL;
    }
    else if(v < a->info)    
        a->esq = insere(a->esq,v);  
    else /* v < a->info */
        a->dir = insere(a->dir,v);
    
    return a;
}


Arv* loadTreeFromFile(const char *nome_arquivo) {
    Arv *arr = init();
    int num;
    FILE *arquivo;
  
    arquivo = fopen(nome_arquivo, "r");
  
    while((fscanf(arquivo, "%d", &num))!=EOF) 
        arr = insere(arr, num);

    fclose(arquivo); 
    return arr;
}
void showTree(Arv *b) {
    system("clear");
    if(!b)
        printf("Arvore nao carregada!!\n");
    else
        printf("Imprime arvore...\n");
    getchar();
}

Arv* removeValue(Arv* r, int v) {
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
}

int isFullTree( Arv* root) { 

    if (root == NULL) 
        return 1; 
  
    if (root->esq == NULL && root->dir == NULL) 
        return 1; 
  
    if ((root->esq) && (root->dir)) 
        return (isFullTree(root->esq) && isFullTree(root->dir)); 
  
    return 0; 
} 


int height(Arv* node)  { 
    if (node==NULL) 
        return 0; 
    
    else  { 
        int lheight = height(node->esq); 
        int rheight = height(node->dir); 
  
        if (lheight > rheight) { 
            return(lheight+1); 
        }  
        else 
            return(rheight+1); 
    } 
}


void printTree(Arv *root, int space)  { 
    if (root == NULL) 
        return; 

    space += 10; 
  
    printTree(root->dir, space); 
   
    printf("\n"); 
    for(int i = 10; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->info); 
    
    
    printTree(root->esq, space); 
} 
  
void print(Arv *root)  { 
   printTree(root, 10); 
}

int getLevel(Arv *node, int info, int level)  { 
    if (node == NULL) 
        return 0; 
  
    if (node->info == info) 
        return level; 
  
    int downlevel = getLevel(node->esq, info, level+1); 
    if (downlevel != 0) 
        return downlevel; 
  
    downlevel = getLevel(node->dir, info, level+1); 
    return downlevel; 
} 
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
}

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
}
