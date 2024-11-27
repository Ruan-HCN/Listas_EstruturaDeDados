/******************************************************************
 * Nome: Pilha                                                    *
 * Descri��o: Implementa��o de uma pilha para manipula��o de      * 
 *            produtos. Este c�digo inclui as principais          * 
 *            opera��es da lista, como:                           *      
 *                                                                *
 * Autor: Ruan Henry                                              *
 * �ltima altera��o: 26/11/2024                                   *
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


/* Nome: excluirPilha
 * Par�metro: pilha - ponteiro que possui o endere�o da pilha
 * Descri��o: Exclui todos os produtos da pilha, liberando a mem�ria alocada
 *            e redefinindo o ponteiro de in�cio para NULL.
 */
void excluirPilha(Pilha *pilha){
	Produto *temp = pilha->topo; //Ponteiro tempor�rio para percorrer a pilha
	
	while(temp != NULL){ //Percorre a pilha liberando a mem�ria de cada produto
		Produto *prox = temp->prox;
		free(temp);
		temp = prox; 
	}
	pilha->topo = NULL; //Redefine o in�cio da pilha para NULL (pilha vazia)
}


/* Nome: carregarDados
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo de onde os dados ser�o carregados
 * Descri��o: Carrega os dados dos produtos armazenados em um arquivo
 *            para a lista, excluindo a lista existente antes de carregar.
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
        Produto *novo = CriarProduto(id, cor, tamanho, material, lote, valor, genero); //Cria um novo produto
        push(pilha, novo); //Insere o produto na pilha
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


/* Nome: pop
 * Par�metro: pilha - ponteiro para a pilha de produtos
 * Descri��o: Remove o produto do topo da pilha.
 *            Libera a mem�ria alocada para o produto removido.
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


/* Nome: push
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            novo - ponteiro para o novo produto que ser� inserido
 * Descri��o: Insere um novo produto no topo da pilha, deslocando os outros 
 *            elementos para a pr�xima posi��o.
 */
void push(Pilha *pilha, Produto *novo){
	novo->prox = pilha->topo; //Faz o novo produto apontar para o topo atual
    pilha->topo = novo;  //Define o novo produto como o topo da pilha
}


/* Nome: iniciarPilhaa
 * Par�metro: pilha - ponteiro para a pilha de produtos
 * Descri��o: Inicializa a pilha de produtos, definindo o ponteiro de in�cio
 *            como NULL, indicando que a pilha est� vazia.
 */
void iniciarPilha(Pilha *pilha){
	pilha->topo = NULL;   //Define o in�cio da lista como NULL (vazia)
}


/* Nome: salvarDados
 * Par�metro: pilha - ponteiro para a pilha de produtos
 *            nomeArquivo - nome do arquivo onde os dados ser�o salvos
 * Descri��o: Salva os dados de todos os produtos presentes na pilha
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
	Lista lista;
	lista.inicio = NULL; //Inicializa a lista como vazia
	
	//variaveis e defini��o de linguagem
	int escolha, id, posicao, lote;
	float tamanho, valor;
    char cor_do_tenis[30], material[30], genero;
    char NomeArquivo[] = "produtos.txt";
    
    setlocale(LC_ALL, "Portuguese");
    
    //inicio do menu com o do while
	
	do{
		printf("\n========================= Menu =========================");
        printf("\n\n1. Inserir elemento no final\n");
        printf("2. Inserir elemento no in�cio\n");
        printf("3. Inserir elemento em uma posi��o espec�fica\n");
        printf("4. Listar todos os elementos\n");
        printf("5. Atualizar produto\n");
        printf("6. Buscar produto por ID\n");
        printf("7. Tamanho da lista\n");
        printf("8. Excluir todos os elementos\n");
        printf("9. Carregar dados de arquivo\n");
        printf("10. Salvar dados em arquivo\n");
        printf("11. Remover Elemento Especifico\n");
        printf("12. Sair\n");
        
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
                LimparBuffer();
                printf("Material: ");
                scanf("%s", material);
                printf("Lote: ");
                scanf("%d", &lote);
                printf("Valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                printf("G�nero: ");
                scanf(" %c", &genero);
                InserirElemento(&lista, CriarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero)); //insere elemnto no final
                break;
            
            case 2:
                printf("\n\nID: ");
                scanf("%d", &id);
                printf("Cor do T�nis: ");
                scanf("%s", cor_do_tenis);
                printf("Tamanho: ");
                scanf("%f", &tamanho);
                LimparBuffer();
                printf("Material: ");
                scanf("%s", material);
                printf("Lote: ");
                scanf("%d", &lote);
                printf("Valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                printf("G�nero: ");
                scanf(" %c", &genero);
                InserirElementoInicio(&lista, CriarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero)); //insere elemnto no inicio
                break;
            
            case 3:
                printf("\nPosi��o: ");
                scanf("%d", &posicao);
                
                printf("\n\nID: ");
                scanf("%d", &id);
                printf("Cor do T�nis: ");
                scanf("%s", cor_do_tenis);
                printf("Tamanho: ");
                scanf("%f", &tamanho);
                LimparBuffer();
                printf("Material: ");
                scanf("%s", material);
                printf("Lote: ");
                scanf("%d", &lote);
                printf("Valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                printf("G�nero: ");
                scanf(" %c", &genero);
                InserirElementoPosicao(&lista, CriarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero), posicao); //insere elemento na posi��o
                break;
            
            case 4:
            	printf("\n");
                ListarElementos(&lista); //Lista todos os elementos
                break;
            
            case 5:
                printf("\nID do produto a ser atualizado: ");
                scanf("%d", &id);
                AtualizarProduto(&lista, id); //atualiza o elemento
                break;
            
            case 6:
                printf("\nID do produto a ser buscado: ");
                scanf("%d", &id);
                Produto *produto = BuscarElemento(&lista, id); //busca o produto
                if (produto != NULL) {
                    printf("\nID: %d\nCor do Tenis: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n",
                           produto->id, produto->cor_do_tenis, produto->tamanho, produto->material, produto->lote, produto->valor, produto->genero);
                } else {
                    printf("\nProduto n�o encontrado!\n");
                }
                break;
            
            case 7:
                printf("\nTamanho da lista: %d\n", TamanhoLista(&lista)); //verifica quantos elementos tem a lista
                break;
            
            case 8:
                ExcluirLista(&lista); //exclui a lista
                printf("\nLista exclu�da!\n");
                break;
            
            case 9:
                CarregarDados(&lista, NomeArquivo); //carregar os dados do txt
                break;
            
            case 10:
                SalvarDados(&lista, NomeArquivo); //salva os dados da lista num txt
                break;
            
            case 11:
            	printf("\nID do produto a ser removido: ");
    			scanf("%d", &id);
            	RemoverElemento(&lista, id);
            	break;
            
            case 12:
                ExcluirLista(&lista); //exclui todos os elementos e sai do script
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("Op��o inv�lida!\n");
                continue;
		}
	}while(escolha != 12);
	
	return 0;
}