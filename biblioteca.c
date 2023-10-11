//
// Created by unifwsilva on 26/09/2023.
//
#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

int listaCliente(struct estadoPrograma state) {
    if (state.tamanho == 0) {
        return -1;
    }
        for (int i = 0; i < state.tamanho; ++i) {
            printf("\nCliente %d.\n", i);
            printf("Nome: %s\n", state.memoria[i].nome);
            printf("Tipo de conta: %d\n", state.memoria[i].tipo);
            if (i == state.tamanho - 1) {
                printf("CPF: %ld", state.memoria[i].cpf);
            }
            else {
                printf("CPF: %ld\n", state.memoria[i].cpf);
            }
        }
    }

int criarCliente(struct estadoPrograma *state){
    char nome[100];
    long cpf;
    enum TipoConta tipo;
    float valorInicial;
    char senha[300];
    printf("Digite o nome do cliente:\n");
    scanf("%100s", &nome);
    do{
        printf("Digite o cpf do cliente:\n");
        scanf("%ld", &cpf);
    }while(buscarCliente(*state, cpf) != -1);
    do{
        printf("Digite o tipo de conta do cliente (0 para COMUM, 1 para PLUS)\n");
        scanf("%d", &tipo);
    }while(tipo != COMUM && tipo != PLUS);
    printf("Digite o valor inicial da conta:\n");
    scanf("%f", &valorInicial);
    printf("Digite a senha da conta:\n");
    scanf("%300s", &senha);
    strcpy(state->memoria[state->tamanho].nome, nome);
    state->memoria[state->tamanho].cpf = cpf;
    state->memoria[state->tamanho].tipo = tipo;
    state->memoria[state->tamanho].valor = valorInicial;
    state->memoria[state->tamanho].qtdMovimentacao = 0;
    strcpy(state->memoria[state->tamanho].senha, senha);
    state->tamanho++;
    return 0;
}

int buscarCliente(struct estadoPrograma state, long cpf){
    if(state.tamanho == 0){
        return -1;
    }
    for(int i = 0; i < state.tamanho; i++){
        if(state.memoria[i].cpf == cpf){
            return i; // RETORNA POSICAO DO CLIENTE NA LISTA
        }
    }
    return -1; // CPF NAO ENCONTRADO
}

void rearranjarArray(struct estadoPrograma *state, int index){ // utilitario pra ordenar a array 
    for(int i = index; i < state->tamanho-1; i++){
        state->memoria[i] = state->memoria[i+1];
    }
}

int deletarCliente(struct estadoPrograma *state, long cpf){
    int posicao = buscarCliente(*state, cpf);
    if(posicao == -1){
        return -1;
    }
    if(posicao == state->tamanho-1){
        state->tamanho--;
    }
    else{
        rearranjarArray(&state, posicao);
    }
    return 0;
}

int debito( float valordeb,struct estadoPrograma*state){
    long CPF;
    printf("Digite o cpf do cliente:\n");
    scanf("%ld", &CPF);
    int pos=buscarCliente(*state,CPF);
    if (pos==-1){
        return -1;
    }
    else{
        char senha[300];
        printf("Digite a senha da conta:\n");
        scanf("%300s", &senha);
        printf("A senha eh %s\n",state->memoria[pos].senha);
        if(strcmp(senha,state->memoria[pos].senha)!=0){
            return -1;
        }
        if(state->memoria[pos].tipo==1){
            printf("oi");
            float totdeb=state->memoria[pos].valor-1.03*valordeb;
            if(totdeb<=-5000){
                return -1;
                }
            printf("Depois do dehbito de R$%.2f, sua conta tem com R$%.2f",valordeb,totdeb);
            }
        else{
            float totdeb=state->memoria[pos].valor-1.05*valordeb;
            if(totdeb<=-1000){
                return -1;
                }
            printf("Depois do dehbito de R$%.2f, sua conta tem com R$%.2f",valordeb,totdeb);
        }
    }
    return 0;
}

void rearranjarArrayExtrato(struct conta *usuario){
    if(usuario->qtdMovimentacao == 0)
        return;
    for(int i = usuario->qtdMovimentacao-1; i > 0; i--){
        usuario->extrato[i] = usuario->extrato[i-1];
    }
}

int adicionarExtrato(struct estadoPrograma *state, int posicaoCliente, enum TipoRegistro tipo, float valor, float tarifa){
    int qtdExtratoCliente = state->memoria[posicaoCliente].qtdMovimentacao;
    struct registroMovimentacao novoRegistro;
    novoRegistro.tipo = tipo;
    novoRegistro.valor = valor;
    novoRegistro.tarifa = tarifa;
    if(qtdExtratoCliente >= 99){
        /*/
         * se tiverem 99 operacoes na conta, a array passa todos elementos pra esquerda
         * ex: [a, b, c, d] -> [b, c, d, d]
         * no final, o primeiro termo (mais antigo) eh apagado, e o ultimo, apesar de ser repetido,
         * sera substituido pelo novo registro
         * dessa forma, os 100 ultimos registros serao mostrados
         * ps: a leitura do extrato e de tras pra frente, dos mais recentes pros mais velhos.
         * /*/
        rearranjarArrayExtrato(state->memoria[posicaoCliente]);
        state->memoria[posicaoCliente].extrato[qtdExtratoCliente] = novoRegistro;
    }
    state->memoria[posicaoCliente].extrato[qtdExtratoCliente] = novoRegistro;
    state->memoria[posicaoCliente].qtdMovimentacao++;
    return 0;
}

int lerExtrato(struct estadoPrograma state, long cpf){
    int pos = buscarCliente(state, cpf);
    if(pos == -1)
        return -1; // cpf nao encontrado
    char senha[300];
    printf("Digite uma senha:\n");
    scanf("%299s", &senha);
    if(strcmp(state.memoria[pos].senha, senha) != 0){
        return -1;
    }
    int qtdExtrato = state.memoria[pos].qtdMovimentacao;
    for(int i = qtdExtrato, j = 1; i >= 0; i--, j++){
        printf("\n%d.\n", j);
        switch(state.memoria[pos].extrato[i].tipo){
            case DEBITO:
                printf("Tipo: Debito\n");
                break;
            case TRANSFERENCIA:
                printf("Tipo: Transferencia\n");
                break;
            default:
                printf("Tipo: Deposito\n");
                break;
        }
        printf("Valor: %f\n", state.memoria[pos].extrato[i].valor);
        printf("Tarifa: %f\n", state.memoria[pos].extrato[i].tarifa);
    }
    return 0;
}