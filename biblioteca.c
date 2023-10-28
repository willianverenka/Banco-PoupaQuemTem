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
    printf("Digite o cpf do cliente:\n");
    scanf("%ld", &cpf);
    while ((getchar()) != '\n');
    while(buscarCliente(state, cpf) != ERRO_CPF && buscarCliente(state, cpf) != ERRO_LISTA_VAZIA){
        printf("O cpf ja existe.\n");
        printf("Digite o cpf do cliente:\n");
        scanf("%ld", &cpf);
        while ((getchar()) != '\n');
    }
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
    if(posicao == state->tamanho-1){ //se o item deletado for o ultimo da lista, entao nao é necessario reordenar
        state->tamanho--;
    }
    else{
        rearranjarArray(state, posicao);
        --state->tamanho;
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
            state->memoria[pos].valor=totdeb;
            printf("Depois do debito de R$%.2f, sua conta tem R$%.2f\n",valordeb,totdeb);
            adicionarExtrato(state, pos, DEBITO, (valordeb * 1.03) * -1, valordeb*0.03);
        }
        else{
            float totdeb=state->memoria[pos].valor-1.05*valordeb;
            if(totdeb<=-1000){
                return OPERACAO_INVALIDA;
                }
            state->memoria[pos].valor=totdeb;
            printf("Depois do debito de R$%.2f, sua conta tem R$%.2f\n",valordeb,totdeb);
            adicionarExtrato(state, pos, DEBITO, (valordeb * 1.05) * -1, valordeb*0.05);
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
    printf("O novo valor da sua conta eh R$%.2f\n",state->memoria[pos].valor);
    adicionarExtrato(state, pos, DEPOSITO, valdep, 0);
    return SUCESSO;
}
int transferencia(struct estadoPrograma*state){
    long CPF;
    printf("Digite o cpf da conta origem:\n");
    scanf("%ld", &CPF);
    int pos=buscarCliente(state,CPF);
    if (pos==-1){
        return ERRO_CPF;
    }
    char senha[300];
    printf("Digite a senha da conta:\n");
    scanf("%300s", senha);
    if (strcmp(senha, state->memoria[pos].senha) != 0) {
        return ERRO_SENHA;
    }
    long CPF2;
    printf("Digite o cpf do destinatario:\n");
    scanf("%ld", &CPF2);
    int pos2=buscarCliente(state,CPF2);
    if(pos2==-1 || pos2 == pos)
        return ERRO_CPF;
    float valtrans;
    printf("Digite o valor a ser transferido: \n");
    scanf("%f",&valtrans);
    if(state->memoria[pos].tipo==1){
        float totdeb=state->memoria[pos].valor-1.03*valtrans;
        if(totdeb<=-5000){
            return OPERACAO_INVALIDA;
        }
        state->memoria[pos].valor=totdeb;
        state->memoria[pos2].valor=valtrans;
        printf("Depois do debito de R$%.2f, sua conta tem R$%.2f\n",valtrans,state->memoria[pos].valor=totdeb);
        adicionarExtrato(state, pos, TRANSFERENCIA, (valtrans*1.03) * -1, valtrans*0.03);
        adicionarExtrato(state, pos2, TRANSFERENCIA, valtrans, 0);
    }
    else{
        float totdeb = state->memoria[pos].valor-1.05*valtrans;
        if(totdeb<=-1000){
            return OPERACAO_INVALIDA;
        }
        state->memoria[pos].valor=totdeb;
        state->memoria[pos2].valor=valtrans;
        printf("Depois do debito de R$%.2f, sua conta tem com R$%.2f\n",valtrans,state->memoria[pos].valor=totdeb);
        adicionarExtrato(state, pos, TRANSFERENCIA, (valtrans*1.05) * -1, valtrans*0.05);
        adicionarExtrato(state, pos2, TRANSFERENCIA, valtrans, 0);
        }
    return SUCESSO;
}

void rearranjarArrayExtrato(struct conta *usuario){ //utilitario pra reordenar array [i] = [i-1]
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
    FILE *f;
    char nomeArquivo[104];
    strcpy(nomeArquivo, state->memoria[pos].nome);
    strcat(nomeArquivo, ".txt");
    f = fopen(nomeArquivo, "w");
    /* le o extrato do final pro inicio, ou seja, o mais recente primeiro*/
    for(int i = qtdExtrato-1, j = 1; i >= 0; i--, j++){
        printf("\n%d.\n", j);
        switch(state->memoria[pos].extrato[i].tipo){
            case DEBITO:
                printf("Tipo: Debito\n");
                fwrite("Movimentação: Débito\n", sizeof(char), strlen("Movimentação: Débito\n"), f);
                break;
            case TRANSFERENCIA:
                printf("Tipo: Transferencia\n");
                fwrite("Movimentação: Transferência\n", sizeof(char), strlen("Movimentação: Transferência\n"), f);
                break;
            default:
                printf("Tipo: Deposito\n");
                fwrite("Movimentação: Deposito\n", sizeof(char), strlen("Movimentação: Deposito\n"), f);
                break;
        }
        char valor[300];
        sprintf(valor, "Valor: %.2f\n", state->memoria[pos].extrato[i].valor);
        fwrite(valor, sizeof(char), strlen(valor), f);
        char tarifa[300];
        sprintf(tarifa, "Tarifa: %.2f\n", state->memoria[pos].extrato[i].tarifa);
        fwrite(tarifa, sizeof(char), strlen(tarifa), f);
        printf("Valor: R$%.2f\n", state->memoria[pos].extrato[i].valor);
        printf("Tarifa: R$%.2f\n", state->memoria[pos].extrato[i].tarifa);
        fwrite("\n", sizeof(char), 1, f);
    }
    fclose(f);
    printf("Um arquivo %s foi criado contendo o extrato do usuario.\nSera possivel consulta-lo uma vez que o programa seja interrompido pelo menu (0. Sair)\n", nomeArquivo);
    return SUCESSO;
}

int salvar(struct estadoPrograma *state){
    FILE *f = fopen("dados.bin", "wb");
    if(f == NULL){
        printf("ERRO:\n");
        printf("Não foi possível abrir o arquivo dados.bin.\n");
        return ERRO_ARQUIVO;
    }
    // salva o tamanho no binario
    fwrite(&state->tamanho, sizeof(int), 1, f);
    // salva a array de structs
    for(int i = 0; i < state->tamanho; i++){
        fwrite(&state->memoria[i], sizeof(struct conta), 1, f);
    }
    fclose(f);
    printf("Arquivo atualizado com sucesso!\n");
    return SUCESSO;
}

int carregar(struct estadoPrograma *ponteiroEstado){
    FILE *f = fopen("dados.bin", "rb");
    if(f == NULL){
        printf("ERRO:\n");
        printf("Nao foi posivel abrir o arquivo dados.bin");
        return ERRO_ARQUIVO;
    }
    // carrega o tamanho
    fread(&(ponteiroEstado->tamanho), sizeof(int), 1, f);
    // carrega a array de contas
    for(int i = 0; i < ponteiroEstado->tamanho; i++){
        fread(&(ponteiroEstado->memoria[i]), sizeof(struct conta), 1, f);
    }
    printf("Contas carregadas com sucesso!\n");
    fclose(f);
    return SUCESSO;
}

void esperarSaida(){ // pausa o fluxo para melhorar a legibilidade dos menus
    printf("Pressione qualquer tecla para sair...");
    getchar();
}