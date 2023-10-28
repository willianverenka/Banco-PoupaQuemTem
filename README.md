# Banco Poupa Quem Tem
  O projeto "Banco Poupa Quem Tem" faz parte da grade de Desenvolvimento de Algoritmos e consiste na criação de um banco na linguagem C, que é operado pelo console e funciona de forma local, com algumas limitações e requisitos.
## Requisitos
* O menu principal do programa deve funcionar como um loop infinito, sempre disponibilizando as funções que o usuário pode acessar;
* Os dados do programa devem ser salvos e carregados entre sessões por meio de arquivos binários, a fim de permitir um uso contínuo;
## Funções
### 1. Novo cliente
Adiciona um novo cliente, que tem como propriedades:
* Nome;
* CPF;
* Tipo de conta: Comum e PLUS;
* Valor inicial da conta;
* Senha;
### 2. Apaga cliente
Apaga um cliente já existente a partir do CPF.
### 3. Listar clientes
Lista todos os clientes registrados, sem revelar dados sensíveis:
#### 🚫 Não mostra:
* Senha;
* Saldo da conta;
#### ✅ Mostra:
* Nome;
* CPF;
* Tipo de conta;
### 4. Débito
Saca o dinheiro da conta a partir de:
* CPF;
* Senha;
* Valor;
  
Para contas _comum_, a tarifa é de 5%.
Para contas _plus_, a tarifa é de 3%. 
### 5. Depósito
Deposita na conta, sem taxas, a partir de:
* CPF;
* Valor;
### 6. Extrato
Mostra o extrato de uma conta a partir de:
* CPF;
* Senha;
  
Um item de extrato tem a seguinte estrutura:
* Tipo de movimentação;
* Valor;
* Tarifa;

Além de ser mostrado no próprio console, tambem é gerado um arquivo .txt com o nome do usuário, com todas as suas movimentações registradas.
### 7. Transferência
Transfere um valor de uma conta para a outra, necessita de:
* CPF (origem);
* Senha (origem);
* CPF (destino);
* Valor
## Limitações
* O programa tem um limite de no máximo 1000 clientes registrados;
* O extrato de um cliente deve mostrar apenas as 100 movimentações mais recentes;
* É estritamente proibido utilizar bibliotecas externas;
   
