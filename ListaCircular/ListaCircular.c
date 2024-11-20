/****************************************************************** 
 * Nome: Lista Cirucular                                          *
 * Descricao: Implementacao de lista Circular                     *
 *            Esse codigo possui as principais operacoes da       *
 *            lista, como:                                        *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Ruan Henry                                              *
 * Ultima alteracao: 20/11/2024                                   *
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

/* Estrutura que representa a lista, com um ponteiro para o primeiro elemento */
typedef struct {
	Produto *inicio;          //Ponteiro para o primeiro produto da lista
}Lista;

void LimparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer até encontrar o '\n' ou EOF
}

/* Nome: BuscarElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            id - elemento que sera buscado pelo id
 * Retorno: o retorno e vazio
 * Descricao: Funcao criada para buscar um elemento na lista
 */
Produto* BuscarElemento(Lista *lista, int id){
	if(lista->inicio == NULL){
		return NULL;
	}
	
	Produto *temp = lista->inicio; 
	
	do{
		if(temp->id == id){
			return temp;
		}
		temp = temp->prox;
	}while(temp != lista->inicio);
	
	return NULL; //Produto não encontrado
}


/* Nome: AtualizarProduto
 * Parametros: lista - ponteiro que possui o endereco lista
 *             id - elemento que sera buscado na lista pelo id 
 * Descricao: Funcao responsavel por atualizar um elemento
 *            da lista, caso o mesmo esteja na lista indicada
 */
void AtualizarProduto(Lista *lista, int id){
	Produto *produto = BuscarElemento(lista, id);  //Busca o produto pelo ID
	
	 //Se o produto foi encontrado
	if (produto != NULL) {
        printf("\nNovo tamanho: ");
        scanf("%f", &produto->tamanho);
        LimparBuffer();
        printf("Nova cor do tênis: ");
        scanf("%s", produto->cor_do_tenis);
        printf("Novo material: ");
        scanf("%s", produto->material);
        printf("Novo lote: ");
        scanf("%d", &produto->lote);
        printf("Novo valor: ");
        scanf("%f", &produto->valor);
        LimparBuffer();
        printf("Novo gênero: ");
        scanf(" %c", &produto->genero);
    } 
	
	//Se o produto não foi encontrado
	else {
        printf("\nProduto não encontrado!\n");
    }
}


/* Nome: CriarProduto
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
Produto* CriarProduto(int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero){
	Produto *novo = (Produto*)malloc(sizeof(Produto)); //Aloca memória para um novo produto
	novo->id = id;
	strcpy(novo->cor_do_tenis, cor_do_tenis); //Define os atributos do produto
	novo->tamanho = tamanho;
	strcpy(novo->material, material);
	novo->lote = lote;
	novo->valor = valor;
	novo->genero = genero;
	novo->prox = NULL; //Inicializa o próximo elemento como NULL (final da lista)
	return novo;
}


/* Nome: InserirElemento
 * Parâmetro: lista - ponteiro para a lista de produtos
 *            novo - ponteiro para o novo produto que será inserido
 * Descrição: Insere um novo produto no final da lista. Caso a lista esteja vazia,
 *            o novo produto será o primeiro elemento. Caso contrário, ele será 
 *            inserido no final.
 */
void InserirElemento(Lista *lista, Produto *novo){
	if(lista->inicio == NULL){ //Se a lista estiver vazia, insere no início
		lista->inicio = novo;
		novo->prox = novo;
	}
	
	else{
		Produto *temp = lista->inicio; //Percorre até o último produto
		while(temp->prox != lista->inicio){
			temp = temp->prox;
		}
		temp->prox = novo;  //Insere o novo produto no final da lista
		novo->prox = lista->inicio;
	}
}


/* Nome: ExcluirLista
 * Parâmetro: lista - ponteiro que possui o endereço da lista
 * Descrição: Exclui todos os produtos da lista, liberando a memória alocada
 *            e redefinindo o ponteiro de início para NULL.
 */
void ExcluirLista(Lista *lista){
	if(lista->inicio == NULL){
		return;
	}
	
	Produto *temp = lista->inicio;
	Produto *prox;
	
	do{
		prox = temp->prox;
		free(temp);
		temp = prox;
	}while(temp != lista->inicio);
	
	lista->inicio = NULL; 	
}


/* Nome: CarregarDados
 * Parâmetro: lista - ponteiro para a lista de produtos
 *            nomeArquivo - nome do arquivo de onde os dados serão carregados
 * Descrição: Carrega os dados dos produtos armazenados em um arquivo
 *            para a lista, excluindo a lista existente antes de carregar.
 */
void CarregarDados(Lista *lista, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); //Abre o arquivo em modo de leitura
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    ExcluirLista(lista); //Exclui a lista atual para evitar duplicatas
    
    int id, lote;
    char cor[30], material[30], genero;
    float tamanho, valor;
    
    while (fscanf(arquivo, "%d %s %f %s %d %f %c", &id, cor, &tamanho, material, &lote, &valor, &genero) != EOF) {
        Produto *novo = CriarProduto(id, cor, tamanho, material, lote, valor, genero); //Cria um novo produto
        InserirElemento(lista, novo); //Insere o produto na lista
    }
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


/* Nome: RemoverElemento
 * Parâmetro: lista - ponteiro para a lista de produtos
 *            id - identificador único do produto a ser removido
 * Descrição: Remove um produto específico da lista com base no ID fornecido.
 *            Libera a memória alocada para o produto removido.
 */
void RemoverElemento(Lista *lista, int id){
	Produto *temp = lista->inicio; //ponteiro temporario do inicio da lista
	Produto *anterior = NULL; //ponterio para o elemento anterior
	
	while(temp != NULL){ //percorre a lista
		if(temp->id == id){ //verifica se o id corresponde
			if(anterior == NULL){ //se for o primeiro elemento
				lista->inicio = temp->prox;
			}
			
			else{ //remove o elemento do emio ou do fim
				anterior->prox = temp->prox;
			}
			
			free(temp);
			printf("\nProduto com ID: %d. Removido com sucesso!\n", id);
			return;
		}
		//avança os ponteiros
		anterior = temp;
		temp = temp->prox;
	}
	printf("\nProduto com ID: %d. Não encontrado.\n", id);
}


/* Nome: InserirElementoInicio
 * Parâmetro: lista - ponteiro para a lista de produtos
 *            novo - ponteiro para o novo produto que será inserido
 * Descrição: Insere um novo produto no início da lista, deslocando os outros 
 *            elementos para a próxima posição.
 */
void InserirElementoInicio(Lista *lista, Produto *novo){
	if (lista->inicio == NULL) { 
        lista->inicio = novo;
        novo->prox = novo; // Torna a lista circular
    } 
	
	else {
        Produto *temp = lista->inicio;
        
        while (temp->prox != lista->inicio) {
            temp = temp->prox; // Encontra o último elemento
        }
        
        temp->prox = novo; // Atualiza o último elemento para apontar para o novo
        novo->prox = lista->inicio; 
        lista->inicio = novo;
	}
}


/* Nome: InserirElementoPosicao
 * Parâmetro: lista - ponteiro para a lista de produtos
 *            novo - ponteiro para o novo produto que será inserido
 *            posicao - a posição na lista onde o novo produto será inserido
 * Descrição: Insere um novo produto em uma posição específica da lista. Se a posição
 *            for 0, o produto será inserido no início. Caso contrário, ele será 
 *            inserido na posição desejada, ou será exibida uma mensagem de erro 
 *            se a posição for inválida.
 */
void InserirElementoPosicao(Lista *lista, Produto *novo, int posicao){
	if (posicao == 0) { 
        InserirElementoInicio(lista, novo);
    } 
	
	else {
        Produto *temp = lista->inicio;
        int i;

        for (i = 0; i < posicao - 1 && temp->prox != lista->inicio; i++) {
            temp = temp->prox;
        }

        if (i == posicao - 1) {
            novo->prox = temp->prox;
            temp->prox = novo;
        } 
		
		else {
            printf("\nPosição inválida!\n");
        }
    }
}


/* Nome: IniciarLista
 * Parâmetro: lista - ponteiro para a lista de produtos
 * Descrição: Inicializa a lista de produtos, definindo o ponteiro de início
 *            como NULL, indicando que a lista está vazia.
 */
void IniciarLista(Lista *lista){
	lista->inicio = NULL;   //Define o início da lista como NULL (vazia)
}


/* Nome: ListarElementos
 * Parâmetro: lista - ponteiro para a lista de produtos
 * Descrição: Percorre a lista e exibe as informações de cada produto 
 *            (ID, cor, tamanho, material, lote, valor e gênero) até o 
 *            final da lista.
 */
void ListarElementos(Lista *lista) {
    if(lista->inicio == NULL){
		printf("Lista Vazia!\n");
		return;
	}
	
	Produto *temp = lista->inicio;
	
	do{
		printf("ID: %d\nCor do Tenis: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",
               temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->valor, temp->genero);
               
               temp = temp->prox;
	}while(temp != lista->inicio);
}


/* Nome: SalvarDados
 * Parâmetro: lista - ponteiro para a lista de produtos
 *            nomeArquivo - nome do arquivo onde os dados serão salvos
 * Descrição: Salva os dados de todos os produtos presentes na lista
 *            em um arquivo de texto, no formato especificado.
 */
void SalvarDados(Lista *lista, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w"); //Abre o arquivo em modo de escrita
    
    if (arquivo == NULL) { //Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    if (lista->inicio == NULL) { 
        fclose(arquivo);
        printf("Lista vazia. Nenhum dado salvo.\n");
        return;
    }
    
    Produto *temp = lista->inicio;  //Percorre a lista para salvar os dados
    
    do {
        fprintf(arquivo, "%d %s %.2f %s %d %.2f %c\n", 
                temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->valor, temp->genero);
        temp = temp->prox;
    } while (temp != lista->inicio);
    
    fclose(arquivo); //Fecha o arquivo
    printf("Dados salvos com sucesso!\n");
}


/* Nome: TamanhoLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: retorna quantos elementos a lista possui
 * Descricao: Funcao criada para saber quantos elementos a lista possui
 */
int TamanhoLista(Lista *lista){
	if(lista->inicio == NULL){
		return 0;
	}
	
	int tamanho = 0;
	Produto *temp = lista->inicio; //Ponteiro temporário para percorrer a lista
	
	do{
		tamanho++;
		temp = temp->prox;
	}while(temp != lista->inicio); //percorre a lista, até que o proximo elemento seja o primeiro. e incrementa no contador os elementos da lista
	
	return tamanho;
}


int main() {
	Lista lista;
	lista.inicio = NULL; //Inicializa a lista como vazia
	
	int escolha, id, posicao, lote;
	float tamanho, valor;
    char cor_do_tenis[30], material[30], genero;
    char NomeArquivo[] = "produtos.txt";
    setlocale(LC_ALL, "Portuguese");
	
	do{
		printf("\n========================= Menu =========================");
        printf("\n\n1. Inserir elemento no final\n");
        printf("2. Inserir elemento no início\n");
        printf("3. Inserir elemento em uma posição específica\n");
        printf("4. Listar todos os elementos\n");
        printf("5. Atualizar produto\n");
        printf("6. Buscar produto por ID\n");
        printf("7. Tamanho da lista\n");
        printf("8. Excluir todos os elementos\n");
        printf("9. Carregar dados de arquivo\n");
        printf("10. Salvar dados em arquivo\n");
        printf("11. Remover Elemento Especifico\n");
        printf("12. Sair\n");
        
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
                LimparBuffer();
                printf("Material: ");
                scanf("%s", material);
                printf("Lote: ");
                scanf("%d", &lote);
                printf("Valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                printf("Gênero: ");
                scanf(" %c", &genero);
                InserirElemento(&lista, CriarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero)); //insere elemnto no final
                break;
            
            case 2:
                printf("\n\nID: ");
                scanf("%d", &id);
                printf("Cor do Tênis: ");
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
                printf("Gênero: ");
                scanf(" %c", &genero);
                InserirElementoInicio(&lista, CriarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero)); //insere elemnto no inicio
                break;
            
            case 3:
                printf("\nPosição: ");
                scanf("%d", &posicao);
                
                printf("\n\nID: ");
                scanf("%d", &id);
                printf("Cor do Tênis: ");
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
                printf("Gênero: ");
                scanf(" %c", &genero);
                InserirElementoPosicao(&lista, CriarProduto(id, cor_do_tenis, tamanho, material, lote, valor, genero), posicao); //insere elemento na posição
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
                    printf("\nProduto não encontrado!\n");
                }
                break;
            
            case 7:
                printf("\nTamanho da lista: %d\n", TamanhoLista(&lista)); //verifica quantos elementos tem a lista
                break;
            
            case 8:
                ExcluirLista(&lista); //exclui a lista
                printf("\nLista excluída!\n");
                break;
            
            case 9:
                CarregarDados(&lista, NomeArquivo); //carregar os dados do txt
                break;
            
            case 10:
                SalvarDados(&lista, NomeArquivo); //salva os dados da lista num txt
                break;
            
            case 11:
            	printf("\nID do produto a ser removido: "); //captura o id do produto que vai ser excluido
    			scanf("%d", &id);
            	RemoverElemento(&lista, id);
            	break;
            
            case 12:
                ExcluirLista(&lista); //exclui todos os elementos e sai do script
                printf("\nSaindo...\n");
                break;
            
            default:
                printf("Opção inválida!\n");
                continue;
		}
	}while(escolha != 12);
	
	return 0;
}