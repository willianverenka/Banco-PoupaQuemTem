//
// Created by unifwsilva on 26/09/2023.
//
#include "biblioteca.h"

int listaCliente(struct estadoPrograma state){
    if(state.tamanho==0){
        return;
    }
    else{
        for (int i = 0; i < state.tamanho; ++i) {
            printf("Cliente %d\n",i);
            printf("Nome: %s\n",state.memoria[i].nome);
            printf("Tipo de conta: %d\n",state.memoria[i].tipo);
            if(i==state.tamanho-1){
                printf("CPF: %ld",state.memoria[i].cpf);
            }
            else{printf("CPF: %ld\n",state.memoria[i].cpf);
            }
        }
    }
}
