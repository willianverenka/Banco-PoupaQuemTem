//
// Created by unifwsilva on 26/09/2023.
//
#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

int listaCliente(struct estadoPrograma state) {
    if (state.tamanho == 0) {
        return -1;
    } else {
        for (int i = 0; i < state.tamanho; ++i) {
            printf("\nCliente %d.\n", i);
            printf("Nome: %s\n", state.memoria[i].nome);
            printf("Tipo de conta: %d\n", state.memoria[i].tipo);
            if (i == state.tamanho - 1) {
                printf("CPF: %ld", state.memoria[i].cpf);
            } else {
                printf("CPF: %ld\n", state.memoria[i].cpf);
            }
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

