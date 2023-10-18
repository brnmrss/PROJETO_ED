#include <iostream>
#include <cstring>

using namespace std;

struct Palavra{
    char nome[50];
    char descricao[150];
    struct Palavra *pProx;
};

struct Dicionario{
    char letra;
    int quantidade;
    struct Palavra *palavra;
    struct Dicionario *pP;
    struct Dicionario *pA;
};
Palavra inicio_palavra, *palavraAnt, *palavraAtual;
Dicionario inicio_dicionario, *dicionarioAnt,*dicionarioAtual;

void inserir(){
    char resp, primeiraLetra;
    char nomeTemp[50];
    char descriTemp[150];

    dicionarioAtual= &inicio_dicionario;

        if(inicio_dicionario.pP == NULL){
            dicionarioAtual->pP = new (Dicionario);
            dicionarioAtual = dicionarioAtual->pP;
            palavraAtual = &inicio_palavra;
            palavraAtual->pProx = new(Palavra);
            palavraAtual = palavraAtual -> pProx;
            dicionarioAtual->palavra = palavraAtual;
            cout << "insira a palavra: ";
            cin.ignore();
            cin.getline(palavraAtual->nome, 50);
            cout << "Insira a descriçao da palavra: ";
            cin.ignore();
            cin.getline(palavraAtual->descricao, 150);
            primeiraLetra = palavraAtual->nome[0];
            dicionarioAtual->letra = primeiraLetra;



        }


}
int main(){
    inicio_dicionario = NULL;
    cout << "Hello world!" << endl;
    return 0;
}
