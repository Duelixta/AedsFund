#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int proximoIDVoo = 1;

typedef struct {
    int codigoPassageiro;
    char nome[100];
    char endereco[150];
    char telefone[15];
    bool fidelidade;
    int pontosFidelidade;
} PASSAGEIRO;

typedef struct {
    int codigoTripulacao;
    char nome[100];
    char telefone[15];
    char cargo[50];
} TRIPULACAO;

typedef struct {
    int codigoVoo;
    char data[11];
    char hora[6];
    char origem[50];
    char destino[50];
    int codigoAviao;
    int codigoPiloto;
    int codigoCopiloto;
    int codigoComissario;
    bool status;
    float tarifa;
} VOO;

typedef struct {
    int numeroAssento;
    int codigoVoo;
    bool statusAssento;
} ASSENTO;

typedef struct {
    int codigoVoo;
    int numeroAssento;
    int codigoPassageiro;
} RESERVA;

void salvarPassageiros(PASSAGEIRO *passageiros, int qtdPassageiros) {
    FILE *arquivo = fopen("passageiros.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&qtdPassageiros, sizeof(int), 1, arquivo);
    fwrite(passageiros, sizeof(PASSAGEIRO), qtdPassageiros, arquivo);
    fclose(arquivo);
}

void carregarPassageiros(PASSAGEIRO **passageiros, int *qtdPassageiros) {
    FILE *arquivo = fopen("passageiros.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    fread(qtdPassageiros, sizeof(int), 1, arquivo);
    *passageiros = (PASSAGEIRO *)malloc(*qtdPassageiros * sizeof(PASSAGEIRO));
    fread(*passageiros, sizeof(PASSAGEIRO), *qtdPassageiros, arquivo);
    fclose(arquivo);
}

void salvarTripulacao(TRIPULACAO *tripulacao, int qtdTripulacao) {
    FILE *arquivo = fopen("tripulacao.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&qtdTripulacao, sizeof(int), 1, arquivo);
    fwrite(tripulacao, sizeof(TRIPULACAO), qtdTripulacao, arquivo);
    fclose(arquivo);
}

void carregarTripulacao(TRIPULACAO **tripulacao, int *qtdTripulacao) {
    FILE *arquivo = fopen("tripulacao.dat", "rb");
    if (arquivo == NULL) {
        *qtdTripulacao = 0;
        *tripulacao = NULL;
        return;
    }
    fread(qtdTripulacao, sizeof(int), 1, arquivo);
    *tripulacao = (TRIPULACAO *)malloc(*qtdTripulacao * sizeof(TRIPULACAO));
    fread(*tripulacao, sizeof(TRIPULACAO), *qtdTripulacao, arquivo);
    fclose(arquivo);
}

void salvarVoos(VOO *voos, int qtdVoos) {
    FILE *arquivo = fopen("voos.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&qtdVoos, sizeof(int), 1, arquivo);
    fwrite(voos, sizeof(VOO), qtdVoos, arquivo);
    fclose(arquivo);
}

void carregarVoos(VOO **voos, int *qtdVoos) {
    FILE *arquivo = fopen("voos.dat", "rb");
    if (arquivo == NULL) {
        *qtdVoos = 0;
        *voos = NULL;
        return;
    }
    fread(qtdVoos, sizeof(int), 1, arquivo);
    *voos = (VOO *)malloc(*qtdVoos * sizeof(VOO));
    fread(*voos, sizeof(VOO), *qtdVoos, arquivo);
    fclose(arquivo);

    for (int i = 0; i < *qtdVoos; i++) {
        if ((*voos)[i].codigoVoo >= proximoIDVoo) {
            proximoIDVoo = (*voos)[i].codigoVoo + 1;
        }
    }
}


void salvarAssentos(ASSENTO *assentos, int qtdAssentos) {
    FILE *arquivo = fopen("assentos.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&qtdAssentos, sizeof(int), 1, arquivo);
    fwrite(assentos, sizeof(ASSENTO), qtdAssentos, arquivo);
    fclose(arquivo);
}

void carregarAssentos(ASSENTO **assentos, int *qtdAssentos) {
    FILE *arquivo = fopen("assentos.dat", "rb");
    if (arquivo == NULL) {
        *qtdAssentos = 0;
        *assentos = NULL;
        return;
    }
    fread(qtdAssentos, sizeof(int), 1, arquivo);
    *assentos = (ASSENTO *)malloc(*qtdAssentos * sizeof(ASSENTO));
    fread(*assentos, sizeof(ASSENTO), *qtdAssentos, arquivo);
    fclose(arquivo);
}

void salvarReservas(RESERVA *reservas, int qtdReservas) {
    FILE *arquivo = fopen("reservas.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&qtdReservas, sizeof(int), 1, arquivo);
    fwrite(reservas, sizeof(RESERVA), qtdReservas, arquivo);
    fclose(arquivo);
}

void carregarReservas(RESERVA **reservas, int *qtdReservas) {
    FILE *arquivo = fopen("reservas.dat", "rb");
    if (arquivo == NULL) {
        *qtdReservas = 0;
        *reservas = NULL;
        return;
    }
    fread(qtdReservas, sizeof(int), 1, arquivo);
    *reservas = (RESERVA *)malloc(*qtdReservas * sizeof(RESERVA));
    fread(*reservas, sizeof(RESERVA), *qtdReservas, arquivo);
    fclose(arquivo);
}

int menu() {
    int opcao;
    printf("\n=== Sistema de Gerenciamento ===\n");
    printf("1. Cadastrar Passageiro\n");
    printf("2. Cadastrar Tripulação\n");
    printf("3. Cadastrar Voo\n");
    printf("4. Cadastrar Assentos\n");
    printf("5. Fazer Reserva\n");
    printf("6. Cancelar Reserva\n");
    printf("7. Consultar Passageiro\n");
    printf("8. Consultar Voos\n");
    printf("9. Consultar Reservas\n");
    printf("10. Programa de Fidelidade\n");
    printf("11. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

void cadastrarPassageiro(PASSAGEIRO *passageiros, int *qtdPassageiros) {
    int codigo, fidelidade, pontosFidelidade;
    char nome[100], endereco[150], telefone[15];
    printf("Digite o código do passageiro: ");
    scanf("%d", &codigo);
    getchar();
    for (int i = 0; i < *qtdPassageiros; i++) {
        if (passageiros[i].codigoPassageiro == codigo) {
            printf("Código já cadastrado!\n");
            return;
        }
    }
    printf("Digite o nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    printf("Digite o endereço: ");
    fgets(endereco, sizeof(endereco), stdin);
    endereco[strcspn(endereco, "\n")] = 0;
    printf("Digite o telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = 0;
    printf("Possui fidelidade? (1-Sim / 0-Não): ");
    scanf("%d", &fidelidade);
    if (fidelidade) {
        printf("Digite os pontos de fidelidade: ");
        scanf("%d", &pontosFidelidade);
    } else pontosFidelidade = 0;
    passageiros[*qtdPassageiros].codigoPassageiro = codigo;
    strcpy(passageiros[*qtdPassageiros].nome, nome);
    strcpy(passageiros[*qtdPassageiros].endereco, endereco);
    strcpy(passageiros[*qtdPassageiros].telefone, telefone);
    passageiros[*qtdPassageiros].fidelidade = fidelidade;
    passageiros[*qtdPassageiros].pontosFidelidade = pontosFidelidade;
    (*qtdPassageiros)++;
    salvarPassageiros(passageiros, *qtdPassageiros);
    printf("Passageiro cadastrado com sucesso!\n");
}

void cadastrarTripulacao(TRIPULACAO *tripulacao, int *qtdTripulacao) {
    int codigo;
    char nome[100], telefone[15], cargo[50];
    printf("Digite o código do membro da tripulação: ");
    scanf("%d", &codigo);
    getchar();
    for (int i = 0; i < *qtdTripulacao; i++) {
        if (tripulacao[i].codigoTripulacao == codigo) {
            printf("Código já cadastrado!\n");
            return;
        }
    }
    printf("Digite o nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    printf("Digite o telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = 0;
    printf("Digite o cargo (piloto, copiloto, comissário): ");
    fgets(cargo, sizeof(cargo), stdin);
    cargo[strcspn(cargo, "\n")] = 0;
    tripulacao[*qtdTripulacao].codigoTripulacao = codigo;
    strcpy(tripulacao[*qtdTripulacao].nome, nome);
    strcpy(tripulacao[*qtdTripulacao].telefone, telefone);
    strcpy(tripulacao[*qtdTripulacao].cargo, cargo);
    (*qtdTripulacao)++;
    salvarTripulacao(tripulacao, *qtdTripulacao);
    printf("Tripulação cadastrada com sucesso!\n");
}

void cadastrarVoo(VOO *voos, int *qtdVoos, TRIPULACAO *tripulacao, int qtdTripulacao) {
    VOO novoVoo;
    novoVoo.codigoVoo = proximoIDVoo++;
    
    printf("Digite a data do voo (dd/mm/aaaa): ");
    scanf("%s", novoVoo.data);
    printf("Digite a hora do voo (hh:mm): ");
    scanf("%s", novoVoo.hora);
    printf("Digite a origem do voo: ");
    scanf("%s", novoVoo.origem);
    printf("Digite o destino do voo: ");
    scanf("%s", novoVoo.destino);
    printf("Digite o código do avião: ");
    scanf("%d", &novoVoo.codigoAviao);
    printf("Digite o código do piloto: ");
    scanf("%d", &novoVoo.codigoPiloto);
    printf("Digite o código do copiloto: ");
    scanf("%d", &novoVoo.codigoCopiloto);
    printf("Digite o código do comissário: ");
    scanf("%d", &novoVoo.codigoComissario);
    novoVoo.status = true;
    printf("Digite a tarifa do voo: ");
    scanf("%f", &novoVoo.tarifa);

    voos[*qtdVoos] = novoVoo;
    (*qtdVoos)++;
    salvarVoos(voos, *qtdVoos);
    printf("Voo cadastrado com sucesso!\n");
}

void cadastrarAssento(ASSENTO *assentos, int *qtdAssentos, int codigoVoo) {
    int numeroAssento;
    printf("Digite o número do assento para o voo %d: ", codigoVoo);
    scanf("%d", &numeroAssento);
    assentos[*qtdAssentos].numeroAssento = numeroAssento;
    assentos[*qtdAssentos].codigoVoo = codigoVoo;
    assentos[*qtdAssentos].statusAssento = true;
    (*qtdAssentos)++;
    salvarAssentos(assentos, *qtdAssentos);
    printf("Assento cadastrado com sucesso!\n");
}

void fazerReserva(RESERVA *reservas, int *qtdReservas, ASSENTO *assentos, int qtdAssentos, PASSAGEIRO *passageiros, int qtdPassageiros, VOO *voos, int qtdVoos) {
    int codigoVoo, numeroAssento, codigoPassageiro;
    printf("Digite o código do voo: ");
    scanf("%d", &codigoVoo);
    printf("Digite o número do assento: ");
    scanf("%d", &numeroAssento);
    printf("Digite o código do passageiro: ");
    scanf("%d", &codigoPassageiro);

    for (int i = 0; i < qtdAssentos; i++) {
        if (assentos[i].codigoVoo == codigoVoo && assentos[i].numeroAssento == numeroAssento) {
            if (assentos[i].statusAssento) {
                for (int j = 0; j < qtdPassageiros; j++) {
                    if (passageiros[j].codigoPassageiro == codigoPassageiro) {
                        reservas[*qtdReservas].codigoVoo = codigoVoo;
                        reservas[*qtdReservas].numeroAssento = numeroAssento;
                        reservas[*qtdReservas].codigoPassageiro = codigoPassageiro;
                        assentos[i].statusAssento = false;
                        (*qtdReservas)++;
                        salvarReservas(reservas, *qtdReservas);
                        printf("Reserva realizada com sucesso!\n");
                        return;
                    }
                }
                printf("Passageiro não encontrado.\n");
                return;
            }
            printf("Assento já reservado.\n");
            return;
        }
    }
    printf("Assento ou voo não encontrado.\n");
}

void cancelarReserva(RESERVA *reservas, int *qtdReservas, ASSENTO *assentos, int qtdAssentos) {
    int codigoVoo, numeroAssento;
    printf("Digite o código do voo: ");
    scanf("%d", &codigoVoo);
    printf("Digite o número do assento: ");
    scanf("%d", &numeroAssento);

    for (int i = 0; i < *qtdReservas; i++) {
        if (reservas[i].codigoVoo == codigoVoo && reservas[i].numeroAssento == numeroAssento) {
            for (int j = 0; j < qtdAssentos; j++) {
                if (assentos[j].codigoVoo == codigoVoo && assentos[j].numeroAssento == numeroAssento) {
                    assentos[j].statusAssento = true;
                    for (int k = i; k < *qtdReservas - 1; k++) {
                        reservas[k] = reservas[k + 1];
                    }
                    (*qtdReservas)--;
                    salvarReservas(reservas, *qtdReservas);
                    salvarAssentos(assentos, qtdAssentos);
                    printf("Reserva cancelada com sucesso!\n");
                    return;
                }
            }
        }
    }
    printf("Reserva não encontrada.\n");
}

void consultarPassageiro(PASSAGEIRO *passageiros, int qtdPassageiros) {
    int codigo;
    printf("Digite o código do passageiro: ");
    scanf("%d", &codigo);
    for (int i = 0; i < qtdPassageiros; i++) {
        if (passageiros[i].codigoPassageiro == codigo) {
            printf("Passageiro: %s\n", passageiros[i].nome);
            printf("Endereço: %s\n", passageiros[i].endereco);
            printf("Telefone: %s\n", passageiros[i].telefone);
            printf("Fidelidade: %s\n", passageiros[i].fidelidade ? "Sim" : "Não");
            printf("Pontos Fidelidade: %d\n", passageiros[i].pontosFidelidade);
            return;
        }
    }
    printf("Passageiro não encontrado.\n");
}

void consultarVoo(VOO *voos, int qtdVoos) {
    int codigo;
    printf("Digite o código do voo: ");
    scanf("%d", &codigo);
    for (int i = 0; i < qtdVoos; i++) {
        if (voos[i].codigoVoo == codigo) {
            printf("Voo %d: %s para %s\n", voos[i].codigoVoo, voos[i].origem, voos[i].destino);
            printf("Data: %s Hora: %s Tarifa: %.2f\n", voos[i].data, voos[i].hora, voos[i].tarifa);
            return;
        }
    }
    printf("Voo não encontrado.\n");
}

void fidelidade(PASSAGEIRO *passageiros, int qtdPassageiros) {
    int codigo;
    printf("Digite o código do passageiro: ");
    scanf("%d", &codigo);
    for (int i = 0; i < qtdPassageiros; i++) {
        if (passageiros[i].codigoPassageiro == codigo) {
            printf("Pontos de fidelidade do passageiro %s: %d\n", passageiros[i].nome, passageiros[i].pontosFidelidade);
            return;
        }
    }
    printf("Passageiro não encontrado.\n");
}

void listarVoos(VOO *voos, int qtdVoos) {
    printf("Lista de Voos:\n");
    for (int i = 0; i < qtdVoos; i++) {
        printf("Voo %d: %s para %s\n", voos[i].codigoVoo, voos[i].origem, voos[i].destino);
        printf("Data: %s Hora: %s Tarifa: %.2f\n", voos[i].data, voos[i].hora, voos[i].tarifa);
    }
}

void consultarReservas(RESERVA *reservas, int qtdReservas) {
    int codigoPassageiro;
    printf("Digite o código do passageiro: ");
    scanf("%d", &codigoPassageiro);
    bool encontrou = false;
    for (int i = 0; i < qtdReservas; i++) {
        if (reservas[i].codigoPassageiro == codigoPassageiro) {
            printf("Reserva %d: Voo %d, Assento %d\n", i + 1, reservas[i].codigoVoo, reservas[i].numeroAssento);
            encontrou = true;
        }
    }
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para o passageiro com código %d.\n", codigoPassageiro);
    }
    } }

int main() {
    PASSAGEIRO *passageiros = NULL;
    int qtdPassageiros = 0;
    TRIPULACAO *tripulacao = NULL;
    int qtdTripulacao = 0;
    VOO *voos = NULL;
    int qtdVoos = 0;
    ASSENTO *assentos = NULL;
    int qtdAssentos = 0;
    RESERVA *reservas = NULL;
    int qtdReservas = 0;

    carregarPassageiros(&passageiros, &qtdPassageiros);
    carregarTripulacao(&tripulacao, &qtdTripulacao);
    carregarVoos(&voos, &qtdVoos);
    carregarAssentos(&assentos, &qtdAssentos);
    carregarReservas(&reservas, &qtdReservas);

    int opcao;
    do {
        printf("Menu:\n");
        printf("1. Cadastrar Passageiro\n");
        printf("2. Cadastrar Tripulação\n");
        printf("3. Cadastrar Voo\n");
        printf("4. Cadastrar Assento\n");
        printf("5. Fazer Reserva\n");
        printf("6. Cancelar Reserva\n");
        printf("7. Consultar Passageiro\n");
        printf("8. Consultar Voo\n");
        printf("9. Consultar Reservas\n");
        printf("10. Fidelidade\n");
        printf("11. Listar Voos\n");
        printf("12. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarPassageiro(passageiros, &qtdPassageiros);
                break;
            case 2:
                cadastrarTripulacao(tripulacao, &qtdTripulacao);
                break;
            case 3:
                cadastrarVoo(voos, &qtdVoos, tripulacao, qtdTripulacao);
                break;
            case 4:
                cadastrarAssento(assentos, &qtdAssentos, qtdVoos);
                break;
            case 5:
                fazerReserva(reservas, &qtdReservas, assentos, qtdAssentos, passageiros, qtdPassageiros, voos, qtdVoos);
                break;
            case 6:
                cancelarReserva(reservas, &qtdReservas, assentos, qtdAssentos);
                break;
            case 7:
                consultarPassageiro(passageiros, qtdPassageiros);
                break;
            case 8:
                consultarVoo(voos, qtdVoos);
                break;
            case 9:
                consultarReservas(reservas, qtdReservas);
                break;
            case 10:
                fidelidade(passageiros, qtdPassageiros);
                break;
            case 11:
                listarVoos(voos, qtdVoos);
                break;
            case 12:
                printf("Saindo...\n");
                
                salvarPassageiros(passageiros, qtdPassageiros);
                salvarTripulacao(tripulacao, qtdTripulacao);
                salvarVoos(voos, qtdVoos);
                salvarAssentos(assentos, qtdAssentos);
                salvarReservas(reservas, qtdReservas);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 12);

    free(passageiros);
    free(tripulacao);
    free(voos);
    free(assentos);
    free(reservas);

    return 0;
}