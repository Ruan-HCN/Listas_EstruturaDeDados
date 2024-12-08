/****************************************************************** 
 * Nome: Lista Duplamente Ligada com Apontadores                                       *
 * Descricao: Esse codigo possui as principais operacoes da       *
 *            lista, como:                                        *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Ruan Henry                                              *
 * Ultima alteracao: 08/12/2024                                   *
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
    struct Produto *ant;
}Produto;


/* Estrutura que representa a lista, com um ponteiro para o primeiro e para o ultimo elemento */
typedef struct {
	Produto *inicio;          //Ponteiro para o primeiro produto da lista
	Produto *fim;             //Ponteiro para o ultimo elemento
	int tamanho;
}Lista;


//Função Limpar Buffer
void LimparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


/* Função: CriarLista
* Descrição: Aloca e inicializa uma nova lista.
* Retorno: Retorna o ponteiro para a lista recém-criada.*/
Lista* CriarLista(){
	Lista *lista = (Lista*) malloc(sizeof(Lista));
	
	if(lista == NULL){
        printf("Sem espaco\n");
        return NULL;
    }
	
	lista->inicio = lista->fim = NULL;
	lista->tamanho = 0;
	return lista;
}


/* Função: inserirProduto
* Parâmetros: lista - ponteiro para a lista onde o produto será inserido
*             id, cor_do_tenis, tamanho, material, lote, valor, genero - dados do produto a ser inserido
* Descrição: Insere um novo produto no final da lista.*/
int inserirProduto(Lista *lista, int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero){
	if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
	
	Produto *novo = (Produto*) malloc(sizeof(Produto));
	if (novo == NULL) {
        printf("Erro ao alocar memória para o novo produto\n");
        return 0;
    }
	
	novo->id = id;
	strcpy(novo->cor_do_tenis, cor_do_tenis);
	novo->tamanho = tamanho;
    strcpy(novo->material, material);
    novo->lote = lote;
    novo->valor = valor;
    novo->genero = genero;
    novo->prox = NULL;
    novo->ant = lista->fim;
    
    if(lista->fim == NULL){
		novo->ant = NULL;
		lista->inicio = novo;
		lista->fim = novo;
	}
	
	else{
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;
	}
	
	lista->tamanho++;
	
	return 1;
}


/* Função: inserirProdutoInicio
* Descrição: Insere um produto no início da lista.
* Parâmetros: lista, dados do produto
*/
int inserirProdutoInicio(Lista *lista, int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero){
	Produto *novo = (Produto*) malloc(sizeof(Produto));
	if (novo == NULL) {
        printf("Erro ao alocar memória para o novo produto\n");
        return 0;
    }
	
	novo->id = id;
	strcpy(novo->cor_do_tenis, cor_do_tenis);
	novo->tamanho = tamanho;
    strcpy(novo->material, material);
    novo->lote = lote;
    novo->valor = valor;
    novo->genero = genero;
    novo->prox = lista->inicio;
    novo->ant = NULL;
    
    if(lista->inicio){
		lista->inicio->ant = novo;
	}
	
	else{
		lista->fim = novo;
	}
	
	lista->inicio = novo;
	lista->tamanho++;
	return 1;
}


/* Função: inserirProdutoID 
*  Parâmetros: lista - ponteiro para a lista
*             dados do produto, pos - posição onde será inserido
* Descrição: Insere um produto em uma posição específica da lista.*/
int inserirProdutoID(Lista *lista, int id, char *cor_do_tenis, float tamanho, char *material, int lote, float valor, char genero, int pos) {
	int i;
	
    if (pos <= 0) {
        inserirProdutoInicio(lista, id, cor_do_tenis, tamanho, material, lote, valor, genero);
    } 
	
	else if (pos >= lista->tamanho) {
        inserirProduto(lista, id, cor_do_tenis, tamanho, material, lote, valor, genero);
    } 
	
	else {
        Produto *novo = (Produto*) malloc(sizeof(Produto));
        if (novo == NULL) {
            printf("Erro ao alocar memória para o novo produto\n");
            return 0;  
        }
        
        novo->id = id;
        strcpy(novo->cor_do_tenis, cor_do_tenis);
        novo->tamanho = tamanho;
        strcpy(novo->material, material);
        novo->lote = lote;
        novo->valor = valor;
        novo->genero = genero;

        Produto *temp = lista->inicio;
        
        for (i = 0; i < pos; i++){
			temp = temp->prox;
		}

        novo->prox = temp;
        novo->ant = temp->ant;
        if (temp->ant) {
		temp->ant->prox = novo;
		}
        temp->ant = novo;

        lista->tamanho++;
        return 1;
    }
    return 0;
}


/* Função: AtualizarProduto
* Descrição: Atualiza os dados de um produto em uma posição específica da lista.
* Parâmetros: lista, pos - posição do produto a ser atualizado, novos dados*/
int AtualizarProduto(Lista *lista, int pos, int novoId, char *novaCor, float novoTamanho, char *novoMaterial, int novoLote, float novoValor, char novoGenero) {
	int i;
	
    if (pos < 0 || pos >= lista->tamanho) {
    	printf("\nPosição Invalida!\n");
    	return 0;
	}

    Produto *temp = lista->inicio;
    for (i = 0; i < pos; i++){
		temp = temp->prox;
	}

    temp->id = novoId;
    strcpy(temp->cor_do_tenis, novaCor);
    temp->tamanho = novoTamanho;
    strcpy(temp->material, novoMaterial);
    temp->lote = novoLote;
    temp->valor = novoValor;
    temp->genero = novoGenero;
    
    return 1;
}


/* Função: RemoverProduto
* Descrição: Remove um produto em uma posição específica da lista.
* Parâmetros: lista, pos - posição do produto a ser removido*/
int RemoverProduto(Lista *lista, int pos) {
	int i;
	
    if (pos < 0 || pos >= lista->tamanho){ 
		return 0;
	}

    Produto *temp = lista->inicio;
    
	for (i = 0; i < pos; i++) { 
		temp = temp->prox; 
	}

    if (temp->ant){
		temp->ant->prox = temp->prox;
	}else {
		lista->inicio = temp->prox;
	}

    if (temp->prox) {
		temp->prox->ant = temp->ant;
	}else {
		lista->fim = temp->ant;
	}

    free(temp);
    lista->tamanho--;
    return 1;
}


/* Função: listarProdutos
* Descrição: Lista todos os produtos da lista na ordem original.
* Parâmetros: lista - ponteiro para a lista a ser exibida*/
void listarProdutos(Lista *lista) {
    Produto *temp = lista->inicio;
    while (temp) {
        printf("ID: %d\nCor: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nGenero: %c\n\n",
               temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->genero);
        temp = temp->prox;
    }
}


/* Função: listarProdutosOrdemInversa
* Descrição: Lista todos os produtos da lista na ordem inversa.
* Parâmetros: lista - ponteiro para a lista a ser exibida*/
void listarProdutosOrdemInversa(Lista *lista) {
    Produto *temp = lista->fim;
    while (temp) {
        printf("ID: %d\nCor: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",  // Corrigido para %.2f
               temp->id, temp->cor_do_tenis, temp->tamanho, temp->material, temp->lote, temp->valor, temp->genero);
        temp = temp->ant;
    }
}


/* Função: BuscarProduto
* Descrição: Busca um produto pelo ID.
* Parâmetros: lista, id - ID do produto a ser buscado
* Retorno: Retorna o ponteiro para o produto encontrado, ou NULL se não encontrado.*/
Produto* BuscarProduto(Lista *lista, int id) {
    Produto *temp = lista->inicio;
    while (temp) {
        if (temp->id == id) {
			return temp;
		}
        temp = temp->prox;
    }
    return NULL;
}


/* Função: ExcluirLista
* Descrição: Remove todos os produtos da lista, liberando a memória.
* Parâmetros: lista - ponteiro para a lista a ser excluída*/
int ExcluirLista(Lista *lista) {
	if(lista == NULL){
		printf("\nA lista não foi criada!\n");
		return 0;
	}
	
	if(lista->inicio == NULL){
		printf("\nLista Vazia!\n");
		return 0;
	}
	
    Produto *temp = lista->inicio;
    while (temp) {
        Produto *prox = temp->prox;
        free(temp);
        temp = prox;
    }
    lista->inicio = lista->fim = NULL;
    lista->tamanho = 0;
    return 1;
}


/* Função: Tamanho
* Descrição: Retorna o número de produtos na lista.
* Parâmetros: lista - ponteiro para a lista
* Retorno: Retorna o tamanho da lista.*/
int Tamanho(Lista *lista) {
    return lista->tamanho;
}


/* Função: CarregarDados
 * Parametros: lista - ponteiro que possui o endereco lista
 *             nomeArquivo - string com o nome do arquivo de onde os dados serão carregados
 * Descrição: Lê os dados de um arquivo e insere os produtos na lista. 
 *            Cada linha do arquivo deve conter os atributos do produto.
 */
void CarregarDados(Lista *lista, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); //Abre o arquivo no modo leitura
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n"); //Se o arquivo não puder ser aberto, exibe erro
        return;
    }

    ExcluirLista(lista); //Exclui a lista para evitar duplicações
    
    int id, lote;
    char cor[30], material[30], genero;
    float tamanho, valor;
    
    // Corrigi o formato de leitura para garantir que o genero seja lido corretamente como 'char'
    while (fscanf(arquivo, "%d %s %f %s %d %f %c", &id, cor, &tamanho, material, &lote, &valor, &genero) == 7) {
    	cor[strcspn(cor, "\n")] = 0;
        material[strcspn(material, "\n")] = 0;
    	
        Produto novo = {id, "", tamanho, "", lote, valor, genero};
        strcpy(novo.cor_do_tenis, cor);
        strcpy(novo.material, material);
        inserirProduto(lista, id, cor, tamanho, material, lote, valor, genero);
    } //Insere os produtos lidos no arquivo na lista
    
    fclose(arquivo); //fecha o arquivo
    printf("Dados carregados com sucesso!\n");
}


/* Função: SalvarDados
 * Parametros: lista - ponteiro que possui o endereco lista
 *             nomeArquivo - string com o nome do arquivo onde os dados serão salvos
 * Descrição: Salva os dados da lista em um arquivo de texto.
 *            Cada produto é salvo em uma linha do arquivo com seus atributos.
 */
void SalvarDados(Lista *lista, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    Produto *temp = lista->inicio;
    while (temp != NULL) {
        fprintf(arquivo, "%d %s %.2f %s %d %.2f %c\n",  // Corrigido para %.2f no valor
                temp->id, temp->cor_do_tenis, temp->tamanho, 
                temp->material, temp->lote, temp->valor, temp->genero);
        temp = temp->prox;
    }
    
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

int main(){
	Lista *lista = NULL;
	lista = CriarLista();
	
    int escolha, id, pos, lote;
    char cor[30], material[30], genero;
    float tamanho, valor;
    
    setlocale(LC_ALL, "Portuguese");
	
	//Opcoes do menu, que dependo da escolha chama a respectiva função 
	do{
		printf("\n========================= Menu =========================");
        printf("\n\n1. Inserir Elemento no Final\n");
        printf("2. Inserir Elemento no Início\n");
        printf("3. Inserir Elemento em uma Posição Específica\n");
        printf("4. Listar Todos os Elementos\n");
        printf("5. Listar Elementos Ordem Inversa\n");
        printf("6. Atualizar Produto\n");
        printf("7. Buscar Produto por ID\n"); 
        printf("8. Tamanho da Lista\n");
        printf("9. Excluir Todos os Elementos\n");
        printf("10. Excluir Elemento Especififco\n");
        printf("11. Carregar Dados de Arquivo\n");
        printf("12. Salvar Dados em Arquivo\n");
        printf("13. Sair\n");
        
		printf("\nEscolha uma opção: ");
        scanf("%d", &escolha);
        
        switch(escolha){
        	
			 case 1:
                printf("\nID: ");
                scanf("%d", &id);
                LimparBuffer();
                
                printf("Cor do tênis: ");
                fgets(cor, sizeof(cor), stdin);
                
                printf("Tamanho: ");
                scanf("%f", &tamanho);
                LimparBuffer();
                
                printf("Material: ");
                fgets(material, sizeof(material), stdin);
                
                printf("Lote: ");
                scanf("%d", &lote);
                
                printf("Valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                
                printf("Gênero (M/F/U): ");
                scanf(" %c", &genero);
                
                inserirProduto(lista, id, cor, tamanho, material, lote, valor, genero);
                break;
            
            case 2:
                printf("\nID: ");
                scanf("%d", &id);
                LimparBuffer();
                
                printf("Cor do tênis: ");
                fgets(cor, sizeof(cor), stdin);
                
                printf("Tamanho: ");
                scanf("%f", &tamanho);
                LimparBuffer();
                
                printf("Material: ");
                fgets(material, sizeof(material), stdin);
                
                printf("Lote: ");
                scanf("%d", &lote);
                
                printf("Valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                
                printf("Gênero (M/F/U): ");
                scanf(" %c", &genero);
                
                inserirProdutoInicio(lista, id, cor, tamanho, material, lote, valor, genero);
                break;
            
            case 3:
                printf("Inserindo produto em uma posição específica da lista:\n");
                printf("Posição (0 a %d): ", lista->tamanho);
                scanf("%d", &pos);
                
                printf("\nID: ");
                scanf("%d", &id);
                LimparBuffer();
                
				printf("Cor do tênis: ");
                fgets(cor, sizeof(cor), stdin);
                cor[strcspn(cor, "\n")] = 0;
                
				printf("Tamanho: ");
                scanf("%f", &tamanho);
                LimparBuffer();
                
				printf("Material: ");
                fgets(material, sizeof(material), stdin);
                material[strcspn(material, "\n")] = 0;
                
				printf("Lote: ");
                scanf("%d", &lote);
                
				printf("Valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                
				printf("Gênero (M/F/U): ");
                scanf(" %c", &genero);
                
				inserirProdutoID(lista, id, cor, tamanho, material, lote, valor, genero, pos);
                
				printf("Produto inserido com sucesso na posição %d.\n", pos);
                break;
            
            case 4:
                listarProdutos(lista);
                break;
            
            case 5:
                listarProdutosOrdemInversa(lista);
                break;
            
            case 6:
				printf("Atualizando um produto na lista:\n");
				printf("Posição a atualizar (0 a %d): ", lista->tamanho - 1);
                scanf("%d", &pos);
                
                if (pos < 0 || pos >= lista->tamanho) {
                    printf("Posição inválida.\n");
                    break;
                }
                
                printf("\nNovo ID: ");
                scanf("%d", &id);
                LimparBuffer();
                
                printf("Nova cor do tênis: ");
                fgets(cor, sizeof(cor), stdin);
                cor[strcspn(cor, "\n")] = 0;
                
                printf("Novo tamanho: ");
                scanf("%f", &tamanho);
                LimparBuffer();
                
                printf("Novo material: ");
                fgets(material, sizeof(material), stdin);
                material[strcspn(material, "\n")] = 0;
                
                printf("Novo lote: ");
                scanf("%d", &lote);
                
                printf("Novo valor: ");
                scanf("%f", &valor);
                LimparBuffer();
                
                printf("Novo gênero (M/F/U): ");
                scanf(" %c", &genero);
                
                AtualizarProduto(lista, pos, id, cor, tamanho, material, lote, valor, genero);
                break;
            
            case 7:
                printf("ID do produto a buscar: ");
                scanf("%d", &id);
                
                Produto *produtoEncontrado = BuscarProduto(lista, id);
                
                if (produtoEncontrado) {
                    printf("\nProduto encontrado:\n");
                    printf("\nID: %d\nCor: %s\nTamanho: %.1f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",
                           produtoEncontrado->id, produtoEncontrado->cor_do_tenis, produtoEncontrado->tamanho,
                           produtoEncontrado->material, produtoEncontrado->lote, produtoEncontrado->valor, produtoEncontrado->genero);
                } 
				
				else {
                    printf("Produto não encontrado.\n");
                }
                break;
            
            case 8:
                printf("Tamanho da lista: %d\n", Tamanho(lista));
                break;
            
            case 9:
                ExcluirLista(lista);
                printf("\nLista Excluida");
                break;
            
            case 10:
                printf("Posicao do Produto: ");
                scanf("%d", &pos);
                RemoverProduto(lista, pos);
                printf("Produto Removido\n");
                break;
            
            case 11:
                CarregarDados(lista, "produtos.txt");
                break;
            
            case 12:
                SalvarDados(lista, "produtos.txt");
                break;
            
            case 13:
                printf("Saindo...\n");
                break;
            
            default:
                printf("Opção inválida!\n");
                continue;
		}
	}while(escolha != 13);
	
	return 0;
}