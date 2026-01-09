# Trabalho-final-em-C.c
Trabalho com base arquivo anexado do professor Wender


TRABALHO PRÁTICO – LOJA DE PRODUTOS FARMACOLÓGICOS
Autor: Estudante Técnico em Informática (Lógica II – C)

Sobre o projeto
Este projeto é uma tentativa de implementar um sistema simples de gerenciamento de uma loja de produtos farmacológicos, usando linguagem C e arquivos binários (.dat) para simular um “banco de dados”.
Ele foi desenvolvido por um aluno iniciante, então o código pode não estar organizado da melhor forma possível e algumas partes podem não estar totalmente completas.

Objetivo do sistema
O sistema tenta atender ao enunciado do trabalho, permitindo:

Cadastrar, alterar, consultar e listar:

Clientes

Vendedores

Fornecedores

Cadastrar produtos (estoque inicial começa em 0).

Efetuar vendas:

Autenticar vendedor (CPF + senha).

Validar cliente pelo ID.

Usar um “carrinho” de vendas (vetor dinâmico) com produtos, quantidades e valor de venda.

Atualizar o estoque dos produtos.

Gerar uma Nota Fiscal e os itens ligados a essa nota.

Algumas funcionalidades podem estar ausentes, simplificadas ou com tratamento de erro limitado, pois ainda estou aprendendo.

Funcionalidades implementadas (ou parcialmente)
Menu principal com acesso às operações básicas.

Cadastro e listagem das principais tabelas (dependendo do que foi possível implementar).

Estruturas (struct) para representar os registros em arquivos binários.

Uso de IDs com auto-incremento simples para identificar registros.

Conversão de textos para letras maiúsculas sem acentuação em alguns campos (onde consegui aplicar).

Limitações e pontos a melhorar
Como sou iniciante em C, algumas coisas ficaram mais fracas ou incompletas:

Tratamento de erros é simples (nem sempre verifica todos os casos possíveis).

Validações (como CPF/CNPJ, datas, etc.) podem estar incompletas ou ausentes.

Alguns menus podem estar confusos ou pouco amigáveis.

A organização do código (separação em arquivos, funções reutilizáveis, etc.) ainda pode ser bastante melhorada.

Pode haver funcionalidades do enunciado que não foram totalmente implementadas, principalmente as partes mais avançadas de compra, relatórios e histórico de preços.

Como compilar e executar (exemplo)
No terminal (ou CMD, dependendo do ambiente):

bash
gcc main.c -o loja
./loja
Ou adaptando para os nomes reais dos arquivos .c do projeto.


