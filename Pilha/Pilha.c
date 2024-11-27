/******************************************************************
 * Nome: Pilha                                                    *
<<<<<<< HEAD
 * Descrição: Implementação de uma pilha para manipulação de      * 
 *            produtos. Este código inclui as principais          * 
 *            operações da lista, como:                           * 
 * 			  push                                                *
 * 			  pop                                                 *
 *            verTopo                                             *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * Última alteração: 27/11/2024                                   *
=======
 * DescriÃ§Ã£o: ImplementaÃ§Ã£o de uma pilha para manipulaÃ§Ã£o de      * 
 *            produtos. Este cÃ³digo inclui as principais          * 
 *            operaÃ§Ãµes da lista, como:                           *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * Ãšltima alteraÃ§Ã£o: 26/11/2024                                   *
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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


<<<<<<< HEAD
//Função para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer até encontrar o '\n' ou EOF
=======
//FunÃ§Ã£o para Limpar o Buffer
void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer atÃ© encontrar o '\n' ou EOF
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
}


/* Nome: criarProduto
<<<<<<< HEAD
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
=======
 * ParÃ¢metro: id - identificador Ãºnico do produto
 *            cor_do_tenis - cor do tÃªnis
 *            tamanho - tamanho do tÃªnis
 *            material - material do tÃªnis
 *            lote - nÃºmero do lote
 *            valor - valor do produto
 *            genero - gÃªnero do produto
 * Retorno: retorna um ponteiro para um novo produto alocado dinamicamente
 * DescriÃ§Ã£o: Cria um novo produto com os atributos fornecidos e retorna
 *            um ponteiro para ele.
 */
Produto* criarProduto(int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero){
	Produto *novo = (Produto*)malloc(sizeof(Produto)); //Aloca memÃ³ria para um novo produto
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
	novo->id = id;
	strcpy(novo->cor_do_tenis, cor_do_tenis); //Define os atributos do produto
	novo->tamanho = tamanho;
	strcpy(novo->material, material);
	novo->lote = lote;
	novo->valor = valor;
	novo->genero = genero;
<<<<<<< HEAD
	novo->prox = NULL; //Inicializa o próximo elemento como NULL 
=======
	novo->prox = NULL; //Inicializa o prÃ³ximo elemento como NULL 
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
	return novo;
}


/* Nome: excluirPilha
<<<<<<< HEAD
 * Parâmetro: pilha - ponteiro que possui o endereço da pilha
 * Descrição: Exclui todos os produtos da pilha, liberando a memória alocada
 *            e redefinindo o ponteiro de início para NULL.
 */
void excluirPilha(Pilha *pilha){
	Produto *temp = pilha->topo; //Ponteiro temporário para percorrer a pilha
	
	while(temp != NULL){ //Percorre a pilha liberando a memória de cada produto
=======
 * ParÃ¢metro: pilha - ponteiro que possui o endereÃ§o da pilha
 * DescriÃ§Ã£o: Exclui todos os produtos da pilha, liberando a memÃ³ria alocada
 *            e redefinindo o ponteiro de inÃ­cio para NULL.
 */
void excluirPilha(Pilha *pilha){
	Produto *temp = pilha->topo; //Ponteiro temporÃ¡rio para percorrer a pilha
	
	while(temp != NULL){ //Percorre a pilha liberando a memÃ³ria de cada produto
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
		Produto *prox = temp->prox;
		free(temp);
		temp = prox; 
	}
<<<<<<< HEAD
	pilha->topo = NULL; //Redefine o início da pilha para NULL (pilha vazia)
=======
	pilha->topo = NULL; //Redefine o inÃ­cio da pilha para NULL (pilha vazia)
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
}


/* Nome: verTopo
<<<<<<< HEAD
 * Parâmetro: pilha - ponteiro que possui o endereço da pilha
 * Descrição: Mostra o elemento no topo da pilha;
=======
 * ParÃ¢metro: pilha - ponteiro que possui o endereÃ§o da pilha
 * DescriÃ§Ã£o: Mostra o elemento no topo da pilha;
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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
<<<<<<< HEAD
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 *            novo - ponteiro para o novo produto que será inserido
 * Descrição: Insere um novo produto no topo da pilha, deslocando os outros 
 *            elementos para a próxima posição.
=======
 * ParÃ¢metro: pilha - ponteiro para a pilha de produtos
 *            novo - ponteiro para o novo produto que serÃ¡ inserido
 * DescriÃ§Ã£o: Insere um novo produto no topo da pilha, deslocando os outros 
 *            elementos para a prÃ³xima posiÃ§Ã£o.
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
 */
void push(Pilha *pilha, Produto *novo){
	novo->prox = pilha->topo; //Faz o novo produto apontar para o topo atual
    pilha->topo = novo;  //Define o novo produto como o topo da pilha
}


/* Nome: carregarDados
<<<<<<< HEAD
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo de onde os dados serão carregados
 * Descrição: Carrega os dados dos produtos armazenados em um arquivo
 *            para a pilha, excluindo a pilha existente antes de carregar.
=======
 * ParÃ¢metro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo de onde os dados serÃ£o carregados
 * DescriÃ§Ã£o: Carrega os dados dos produtos armazenados em um arquivo
 *            para a lista, excluindo a lista existente antes de carregar.
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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
<<<<<<< HEAD
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 * Descrição: Remove o produto do topo da pilha.
 *            Libera a memória alocada para o produto removido.
=======
 * ParÃ¢metro: pilha - ponteiro para a pilha de produtos
 * DescriÃ§Ã£o: Remove o produto do topo da pilha.
 *            Libera a memÃ³ria alocada para o produto removido.
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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
<<<<<<< HEAD
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 * Descrição: Inicializa a pilha de produtos, definindo o ponteiro de início
 *            como NULL, indicando que a pilha está vazia.
 */
void iniciarPilha(Pilha *pilha){
	pilha->topo = NULL;   //Define o início da lista como NULL (vazia)
=======
 * ParÃ¢metro: pilha - ponteiro para a pilha de produtos
 * DescriÃ§Ã£o: Inicializa a pilha de produtos, definindo o ponteiro de inÃ­cio
 *            como NULL, indicando que a pilha estÃ¡ vazia.
 */
void iniciarPilha(Pilha *pilha){
	pilha->topo = NULL;   //Define o inÃ­cio da lista como NULL (vazia)
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
}


/* Nome: salvarDados
<<<<<<< HEAD
 * Parâmetro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo onde os dados serão salvos
 * Descrição: Salva os dados de todos os produtos presentes na pilha
=======
 * ParÃ¢metro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo onde os dados serÃ£o salvos
 * DescriÃ§Ã£o: Salva os dados de todos os produtos presentes na pilha
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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
	
<<<<<<< HEAD
	//variaveis e definição de linguagem
=======
	//variaveis e definiÃ§Ã£o de linguagem
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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
        
<<<<<<< HEAD
		printf("\nEscolha uma opção: ");
=======
		printf("\nEscolha uma opÃ§Ã£o: ");
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
        scanf("%d", &escolha);
        
        switch(escolha){
			 case 1:
                printf("\n\nID: ");
                scanf("%d", &id);
<<<<<<< HEAD
                printf("Cor do Tênis: ");
=======
                printf("Cor do TÃªnis: ");
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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
<<<<<<< HEAD
                printf("Gênero: ");
=======
                printf("GÃªnero: ");
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
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
<<<<<<< HEAD
                printf("Opção inválida!\n");
=======
                printf("OpÃ§Ã£o invÃ¡lida!\n");
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
                continue;
		}
	}while(escolha != 7);
	
	return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 62e39875a6a6d581a55945c868f88c92f299ed8d
