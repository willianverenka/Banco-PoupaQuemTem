//
// Created by unifwsilva on 26/09/2023.
//
#include "biblioteca.h"
#include <stdio.h>
#include <string.h>


int listaCliente(struct estadoPrograma *state) {
    if (state->tamanho == 0) {
        return ERRO_LISTA_VAZIA;
    }
        for (int i = 0; i < state->tamanho; ++i) {
            printf("\nCliente %d.\n", i+1);
            printf("Nome: %s\n", state->memoria[i].nome);
            char *tipo;
            tipo = (state->memoria[i].tipo == 0) ? "Comum" : "Plus";
            printf("Tipo de conta: %s\n", tipo);
            printf("CPF: %ld\n", state->memoria[i].cpf);
        }
        return SUCESSO;
    }


int buscarCliente(struct estadoPrograma *state, long cpf){
    if(state->tamanho == 0){
        return ERRO_LISTA_VAZIA;
    }
    for(int i = 0; i < state->tamanho; i++){
        if(state->memoria[i].cpf == cpf){
            return i; // RETORNA POSICAO DO CLIENTE NA LISTA
        }
    }
    return ERRO_CPF; // CPF NAO ENCONTRADO
}

int criarCliente(struct estadoPrograma *state){
    if(state->tamanho >= 1000){
        return ERRO_LISTA_CHEIA;
    }
    char nome[100];
    long cpf;
    enum TipoConta tipo;
    float valorInicial;
    char senha[300];
    printf("Digite o nome do cliente:\n");
    scanf("%100s", nome);
    do{
        printf("Digite o cpf do cliente:\n");
        scanf("%ld", &cpf);
    }while(buscarCliente(state, cpf) != -1);
    do{
        printf("Digite o tipo de conta do cliente (0 para COMUM, 1 para PLUS)\n");
        scanf("%d", &tipo);
    }while(tipo != COMUM && tipo != PLUS);
    printf("Digite o valor inicial da conta:\n");
    scanf("%f", &valorInicial);
    printf("Digite a senha da conta:\n");
    scanf("%300s", senha);
    strcpy(state->memoria[state->tamanho].nome, nome);
    state->memoria[state->tamanho].cpf = cpf;
    state->memoria[state->tamanho].tipo = tipo;
    state->memoria[state->tamanho].valor = valorInicial;
    state->memoria[state->tamanho].qtdMovimentacao = 0;
    strcpy(state->memoria[state->tamanho].senha, senha);
    state->tamanho++;
    return SUCESSO;
}

void rearranjarArray(struct estadoPrograma *state, int index){ // utilitario pra ordenar a array 
    for(int i = index; i < state->tamanho-1; i++){
        state->memoria[i] = state->memoria[i+1];
    }
}

int deletarCliente(struct estadoPrograma *state, long cpf){
    int posicao = buscarCliente(state, cpf);
    if(posicao == -1){
        return ERRO_CPF;
    }
    if(posicao == state->tamanho-1){
        state->tamanho--;
    }
    else{
        rearranjarArray(state, posicao);
    }
    return SUCESSO;
}

int debito(struct estadoPrograma*state){
    long CPF;
    printf("Digite o cpf do cliente:\n");
    scanf("%ld", &CPF);
    int pos=buscarCliente(state,CPF);
    if (pos==-1){
        return ERRO_CPF;
    }
    else{
        float valordeb;
        char senha[300];
        printf("Digite a senha da conta:\n");
        scanf("%300s", senha);
        if(strcmp(senha,state->memoria[pos].senha)!=0){
            return ERRO_SENHA;
        }
        printf("Digite o valor a ser debitado:\n");
        scanf("%f", &valordeb);
        if(state->memoria[pos].tipo==1){
            float totdeb=state->memoria[pos].valor-1.03*valordeb;
            if(totdeb<=-5000){
                return OPERACAO_INVALIDA;
                }
            else{
                state->memoria[pos].valor=totdeb;
                printf("Depois do dehbito de R$%.2f, sua conta tem com R$%.2f\n",valordeb,totdeb);
                adicionarExtrato(state, pos, DEBITO, totdeb, 0.03*valordeb);
            }
        }
        else{
            float totdeb=state->memoria[pos].valor-1.05*valordeb;
            if(totdeb<=-1000){
                return OPERACAO_INVALIDA;
                }
            else{
                state->memoria[pos].valor=totdeb;
                printf("Depois do dehbito de R$%.2f, sua conta tem com R$%.2f\n",valordeb,totdeb);
                adicionarExtrato(state, pos, DEBITO, totdeb, 0.05*valordeb);
            }
        }
    }
    return SUCESSO;
}

int deposito(struct estadoPrograma*state){
    long CPF;
    printf("Digite o cpf do cliente:\n");
    scanf("%ld", &CPF);
    int pos=buscarCliente(state,CPF);
    if(pos==-1){
        return ERRO_CPF;
    }
    float valdep;
    printf("Digite o valor a ser depositado:\n");
    scanf("%f",&valdep);
    state->memoria[pos].valor=state->memoria[pos].valor+valdep;
    printf("O novo valor da sua conta eh R$%.2f",state->memoria[pos].valor);
    return SUCESSO;
}
int transferencia(struct estadoPrograma*state){
    long CPF;
    printf("Digite o cpf do cliente que irah transferir o dinheiro:\n");
    scanf("%ld", &CPF);
    int pos=buscarCliente(state,CPF);
    if (pos==-1){
        return ERRO_CPF;
    }
    else {
        char senha[300];
        printf("Digite a senha da conta:\n");
        scanf("%300s", senha);
        if (strcmp(senha, state->memoria[pos].senha) != 0) {
            return ERRO_SENHA;
        }
        else{
            long CPF2;
            printf("Digite o cpf do cliente que irah receber o dinheiro:\n");
            scanf("%ld", &CPF2);
            int pos2=buscarCliente(state,CPF2);
            if(pos2==-1 && pos2!=pos){
                return OPERACAO_INVALIDA;
            }
            else{
                float valtrans;
                printf("Digite o valor a ser tranferido: \n");
                scanf("%f",&valtrans);
                if(state->memoria[pos].tipo==1){
                    float totdeb=state->memoria[pos].valor-1.03*valtrans;
                    if(totdeb<=-5000){
                        return OPERACAO_INVALIDA;
                    }
                    else{
                        state->memoria[pos].valor=totdeb;
                        state->memoria[pos2].valor=valtrans;
                        printf("O valor da conta do receptor é R$%.2f",state->memoria[pos2].valor);
                        printf("Depois do dehbito de R$%.2f, sua conta tem com R$%.2f",valtrans,state->memoria[pos].valor=totdeb);
                    }
                }
                else{
                    float totdeb = state->memoria[pos].valor-1.05*valtrans;
                    if(totdeb<=-1000){
                        return OPERACAO_INVALIDA;
                    }
                    else{
                        state->memoria[pos].valor=totdeb;
                        state->memoria[pos2].valor=valtrans;
                        printf("O valor da conta do receptor eh R$%.2f\n",state->memoria[pos2].valor);
                        printf("Depois do dehbito de R$%.2f, sua conta tem com R$%.2f",valtrans,state->memoria[pos].valor=totdeb);
                    }
                }
            }
        }
    }
    return SUCESSO;
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
    printf("qtd de movimentacoes inicial: %d\n", qtdExtratoCliente);
    struct registroMovimentacao novoRegistro;
    novoRegistro.tipo = tipo;
    novoRegistro.valor = valor;
    novoRegistro.tarifa = tarifa;
    if(qtdExtratoCliente >= 99){
/*
         * se tiverem 99 operacoes na conta, a array passa todos elementos pra esquerda
         * ex: [a, b, c, d] -> [b, c, d, d]
         * no final, o primeiro termo (mais antigo) eh apagado, e o ultimo, apesar de ser repetido,
         * sera substituido pelo novo registro
         * dessa forma, os 100 ultimos registros serao mostrados
         * ps: a leitura do extrato e de tras pra frente, dos mais recentes pros mais velhos.
         */
        rearranjarArrayExtrato(&state->memoria[posicaoCliente]);
        state->memoria[posicaoCliente].extrato[qtdExtratoCliente] = novoRegistro;
    }
    state->memoria[posicaoCliente].extrato[qtdExtratoCliente] = novoRegistro;
    state->memoria[posicaoCliente].qtdMovimentacao++;
    return SUCESSO;
}

int lerExtrato(struct estadoPrograma *state, long cpf){
    int pos = buscarCliente(state, cpf);
    if(pos == -1)
        return ERRO_CPF; // cpf nao encontrado
    char senha[300];
    printf("Digite uma senha:\n");
    scanf("%299s", &senha);
    if(strcmp(state->memoria[pos].senha, senha) != 0){
        return ERRO_SENHA;
    }
    int qtdExtrato = state->memoria[pos].qtdMovimentacao;
    if(qtdExtrato == 0)
        return ERRO_LISTA_VAZIA;
    for(int i = qtdExtrato-1, j = 1; i >= 0; i--, j++){
        printf("\n%d.\n", j);
        switch(state->memoria[pos].extrato[i].tipo){
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
        printf("Valor: R$%.2f\n", state->memoria[pos].extrato[i].valor);
        printf("Tarifa: R$%.3f\n", state->memoria[pos].extrato[i].tarifa);
    }
    return SUCESSO;
}

void esperarSaida(){
    printf("Pressione qualquer tecla para sair...");
    getchar();
}