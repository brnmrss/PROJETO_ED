// DICIONARIO (CIDADES).
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
    struct Dicionario* pP;
    struct Dicionario* pA;
};

struct Ocorrencia {
    string palavra;
    string descricao;
    int contagem;
};

Dicionario inicio_dicionario, *dicionarioAtual;

void clearScreen() {
    system("cls");
}

Dicionario* encontrarOuCriarNo(char letra) {
    Dicionario* dicionarioAtual = inicio_dicionario.pP;

    while (dicionarioAtual != NULL) {
        if (dicionarioAtual->letra == letra) {
            return dicionarioAtual;
        }
        dicionarioAtual = dicionarioAtual->pP;
    }


    Dicionario* novoNo = new Dicionario;
    novoNo->letra = letra;
    novoNo->quantidade = 0;
    novoNo->palavra = NULL;
    novoNo->pP = NULL;
    novoNo->pA = NULL;


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
    FILE* arquivo = fopen("dicionario.txt","w");
    Dicionario* dicionarioAtual = inicio_dicionario.pP;

    while (dicionarioAtual != NULL) {
        Palavra* palavraAtual = dicionarioAtual->palavra;

        while (palavraAtual != NULL) {
            fprintf(arquivo, "%s\n", palavraAtual->nome);
            fprintf(arquivo, "%s\n", palavraAtual->descricao);
            palavraAtual = palavraAtual->pProx;
        }

        dicionarioAtual = dicionarioAtual->pP;
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

void quebrarString(const string& texto, int palavrasPorLinha) {
    istringstream stream(texto);
    string palavra;
    int contador = 0;

    while (stream >> palavra) {
        cout << palavra << " ";
        contador++;

        if (contador == palavrasPorLinha) {
            cout << std::endl;
            contador = 0;
        }
    }
    cout << "\n";
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

void excluirPalavra(const char nomeTemp[PALAVRA_MAX]) {
    char primeiraLetra = toupper(nomeTemp[0]);
    Dicionario* dicionarioAtual = inicio_dicionario.pP;

    while (dicionarioAtual != NULL) {
        if (dicionarioAtual->letra == primeiraLetra) {
            Palavra* palavraAux = NULL;
            Palavra* palavraAtual = dicionarioAtual->palavra;

            while (palavraAtual != NULL) {
                if (strcmp(nomeTemp, palavraAtual->nome) == 0) {
                    if (palavraAux == NULL) {
                        dicionarioAtual->palavra = palavraAtual->pProx;
                    } else {
                        palavraAux->pProx = palavraAtual->pProx;
                    }
                    delete palavraAtual;
                    dicionarioAtual->quantidade--;

                    cout << "Palavra removida com sucesso." << endl;

                    if (dicionarioAtual->quantidade == 0) {

                        deleteLetra(dicionarioAtual);
                    }

                    salvarEmArquivo();
                    return;
                }
                palavraAux = palavraAtual;
                palavraAtual = palavraAtual->pProx;
            }
        }
        dicionarioAtual = dicionarioAtual->pP;
    }

    cout << "Palavra não encontrada." << endl;
}

void excluirPalavraIn(){
    char nomeTemp[PALAVRA_MAX];
    cout << "Insira a palavra que deseja excluir: ";
    cin.ignore();
    cin.getline(nomeTemp,PALAVRA_MAX);
    excluirPalavra(nomeTemp);
    system("pause");

}

void exibir() {
    // armazenar as letras
    char letras[26];
    int numLetras = 0;

    // Percorrer o dicionario e adicionar as letras ao array
    Dicionario* dicionarioAtual = inicio_dicionario.pP;
    while (dicionarioAtual != nullptr) {
        letras[numLetras] = dicionarioAtual->letra;
        numLetras++;
        dicionarioAtual = dicionarioAtual->pP;
    }

    // Ordenar o array de letras em ordem alfabetica
    for (int i = 0; i < numLetras - 1; i++) {
        for (int j = i + 1; j < numLetras; j++) {
            if (letras[i] > letras[j]) {
                // Trocar as letras
                char temp = letras[i];
                letras[i] = letras[j];
                letras[j] = temp;
            }
        }
    }

    int palavrasPorlinha = 10;
    for (int i = 0; i < numLetras; i++) {
        char letra = letras[i];
        dicionarioAtual = inicio_dicionario.pP;
        while (dicionarioAtual != nullptr) {
            if (dicionarioAtual->letra == letra) {
                cout << "Letra: " << dicionarioAtual->letra << "\tQuantidade de palavras: " << dicionarioAtual->quantidade << "\n";

                Palavra* palavraAtual = dicionarioAtual->palavra;
                while (palavraAtual != nullptr) {
                    cout << palavraAtual->nome << "\n";
                    quebrarString(palavraAtual->descricao, palavrasPorlinha);
                    cout <<"\n";
                    palavraAtual = palavraAtual->pProx;
                }
            }
            dicionarioAtual = dicionarioAtual->pP;
        }
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

Palavra* buscarPorNome(char palavra[PALAVRA_MAX]) {
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

    return NULL;
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

void alterarDescricao() {
    clearScreen();
    char nomeTemp[PALAVRA_MAX], descriNovo[DESCRICAO_MAX];
    cout << "Insira a palavra que deseja alterar a descricao: ";
    cin.ignore();
    cin.getline(nomeTemp, PALAVRA_MAX);

    Palavra* palavraAtual = buscarPorNome(nomeTemp);

    if (palavraAtual != NULL) {
        cout << "Insira a nova descricao da palavra: ";
        cin.getline(descriNovo, DESCRICAO_MAX);
        strcpy(palavraAtual->descricao, descriNovo);
        salvarEmArquivo();
        cout << "Descricao da palavra alterada!\n";
    } else {
        cout << "Palavra nao encontrada!\n";
    }
    system("pause");
}

void alterarNome() {
    clearScreen();
    char nomeTemp[PALAVRA_MAX], nomeNovo[PALAVRA_MAX];
    cout << "Insira a palavra que deseja alterar o nome: ";
    cin.ignore();
    cin.getline(nomeTemp, PALAVRA_MAX);

    Palavra* palavraAtual = buscarPorNome(nomeTemp);

    if (palavraAtual != NULL) {
        cout << "Insira o novo nome: ";
        cin.getline(nomeNovo, PALAVRA_MAX);

        if (strlen(nomeNovo) == 0) {
            cout << "Nome nao pode ser vazio. Operaçao cancelada." << endl;
            system("pause");
            return;
        }

        char descriTemp[DESCRICAO_MAX];
        strcpy(descriTemp, palavraAtual->descricao);


        if (nomeTemp[0] != nomeNovo[0]) {
            inserir(nomeNovo, descriTemp);
            excluirPalavra(nomeTemp);
        } else {

            strcpy(palavraAtual->nome, nomeNovo);
            strcpy(palavraAtual->descricao, descriTemp);
        }

        salvarEmArquivo();
        cout << "Nome da palavra alterado!\n";
    } else {
        cout << "Palavra nao encontrada!\n";
    }
    system("pause");
}

void alterarTudo() {
    clearScreen();
    char nomeTemp[PALAVRA_MAX], nomeNovo[PALAVRA_MAX], descriNovo[DESCRICAO_MAX];
    cout << "Insira a palavra que deseja alterar: ";
    cin.ignore();
    cin.getline(nomeTemp, PALAVRA_MAX);

    Palavra* palavraAtual = buscarPorNome(nomeTemp);

    if (palavraAtual != NULL) {
        cout << "Insira o novo nome: ";
        cin.getline(nomeNovo, PALAVRA_MAX);
        cout << "Insira a nova descricao: ";
        cin.getline(descriNovo, DESCRICAO_MAX);
        inserir(nomeNovo, descriNovo);
        excluirPalavra(nomeTemp);
        salvarEmArquivo();
        cout << "Palavra alterada!\n";
    } else {
        cout << "Palavra nao encontrada!\n";
    }
    system("pause");
}

void menuEditar(){
    int opMenu;
    do{
    system("cls");
        cout << "\n*********************  EDITAR  ************************ \n\n";
        cout << "1 - Editar Descricao. \n";
        cout << "2 - Editar Nome.\n";
        cout << "3 - Editar Tudo.\n";
        cout << "4 - Voltar.\n";
        cout << "Informe qual campo deseja acessar, de acordo com o numero: ";
        cin >> opMenu;

        switch(opMenu){

            case 1:
                alterarDescricao();
                break;

            case 2:
                alterarNome();
                break;

            case 3:
                alterarTudo();
                break;

            case 4:
                break;

            default:
                cout << "\nOpcao invalida, por favor tente novamente.\n";
                system("pause");
        }
    }while(opMenu!=4);
}

void pesquisaPorRelevancia() {


    cin.ignore();
    string palavraChave;
    cout << "Digite a palavra-chave para pesquisa de relevancia: ";
    cout << endl;
    getline(cin, palavraChave);

    int maxOcorrencias = 125;
    Ocorrencia* ocorrencias = new Ocorrencia[maxOcorrencias];

    int numOcorrencias = 0;

    // Percorrer o dicionario e suas descricoes
    Dicionario* dicionarioAtual = inicio_dicionario.pP;
    while (dicionarioAtual != nullptr) {
        Palavra* palavraAtual = dicionarioAtual->palavra;

        while (palavraAtual != nullptr) {

            // Verifica se a palavra-chave esta na descricao
            const string descricao = palavraAtual->descricao;
            int contagem = 0;
            size_t posicao = descricao.find(palavraChave);
            while (posicao != string::npos) {
                contagem++;
                posicao = descricao.find(palavraChave, posicao + 1);
            }

            // Se a palavra-chave for encontrada e houver espaço armazene as informações
            if (contagem > 0 && numOcorrencias < maxOcorrencias) {
                ocorrencias[numOcorrencias].palavra = palavraAtual->nome;
                ocorrencias[numOcorrencias].descricao = descricao;
                ocorrencias[numOcorrencias].contagem = contagem;
                numOcorrencias++;
            }
            palavraAtual = palavraAtual->pProx;
        }
        dicionarioAtual = dicionarioAtual->pP;
    }

    // Ordena em decrescente
    for (int i = 0; i < numOcorrencias - 1; i++) {
        for (int j = i + 1; j < numOcorrencias; j++) {
            if (ocorrencias[i].contagem < ocorrencias[j].contagem) {
                Ocorrencia temp = ocorrencias[i];
                ocorrencias[i] = ocorrencias[j];
                ocorrencias[j] = temp;
            }
        }
    }

    // Exibir o resultado
    for (int i = 0; i < numOcorrencias; i++) {
        cout << "Palavra: " << ocorrencias[i].palavra << endl;
        cout << "Descriçao: " << ocorrencias[i].descricao << endl;
        cout << "Ocorrencias: " << ocorrencias[i].contagem << endl;
        cout << endl;
    }

    if (numOcorrencias == 0) {
        cout << "Nenhuma descrição relevante encontrada para '" << palavraChave << "'." << endl;
    }
    delete[] ocorrencias;

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
        cout << "\n*********************  DICIONARIO (CIDADES) ************************ \n\n";
        cout << "1 - Adicionar palavra. \n";
        cout << "2 - Exibir todas as palavras.\n";
        cout << "3 - Pesquisar por palavra.\n";
        cout << "4 - Pesquisar por relevancia.\n";
        cout << "5 - Excluir Palavra.\n";
        cout << "6 - Editar.\n";
        cout << "7 - Fechar programa.\n\n";
        cout << "Informe qual campo deseja acessar, de acordo com o numero: ";
        cin >> opMenu;

        switch(opMenu){

            case 1:
                clearScreen();
                inserirManualmente();
                break;

            case 2:
                clearScreen();
                exibir();
                break;

            case 3:
                clearScreen();
                exibirBuscaPorNome();
                break;

            case 4:
                clearScreen();
                pesquisaPorRelevancia();
                break;

            case 5:
                clearScreen();
                excluirPalavraIn();
                break;

            case 6:
                clearScreen();
                menuEditar();
                break;

            case 7:
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
