/******************************************************************
 * Nome: Fila com Vetor                                           *
 * Descri��o: Implementa��o de uma fila com vetor para            *
 *            manipula��o de produtos. Este c�digo inclui as      *
 *            principais opera��es da fila, como:                 *
 *            dequeue                                             *
 *            enqueue                                             *
 *            verInicio                                           *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * �ltima altera��o: 08/12/2024                                   *
 ******************************************************************/


/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 5

/*Definicao da estrutura*/
typedef struct Produto{
	int id;
    char cor_do_tenis[30];
    float tamanho;
    char material[30];
    int lote;
    float valor;
    char genero;
    struct Produto *prox;
}Produto;

/* Estrutura que representa a fila, com a representa��o do seu inicio, fim e tamanho. E um array para armazenar os produtos*/
typedef struct {
	Produto produtos[MAX];
	int inicio;
	int fim;
	int tamanho;       
}Fila;


//Fun��o para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer at� encontrar o '\n' ou EOF
}


/* Nome: iniciarFila
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: Inicializa a fila de produtos, definindo o ponteiro de in�cio como 0 e de fim
 *            como -1, indicando que a fila est� vazia.
 */
Fila* iniciarFila(){
	Fila *fila = (Fila*)malloc(sizeof(Fila));
	
	if(fila == NULL){
		printf("\nA fila n�o foi criada!\n");
		return NULL;
	}
	
	fila->inicio = 0;   
	fila->fim = -1;
	fila->tamanho = 0;
	
	return fila;   
}


/* Nome: filaCheia
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: verifica se a fila esta no seu tamanho maximo.
 */
int filaCheia(Fila *fila){
	return fila->tamanho == MAX;
}

/* Nome: filaVazia
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: verifica se a fila esta Vazia.
 */
int filaVazia(Fila *fila){
	return fila->tamanho == 0;
}


/* Nome: enqueue
 * Par�metro: fila - ponteiro para a fila de produtos
              produto - variavel do tipo produto 
 * Descri��o: Verifica se a fila esta cheia, se n�o,
              o fila->fim � usado para indicar a posi��o do elemento a ser inserio
              atraves do resto da divisao pela constante maximo. E por fim incrementa o tamanho da fila.
 */
int enqueue(Fila *fila, Produto produto){
	if(fila == NULL){
		printf("\nA fila n�o foi criada!\n");
		return 0;
	}
	
	if(filaCheia(fila)){
		printf("\nA fila esta cheia!\n");
		return 0;
	}
	
	fila->fim = (fila->fim + 1) % MAX;
	fila->produtos[fila->fim] = produto;
	fila->tamanho++;
	
	return 1;
}


/* Nome: dequeue
 * Par�metro: fila - ponteiro para a fila de produtos
              produto - variavel do tipo produto 
 * Descri��o: Verifica se a fila esta vazia, se n�o,
              o fila->inicio � usado para indicar a posi��o do primeiro elemento
              a ser "removiso". e por fim decrementa o tamanho da fila.
 */
int dequeue(Fila *fila){
	if(fila == NULL){
		printf("\nA fila n�o foi criada!\n");
		return 0;
	}
	
	if(filaVazia(fila)){
		printf("\nA fia esta vazia!\n");
		return 0;
	}
	
	fila->inicio = (fila->inicio + 1) % MAX;
	fila->tamanho--;
    printf("\nProduto removido da fila com sucesso!\n");
    
    return 1;
}


/* Nome: verInicio
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: Verifica se a fila esta vazia, se n�o,
              exibe a o primeiro elemento da fila. 
 */
int verInicio(Fila *fila) {
	if(fila == NULL){
		printf("\nA fila n�o foi criada!\n");
		return 0;
	}
	
    if (filaVazia(fila)) {
        printf("\nFila Vazia!\n");
        return 0;
    }

    Produto *produto = &fila->produtos[fila->inicio];
    printf("ID: %d\nCor do Tenis: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",
           produto->id, produto->cor_do_tenis, produto->tamanho, produto->material, produto->lote, produto->valor, produto->genero);
           
    return 1; 
}


/* Nome: excluirFila
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: Verifica se a fila esta vazia, se n�o,
              "reinicia" a fila. 
 */
int excluirFila(Fila *fila){
	if(fila == NULL){
		printf("\nA fila n�o foi criada!\n");
		return 0;
	}
	
	if(filaVazia(fila)){
		printf("\nA fila esta Vazia!\n");
		return 0;
	}
	
	iniciarFila(fila);
	printf("\nFila Excluida!\n");
	
	return 1;
}


/* Nome: carregarDados
 * Par�metro: fila - ponteiro para a fila de produtos
 *            nomeArquivo - nome do arquivo de onde os dados ser�o carregados
 * Descri��o: Carrega os dados dos produtos armazenados em um arquivo
 *            para a fila, excluindo a fila existente antes de carregar.
 */
void carregarDados(Fila *fila, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); //Abre o arquivo em modo de leitura
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    excluirFila(fila); //Exclui a fila atual para evitar duplicatas
    
    Produto produto;
    
    while (fscanf(arquivo, "%d %s %f %s %d %f %c", &produto.id, produto.cor_do_tenis, &produto.tamanho, produto.material, &produto.lote, &produto.valor, &produto.genero) != EOF){
        enqueue(fila, produto); //Insere o produto na fila
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


/* Nome: salvarDados
 * Par�metro: fila - ponteiro para a fila de produtos
 *            nomeArquivo - nome do arquivo de onde os dados ser�o carregados
 * Descri��o: Salva os dados da fila em um arquivo txt, atraves do loop for, que percorre a fila
              e escreve os elementos no arquivo e texto.
 */
void salvarDados(Fila *fila, char *nomeArquivo) {
	if(filaVazia(fila)){
		printf("\nA fila esta vazia!\n");
		return;
	}
	
    FILE *arquivo = fopen(nomeArquivo, "w"); //Abre o arquivo em modo de escrita
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    int i;
    
    for (i = 0; i < fila->tamanho; i++) {
    	int prox = (fila->inicio + 1) % MAX;
    	Produto *produto = &fila->produtos[prox];
        fprintf(arquivo, "%d %s %.2f %s %d %.2f %c\n", produto->id, produto->cor_do_tenis, produto->tamanho, produto->material, produto->lote, produto->valor, produto->genero);
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados salvos com sucesso!\n");
}


int main() {
	Fila *fila;
	fila = iniciarFila();
	
	//variaveis e defini��o de linguagem
	int escolha, id, lote;
	float tamanho, valor;
    char cor_do_tenis[30], material[30], genero;
    char NomeArquivo[] = "produtos.txt";
    
    setlocale(LC_ALL, "Portuguese");
    
    //inicio do menu com o do while
	
	do{
		printf("\n========================= Menu =========================");
        printf("\n\n1. Inserir elemento na Fila\n");
        printf("2. Excluir Elemento do Inicio\n");
        printf("3. Ver Inicio da Fila\n");
        printf("4. Excluir Fila\n");
        printf("5. Salvar Dados\n");
        printf("6. Carregar Dados\n");
        printf("7. Sair\n");
        
		printf("\nEscolha uma op��o: ");
        scanf("%d", &escolha);
        
        switch(escolha){
			 case 1:
			 	if (filaCheia(fila)) {
                    printf("\nA fila est� cheia!\n");
                    break;
                }
                
                printf("\n\nID: ");
                scanf("%d", &id);
                printf("Cor do T�nis: ");
                scanf("%s", cor_do_tenis);
                printf("Tamanho: ");
                scanf("%f", &tamanho);
                limparBuffer();
                printf("Material: ");
                scanf("%s", material);
                printf("Lote: ");
                scanf("%d", &lote);
                printf("Valor: ");
                scanf("%f", &valor);
                limparBuffer();
                printf("G�nero: ");
                scanf(" %c", &genero);
                
                Produto produto = {id, "", tamanho, "", lote, valor, genero};
                strcpy(produto.cor_do_tenis, cor_do_tenis);
                strcpy(produto.material, material);
                enqueue(fila, produto); //insere elemnto na fila
                printf("\nProduto Inserido!\n");
                break;
            
            case 2:
                dequeue(fila);
                break;
            
            case 3:
            	printf("\n");
                verInicio(fila);
                break;
            
            case 4:
            	excluirFila(fila);
                break;
            
            case 5:
            	salvarDados(fila, NomeArquivo); //salva os dados da lista num txt
                break;
            
            case 6:
                carregarDados(fila, NomeArquivo); //carregar os dados do txt
                break;
            
            case 7:
                excluirFila(fila); //exclui todos os elementos e sai do script
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("Op��o inv�lida!\n");
                continue;
		}
	}while(escolha != 7);
	
	return 0;
}