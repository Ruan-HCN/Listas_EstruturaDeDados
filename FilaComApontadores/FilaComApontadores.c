/******************************************************************
 * Nome: Fila com Apontadores                                     *
 * Descri��o: Implementa��o de uma fila com apontadores para      *
 *            manipula��o de produtos. Este c�digo inclui as      *
 *            principais opera��es da fila, como:                 *
 *            dequeue                                             *
 *            enqueue                                             *
 *            verInicio                                           *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * �ltima altera��o: 01/12/2024                                   *
 ******************************************************************/


/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


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

/* Estrutura que representa a fila, com dois ponteiros, um para o inicio e um para o final*/
typedef struct {
	Produto *inicio;
	Produto *fim;       
}Fila;


//Fun��o para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer at� encontrar o '\n' ou EOF
}


/* Nome: criarProduto
 * Par�metro: id - identificador �nico do produto
 *            cor_do_tenis - cor do t�nis
 *            tamanho - tamanho do t�nis
 *            material - material do t�nis
 *            lote - n�mero do lote
 *            valor - valor do produto
 *            genero - g�nero do produto
 * Retorno: retorna um ponteiro para um novo produto alocado dinamicamente
 * Descri��o: Cria um novo produto com os atributos fornecidos e retorna
 *            um ponteiro para ele.
 */
Produto* criarProduto(int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero){
	Produto *novo = (Produto*)malloc(sizeof(Produto)); //Aloca mem�ria para um novo produto
	novo->id = id;
	strcpy(novo->cor_do_tenis, cor_do_tenis); //Define os atributos do produto
	novo->tamanho = tamanho;
	strcpy(novo->material, material);
	novo->lote = lote;
	novo->valor = valor;
	novo->genero = genero;
	novo->prox = NULL; //Inicializa o pr�ximo elemento como NULL 
	return novo;
}


/* Nome: iniciarFila
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: Inicializa a fila de produtos, definindo o ponteiro de in�cio e de fim
 *            como NULL, indicando que a fila est� vazia.
 */
void iniciarFila(Fila *fila){
	fila->inicio = NULL;   //Define o in�cio da fila como NULL (vazia)
	fila->fim = NULL;   //Define o fim da fila como NULL (vazia)
}


/* Nome: enqueue
 * Par�metro: fila - ponteiro para a fila de produtos
 	 	 	  novo - ponteiro para o novo produto inserido na fila
 * Descri��o: Enfileira os elementos, sempre os colocando no fim dda fila
 */
void enqueue(Fila *fila, Produto *novo){
	if(fila->fim == NULL){
		fila->inicio = novo;
		fila->fim = novo;
	}
	
	else{
		fila->fim->prox = novo;
		fila->fim = novo;
	}
}


/* Nome: dequeue
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: remove o primeiro elemento da fila, ava�ando o proximo elemento para a primeira posi��o
 */
void dequeue(Fila *fila){
	if(fila->inicio == NULL){
		printf("\nA fia esta vazia!\n");
		return;
	}
	
	Produto *temp = fila->inicio;
	fila->inicio = fila->inicio->prox;
	
	if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(temp);
    printf("\nProduto removido da fila com sucesso!\n");
}


/* Nome: verInicio
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: Ver o primeiro elemento da fila, faz a verifica��o se a fila esta vazia, e tem um ponteiro temporario para o primeiro elemento
 */
void verInicio(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("\nFila Vazia!\n");
        return;
    }

    Produto *temp = fila->inicio;
    printf("ID: %d\nCor do Tenis: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",
           temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->valor, temp->genero);
}


/* Nome: excluirFila
 * Par�metro: fila - ponteiro para a fila de produtos
 * Descri��o: remove todos os elementos da fila, liberando memoria no caminho. 
              o ponteiro temp pega o primeiro elemento, e vai avan�ando pra os proximos.
 */
void excluirFila(Fila *fila){
	Produto *temp = fila->inicio;
	
	while(temp != NULL){
		Produto *prox = temp->prox;
		free(temp);
		temp = prox;
	}
	
	fila->inicio = NULL;
	fila->fim = NULL;
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
    
    int id, lote;
    char cor[30], material[30], genero;
    float tamanho, valor;
    
    while (fscanf(arquivo, "%d %s %f %s %d %f %c", &id, cor, &tamanho, material, &lote, &valor, &genero) != EOF) {
        Produto *novo = criarProduto(id, cor, tamanho, material, lote, valor, genero); //Cria um novo produto
        enqueue(fila, novo); //Insere o produto na fila
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


/* Nome: salvarDados
 * Par�metro: fila - ponteiro para a fila de produtos
 *            nomeArquivo - nome do arquivo de onde os dados ser�o carregados
 * Descri��o: Salva os dados da fila existente em um arquivo de texto.
 */
void salvarDados(Fila *fila, char *nomeArquivo) {
	if(fila->inicio == NULL){
		printf("\nA fila esta vazia!\n");
		return;
	}
	
    FILE *arquivo = fopen(nomeArquivo, "w"); //Abre o arquivo em modo de escrita
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    Produto *temp = fila->inicio;  //Percorre a fila para salvar os dados
    
    while (temp != NULL) {
        fprintf(arquivo, "%d %s %.2f %s %d %.2f %c\n", temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->valor, temp->genero);
        temp = temp->prox;
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados salvos com sucesso!\n");
}


int main() {
	Fila fila;
	iniciarFila(&fila);
	
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
                enqueue(&fila, criarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero)); //insere elemnto na fila
                break;
            
            case 2:
                dequeue(&fila);
                break;
            
            case 3:
            	printf("\n");
                verInicio(&fila);
                break;
            
            case 4:
            	excluirFila(&fila);
                break;
            
            case 5:
            	salvarDados(&fila, NomeArquivo); //salva os dados da lista num txt
                break;
            
            case 6:
                carregarDados(&fila, NomeArquivo); //carregar os dados do txt
                break;
            
            case 7:
                excluirFila(&fila); //exclui todos os elementos e sai do script
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("Op��o inv�lida!\n");
                continue;
		}
	}while(escolha != 7);
	
	return 0;
}