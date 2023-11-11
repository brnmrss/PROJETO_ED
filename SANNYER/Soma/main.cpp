#include <iostream>
#define MAX 7
using namespace std;

struct Numero {
    int numero;
    struct Numero* prox;
};

Numero topo_1, topo_2, topo_resultado;

void push(int numero, Numero& pilha) {
    Numero* no;
    no = new Numero;

    if (no == NULL) {
        cout << "Erro ao alocar memória.\n";
        return;
    }

    no->numero = numero;
    no->prox = pilha.prox;
    pilha.prox = no;
}

int pop(Numero& topo) {
    int numeroTemp;
    Numero* no, * aux;
    no = topo.prox;
    numeroTemp = no->numero;
    aux = no->prox;
    topo.prox = aux;
    delete no;
    return numeroTemp;
}

void inserirNaPilha(char numero[MAX], Numero& pilha) {
    int numeroTemp, i = 0;
    while (numero[i] != '\0') {
        numeroTemp = int(numero[i] - '0'); // convertendo char para int
        push(numeroTemp, pilha);
        i++;
    }
}

void exibir() {
    system("cls");
    Numero* no;
    no = topo_resultado.prox;
    cout << "Resultado: ";
    while (no != NULL) {
        cout << no->numero;
        no = no->prox;
    }
    cout << "\n";
    system("pause");
}

void soma() {
    int num_1, num_2, resultado, digitoSig = 0;

    while (topo_1.prox != NULL || topo_2.prox != NULL || digitoSig != 0) {
        num_1 = (topo_1.prox != NULL) ? pop(topo_1) : 0,
        ;
        num_2 = (topo_2.prox != NULL) ? pop(topo_2) : 0;
        resultado = num_1 + num_2 + digitoSig;
        if (resultado < 10) {
            push(resultado, topo_resultado);
            digitoSig = 0;
        } else {
            resultado = resultado - 10;
            push(resultado, topo_resultado);
            digitoSig = 1;
        }
    }
}

void inserirManualmente() {
    char num_1[MAX], num_2[MAX];
    cout << "Digite um numero inteiro de ate 7 digitos: ";
    cin.ignore();
    cin.getline(num_1, MAX);
    cout << "Digite outro inteiro de ate 7 digitos: ";
    cin.ignore();
    cin.getline(num_2, MAX);
    inserirNaPilha(num_1, topo_1);
    inserirNaPilha(num_2, topo_2);
}

int main() {
    topo_1.prox = NULL;
    topo_2.prox = NULL;
    topo_resultado.prox = NULL;

    inserirManualmente();
    soma();
    exibir();

    return 0;
}
