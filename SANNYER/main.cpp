﻿// DICIONARIO (CIDADES).
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <sstream>
#include <locale.h>

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

    while (dicionarioAtual != NULL) {
        if (dicionarioAtual->letra == letra) {
            return dicionarioAtual; // O n� para a letra j� existe, retorne-o
        }
        dicionarioAtual = dicionarioAtual->pP;
    }

    // Nenhum n� com a letra encontrada, crie um novo
    Dicionario* novoNo = new Dicionario;
    novoNo->letra = letra;
    novoNo->quantidade = 0;
    novoNo->palavra = NULL;
    novoNo->pP = NULL;
    novoNo->pA = NULL; // N�o � necess�rio definir o n� anterior

    // Insira o novo n� no in�cio da lista
    novoNo->pP = inicio_dicionario.pP;
    if (inicio_dicionario.pP != NULL) {
        inicio_dicionario.pP->pA = novoNo;
    }
    inicio_dicionario.pP = novoNo;

    return novoNo;
}

void inserirPalavra(Dicionario* dicionario, const char nomeTemp[PALAVRA_MAX], const char descriTemp[DESCRICAO_MAX]) {
    Palavra* novaPalavra = new Palavra;
    strcpy(novaPalavra->nome, nomeTemp);
    strcpy(novaPalavra->descricao, descriTemp);
    novaPalavra->pProx = NULL;

    if (dicionario->palavra == NULL) {
        dicionario->palavra = novaPalavra;
    } else {
        Palavra* palavraAtual = dicionario->palavra;
        while (palavraAtual->pProx != NULL) {
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

    while (dicionarioAtual != NULL) {
        Palavra* palavraAtual = dicionarioAtual->palavra;

        while (palavraAtual != NULL) {
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

        while (palavraAtual != NULL) {
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
    cout << " Insira a Descricao da Palavra: ";
    cin.getline(descrTemp, DESCRICAO_MAX);
    inserir(nomeTemp, descrTemp);
    salvarEmArquivo();
}



void quebrarString(const std::string& texto, int palavrasPorLinha) {
    std::istringstream stream(texto);
    std::string palavra;
    int contador = 0;

    while (stream >> palavra) {
        std::cout << palavra << " ";
        contador++;

        if (contador == palavrasPorLinha) {
            std::cout << std::endl;
            contador = 0;
        }
    }
}

void deleteLetra(Dicionario* dicionario) {
    Dicionario* dicionarioNo = dicionario;
    Dicionario* dicionarioAux = dicionarioNo->pA;

    if (dicionarioAux != NULL) {
        dicionarioAux->pP = dicionarioNo->pP;
    }


    if (dicionarioNo->pP != NULL) {
        dicionarioAux = dicionarioNo->pP;
        dicionarioAux->pA = dicionarioNo->pA;
    }

    dicionarioNo->pP = NULL;
    dicionarioNo->pA = NULL;
    delete dicionarioNo;
}

void excluirPalavra() {
    char nomeTemp[PALAVRA_MAX];
    char primeiraLetra;
    Palavra* palavraAux = NULL;
    Palavra* palavraAtual = NULL;

    cout << " Insira a Palavra Desejada: ";
    cin.ignore();
    cin.getline(nomeTemp, PALAVRA_MAX);
    primeiraLetra = toupper(nomeTemp[0]);

    Dicionario* dicionarioAtual = inicio_dicionario.pP;

    while (dicionarioAtual != NULL) {
        if (dicionarioAtual->letra == primeiraLetra) {
            palavraAtual = dicionarioAtual->palavra;
            while (palavraAtual != NULL) {
                if (strcmp(nomeTemp, palavraAtual->nome) == 0) {
                    cout << "Remover " << palavraAtual->nome << "? Sim[S] Nao[outra tecla]----> ";
                    char resp;
                    cin.get(resp);
                    cin.ignore();

                    if (toupper(resp) == 'S') {
                        if (palavraAux == NULL) {
                            dicionarioAtual->palavra = palavraAtual->pProx;
                        } else {
                            palavraAux->pProx = palavraAtual->pProx;
                        }
                        delete palavraAtual;
                        dicionarioAtual->quantidade--;

                        // Verifique se não há mais palavras no dicionário e exclua a letra
                        if (dicionarioAtual->quantidade == 0) {
                            deleteLetra(dicionarioAtual);
                        }

                        cout << "Palavra removida com sucesso." << endl;
                        salvarEmArquivo();
                        return;
                    } else {
                        cout << "Ação cancelada." << endl;
                        return;
                    }
                }
                palavraAux = palavraAtual;
                palavraAtual = palavraAtual->pProx;
            }
        }
        dicionarioAtual = dicionarioAtual->pP;
    }

    cout << "Palavra não encontrada." << endl;
}

void exibir() {
    Dicionario* dicionarioAtual = inicio_dicionario.pP;
    int palavrasPorlinha = 10;
    while (dicionarioAtual != NULL) {
        cout << "Letra: " << dicionarioAtual->letra << "\tQuantidade de palavras: " << dicionarioAtual->quantidade << "\n";

        Palavra* palavraAtual = dicionarioAtual->palavra;
        while (palavraAtual != NULL) {
            cout << palavraAtual->nome << "\n";
            quebrarString(palavraAtual->descricao, palavrasPorlinha);
            cout <<"\n";
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
Palavra* buscarPorNome(const char palavra[PALAVRA_MAX]) {
    Dicionario* dicionarioAtual = inicio_dicionario.pP;

    while (dicionarioAtual != NULL) {
        Palavra* palavraAtual = dicionarioAtual->palavra;

        while (palavraAtual != NULL) {
            if (strcmp(palavra, palavraAtual->nome) == 0) {
                return palavraAtual;
            }
            palavraAtual = palavraAtual->pProx;
        }

        dicionarioAtual = dicionarioAtual->pP;
    }

    return NULL; // Retorna NULL se a palavra não for encontrada
}

void exibirBuscaPorNome() {
    char nomeTemp[PALAVRA_MAX];
    cout << "Digite a palavra que deseja buscar: ";
    cin.ignore();
    cin.getline(nomeTemp, PALAVRA_MAX);
    Palavra* palavraTemp = buscarPorNome(nomeTemp);

    if (palavraTemp != NULL) {
        cout << "Nome: " << palavraTemp->nome << "\n";
        cout << "Descricao: " << palavraTemp->descricao << "\n";
    } else {
        cout << "Palavra nao encontrada.\n";
    }
     system("pause");
}


int main(){
    setlocale(LC_ALL, "Portuguese");
    inicio_dicionario.pP = NULL;
    carregarDeArquivo();

// MENU PRINCIPAL
    int opFechar, opMenu;
    while(opFechar != 1){
        system("cls");
        cout << "\n*********************  DICIONÁRIO (CIDADES) ************************ \n\n";
        cout << "1 - Adicionar palavra. \n";
        cout << "2 - Exibir todas as palavras.\n";
        cout << "3 - Pesquisar por palavra.\n";
        cout << "4 - Pesquisar por relevancia.\n";
        cout << "5 - Excluir Palavra.\n";
        cout << "6 - Fechar programa.\n\n";
        cout << "Informe qual campo deseja acessar, de acordo com o numero: ";
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
                exibirBuscaPorNome();
                break;

// EXIBE A CIDADE DE ACORDO COM A PALAVRA FORNECIDA E A DESCRI��O
            case 4:

                break;
// EXCLUE A CIDADE PELA NOME
            case 5:
                excluirPalavra();

// ENCERRAR
            case 6:
                cout << "\n\nTem certeza que deseja fechar o programa?\n";
                cout << "[1] sim    [2] nao";
                cout << "\nopcao: ";
                cin >> opFechar;

                switch(opFechar){

                    case 1:
                        cout << "\nPrograma encerrado!\n";
                        break;

                    case 2:
                        break;

                    default:
                        cout << "\nOpcao invalida, por favor tente novamente.\n";
                        system("pause");
                }
                break;


            default:
                cout << "\nOpcao invalida, por favor tente novamente.\n";
                system("pause");

        }

    }
    cout << "\n\n";
    system("pause");
    return 0;
}
