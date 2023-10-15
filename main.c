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
        scanf("%c", &input);
        switch(input){
            case '0':
                printf("SAINDO.\n");
                state.estadoLoop = FECHADO;
                break;
                case '1':
                    criarCliente(&state);
                    break;
                case '2':
                    printf("Digite o CPF do cliente a ser apagado:\n");
                    long input2;
                    scanf("%ld", &input2);
                    do{
                        printf("CPF invalido.\n");
                        printf("Digite o CPF do cliente a ser apagado:\n");
                        scanf("%ld", &input2);
                    }while(deletarCliente(&state, input2) == -1);
                    break;
                case '3':
                    listaCliente(&state);
                    break;
                case '4':
                    // debito();
                    break;
                case '5':
                    deposito(&state);
                    break;
                case '6':
                    printf("Digite o CPF do cliente a ser consultado:\n");
                    long input3;
                    scanf("%ld", &input3);
                    do{
                        printf("CPF invalido.\n");
                        printf("Digite o CPF do cliente a ser apagado:\n");
                        scanf("%ld", &input2);
                    }while(lerExtrato(&state, input3) == -1);
                    break;
                case '7':
                    transferencia(&state);
                    break;
                default:
                    printf("Insira uma entrada valida (0-7)\n");
                    break;
            }

    }while(state.estadoLoop == FUNCIONANDO);
    return 0;
}
