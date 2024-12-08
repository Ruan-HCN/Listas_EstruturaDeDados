/******************************************************************
 * Nome: Fila com Vetor                                           *
 * Descrição: Implementação de uma fila com vetor para            *
 *            manipulação de produtos. Este código inclui as      *
 *            principais operações da fila, como:                 *
 *            dequeue                                             *
 *            enqueue                                             *
 *            verInicio                                           *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * Última alteração: 08/12/2024                                   *
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

/* Estrutura que representa a fila, com a representação do seu inicio, fim e tamanho. E um array para armazenar os produtos*/
typedef struct {
	Produto produtos[MAX];
	int inicio;
	int fim;
	int tamanho;       
}Fila;


//Função para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer até encontrar o '\n' ou EOF
}


/* Nome: iniciarFila
 * Parâmetro: fila - ponteiro para a fila de produtos
 * Descrição: Inicializa a fila de produtos, definindo o ponteiro de início como 0 e de fim
 *            como -1, indicando que a fila está vazia.
 */
Fila* iniciarFila(){
	Fila *fila = (Fila*)malloc(sizeof(Fila));
	
	if(fila == NULL){
		printf("\nA fila não foi criada!\n");
		return NULL;
	}
	
	fila->inicio = 0;   
	fila->fim = -1;
	fila->tamanho = 0;
	
	return fila;   
}


/* Nome: filaCheia
 * Parâmetro: fila - ponteiro para a fila de produtos
 * Descrição: verifica se a fila esta no seu tamanho maximo.
 */
int filaCheia(Fila *fila){
	return fila->tamanho == MAX;
}

/* Nome: filaVazia
 * Parâmetro: fila - ponteiro para a fila de produtos
 * Descrição: verifica se a fila esta Vazia.
 */
int filaVazia(Fila *fila){
	return fila->tamanho == 0;
}


/* Nome: enqueue
 * Parâmetro: fila - ponteiro para a fila de produtos
              produto - variavel do tipo produto 
 * Descrição: Verifica se a fila esta cheia, se não,
              o fila->fim é usado para indicar a posição do elemento a ser inserio
              atraves do resto da divisao pela constante maximo. E por fim incrementa o tamanho da fila.
 */
int enqueue(Fila *fila, Produto produto){
	if(fila == NULL){
		printf("\nA fila não foi criada!\n");
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
 * Parâmetro: fila - ponteiro para a fila de produtos
              produto - variavel do tipo produto 
 * Descrição: Verifica se a fila esta vazia, se não,
              o fila->inicio é usado para indicar a posição do primeiro elemento
              a ser "removiso". e por fim decrementa o tamanho da fila.
 */
int dequeue(Fila *fila){
	if(fila == NULL){
		printf("\nA fila não foi criada!\n");
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
 * Parâmetro: fila - ponteiro para a fila de produtos
 * Descrição: Verifica se a fila esta vazia, se não,
              exibe a o primeiro elemento da fila. 
 */
int verInicio(Fila *fila) {
	if(fila == NULL){
		printf("\nA fila não foi criada!\n");
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
 * Parâmetro: fila - ponteiro para a fila de produtos
 * Descrição: Verifica se a fila esta vazia, se não,
              "reinicia" a fila. 
 */
int excluirFila(Fila *fila){
	if(fila == NULL){
		printf("\nA fila não foi criada!\n");
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
 * Parâmetro: fila - ponteiro para a fila de produtos
 *            nomeArquivo - nome do arquivo de onde os dados serão carregados
 * Descrição: Carrega os dados dos produtos armazenados em um arquivo
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
 * Parâmetro: fila - ponteiro para a fila de produtos
 *            nomeArquivo - nome do arquivo de onde os dados serão carregados
 * Descrição: Salva os dados da fila em um arquivo txt, atraves do loop for, que percorre a fila
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
	
	//variaveis e definição de linguagem
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
        
		printf("\nEscolha uma opção: ");
        scanf("%d", &escolha);
        
        switch(escolha){
			 case 1:
			 	if (filaCheia(fila)) {
                    printf("\nA fila está cheia!\n");
                    break;
                }
                
                printf("\n\nID: ");
                scanf("%d", &id);
                printf("Cor do Tênis: ");
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
                printf("Gênero: ");
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
                printf("Opção inválida!\n");
                continue;
		}
	}while(escolha != 7);
	
	return 0;
}