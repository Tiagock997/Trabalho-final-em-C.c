#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
} Cliente;

typedef struct {
    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
    char password[20];
} Vendedor;

typedef struct {
    unsigned long id;
    char nome[100];
    unsigned int quantidadeEstoque;
    float precoUnitario;
} Produto;

typedef struct {
    unsigned long idProduto;
    unsigned int quantidadeVendida;
    float valorVenda;
} ItemCarrinhoVenda;

typedef struct {
    unsigned long id;
    unsigned long idCliente;
    unsigned long idVendedor;
    char dataCompra[11];
    float valorTotal;
} NotaFiscal;

typedef struct {
    unsigned long id;
    unsigned long idNotaFiscal;
    unsigned long idProduto;
    float valorVenda;
    unsigned int quantidade;
} ItemNotaFiscal;

typedef struct {
    unsigned long id;
    char cnpj[15];
    char nome[100];
    char email[50];
    char telefone[15];
} Fornecedor;

typedef struct {
    unsigned long id;
    unsigned long idFornecedor;
    char dataCompra[11];
    float valorTotal;
} NotaCompra; //ainda não finalizada, terminarei no tempo livre

typedef struct {
    unsigned long id;
    unsigned long idProduto;
    unsigned long idNotaCompra;
    unsigned int quantidade;
    float valorUnitario;
} ItemNotaCompra; //Terminarei este daqui a pouco.

//QUestões sobre o cliente

void converterMaiuscula(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

unsigned long proximoIdCliente(void) {
    FILE *f = fopen("cliente.dat", "rb");
    Cliente c;
    unsigned long maxId = 0;
    if (f == NULL) return 1;
    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        if (c.id > maxId) maxId = c.id;
    }
    fclose(f);
    return maxId + 1;
}

void cadastrarCliente(void) {
    Cliente c;
    FILE *f = fopen("cliente.dat", "ab"); //abrir em modo ab
    if (f == NULL) { printf("Erro ao abrir cliente.dat\n"); //Se o arquivo não existe (f == NULL)
    return; }

    printf("Nome: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';
    converterMaiuscula(c.nome);

    printf("CPF: ");
    fgets(c.cpf, sizeof(c.cpf), stdin);
    c.cpf[strcspn(c.cpf, "\n")] = '\0';
    getchar(); //alteração nescessária pois tava pulando a entrada do email.

    printf("Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = '\0';

    printf("Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    c.id = proximoIdCliente();
    fwrite(&c, sizeof(Cliente), 1, f); //gravar tudo no arquivo
    fclose(f);
    printf("Cliente cadastrado com ID %lu\n", c.id);
}

void listarClientes(void) {
    FILE *f = fopen("cliente.dat", "rb");
    Cliente c;
    int tem = 0;
    if (f == NULL) { printf("Nenhum cliente cadastrado.\n"); return; }
    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        tem = 1;
        printf("ID: %lu\nNome: %s\nCPF: %s\nEmail: %s\nTelefone: %s\n\n",
               c.id, c.nome, c.cpf, c.email, c.telefone);
    }   //fazer um loop básico com o fread
    if (!tem) printf("Nenhum cliente cadastrado.\n");
    fclose(f);
}

void consultarClientePorId(void) {
    unsigned long idBusca;
    FILE *f = fopen("cliente.dat", "rb");
    Cliente c;
    int encontrado = 0;
    if (f == NULL) { printf("Nenhum cliente cadastrado.\n"); 
        return; 
    }

    printf("Digite o ID do cliente: ");
    scanf("%lu", &idBusca);

    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        if (c.id == idBusca) { // c.id == idBusca imprime e fé.
            printf("ID: %lu\nNome: %s\nCPF: %s\nEmail: %s\nTelefone: %s\n",
                   c.id, c.nome, c.cpf, c.email, c.telefone);
            encontrado = 1;
            break;
        }
    }
    fclose(f);
    if (!encontrado) printf("Cliente com ID %lu nao encontrado.\n", idBusca);
}

void consultarClientePorCpf(void) {
    char cpfBusca[12];
    FILE *f = fopen("cliente.dat", "rb");
    Cliente c;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("Digite o CPF do cliente: ");
    fgets(cpfBusca, sizeof(cpfBusca), stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = '\0';

    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        if (strcmp(c.cpf, cpfBusca) == 0) { //compara strcmp(c.cpf, cpfBusca), se der certo imprime e fé dnv
            printf("ID: %lu\nNome: %s\nCPF: %s\nEmail: %s\nTelefone: %s\n",
                   c.id, c.nome, c.cpf, c.email, c.telefone);
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Cliente com CPF %s nao encontrado.\n", cpfBusca);
    }
}

void alterarClientePorId(void) {
    unsigned long idBusca;
    FILE *f = fopen("cliente.dat", "r+b"); //leitura e escrita
    Cliente c;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("Digite o ID do cliente a alterar: ");
    scanf("%lu", &idBusca);
    getchar();

    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        if (c.id == idBusca) {
            encontrado = 1;

            printf("Nome atual: %s\nNovo nome: ", c.nome);
            fgets(c.nome, sizeof(c.nome), stdin);
            c.nome[strcspn(c.nome, "\n")] = '\0';
            converterMaiuscula(c.nome);

            printf("CPF atual: %s\nNovo CPF: ", c.cpf);
            fgets(c.cpf, sizeof(c.cpf), stdin);
            c.cpf[strcspn(c.cpf, "\n")] = '\0';

            getchar(); //testando se resolve o problema do pulo de entrada do email
            printf("Email atual: %s\nNovo email: ", c.email);
            fgets(c.email, sizeof(c.email), stdin);
            c.email[strcspn(c.email, "\n")] = '\0';

            printf("Telefone atual: %s\nNovo telefone: ", c.telefone);
            fgets(c.telefone, sizeof(c.telefone), stdin);
            c.telefone[strcspn(c.telefone, "\n")] = '\0';

            fseek(f, -(long)sizeof(Cliente), SEEK_CUR); //Volta o ponteiro do arquivo
            fwrite(&c, sizeof(Cliente), 1, f);
            printf("Cliente atualizado com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com ID %lu nao encontrado.\n", idBusca);
    }

    fclose(f);
}

//Questões sobre o fornecedor. (sem coments)

unsigned long proximoIdFornecedor(void) {
    FILE *f = fopen("fornecedor.dat", "rb");
    Fornecedor fnd;
    unsigned long maxId = 0;
    if (f == NULL) return 1;
    while (fread(&fnd, sizeof(Fornecedor), 1, f) == 1) {
        if (fnd.id > maxId) maxId = fnd.id;
    }
    fclose(f);
    return maxId + 1;
}

void cadastrarFornecedor(void) {
    Fornecedor fnd;
    FILE *f = fopen("fornecedor.dat", "ab");
    if (f == NULL) {
        printf("Erro ao abrir fornecedor.dat\n");
        return;
    }

    printf("Nome: ");
    fgets(fnd.nome, sizeof(fnd.nome), stdin);
    fnd.nome[strcspn(fnd.nome, "\n")] = '\0';
    converterMaiuscula(fnd.nome);

    printf("CNPJ: ");
    fgets(fnd.cnpj, sizeof(fnd.cnpj), stdin);
    fnd.cnpj[strcspn(fnd.cnpj, "\n")] = '\0';

    printf("Email: ");
    fgets(fnd.email, sizeof(fnd.email), stdin);
    fnd.email[strcspn(fnd.email, "\n")] = '\0';

    printf("Telefone: ");
    fgets(fnd.telefone, sizeof(fnd.telefone), stdin);
    fnd.telefone[strcspn(fnd.telefone, "\n")] = '\0';

    fnd.id = proximoIdFornecedor();
    fwrite(&fnd, sizeof(Fornecedor), 1, f);
    fclose(f);

    printf("Fornecedor cadastrado com ID %lu\n", fnd.id);
}

void listarFornecedores(void) {
    FILE *f = fopen("fornecedor.dat", "rb");
    Fornecedor fnd;
    int tem = 0;

    if (f == NULL) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    while (fread(&fnd, sizeof(Fornecedor), 1, f) == 1) {
        tem = 1;
        printf("ID: %lu\n", fnd.id);
        printf("Nome: %s\n", fnd.nome);
        printf("CNPJ: %s\n", fnd.cnpj);
        printf("Email: %s\n", fnd.email);
        printf("Telefone: %s\n\n", fnd.telefone);
    }

    if (!tem) {
        printf("Nenhum fornecedor cadastrado.\n");
    }

    fclose(f);
}

void consultarFornecedorPorId(void) {
    unsigned long idBusca;
    FILE *f = fopen("fornecedor.dat", "rb");
    Fornecedor fnd;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("Digite o ID do fornecedor: ");
    scanf("%lu", &idBusca);
    getchar();

    while (fread(&fnd, sizeof(Fornecedor), 1, f) == 1) {
        if (fnd.id == idBusca) {
            printf("ID: %lu\nNome: %s\nCNPJ: %s\nEmail: %s\nTelefone: %s\n",
                   fnd.id, fnd.nome, fnd.cnpj, fnd.email, fnd.telefone);
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Fornecedor com ID %lu nao encontrado.\n", idBusca);
    }
}

void consultarFornecedorPorCnpj(void) {
    char cnpjBusca[15];
    FILE *f = fopen("fornecedor.dat", "rb");
    Fornecedor fnd;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("Digite o CNPJ do fornecedor: ");
    fgets(cnpjBusca, sizeof(cnpjBusca), stdin);
    cnpjBusca[strcspn(cnpjBusca, "\n")] = '\0';

    while (fread(&fnd, sizeof(Fornecedor), 1, f) == 1) {
        if (strcmp(fnd.cnpj, cnpjBusca) == 0) {
            printf("ID: %lu\nNome: %s\nCNPJ: %s\nEmail: %s\nTelefone: %s\n",
                   fnd.id, fnd.nome, fnd.cnpj, fnd.email, fnd.telefone);
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Fornecedor com CNPJ %s nao encontrado.\n", cnpjBusca);
    }
}

void alterarFornecedorPorId(void) {
    unsigned long idBusca;
    FILE *f = fopen("fornecedor.dat", "r+b");
    Fornecedor fnd;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("Digite o ID do fornecedor a alterar: ");
    scanf("%lu", &idBusca);
    getchar();

    while (fread(&fnd, sizeof(Fornecedor), 1, f) == 1) {
        if (fnd.id == idBusca) {
            encontrado = 1;

            printf("Nome atual: %s\nNovo nome: ", fnd.nome);
            fgets(fnd.nome, sizeof(fnd.nome), stdin);
            fnd.nome[strcspn(fnd.nome, "\n")] = '\0';
            converterMaiuscula(fnd.nome);

            printf("CNPJ atual: %s\nNovo CNPJ: ", fnd.cnpj);
            fgets(fnd.cnpj, sizeof(fnd.cnpj), stdin);
            fnd.cnpj[strcspn(fnd.cnpj, "\n")] = '\0';

            printf("Email atual: %s\nNovo email: ", fnd.email);
            fgets(fnd.email, sizeof(fnd.email), stdin);
            fnd.email[strcspn(fnd.email, "\n")] = '\0';

            printf("Telefone atual: %s\nNovo telefone: ", fnd.telefone);
            fgets(fnd.telefone, sizeof(fnd.telefone), stdin);
            fnd.telefone[strcspn(fnd.telefone, "\n")] = '\0';

            fseek(f, -(long)sizeof(Fornecedor), SEEK_CUR);
            fwrite(&fnd, sizeof(Fornecedor), 1, f);
            printf("Fornecedor atualizado com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Fornecedor com ID %lu nao encontrado.\n", idBusca);
    }

    fclose(f);
}


//Questões sobre o vendedor. (segue a mesma logica de cliente)

unsigned long proximoIdVendedor(void) {
    FILE *f = fopen("vendedor.dat", "rb");
    Vendedor v;
    unsigned long maxId = 0;
    if (f == NULL) return 1;
    while (fread(&v, sizeof(Vendedor), 1, f) == 1) {
        if (v.id > maxId) maxId = v.id;
    }
    fclose(f);
    return maxId + 1;
}

void cadastrarVendedor(void) {
    Vendedor v;
    FILE *f = fopen("vendedor.dat", "ab");
    if (f == NULL) { printf("Erro ao abrir vendedor.dat\n"); return; }

    printf("Nome: ");
    fgets(v.nome, sizeof(v.nome), stdin);
    v.nome[strcspn(v.nome, "\n")] = '\0';
    converterMaiuscula(v.nome);

    printf("CPF: ");
    fgets(v.cpf, sizeof(v.cpf), stdin);
    v.cpf[strcspn(v.cpf, "\n")] = '\0';
    getchar(); //alteração nescessária pois tava pulando a entrada do email tambem.

    printf("Email: ");
    fgets(v.email, sizeof(v.email), stdin);
    v.email[strcspn(v.email, "\n")] = '\0';

    printf("Telefone: ");
    fgets(v.telefone, sizeof(v.telefone), stdin);
    v.telefone[strcspn(v.telefone, "\n")] = '\0';

    printf("Senha será: ");
    fgets(v.password, sizeof(v.password), stdin);
    v.password[strcspn(v.password, "\n")] = '\0';

    v.id = proximoIdVendedor();
    fwrite(&v, sizeof(Vendedor), 1, f);
    fclose(f);
    printf("Vendedor cadastrado com ID %lu\n", v.id);
}

void listarVendedores(void) {
    FILE *f = fopen("vendedor.dat", "rb");
    Vendedor v;
    int tem = 0;
    if (f == NULL) { printf("Nenhum vendedor cadastrado.\n"); return; }
    while (fread(&v, sizeof(Vendedor), 1, f) == 1) {
        tem = 1;
        printf("ID: %lu\nNome: %s\nCPF: %s\nEmail: %s\nTelefone: %s\n\n",
               v.id, v.nome, v.cpf, v.email, v.telefone);
    }
    if (!tem) printf("Nenhum vendedor cadastrado.\n");
    fclose(f);
}

void consultarVendedorPorCpf(void) {
    char cpfBusca[12];
    FILE *f = fopen("vendedor.dat", "rb");
    Vendedor v;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum vendedor cadastrado.\n");
        return;
    }

    getchar();
    printf("Digite o CPF do vendedor: ");
    fgets(cpfBusca, sizeof(cpfBusca), stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = '\0';

    while (fread(&v, sizeof(Vendedor), 1, f) == 1) {
        if (strcmp(v.cpf, cpfBusca) == 0) {
            printf("ID: %lu\nNome: %s\nCPF: %s\nEmail: %s\nTelefone: %s\n",
                   v.id, v.nome, v.cpf, v.email, v.telefone);
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Vendedor com CPF %s nao encontrado.\n", cpfBusca);
    }
}

void consultarVendedorPorId(void) {
    unsigned long idBusca;
    FILE *f = fopen("vendedor.dat", "rb");
    Vendedor v;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum vendedor cadastrado.\n");
        return;
    }

    printf("Digite o ID do vendedor: ");
    scanf("%lu", &idBusca);

    while (fread(&v, sizeof(Vendedor), 1, f) == 1) {
        if (v.id == idBusca) {
            printf("ID: %lu\nNome: %s\nCPF: %s\nEmail: %s\nTelefone: %s\n",
                   v.id, v.nome, v.cpf, v.email, v.telefone);
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Vendedor com ID %lu nao encontrado.\n", idBusca);
    }
}

void alterarVendedorPorId(void) {
    unsigned long idBusca;
    FILE *f = fopen("vendedor.dat", "r+b");
    Vendedor v;
    int encontrado = 0;

    if (f == NULL) {
        printf("Nenhum vendedor cadastrado.\n");
        return;
    }

    printf("Digite o ID do vendedor a alterar: ");
    scanf("%lu", &idBusca);
    getchar();

    while (fread(&v, sizeof(Vendedor), 1, f) == 1) {
        if (v.id == idBusca) {
            encontrado = 1;

            printf("Nome atual: %s\nNovo nome: ", v.nome);
            fgets(v.nome, sizeof(v.nome), stdin);
            v.nome[strcspn(v.nome, "\n")] = '\0';
            converterMaiuscula(v.nome);

            printf("CPF atual: %s\nNovo CPF: ", v.cpf);
            fgets(v.cpf, sizeof(v.cpf), stdin);
            v.cpf[strcspn(v.cpf, "\n")] = '\0';

            getchar(); //testando se resolve o problema do pulo de entrada do email novamente
            printf("Email atual: %s\nNovo email: ", v.email);
            fgets(v.email, sizeof(v.email), stdin);
            v.email[strcspn(v.email, "\n")] = '\0';

            printf("Telefone atual: %s\nNovo telefone: ", v.telefone);
            fgets(v.telefone, sizeof(v.telefone), stdin);
            v.telefone[strcspn(v.telefone, "\n")] = '\0';

            printf("Senha atual: %s\nNova senha: ", v.password);
            fgets(v.password, sizeof(v.password), stdin);
            v.password[strcspn(v.password, "\n")] = '\0';

            fseek(f, -(long)sizeof(Vendedor), SEEK_CUR);
            fwrite(&v, sizeof(Vendedor), 1, f);
            printf("Vendedor atualizado com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Vendedor com ID %lu nao encontrado.\n", idBusca);
    }

    fclose(f);
}

int autenticarVendedor(char *cpf, char *senha, Vendedor *out) {
    FILE *f = fopen("vendedor.dat", "rb");
    Vendedor v;
    if (f == NULL) { printf("Nenhum vendedor cadastrado.\n"); return 0; }

    while (fread(&v, sizeof(Vendedor), 1, f) == 1) {
        if (strcmp(v.cpf, cpf) == 0 && strcmp(v.password, senha) == 0) {
            if (out) *out = v;
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void telaLoginVendedor(void) {
    char cpf[12], senha[20];
    Vendedor v;

    getchar();
    printf("CPF do vendedor: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if (autenticarVendedor(cpf, senha, &v)) {
        printf("Vendedor autenticado: %s (ID %lu)\n", v.nome, v.id);
    } else {
        printf("CPF ou senha invalidos.\n");
    }
}

//Questões sobre o produto

unsigned long proximoIdProduto(void) {
    FILE *f = fopen("produto.dat", "rb");
    Produto p;
    unsigned long maxId = 0;//regra 

    if (f == NULL) return 1;

    while (fread(&p, sizeof(Produto), 1, f) == 1) {
        if (p.id > maxId) maxId = p.id;
    }
    fclose(f);
    return maxId + 1;
}

void cadastrarProduto(void) {
    Produto p;
    FILE *f = fopen("produto.dat", "ab");
    if (f == NULL) {
        printf("Erro ao abrir produto.dat\n");
        return;
    }
    printf("Nome do produto: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';
    converterMaiuscula(p.nome);

    printf("Preco unitario: ");
    scanf("%f", &p.precoUnitario);

    p.quantidadeEstoque = 0;   // regra do trabalho
    p.id = proximoIdProduto();

    fwrite(&p, sizeof(Produto), 1, f);
    fclose(f);

    printf("Produto cadastrado com ID %lu\n", p.id);
    getchar();
}

void listarProdutos(void) {
    FILE *f = fopen("produto.dat", "rb");
    Produto p;
    int tem = 0;

    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    while (fread(&p, sizeof(Produto), 1, f) == 1) {
        tem = 1;
        printf("ID: %lu\n", p.id);
        printf("Nome: %s\n", p.nome);
        printf("Estoque: %u\n", p.quantidadeEstoque);
        printf("Preco: %.2f\n\n", p.precoUnitario);
    }

    if (!tem) {
        printf("Nenhum produto cadastrado.\n");
    }

    fclose(f);
}

int buscarProdutoPorId(unsigned long id, Produto *out) {
    FILE *f = fopen("produto.dat", "rb");
    Produto p;

    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return 0;
    }

    while (fread(&p, sizeof(Produto), 1, f) == 1) {
        if (p.id == id) {
            if (out) *out = p;//copia a struct para *out
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int atualizarEstoqueProduto(unsigned long id, int delta) {
    FILE *f = fopen("produto.dat", "r+b");
    Produto p;

    if (f == NULL) {
        printf("Erro ao abrir produto.dat para atualizar estoque.\n");
        return 0;
    }

    while (fread(&p, sizeof(Produto), 1, f) == 1) {
        if (p.id == id) {
            if ((int)p.quantidadeEstoque + delta < 0) {//não deixa ficar negativo
                printf("Estoque insuficiente para o produto ID %lu.\n", id);
                fclose(f);
                return 0;
            }

            p.quantidadeEstoque = (unsigned int)((int)p.quantidadeEstoque + delta);//atualiza(+-)

            fseek(f, -(long)sizeof(Produto), SEEK_CUR);//volta um resgistro e salva
            fwrite(&p, sizeof(Produto), 1, f);

            fclose(f);
            return 1;
        }
    }

    fclose(f);
    printf("Produto ID %lu nao encontrado para atualizar estoque.\n", id);
    return 0;
}

//Sobre nota fiscal (comentários com mesma lógica anterior)

unsigned long proximoIdNotaFiscal(void) {
    FILE *f = fopen("notaFiscal.dat", "rb");
    NotaFiscal n;
    unsigned long maxId = 0;

    if (f == NULL) return 1;

    while (fread(&n, sizeof(NotaFiscal), 1, f) == 1) {
        if (n.id > maxId) maxId = n.id;
    }
    fclose(f);
    return maxId + 1;
}

unsigned long proximoIdItemNotaFiscal(void) {
    FILE *f = fopen("itemNotaFiscal.dat", "rb");
    ItemNotaFiscal i;
    unsigned long maxId = 0;

    if (f == NULL) return 1;

    while (fread(&i, sizeof(ItemNotaFiscal), 1, f) == 1) {
        if (i.id > maxId) maxId = i.id;
    }
    fclose(f);
    return maxId + 1;
}

//SOBre o carrinho

ItemCarrinhoVenda *adicionarItemCarrinho(ItemCarrinhoVenda *carrinho,
                                         int *qtd,
                                         unsigned long idProduto,
                                         unsigned int quantidade,
                                         float valorVenda) {
    for (int i = 0; i < *qtd; i++) {
        if (carrinho[i].idProduto == idProduto) {
            carrinho[i].quantidadeVendida += quantidade;
            return carrinho;
        }
    }

    ItemCarrinhoVenda *novo =
        realloc(carrinho, (*qtd + 1) * sizeof(ItemCarrinhoVenda));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o carrinho.\n");
        return carrinho;
    }
    carrinho = novo;

    carrinho[*qtd].idProduto = idProduto;
    carrinho[*qtd].quantidadeVendida = quantidade;
    carrinho[*qtd].valorVenda = valorVenda;

    (*qtd)++;

    return carrinho;
}

void imprimirCarrinho(ItemCarrinhoVenda *carrinho, int qtd) {
    if (qtd == 0) {
        printf("Carrinho vazio.\n");
        return;
    }

    float total = 0;
    printf("\n--- CARRINHO DE VENDAS ---\n");
    for (int i = 0; i < qtd; i++) {
        float subtotal = carrinho[i].quantidadeVendida * carrinho[i].valorVenda;
        printf("Produto ID: %lu | Qtd: %u | Valor: %.2f | Subtotal: %.2f\n",
               carrinho[i].idProduto,
               carrinho[i].quantidadeVendida,
               carrinho[i].valorVenda,
               subtotal);
        total += subtotal;
    }
    printf("TOTAL: %.2f\n", total);
}

void efetuarVenda(void) {
    Vendedor vend;
    Cliente cli;
    unsigned long idCli;
    char cpfVend[12], senhaVend[20];

    getchar();
    printf("CPF do vendedor: ");
    fgets(cpfVend, sizeof(cpfVend), stdin);
    cpfVend[strcspn(cpfVend, "\n")] = '\0';

    printf("Senha do vendedor: ");
    fgets(senhaVend, sizeof(senhaVend), stdin);
    senhaVend[strcspn(senhaVend, "\n")] = '\0';

    if (!autenticarVendedor(cpfVend, senhaVend, &vend)) {
        printf("Falha na autenticacao do vendedor.\n");
        return;
    }
    printf("Vendedor autenticado: %s (ID %lu)\n", vend.nome, vend.id);

    FILE *fc = fopen("cliente.dat", "rb");
    if (fc == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("ID do cliente: ");
    scanf("%lu", &idCli);

    int achouCli = 0;
    while (fread(&cli, sizeof(Cliente), 1, fc) == 1) {
        if (cli.id == idCli) {
            achouCli = 1;
            break;
        }
    }
    fclose(fc);

    if (!achouCli) {
        printf("Cliente com ID %lu nao encontrado.\n", idCli);
        return;
    }
    printf("Cliente: %s (ID %lu)\n", cli.nome, cli.id);

    ItemCarrinhoVenda *carrinho = NULL;
    int qtdItens = 0;
    int opc;
    do {
        printf("\n--- MENU CARRINHO ---\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Ver carrinho\n");
        printf("3 - Remover produto do carrinho\n");
        printf("4 - Alterar quantidade de um produto\n");
        printf("0 - Finalizar venda\n");
        printf("Opcao: ");
        scanf("%d", &opc);

        if (opc == 1) {
            unsigned long idProd;
            unsigned int qtd;
            Produto p;
            printf("ID do produto: ");
            scanf("%lu", &idProd);

            if (!buscarProdutoPorId(idProd, &p)) {
                printf("Produto nao encontrado.\n");
                continue;
            }

            printf("Quantidade em estoque: %u\n", p.quantidadeEstoque);

            printf("Quantidade desejada: ");
            scanf("%u", &qtd);

            if (qtd == 0) {
                printf("Quantidade invalida.\n");
                continue;
            }

            if (qtd > p.quantidadeEstoque) {
                printf("Quantidade acima do estoque disponivel.\n");
                continue;
            }

            carrinho = adicionarItemCarrinho(carrinho, &qtdItens,
                                             idProd, qtd, p.precoUnitario);
        } else if (opc == 2) {
            imprimirCarrinho(carrinho, qtdItens);
        } else if (opc == 3) {
            unsigned long idRemover;
            printf("ID do produto a remover: ");
            scanf("%lu", &idRemover);

            int indice = -1;
            for (int i = 0; i < qtdItens; i++) {
                if (carrinho[i].idProduto == idRemover) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1) {
                printf("Produto nao encontrado no carrinho.\n");
            } else {
                for (int i = indice; i < qtdItens - 1; i++) {
                    carrinho[i] = carrinho[i + 1];
                }
                qtdItens--;
                if (qtdItens == 0) {
                    free(carrinho);
                    carrinho = NULL;
                } else {
                    ItemCarrinhoVenda *novo =
                        realloc(carrinho, qtdItens * sizeof(ItemCarrinhoVenda));
                    if (novo != NULL) {
                        carrinho = novo;
                    }
                }
                printf("Produto removido do carrinho.\n");
            }
        } else if (opc == 4) {
            unsigned long idAlt;
            unsigned int novaQtd;
            printf("ID do produto para alterar quantidade: ");
            scanf("%lu", &idAlt);

            int indice = -1;
            for (int i = 0; i < qtdItens; i++) {
                if (carrinho[i].idProduto == idAlt) {
                    indice = i;
                    break;
                }
            }

            if (indice == -1) {
                printf("Produto nao encontrado no carrinho.\n");
            } else {
                Produto p;
                if (!buscarProdutoPorId(idAlt, &p)) {
                    printf("Produto nao encontrado na base de produtos.\n");
                } else {
                    printf("Quantidade em estoque: %u\n", p.quantidadeEstoque);
                    printf("Nova quantidade desejada: ");
                    scanf("%u", &novaQtd);

                    if (novaQtd == 0) {
                        printf("Quantidade invalida.\n");
                    } else if (novaQtd > p.quantidadeEstoque) {
                        printf("Quantidade acima do estoque disponivel.\n");
                    } else {
                        carrinho[indice].quantidadeVendida = novaQtd;
                        printf("Quantidade atualizada no carrinho.\n");
                    }
                }
            }
        }

    } while (opc != 0);

    for (int i = 0; i < qtdItens; i++) {
        if (!atualizarEstoqueProduto(carrinho[i].idProduto,
                                     -(int)carrinho[i].quantidadeVendida)) {
            printf("Falha ao atualizar estoque do produto ID %lu.\n",
                   carrinho[i].idProduto);
        }
    }

    float total = 0.0f;
    for (int i = 0; i < qtdItens; i++) {
        total += carrinho[i].quantidadeVendida * carrinho[i].valorVenda;
    }

    char data[11];
    getchar();
    printf("Informe a data da compra (dd/mm/aaaa): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    NotaFiscal nf;
    nf.id = proximoIdNotaFiscal();
    nf.idCliente = cli.id;
    nf.idVendedor = vend.id;
    strncpy(nf.dataCompra, data, sizeof(nf.dataCompra));
    nf.dataCompra[sizeof(nf.dataCompra) - 1] = '\0';
    nf.valorTotal = total;

    FILE *fn = fopen("notaFiscal.dat", "ab");
    if (fn == NULL) {
        printf("Erro ao abrir notaFiscal.dat\n");
        free(carrinho);
        return;
    }
    fwrite(&nf, sizeof(NotaFiscal), 1, fn);
    fclose(fn);

    FILE *fi = fopen("itemNotaFiscal.dat", "ab");
    if (fi == NULL) {
        printf("Erro ao abrir itemNotaFiscal.dat\n");
        free(carrinho);
        return;
    }

    for (int i = 0; i < qtdItens; i++) {
        ItemNotaFiscal item;
        item.id = proximoIdItemNotaFiscal();
        item.idNotaFiscal = nf.id;
        item.idProduto = carrinho[i].idProduto;
        item.valorVenda = carrinho[i].valorVenda;
        item.quantidade = carrinho[i].quantidadeVendida;
        fwrite(&item, sizeof(ItemNotaFiscal), 1, fi);
    }
    fclose(fi);

    printf("\nVenda finalizada. Estoque atualizado e nota fiscal gerada (ID %lu).\n", nf.id);
    imprimirCarrinho(carrinho, qtdItens);

    free(carrinho);
}

int main(void) {
    int op;
    do {
        printf("0 - Sair\n");
        printf("1 - Menu Cliente\n");
        printf("2 - Menu Vendedor\n");
        printf("3 - Menu Fornecedor\n");
        printf("4 - Menu Produto\n");
        printf("5 - Login Vendedor (teste)\n");
        printf("6 - Efetuar venda\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 0:
                printf("Saindo...\n");
                break;

            case 1: {
                int opcC;
                do {
                    printf("\n%%%%%%%%%%%%%%%%%%%% CLIENTE %%%%%%%%%%%%%%%%\n");
                    printf("0 - Voltar\n");
                    printf("1 - Cadastrar\n");
                    printf("2 - Listar\n");
                    printf("3 - Consultar por ID\n");
                    printf("4 - Consultar por CPF\n");
                    printf("5 - Alterar por ID\n");
                    printf("Opcao: ");
                    scanf("%d", &opcC);
                    getchar();

                    switch (opcC) {
                        case 0: break;
                        case 1: cadastrarCliente(); break;
                        case 2: listarClientes(); break;
                        case 3: consultarClientePorId(); break;
                        case 4: consultarClientePorCpf(); break;
                        case 5: alterarClientePorId(); break;
                        default: printf("Opcao invalida!\n");
                    }
                } while (opcC != 0);
                break;
            }

            case 2: {
                int opcV;
                do {
                    printf("\n&&&&&&&&&&&&&&&&&&&&&& VENDEDOR &&&&&&&&&&&&&&&&&&&&\n");
                    printf("0 - Voltar\n");
                    printf("1 - Cadastrar\n");
                    printf("2 - Listar\n");
                    printf("3 - Consultar por ID\n");
                    printf("4 - Consultar por CPF\n");
                    printf("5 - Alterar por ID\n");
                    printf("Opcao: ");
                    scanf("%d", &opcV);
                    getchar();

                    switch (opcV) {
                        case 0: break;
                        case 1: cadastrarVendedor(); break;
                        case 2: listarVendedores(); break;
                        case 3: consultarVendedorPorId(); break;
                        case 4: consultarVendedorPorCpf(); break;
                        case 5: alterarVendedorPorId(); break;
                        default: printf("Opcao invalida!\n");
                    }
                } while (opcV != 0);
                break;
            }

            case 3: {
                int opcF;
                do {
                    printf("\n########## FORNECEDOR ##########\n");
                    printf("0 - Voltar\n");
                    printf("1 - Cadastrar\n");
                    printf("2 - Listar\n");
                    printf("3 - Consultar por ID\n");
                    printf("4 - Consultar por CNPJ\n");
                    printf("5 - Alterar por ID\n");
                    printf("Opcao: ");
                    scanf("%d", &opcF);
                    getchar();

                    switch (opcF) {
                        case 0: break;
                        case 1: cadastrarFornecedor(); break;
                        case 2: listarFornecedores(); break;
                        case 3: consultarFornecedorPorId(); break;
                        case 4: consultarFornecedorPorCnpj(); break;
                        case 5: alterarFornecedorPorId(); break;
                        default: printf("Opcao invalida!\n");
                    }
                } while (opcF != 0);
                break;
            }


            case 4: {
                int opcP;
                do {
                    printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$ PRODUTO $$$$$$$$$$$$$$$$$$$$$$$$\n");
                    printf("0 - Voltar\n");
                    printf("1 - Cadastrar produto\n");
                    printf("2 - Listar produtos\n");
                    printf("Opcao: ");
                    scanf("%d", &opcP);
                    getchar();

                    switch (opcP) {
                        case 0: break;
                        case 1: cadastrarProduto(); 
                        break;
                        case 2: listarProdutos(); 
                        break;
                        default: printf("Opcao invalida!\n");
                    }
                } while (opcP != 0);
                break;
            }

            case 5:
                telaLoginVendedor();
                break;

            case 6:
                efetuarVenda();
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (op != 0);

    return 0;
}