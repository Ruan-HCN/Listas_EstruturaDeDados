/******************************************************************
 * Nome: Pilha com Vetor                                          *
 * Descri��o: Implementa��o de uma pilha com vetor                *
 *            para manipula��o de produtos, de tamanho mXIMO 5    *
 *            Este c�digo inclui as principais opera��es da       *
 *            lista, como:                                        * 
 * 			  push                                                *
 * 			  pop                                                 *
 *            verTopo                                             *
 * 			  ehVazia	                                          *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * �ltima altera��o: 30/11/2024                                   *     
 *                                                                *
 * Autor: Ruan Henry                                              *                     
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

/* Estrutura que representa a pilha, com a representa��o do topo, e uma array para armazenar os produtos*/
typedef struct {
	Produto produtos[MAX];
	int topo;       
}Pilha;


//Fun��o para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer at� encontrar o '\n' ou EOF
}


/* Nome: ehVazia
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: Retorna o pilha->topo == -1, ou seja verifica se a pilha esta vzaia.
 */
int ehVazia(Pilha *pilha) {
    return pilha->topo == -1;
}


/* Nome: ehCheia
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: Retorna o pilha->topo == MAX - 1, ou seja verifica se a pilha esta cheia.
 */
int ehCheia(Pilha *pilha) {
    return pilha->topo == MAX - 1;
}


/* Nome: excluirPilha
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: define o topo da pilha como -1
 */
void excluirPilha(Pilha *pilha){
	if(ehVazia(pilha)){
		printf("\nA Pilha est� vazia. Nenhum elemento a remover!\n");
		return;
	}
	pilha->topo = -1;
}


/* Nome: verTopo
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: Mostra o elemento no topo da pilha;
 */
void verTopo(Pilha *pilha){
	if(ehVazia(pilha)){
		printf("\nPilha Vazia!\n");
		return;
	}
	
	
	Produto *produto = &pilha->produtos[pilha->topo];
	printf("ID: %d\nCor do Tenis: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",
               produto->id, produto->cor_do_tenis, produto->tamanho, produto->material, produto->lote, produto->valor, produto->genero);
	
}


/* Nome: push
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            novo - ponteiro para o novo produto que ser� inserido
 * Descri��o: Insere um novo produto no topo da pilha, inserindo no vetor.
 */
void push(Pilha *pilha, Produto produto){
	if(ehCheia(pilha)){
		printf("\nA pilha esta cheia. N�o � possivel inserir um novo elemento.\n");
		return;
	}
	
	pilha->produtos[++(pilha->topo)] = produto;
}


/* Nome: carregarDados
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo de onde os dados ser�o carregados
 * Descri��o: Carrega os dados dos produtos armazenados em um arquivo
 *            para a pilha, excluindo a pilha existente antes de carregar.
 */
void carregarDados(Pilha *pilha, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); //Abre o arquivo em modo de leitura
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    excluirPilha(pilha); //Exclui a pilha atual para evitar duplicatas
    
    Produto produto;
    
    while (fscanf(arquivo, "%d %s %f %s %d %f %c", &produto.id, produto.cor_do_tenis, &produto.tamanho, produto.material, &produto.lote, &produto.valor, &produto.genero) != EOF) {
        push(pilha, produto); //Insere o produto na pilha
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


/* Nome: pop
 * Par�metro: pilha - ponteiro para a pilha de produtos
 * Descri��o: Remove o produto do topo da pilha, atraves do decremento.
 */
void pop(Pilha *pilha){
	if(ehVazia(pilha)){ //Verifica se a pilha esta vazia
		printf("\nPilha Vazia!\n");
		return;
	}
	
	pilha->topo--;
	printf("\nO produto do topo foi removido com sucesso!\n");
}


/* Nome: iniciarPilha
 * Par�metro: pilha - ponteiro para a pilha de produtos
 * Descri��o: Inicializa a pilha de produtos, definindo o ponteiro de in�cio
 *            como NULL, indicando que a pilha est� vazia.
 */
void iniciarPilha(Pilha *pilha){
	pilha->topo = -1;   //Define o inicio da lista como -1
}


/* Nome: salvarDados
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo onde os dados ser�o salvos
 * Descri��o: Salva os dados de todos os produtos presentes na pilha em um arquivo de texto.
 */
void salvarDados(Pilha *pilha, char *nomeArquivo) {
	if(ehVazia(pilha)){
		printf("\nn�o a dados para serem salvos!\n");
		return;
	}
	
    FILE *arquivo = fopen(nomeArquivo, "w"); //Abre o arquivo em modo de escrita
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    int i;
    
    for(i = 0; i <= pilha->topo; i++) {
    	Produto *produto = &pilha->produtos[i];
        fprintf(arquivo, "%d %s %.2f %s %d %.2f %c\n", produto->id, produto->cor_do_tenis, produto->tamanho, produto->material, produto->lote, produto->valor, produto->genero);
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados salvos com sucesso!\n");
}


int main() {
	Pilha pilha;
	iniciarPilha(&pilha);
	
	int escolha;
	Produto produto;
    char NomeArquivo[] = "produtos.txt";
    
    setlocale(LC_ALL, "Portuguese");
    
    //inicio do menu com o do while
	do{
		printf("\n========================= Menu =========================");
        printf("\n\n1. Inserir elemento na pilha\n");
        printf("2. Excluir Elemento do Topo\n");
        printf("3. Ver Topo da Pilha\n");
        printf("4. Excluir Pilha\n");
        printf("5. Salvar Dados\n");
        printf("6. Carregar Dados\n");
        printf("7. Sair\n");
        
		printf("\nEscolha uma op��o: ");
        scanf("%d", &escolha);
        
        switch(escolha){
			 case 1:
			 	if(ehCheia(&pilha)){
					printf("\nA pilha est� cheia! N�o � poss�vel adicionar mais produtos.\n");
                    break;
				 }
			 	
                printf("\n\nID: ");
                scanf("%d", &produto.id);
                printf("Cor do T�nis: ");
                scanf("%s", produto.cor_do_tenis);
                printf("Tamanho: ");
                scanf("%f", &produto.tamanho);
                limparBuffer();
                printf("Material: ");
                scanf("%s", produto.material);
                printf("Lote: ");
                scanf("%d", &produto.lote);
                printf("Valor: ");
                scanf("%f", &produto.valor);
                limparBuffer();
                printf("G�nero: ");
                scanf(" %c", &produto.genero);
                push(&pilha, produto); //insere elemnto na pilha
                printf("\nProduto inserido com sucesso!\n");
                break;
            
            case 2:
                pop(&pilha);
                break;
            
            case 3:
            	printf("\n");
                verTopo(&pilha);
                break;
            
            case 4:
            	excluirPilha(&pilha);
            	printf("\nTodos os elementos foram removidos com sucesso!\n");
                break;
            
            case 5:
            	salvarDados(&pilha, NomeArquivo); //salva os dados da lista num txt
                break;
            
            case 6:
                carregarDados(&pilha, NomeArquivo); //carregar os dados do txt
                break;
            
            case 7:
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("Op��o inv�lida!\n");
                continue;
		}
	}while(escolha != 7);
	
	return 0;
}