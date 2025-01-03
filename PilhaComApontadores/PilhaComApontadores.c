/******************************************************************
 * Nome: Pilha com Apontadores                                    *
 * Descri��o: Implementa��o de uma pilha com apontadores          *
 *            para manipula��o de produtos. Este c�digo           *
 *            inclui as principais opera��es da lista, como:      * 
 * 			  push                                                *
 * 			  pop                                                 *
 *            verTopo                                             *
 * 			  ehVazia	                                          *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * �ltima altera��o: 08/12/2024                                   *     
 *                                                                *
 * Autor: Ruan Henry                                              *                     
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

/* Estrutura que representa a pilha, com um ponteiro para o topo */
typedef struct {
	Produto *topo;       
}Pilha;


//Fun��o para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer at� encontrar o '\n' ou EOF
}


/* Nome: ehVazia
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: Retorna o pilha->topo == NULL, ou seja verifica se a pilha esta vazia.
 */
int ehVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}


/* Nome: criarProduto
 * Par�metro: id - identificador �nico do produto
 *            cor_do_tenis - cor do t�nis
 *            tamanho - tamanho do t�nis
 *            material - material do t�nis
 *            lote - n�mero do loteif (verTopo(minhaPilha) == -1) {
        printf("\nPilha n�o est� mais dispon�vel.\n");
    }
 *            valor - valor do produto
 *            genero - g�nero do produto
 * Retorno: retorna um ponteiro para um novo produto alocado dinamicamente
 * Descri��o: Cria um novo produto com os atributos fornecidos e retorna
 *            um ponteiro para ele.
 */
Produto* criarProduto(int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero){
	Produto *novo = (Produto*)malloc(sizeof(Produto)); //Aloca memoria para um novo produto
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


/* Nome: excluirPilha
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: Exclui todos os produtos da pilha, liberando a mem�ria alocada
 *            e redefinindo o ponteiro de in�cio para NULL.
 */
Pilha* excluirPilha(Pilha *pilha){
	if (pilha == NULL) {
        printf("\nPilha n�o foi criada!\n");
        return NULL;
    }

	Produto *temp = pilha->topo;
    while (temp != NULL) {
            Produto *prox = temp->prox;
            free(temp); // Libera cada elemento
            temp = prox;
   	 }
    

    free(pilha);        
    return NULL;  
}


/* Nome: verTopo
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: Mostra o elemento no topo da pilha;
 */
int verTopo(Pilha *pilha){
	// Verifica se a pilha foi criada
    if (!pilha) {
        printf("\nPilha n�o criada.\n");
        return -1;
    }

    // Verifica se a pilha est� vazia
    if (ehVazia(pilha)) {
        printf("\nPilha vazia.\n");
        return 0;
    }

    Produto *topo = pilha->topo;
   
    printf("ID: %d\n", topo->id);
    printf("Cor: %s\n", topo->cor_do_tenis);
    printf("Tamanho: %.2f\n", topo->tamanho);
    printf("Material: %s\n", topo->material);
    printf("Lote: %d\n", topo->lote);
    printf("Valor: %.2f\n", topo->valor);
    printf("G�nero: %c\n", topo->genero);

    return 1;
}


/* Nome: push
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            novo - ponteiro para o novo produto que ser� inserido
 * Descri��o: Insere um novo produto no topo da pilha, deslocando os outros 
 *            elementos para a pr�xima posi��o.
 */
int push(Pilha *pilha, Produto *novo){
	if(pilha == NULL){
		printf("\nA pilha n�o foi criada!\n");
		return 0;
	}
	
	if(novo == NULL){
		printf("\nProduto n�o foi criado!\n");
		return 0;
	}
	
	novo->prox = pilha->topo; //Faz o novo produto apontar para o topo atual
    pilha->topo = novo;  //Define o novo produto como o topo da pilha
    
    return 1;
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
    
    int id, lote;
    char cor[30], material[30], genero;
    float tamanho, valor;
    
    while (fscanf(arquivo, "%d %s %f %s %d %f %c", &id, cor, &tamanho, material, &lote, &valor, &genero) != EOF) {
        Produto *novo = criarProduto(id, cor, tamanho, material, lote, valor, genero); //Cria um novo produto
        push(pilha, novo); //Insere o produto na pilha
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


/* Nome: pop
 * Par�metro: pilha - ponteiro para a pilha de produtos
 * Descri��o: Remove o produto do topo da pilha.
 *            Libera a mem�ria alocada para o produto removido. */
int pop(Pilha *pilha){
	if(pilha == NULL){
		printf("\nPilha n�o foi criada!\n");
		return 0;
	}
	
	if(ehVazia(pilha)){ //Verifica se a pilha esta vazia
		printf("\nPilha Vazia!\n");
		return 0;
	}
	
	Produto *temp = pilha->topo; //ponteiro temporario do topo da pilha		
	pilha->topo = pilha->topo->prox; //Atualiza o topo para o proximo elemento
	free(temp);
	printf("\nO produto do topo foi removido com sucesso!\n");
	
	return 1;
}


/* Nome: iniciarPilha
 * Par�metro: pilha - ponteiro para a pilha de produtos
 * Descri��o: Inicializa a pilha de produtos, definindo o ponteiro de in�cio
 *            como NULL, indicando que a pilha est� vazia.
 */
Pilha* iniciarPilha(){
	Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));
	if(pilha == NULL){
		printf("\nFalha ao alocar memoria!\n");
		return NULL;
	}
	
	pilha->topo = NULL;   //Define o inicio da lista como NULL (vazia)
	
	return pilha;
}


/* Nome: salvarDados
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo onde os dados ser�o salvos
 * Descri��o: Salva os dados de todos os produtos presentes na pilha em um arquivo de texto.
 */
void salvarDados(Pilha *pilha, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w"); //Abre o arquivo em modo de escrita
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    Produto *temp = pilha->topo;  //Percorre a pilha para salvar os dados
    
    while (temp != NULL) {
        fprintf(arquivo, "%d %s %.2f %s %d %.2f %c\n", temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->valor, temp->genero);
        temp = temp->prox;
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados salvos com sucesso!\n");
}


int main() {
	Pilha *pilha = iniciarPilha();
	
	//variaveis e defini��o de linguagem
	int escolha, id, lote;
	float tamanho, valor;
    char cor_do_tenis[30], material[30], genero;
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
                push(pilha, criarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero)); //insere elemnto na pilha
                break;
            
            case 2:
                pop(pilha);
                break;
            
            case 3:
            	printf("\n");
                verTopo(pilha);
                break;
            
            case 4:
            	pilha = excluirPilha(pilha);
                break;
            
            case 5:
            	salvarDados(pilha, NomeArquivo); //salva os dados da lista num txt
                break;
            
            case 6:
                carregarDados(pilha, NomeArquivo); //carregar os dados do txt
                break;
            
            case 7:
                excluirPilha(pilha); //exclui todos os elementos e sai do script
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("Op��o inv�lida!\n");
                continue;
		}
	}while(escolha != 7);
	
	return 0;
}