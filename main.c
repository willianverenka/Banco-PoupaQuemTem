#include <stdio.h>
#include "biblioteca.h"
int main() {
    struct estadoPrograma state;
    state.tamanho = 0;
    state.estadoLoop = FUNCIONANDO;
    do{
        printf("1. Novo cliente\n");
        printf("2. Apaga cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Debito\n");
        printf("5. Deposito\n");
        printf("6. Extrato\n");
        printf("7. Transferencia entre contas\n");
        printf("0. Sair\n");
        char input;
        scanf(" %c", &input);
        printf("tamanho eh %d\n", state.tamanho);
        while ((getchar()) != '\n');
        switch(input){
            case '0':
                printf("SAINDO.\n");
                state.estadoLoop = FECHADO;
                break;
            case '1':
                if(criarCliente(&state) == ERRO_LISTA_CHEIA){
                    printf("ERRO: ja existem 1000 clientes registrados.\n");
                }
                while ((getchar()) != '\n');
                esperarSaida();
                break;
            case '2':
                printf("Digite o CPF do cliente a ser apagado:\n");
                long input2;
                scanf("%ld", &input2);
                while ((getchar()) != '\n');
                printf("input eh %ld\n", input2);
                while (deletarCliente(&state, input2) == -1){
                    printf("CPF invalido.\n");
                    printf("Digite o CPF do cliente a ser apagado:\n");
                    scanf("%ld", &input2);
                    while ((getchar()) != '\n');
                }
                printf("Cliente apagado com sucesso.\n");
                esperarSaida();
                break;
            case '3':
                if(listaCliente(&state) == ERRO_LISTA_VAZIA){
                    printf("Nenhum cliente registrado.\n");
                }
                esperarSaida();
                break;
            case '4':
                switch(debito(&state)){
                    case ERRO_SENHA:
                        printf("ERRO: Senha invalida.\n");
                        break;
                    case ERRO_CPF:
                        printf("ERRO: CPF invalido.\n");
                        break;
                    case OPERACAO_INVALIDA:
                        printf("ERRO: Operacao invalida.\n");
                        break;
                }
                while ((getchar()) != '\n');
                esperarSaida();
                break;
            case '5':
                if(deposito(&state) == ERRO_CPF){
                    printf("ERRO: CPF ou senha invalidos.\n");
                }
                while ((getchar()) != '\n');
                break;
            case '6':
                printf("Digite o CPF do cliente a ser consultado:\n");
                long input3;
                scanf("%ld", &input3);
                while ((getchar()) != '\n');
                switch(lerExtrato(&state, input3)){
                    case ERRO_SENHA:
                        printf("ERRO: Senha invalida.\n");
                        break;
                    case ERRO_CPF:
                        printf("ERRO: CPF invalido.\n");
                        break;
                    case OPERACAO_INVALIDA:
                        printf("ERRO: Operacao invalida.\n");
                        break;
                }
                    while ((getchar()) != '\n');
                    esperarSaida();
                    break;
                case '7':
                    switch(transferencia(&state)){
                        case ERRO_SENHA:
                            printf("ERRO: Senha invalida.\n");
                            break;
                        case ERRO_CPF:
                            printf("ERRO: CPF invalido.\n");
                            break;
                    }
                    while ((getchar()) != '\n');
                    esperarSaida();
                    break;
                default:
                    printf("Insira uma entrada valida (0-7)\n");
                    break;
            }
    }while(state.estadoLoop == FUNCIONANDO);
    return SUCESSO;
}
