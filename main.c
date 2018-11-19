#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_FILE 40

/*
 * STRUCTS
 */
typedef struct no{
  int num;
  struct no *no_left, *no_right;
}No;

 /*
  * ASSINATURA DAS FUNÇÕES
  */
//FUNÇÕES OBRIGATÓRIAS
No* loadTreeFromFile(char *arquivo);  //[1]
void showTree(No *raiz);              //[2]
void isFull(No *raiz);                //[3]
void searchValue(No *raiz, int num);  //[4]
void getHeight(No *raiz);             //[5]
void removeValue(No *raiz, int num);  //[6]
void printInOrder(No *raiz);          //[7]
void printPreOrder(No *raiz);         //[8]
void printPostOrder(No *raiz);        //[9]
void balanceTree(No *raiz);           //[10]
//OUTRAS FUNÇÕES
int esta_balanceada(No *raiz);
No* cria_no(int num);
void insere_no(No *no, int num);


/*
 * FUNÇÃO MAIN
 */
int int main(int argc, char const *argv[]){

  return 0;
}/*Fim-main*/


 /*
  * ESCOPO DAS FUNÇÕES
  */
//FUNÇÕES OBRIGATÓRIAS
No* loadTreeFromFile(char *arquivo){ //[1]

  FILE *file;
  char File_name[MAX_FILE];
  int Nums[100], qtd_no = 0;
  No *raiz = NULL, *novo = NULL;

  File_name = "./BSTs/";

  strncat(File_name, arquivo, MAX_FILE);

  file = fopen(File_name, "r");

  if(file == NULL){
      exit(-1);
  }

  while((fscanf(file, "%d \n", Nums[qtd_no]))!=EOF)
    qtd_no++;

  fclose(file);

  //Inserir números na árvore
  for(int i = 0; i < qtd_no; i++){

    novo = insere_no(raiz, Nums[i]);

    if(i == 0)
      raiz = novo;
    }

  }

}/*Fim-loadTreeFromFile*/

void showTree(No *raiz){ //[2]

}/*Fim-showTree*/

void isFull(No *raiz){ //[3]

}/*Fim-isFull*/

void searchValue(No *raiz, int num){ //[4]
  /*if(raiz == NULL)
    return 0; //Não encontrou
  else
    return raiz->num == num || searchValue(raiz->no_left, num) || searchValue(raiz->no_right, num);*/

}/*Fim-searchValue*/

void getHeight(No *raiz){ //[5]

}/*Fim-getHeight*/

void removeValue(No *raiz, int num){ //[6]

}/*Fim-removeValue*/

void printInOrder(No *raiz){ //[7]

}/*Fim-printInOrder*/

void printPreOrder(No *raiz){ //[8]

}/*Fim-printPreOrder*/

void printPostOrder(No *raiz){ //[9]

}/*Fim-printPostOrder*/

void balanceTree(No *raiz){ //[10]

}/*Fim-balanceTree*/

//OUTRAS FUNÇÕES
int esta_balanceada(No *raiz){

}/*Fim-esta_balanceada*/

No* cria_no(int num){
  No *novo;

  novo = (No*) malloc(sizeof(No));

	if (novo == NULL)
		exit(-1000);

  novo->num = num;
  novo->no_left = NULL;
  novo->no_right = NULL;

  return novo;

}/*Fim-cria_no*/

void insere_no(No *no, int num){

  if(no == NULL){
    no = cria_no(num);
  }else{
    if(no->num < num){
      no->no_left = insere_no(no->no_left, num);
    }else if(no->num > num){
      no->no_right = insere_no(no->no_right, num);
    }
  }

  return no;

}/*Fim-insere_no*/
