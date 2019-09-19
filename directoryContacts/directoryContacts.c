#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct contato{
    char nome[50];
    int fone;
    int idade;
    char sexo;
    char cidade[20];
    struct contato **proximo;
};

struct contato *inicio = NULL;

void cadastrarContato(struct contato **inicio){
    struct contato *novoContato;
    novoContato = (struct contato*) malloc (sizeof(struct contato));

    fflush(stdin);
    printf("\nNome: ");
    scanf("%[^\n]s", &novoContato->nome);

    fflush(stdin);
    printf("Fone: ");
    scanf("%d", &novoContato->fone);
    getchar();
    fflush(stdin);

    printf("Sexo (M ou F): ");
    novoContato->sexo = getchar();
    getchar();

    fflush(stdin);
    printf("Cidade: ");
    scanf("%[^\n]s", &novoContato->cidade);

    printf("Idade: ");
    fflush(stdin);
    scanf("%d", &novoContato->idade);

    if(*inicio){
        (*inicio)->proximo = novoContato;
    }else{
        *inicio = novoContato;
    }
}

void printLista(struct contato **inicio){
    struct contato *contatoAtual = *inicio;
    printf("\n[\n");
    while(contatoAtual != NULL){
        printf("{\"nome\": \"%s\", \"fone\": \"%d\", \"idade\": \"%d\", \"sexo\": \"%c\", \"cidade\": \"%s\"}\n", contatoAtual->nome, contatoAtual->fone, contatoAtual->idade, contatoAtual->sexo, contatoAtual->cidade);
        contatoAtual = contatoAtual->proximo;
    }
    printf("]");
}

void buscarContato(struct contato **inicio){
    struct contato *contatoAtual = *inicio;
    char nomeBusca[10];
    printf("\nNome: ");
    scanf("%[^\n]s", &nomeBusca);
    while(contatoAtual != NULL){
        if(strcmp(contatoAtual->nome, nomeBusca) == 0){
            printf("\n{\"nome\": \"%s\", \"fone\": \"%d\", \"idade\": \"%d\", \"sexo\": \"%c\", \"cidade\": \"%s\"}", contatoAtual->nome, contatoAtual->fone, contatoAtual->idade, contatoAtual->sexo, contatoAtual->cidade);
            break;
        }
        contatoAtual = contatoAtual->proximo;
    }
}

void excluirContato(struct contato **inicio){
    if((*inicio)->proximo == NULL){
        *inicio = NULL;
    }
    struct contato *contatoAtual = *inicio;
    struct contato *anterior;
    char nomeExcluir[10];
    printf("\nNome: ");
    scanf("%[^\n]s", &nomeExcluir);
    while(contatoAtual != NULL){
        if(strcmp(contatoAtual->nome, nomeExcluir) == 0){
            anterior->proximo = contatoAtual->proximo;
            free(contatoAtual);
            break;
        }
        anterior = contatoAtual;
        contatoAtual = contatoAtual->proximo;
    }
}

void limparLista(struct contato **inicio){
    struct contato *contatoAtual = *inicio;
    struct contato *contatoAnteior;
    while(contatoAtual != NULL){
        contatoAnteior = contatoAtual;
        free(contatoAnteior);
        contatoAtual = contatoAtual->proximo;
    }
}

void main(){
    int escolha = 1;
    printf("--- Agenda de contatos ---");
    while(escolha != 0){
        printf("\n1 - Cadastrar / 2 - Buscar contato / 3 - Excluir contato / 4 - Listar contato / 0 - Sair");
        printf("\nInforme a opcao: ");
        scanf("%d", &escolha);
        getchar();
        switch (escolha){
            case 1:
                printf("--- Cadastro de contato ---");
                cadastrarContato(&inicio);
                printf("\nCadastro realizado!");
                break;
            case 2:
                printf("--- Buscar contato ---");
                buscarContato(&inicio);
                break;
            case 3:
                printf("--- Excluir contato ---");
                excluirContato(&inicio);
                break;
            case 4:
                printf("--- Listar contatos ---");
                printLista(&inicio);
                break;
            case 0:
                printf("\nPrograma encerrado...");
                printf("\nLimpando lista...");
                limparLista(&inicio);
                printf("\nLista excluída!");
                break;
            default:
                printf("\nOpcao invalida!");
                break;
        }
    }
}

