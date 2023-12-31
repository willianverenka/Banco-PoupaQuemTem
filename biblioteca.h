//
// Created by unifwsilva on 26/09/2023.
//

#ifndef PROJETO_2_BIBLIOTECA_H
#define PROJETO_2_BIBLIOTECA_H

enum Respostas{
    SUCESSO = 0,
    ERRO_CPF = -1,
    ERRO_SENHA = -2,
    ERRO_LISTA_VAZIA = -3,
    ERRO_LISTA_CHEIA = -4,
    OPERACAO_INVALIDA = -5, //debito/transferencias impossiveis
    ERRO_ARQUIVO = -6
};

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
    int qtdMovimentacao;
};

struct estadoPrograma{
    enum Loop estadoLoop;
    struct conta memoria[1000];
    int tamanho;
};

void rearranjarArrayExtrato(struct conta *usuario);
int listaCliente(struct estadoPrograma *state);
int criarCliente(struct estadoPrograma *state);
int buscarCliente(struct estadoPrograma *state, long cpf);
void rearranjarArray(struct estadoPrograma *state, int index);
int deletarCliente(struct estadoPrograma *state, long cpf);
int debito(struct estadoPrograma*state);
int deposito(struct estadoPrograma*state);
int transferencia(struct estadoPrograma*state);
int lerExtrato(struct estadoPrograma *state, long cpf);
int adicionarExtrato(struct estadoPrograma *state, int posicaoCliente, enum TipoRegistro tipo, float valor, float tarifa);
int carregar(struct estadoPrograma *ponteiroEstado);
int salvar(struct estadoPrograma *state);
void esperarSaida();

#endif //PROJETO_2_BIBLIOTECA_H
