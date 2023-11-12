#include <iostream>
#include <queue>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

const int TAMANHO_PACOTE = 1024; // Tamanho máximo de cada pacote em bytes

// Estrutura para representar um pacote
struct Pacote {
    int numero;
    int tamanho;
};

// Função para simular a transferência
void simularTransferencia(int tamanhoArquivo) {

    queue <Pacote> filaPacotes;

    int numeroPacote = 1;
    int tamRestanteArquivo = tamanhoArquivo;

    // Enfileira todos os pacotes
    while (tamRestanteArquivo > 0) {
        Pacote pacote;
        pacote.numero = numeroPacote++;
        pacote.tamanho = min(TAMANHO_PACOTE, tamRestanteArquivo);

        filaPacotes.push(pacote);

        tamRestanteArquivo -= pacote.tamanho;
    }

    // Envia os pacotes sequencialmente
    while (!filaPacotes.empty()) {
        Pacote pacoteEnviado = filaPacotes.front();
        filaPacotes.pop();

        cout << "Enviando pacote " << pacoteEnviado.numero << " - Tamanho: " << pacoteEnviado.tamanho << " bytes\n";

        // Simula o tempo de envio (1 segundo)
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "\nTransferência concluída!\n";
}

int main() {
    int tamanhoArquivo;

    cout << "Informe o tamanho do arquivo a ser transmitido (em bytes): ";
    cin >> tamanhoArquivo;

    if(tamanhoArquivo == 0) {
        cout << "\nSEM ARQUIVO PARA TRANSFERIR.\n";

    }else{
        simularTransferencia(tamanhoArquivo);
    }

    return 0;
}
