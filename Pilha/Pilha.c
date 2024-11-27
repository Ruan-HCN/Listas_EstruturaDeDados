/******************************************************************
 * Nome: Pilha                                                    *
 * Descrição: Implementação de uma pilha para manipulação de      * 
 *            produtos. Este código inclui as principais          * 
 *            operações da lista, como:                           * 
 * 			  push                                                *
 * 			  pop                                                 *
 *            verTopo                                             *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * Última alteração: 27/11/2024                                   *
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


//Função para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer até encontrar o '\n' ou EOF
}


/* Nome: criarProduto
 * Parâmetro: id - identificador único do produto
 *            cor_do_tenis - cor do tênis
 *            tamanho - tamanho do tênis
 *            material - material do tênis
 *            lote - número do lote
 *            valor - valor do produto
 *            genero - gênero do produto
 * Retorno: retorna um ponteiro para um novo produto alocado dinamicamente
 * Descrição: Cria um novo produto com os atributos fornecidos e retorna
 *            um ponteiro para ele.
 */
Produto* criarProduto(int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero){
	Produto *novo = (Produto*)malloc(sizeof(Produto)); //Aloca memória para um novo produto
	novo->id = id;
	strcpy(novo->cor_do_tenis, cor_do_tenis); //Define os atributos do produto
	novo->tamanho = tamanho;
	strcpy(novo->material, material);
	novo->lote = lote;
	novo->valor = valor;
	novo->genero = genero;
	novo->prox = NULL; //Inicializa o próximo elemento como NULL 
	return novo;
}


/* Nome: excluirPilha
 * Parâmetro: pilha - ponteiro que possui o endereço da pilha
 * Descrição: Exclui todos os produtos da pilha, liberando a memória alocada
 *            e redefinindo o ponteiro de início para NULL.
 */
void excluirPilha(Pilha *pilha){
	Produto *temp = pilha->topo; //Ponteiro temporário para percorrer a pilha
	
	while(temp != NULL){ //Percorre a pilha liberando a memória de cada produto
		Produto *prox = temp->prox;
		free(temp);
		temp = prox; 
	}
	pilha->topo = NULL; //Redefine o início da pilha para NULL (pilha vazia)
}


/* Nome: verTopo
 * Parâmetro: pilha - ponteiro que possui o endereço da pilha
 * Descrição: Mostra o elemento no topo da pilha;
 */
void verTopo(Pilha *pilha){
	if(pilha->topo == NULL){
		printf("\nPilha Vazia!\n");
		return;
	}
	
	
	Produto *temp = pilha->topo;
	printf("ID: %d\nCor do Tenis: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",
               temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->valor, temp->genero);
	
}


/* Nome: push
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 *            novo - ponteiro para o novo produto que será inserido
 * Descrição: Insere um novo produto no topo da pilha, deslocando os outros 
 *            elementos para a próxima posição.
 */
void push(Pilha *pilha, Produto *novo){
	novo->prox = pilha->topo; //Faz o novo produto apontar para o topo atual
    pilha->topo = novo;  //Define o novo produto como o topo da pilha
}


/* Nome: carregarDados
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo de onde os dados serão carregados
 * Descrição: Carrega os dados dos produtos armazenados em um arquivo
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
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 * Descrição: Remove o produto do topo da pilha.
 *            Libera a memória alocada para o produto removido.
 */
void pop(Pilha *pilha){
	if(pilha->topo == NULL){ //Verifica se a pilha esta vazia
		printf("\nPilha Vazia!\n");
		return;
	}
	
	Produto *temp = pilha->topo; //ponteiro temporario do topo da pilha		
	pilha->topo = pilha->topo->prox; //Atualiza o topo para o proximo elemento
	free(temp);
	printf("\nO produto do topo foi removido com sucesso!\n");
}


/* Nome: iniciarPilhaa
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 * Descrição: Inicializa a pilha de produtos, definindo o ponteiro de início
 *            como NULL, indicando que a pilha está vazia.
 */
void iniciarPilha(Pilha *pilha){
	pilha->topo = NULL;   //Define o início da lista como NULL (vazia)
}


/* Nome: salvarDados
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo onde os dados serão salvos
 * Descrição: Salva os dados de todos os produtos presentes na pilha
 *            em um arquivo de texto.
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
	Pilha pilha;
	pilha.topo = NULL; //Inicializa o topo da pilha como vazia
	
	//variaveis e definição de linguagem
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
        
		printf("\nEscolha uma opção: ");
        scanf("%d", &escolha);
        
        switch(escolha){
			 case 1:
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
                push(&pilha, criarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero)); //insere elemnto na pilha
                break;
            
            case 2:
                pop(&pilha);
                break;
            
            case 3:
            	printf("\n");
                verTopo(&pilha);
                printf("\n");
                break;
            
            case 4:
            	excluirPilha(&pilha);
                break;
            
            case 5:
            	salvarDados(&pilha, NomeArquivo); //salva os dados da lista num txt
                break;
            
            case 6:
                carregarDados(&pilha, NomeArquivo); //carregar os dados do txt
                break;
            
            case 7:
                excluirPilha(&pilha); //exclui todos os elementos e sai do script
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("Opção inválida!\n");
                continue;
		}
	}while(escolha != 7);
	
	return 0;
}