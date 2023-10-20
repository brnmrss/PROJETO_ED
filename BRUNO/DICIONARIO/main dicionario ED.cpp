// DICION�RIO (CIDADES).
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <string>

#define PALAVRA_MAX 255
#define DESCRICAO_MAX 255

using namespace std;

struct Palavra {
    char nome[PALAVRA_MAX];
    char descricao[DESCRICAO_MAX];
    struct Palavra* pProx;
};

struct Dicionario {
    char letra;
    int quantidade;
    struct Palavra* palavra;
    struct Dicionario* pP; // Apontador para o pr�ximo n�
    struct Dicionario* pA; // Apontador para o n� anterior
};

Dicionario inicio_dicionario, *dicionarioAtual;

Dicionario* encontrarOuCriarNo(char letra) {
    Dicionario* dicionarioAtual = inicio_dicionario.pP; // Comece no primeiro dicion�rio da lista

    while (dicionarioAtual != nullptr) {
        if (dicionarioAtual->letra == letra) {
            return dicionarioAtual; // O n� para a letra j� existe, retorne-o
        }
        dicionarioAtual = dicionarioAtual->pP;
    }

    // Nenhum n� com a letra encontrada, crie um novo
    Dicionario* novoNo = new Dicionario;
    novoNo->letra = letra;
    novoNo->quantidade = 0;
    novoNo->palavra = nullptr;
    novoNo->pP = nullptr;
    novoNo->pA = nullptr; // N�o � necess�rio definir o n� anterior

    // Insira o novo n� no in�cio da lista
    novoNo->pP = inicio_dicionario.pP;
    if (inicio_dicionario.pP != nullptr) {
        inicio_dicionario.pP->pA = novoNo;
    }
    inicio_dicionario.pP = novoNo;

    return novoNo;
}

void inserirPalavra(Dicionario* dicionario, const char nomeTemp[PALAVRA_MAX], const char descriTemp[DESCRICAO_MAX]) {
    Palavra* novaPalavra = new Palavra;
    strcpy(novaPalavra->nome, nomeTemp);
    strcpy(novaPalavra->descricao, descriTemp);
    novaPalavra->pProx = nullptr;

    if (dicionario->palavra == nullptr) {
        dicionario->palavra = novaPalavra;
    } else {
        Palavra* palavraAtual = dicionario->palavra;
        while (palavraAtual->pProx != nullptr) {
            palavraAtual = palavraAtual->pProx;
        }
        palavraAtual->pProx = novaPalavra;
    }

    dicionario->quantidade++;
}

void inserir(char nomeTemp[PALAVRA_MAX], char descriTemp[DESCRICAO_MAX]) {
    char primeiraLetra = toupper(nomeTemp[0]);
    Dicionario* dicionario = encontrarOuCriarNo(primeiraLetra);
    inserirPalavra(dicionario, nomeTemp, descriTemp);
}

void salvarEmArquivo() {
    FILE *arquivo = fopen("dicionario.txt", "w");
    Dicionario* dicionarioAtual = inicio_dicionario.pP; // Comece no primeiro dicion�rio

    while (dicionarioAtual != nullptr) {
        Palavra* palavraAtual = dicionarioAtual->palavra;

        while (palavraAtual != nullptr) {
            fprintf(arquivo, "%s\n", palavraAtual->nome);
            fprintf(arquivo, "%s\n", palavraAtual->descricao);
            palavraAtual = palavraAtual->pProx;
        }

        dicionarioAtual = dicionarioAtual->pP; // Avance para o pr�ximo dicion�rio
    }

    fclose(arquivo);
}

void carregarDeArquivo() {
    char nomeTemp[PALAVRA_MAX];
    char descriTemp[DESCRICAO_MAX];

    FILE* arquivo = fopen("dicionario.txt", "r");
    if (arquivo == NULL) {
        cout << "Arquivo 'dicionario.txt' nao encontrado!" << endl;
        return;
    }

    while (!feof(arquivo)) {
        fgets(nomeTemp, sizeof(nomeTemp), arquivo);
        fgets(descriTemp, sizeof(descriTemp), arquivo);
        nomeTemp[strcspn(nomeTemp, "\n")] = '\0';
        descriTemp[strcspn(descriTemp, "\n")] = '\0';

        // Verifique se a palavra j� existe no dicion�rio atual antes de inserir
        char primeiraLetra = toupper(nomeTemp[0]);
        Dicionario* dicionario = encontrarOuCriarNo(primeiraLetra);
        Palavra* palavraAtual = dicionario->palavra;
        bool palavraEncontrada = false;

        while (palavraAtual != nullptr) {
            if (strcmp(palavraAtual->nome, nomeTemp) == 0) {
                palavraEncontrada = true;
                break;
            }
            palavraAtual = palavraAtual->pProx;
        }

        if (!palavraEncontrada) {
            inserirPalavra(dicionario, nomeTemp, descriTemp);
        }
    }

    fclose(arquivo);
}

void inserirManualmente() {
    char nomeTemp[PALAVRA_MAX], descrTemp[DESCRICAO_MAX];
    cout << " Insira a Palavra Desejada: ";
    cin.ignore();
    cin.getline(nomeTemp, PALAVRA_MAX);
    cout << " Insira a Descri��o da Palavra: ";
    cin.getline(descrTemp, DESCRICAO_MAX);
    inserir(nomeTemp, descrTemp);
    salvarEmArquivo();
}

void exibir() {
    Dicionario* dicionarioAtual = inicio_dicionario.pP;
    while (dicionarioAtual != nullptr) {
        cout << "Letra: " << dicionarioAtual->letra << "\tQuantidade de palavras: " << dicionarioAtual->quantidade << "\n";

        Palavra* palavraAtual = dicionarioAtual->palavra;
        while (palavraAtual != nullptr) {
            cout << palavraAtual->nome << "\n";
            cout << palavraAtual->descricao << "\n";
            palavraAtual = palavraAtual->pProx;
        }

        dicionarioAtual = dicionarioAtual->pP;
    }

    system("pause");
}

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
  CursorPosition.X = x; // Locates column
  CursorPosition.Y = y; // Locates Row
  SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}


int main(){
    setlocale(LC_ALL, "Portuguese");

    inicio_dicionario.pP = nullptr;
    carregarDeArquivo();

// MENU PRINCIPAL
    int opFechar, opMenu;
    while(opFechar != 1){
        system("cls");
        cout << "\n*********************  DICION�RIO (CIDADES) ************************ \n\n";
        cout << "1 - Adicionar palavra. \n";
        cout << "2 - Exibir todas as palavras.\n";
        cout << "3 - Pesquisar por palavra.\n";
        cout << "4 - Pesquisar por relev�ncia.\n";
        cout << "5 - Fechar programa.\n\n";
        cout << "Informe qual campo deseja acessar, de acordo com o n�mero: ";
        cin >> opMenu;

        switch(opMenu){

// ADICIONA AO DICION�RIO A CIDADE COM A DESCRI��O.
            case 1:
                inserirManualmente();
                break;

// EXIBE TODAS AS CIDADES DO DICION�RIO JUNTO COM A DESCRI��O.
            case 2:
                exibir();
                break;

// PESQUISA UMA CIDADE ESPEC�FICA DENTRO DO DICION�RIO
            case 3:

                break;

// EXIBE A CIDADE DE ACORDO COM A PALAVRA FORNECIDA E A DESCRI��O
            case 4:

                break;

// ENCERRAR
            case 5:
                cout << "\n\nTem certeza que deseja fechar o programa?\n";
                cout << "[1] sim    [2] n�o";
                cout << "\nOp��o: ";
                cin >> opFechar;

                switch(opFechar){

                    case 1:
                        cout << "\nPrograma encerrado!\n";
                        break;

                    case 2:
                        break;

                    default:
                        cout << "\nOp��o inv�lida, por favor tente novamente.\n";
                        system("pause");
                }
                break;


            default:
                cout << "\nOp��o inv�lida, por favor tente novamente.\n";
                system("pause");

        }

    }
    cout << "\n\n";
    system("pause");
    return 0;
}
