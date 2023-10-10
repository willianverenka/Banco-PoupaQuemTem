//
// Created by unifwsilva on 26/09/2023.
//

#ifndef PROJETO_2_BIBLIOTECA_H
#define PROJETO_2_BIBLIOTECA_H

enum TipoConta{
    COMUM,
    PLUS
};

enum Loop{
    FUNCIONANDO,
    FECHADO
};

enum TipoRegistro{
    DEBITO,
    DEPOSITO,
    TRANSFERENCIA,
};

struct registroMovimentacao{
    enum TipoRegistro tipo;
    float valor;
    float tarifa;
};

struct conta{
    char nome[100];
    long cpf;
    enum TipoConta tipo;
    float valor;
    char senha[300];
    struct registroMovimentacao extrato[100];
};

struct estadoPrograma{
    enum Loop estadoLoop;
    struct conta memoria[1000];
    int tamanho;
};

int listaCliente(struct estadoPrograma state);
int criarCliente(struct estadoPrograma *state);
int buscarCliente(struct estadoPrograma state, long cpf);
void rearranjarArray(struct estadoPrograma *state, int index);
int deletarCliente(struct estadoPrograma *state, long cpf);
int debito( float valordeb,struct estadoPrograma*state);
#endif //PROJETO_2_BIBLIOTECA_H
