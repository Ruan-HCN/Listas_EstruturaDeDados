/****************************************************************** 
 * Nome: Lista com vetores                                        *
 * Descricao: Implementacao de lista com uso de vetores (array).  *
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
 * Ultima alteracao: 08/12/2024                                   *
 ******************************************************************/

//Include das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Definicao da estrutura
typedef struct Produto {
    int id;
    char cor_do_tenis[30];
    float tamanho;
    char material[30];
    int lote;
    float valor;
    char genero;
} Produto;

//Estrutura que representa a lista, com um vetor de produtos 
#define MAX_PRODUTOS 5 //Tamanho máximo da lista (vetor)
typedef struct {
    Produto produtos[MAX_PRODUTOS];  //Vetor de produtos
    int tamanho;                    //Quantidade de produtos na lista
} Lista;


/* Nome: CriarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo tamanho e alocacao do vetor de elementos
 */
Lista* CriarLista() {
	Lista *nova = (Lista*)malloc(sizeof(Lista));

    /*Verificando se o espaco foi resevado*/
    if(nova == NULL){
        printf("Nao tem espaco\n");
        return NULL;
    }
    
	nova->tamanho = 0;

    /*Retonando o espaco resevado*/
    return nova;
}


void LimparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Consome o buffer até encontrar o '\n' ou EOF
}


/* Nome: InserirElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             novo - elemento do tipo Produto que sera adicionado na lista
 * Descricao: Funcao criada para inserir um elemento no final da lista
 */
int InserirElemento(Lista *lista, Produto novo) {
	if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }
	
    if (lista->tamanho < MAX_PRODUTOS) { //Verifica se a lista esta cheia
        lista->produtos[lista->tamanho] = novo; //adiciona o produto no final da lista
        lista->tamanho++; //atualiza o tamnho da lista
    } 
	
	else {
        printf("\nLista cheia!\n"); //se a lista estiaer cheia
        return 0;
    }
    return 1;
}


/* Nome: InserirElementoID
 * Parametros: lista - ponteiro que possui o endereco lista
 *             novo - elemento do tipo Produto que sera adicionado na lista
 *             posicao - posicao que o elemento sera adicionado na lista
 * Descricao: Funcao criada para inserir um elemento na posicao indicada na lista
 */
int InserirElementoID(Lista *lista, Produto novo, int id) {
	int i;
	
	if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }
	
    if (id < 0 || id > lista->tamanho) { //verifica se o id do elemento esta entre os limites
        printf("\nPosição inválida!\n");
        return 0;
    }

    if (lista->tamanho < MAX_PRODUTOS) { //verifica se alista não esta cheia
    	// Move os elementos a partir da posição para frente, para abrir espaço
        for (i = lista->tamanho; i > id; i--) {
            lista->produtos[i] = lista->produtos[i - 1];
        }
        lista->produtos[id] = novo; //insere o produto na posição indicada
        lista->tamanho++; //atuliaza o tamanho da lista
    } 
	
	else {
        printf("\nLista cheia!\n"); //se a lista estiaer cheia
        return 0;
    }
    
	return 1;
}


/* Nome: InserirElementoInicio
 * Parametros: lista - ponteiro que possui o endereco lista
 *             novo - elemento do tipo Produto que sera adicionado na lista
 * Descricao: Funcao criada para inserir um elemento no inicio da lista
 */
int InserirElementoInicio(Lista *lista, Produto novo) {
	if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }
	
    InserirElementoID(lista, novo, 0); //Chama a função para inserir no início, usando posição 0
    return 1;
}


/* Nome: RemoverElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            posicao - elemento que sera removido da lista
 * Descricao: Funcao criada para remover um elemento da lista
 */
int RemoverElemento(Lista *lista, int id) {
    int i, posicao = -1;
    
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    // Busca o produto pelo ID
    for (i = 0; i < lista->tamanho; i++) {
        if (lista->produtos[i].id == id) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("\nProduto não encontrado!\n");
        return 0;
    }

    // Move os elementos após a posição para trás
    for (i = posicao; i < lista->tamanho - 1; i++) {
        lista->produtos[i] = lista->produtos[i + 1];
    }

    lista->tamanho--; // Atualiza o tamanho da lista
    printf("\nProduto removido com sucesso!\n");
    return 1;
}


/* Nome: BuscarElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            id - elemento que sera buscado na lista
 * Retorno: o indice do elemento encontrado, NULL caso contrario
 * Descricao: Funcao criada para buscar um elemento na lista
 */
Produto* BuscarElemento(Lista *lista, int id) {
	int i;
	
	if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }
	
	//percorre a lista e verifica se o id informado existe, caso nao, retorna NULL 
    for (i = 0; i < lista->tamanho; i++) {
        if (lista->produtos[i].id == id) {
            return &lista->produtos[i];
        }
    }
    return NULL;
}


/* Nome: AtualizarProduto
 * Parametros: lista - ponteiro que possui o endereco lista
 *             id - id do elemento que sera alterado 
 * Descricao: Funcao responsavel por atualizar um elemento
 *            da lista, caso o mesmo esteja na lista indicada
 */
int AtualizarProduto(Lista *lista, int id) {
    Produto *produto = BuscarElemento(lista, id); //chama a função buscarelemento apra encontrar o produto e atuaizalo
    
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }
    
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
        return 1;
    } 
	
	//caso não ache, produto nao encontrado
	else {
        printf("\nProduto não encontrado!\n");
        return 0;
    }
}


/* Nome: ListarElementos
 * Parametro: lista - ponteiro que possui o endereco lista
 * Descricao: Funcao criada para apresentar todos elementos presentes na lista
 */
int ListarElementos(Lista *lista) {
	int i;
	
	if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }
	
	//Se a lista estiver vazia
    if (lista->tamanho == 0) {
        printf("\nLista vazia!\n");
        return 0;
    }

	//caso não, usa o for para imprimir todos os elementos da listta
    for (i = 0; i < lista->tamanho; i++) {
        printf("ID: %d\nCor do Tenis: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n\n",
               lista->produtos[i].id, lista->produtos[i].cor_do_tenis, lista->produtos[i].tamanho, 
               lista->produtos[i].material, lista->produtos[i].lote, lista->produtos[i].valor, 
               lista->produtos[i].genero);
    }
    return 1;
}


/* Nome: ExcluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Descricao: Funcao responsavel pela exclusao da lista
 */
Lista* ExcluirLista(Lista *lista) {
	/*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }
	
    lista->tamanho = 0; //reinicia a lista com 0 elementos
    return NULL;
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
    
    while (fscanf(arquivo, "%d %s %f %s %d %f %c", &id, cor, &tamanho, material, &lote, &valor, &genero) != EOF) {
        Produto novo = {id, "", tamanho, "", lote, valor, genero};
        strcpy(novo.cor_do_tenis, cor);
        strcpy(novo.material, material);
        InserirElemento(lista, novo);
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
	int i;
	
    FILE *arquivo = fopen(nomeArquivo, "w"); //abre um aqruivo no mode escrita
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (i = 0; i < lista->tamanho; i++) {
        fprintf(arquivo, "%d %s %.2f %s %d %.2f %c\n", lista->produtos[i].id, lista->produtos[i].cor_do_tenis, 
                lista->produtos[i].tamanho, lista->produtos[i].material, lista->produtos[i].lote, 
                lista->produtos[i].valor, lista->produtos[i].genero);
    } //escreve os da dos do array num txt e os salva
    
    fclose(arquivo); //fecha o arquivo
    printf("Dados salvos com sucesso!\n");
}


/* Função: ContarElementos
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: número de produtos armazenados na lista
 * Descrição: Retorna a quantidade de produtos atualmente armazenados na lista.
 */
int ContarElementos(Lista *lista) {
    return lista->tamanho; //conta quantos elementos alista possui
}

/* Função principal */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
    Lista lista;
    CriarLista(&lista);
    
    int opcao;
    int id, lote, posicao;
    char cor[30], material[30], genero;
    float tamanho, valor;
    
    do {
        printf("\nMenu:\n\n");
	    printf("1. Inserir Produto\n");	    
	    printf("2. Inserir Produto no Inicio\n");	    
	    printf("3. Inserir Produto em uma Posicao\n");	    
	    printf("4. Contar Elementos\n");	    
	    printf("5. Atualizar Produto\n");	    
	    printf("6. Remover Produto\n");	    
	    printf("7. Listar Produtos\n");	    
	    printf("8. Buscar Produto por ID\n");	    
	    printf("9. Carregar Dados de um Arquivo\n");	    
	    printf("10. Salvar Dados em um Arquivo\n");
	    printf("11. Excluir Lista\n"); 
	    printf("12. Sair\n");
        
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: // Adicionar Produto
                printf("ID: ");
                scanf("%d", &id);
                printf("Cor do Tenis: ");
                scanf("%s", cor);
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
				printf("Genero: ");
                scanf(" %c", &genero);
                
                Produto novo = {id, "", tamanho, "", lote, valor, genero};
                strcpy(novo.cor_do_tenis, cor);
                strcpy(novo.material, material);
                InserirElemento(&lista, novo);
                break;
                
            case 2: //Inserir Produto no início da lista
                printf("ID: ");
                scanf("%d", &id);
                printf("Cor do Tenis: ");
                scanf("%s", cor);
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
                printf("Genero: ");
                scanf(" %c", &genero);
                
                novo = (Produto){id, "", tamanho, "", lote, valor, genero};
                strcpy(novo.cor_do_tenis, cor);
                strcpy(novo.material, material);
                InserirElementoInicio(&lista, novo);
                break;
                
            case 3: //Inserir Produto em uma Posição especifica
                printf("ID: ");
                scanf("%d", &id);
                printf("Cor do Tenis: ");
                scanf("%s", cor);
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
                printf("Genero: ");
                scanf(" %c", &genero);
                
                printf("Posição: ");
                scanf("%d", &posicao);
                
                novo = (Produto){id, "", tamanho, "", lote, valor, genero};
                strcpy(novo.cor_do_tenis, cor);
                strcpy(novo.material, material);
                InserirElementoID(&lista, novo, posicao);
                break;
                
            case 4: //Conta qunatos Elementos a lista possui
            	printf("Número de produtos armazenados: %d\n", ContarElementos(&lista));
           	    break;
                
            case 5: // Atualizar Produto
                printf("ID do Produto para atualizar: ");
                scanf("%d", &id);
                AtualizarProduto(&lista, id);
                break;
                
            case 6: // Remover Produto
                printf("ID do Produto para remover: ");
                scanf("%d", &id);
                RemoverElemento(&lista, id);
                break;
                
            case 7: // Listar Produtos
                ListarElementos(&lista);
                break;
                
            case 8: // Buscar Produto por ID
                printf("ID do Produto para buscar: ");
                scanf("%d", &id);
                Produto *p = BuscarElemento(&lista, id);
                if (p != NULL) {
                    printf("Produto encontrado:\nID: %d\nCor: %s\nTamanho: %.2f\nMaterial: %s\nLote: %d\nValor: %.2f\nGenero: %c\n",
                           p->id, p->cor_do_tenis, p->tamanho, p->material, p->lote, p->valor, p->genero);
                } else {
                    printf("Produto não encontrado!\n");
                }
                break;
                
            case 9: // Carregar Dados
                CarregarDados(&lista, "produtos.txt");
                break;
                
            case 10: // Salvar Dados
                SalvarDados(&lista, "produtos.txt");
                break;
            
            case 11: //Excluir a Lista
                ExcluirLista(&lista);
                printf("Lista excluída!\n");
                break;
        
	        case 12: //Função para Sair do programa
	            printf("Saindo..\n");
	            break;
	        
	        default:
	            printf("Digite uma opcao valida\n");
	            break;
        }
        
    } while (opcao != 12);  //Sair
    
    return 0;
}
