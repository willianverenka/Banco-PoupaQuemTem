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

struct conta{
    char nome[100];
    long cpf;
    enum TipoConta tipo;
    float valor;
    char senha[300];
};

struct estadoPrograma{
    enum Loop estadoLoop;
    struct conta memoria[1000];
    int tamanho;
};

int criarCliente(struct estadoPrograma *state);
#endif //PROJETO_2_BIBLIOTECA_H
