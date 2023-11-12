#include <iostream>
#include <queue>
#include <iomanip>
#include <chrono>
#include <thread>

#define TAMANHO_PACOTE 1024 // pacotes de 1024 bytes

using namespace std;

struct Pacote {
    int numero;
    int tamanho;
};

void simularTransferencia(int tamanhoArquivo) {

    queue <Pacote> filaPacotes; // 'queue' é usado para trabalhar com filas

    int numeroPacote = 1;
    int tamRestanteArquivo = tamanhoArquivo;


    while (tamRestanteArquivo > 0) {
        Pacote pacote;
        pacote.numero = numeroPacote++;
        pacote.tamanho = min(TAMANHO_PACOTE, tamRestanteArquivo); // pega o mínimo entre os dois, nesse caso 'tam_pacote' até que tamanho restante seja menor

        filaPacotes.push(pacote);       // usa o 'push' pra add a fila os pacotes já definidos

        tamRestanteArquivo -= pacote.tamanho;       // subtrai do restante o for adicionado a fila
    }

    while (!filaPacotes.empty()) {
        Pacote pacoteEnviado = filaPacotes.front();     // retorna o primeiro pacote da fila no momento
        filaPacotes.pop();      // retira o primeiro pacote da fila no momento

        cout << "\nEnviando pacote " << pacoteEnviado.numero << " - Tamanho: " << pacoteEnviado.tamanho << " bytes\n";

        this_thread::sleep_for(chrono::seconds(1));     // simula o tempo de envio (1 segundo)
    }

    cout << "\nTransferência concluída!\n";
}

int main() {
    int tamanhoArquivo;
    setlocale(LC_ALL, "Portuguese");

    cout << "Informe o tamanho do arquivo a ser transmitido (em bytes): ";
    cin >> tamanhoArquivo;

    if(tamanhoArquivo == 0) {
        cout << "\nSEM ARQUIVO PARA TRANSFERIR.\n";

    }else{
        simularTransferencia(tamanhoArquivo);
    }

    return 0;
}
