#include "Leito.h"
#include "Arquivo.h"
#include "Paciente.h"

Arquivo arquivo_leito("arquivo/leito.csv");

int Leito::alterar(int max_leito) {
    std::vector<std::vector<std::string>> data = arquivo_leito.getConteudo();
    data[1][0] = std::to_string(max_leito);
    arquivo_leito.setConteudo(data);
    return 0;
}
int Leito::exibir() {
    std::vector<std::vector<std::string>> data = arquivo_leito.getConteudo();
    return stoi(data[1][0]);
}
double Leito::ocupacao() {
    return (double) Paciente::getLenght()*100/exibir();
}