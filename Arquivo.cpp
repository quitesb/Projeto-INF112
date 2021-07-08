#include "arquivo/rapidcsv.h"
#include "Arquivo.h"

Arquivo::Arquivo(std::string dirArquivo) {
    try
    {

        //abre o arquivo
        this->filename = dirArquivo;
        rapidcsv::Document doc(this->filename, rapidcsv::LabelParams(-1, -1));
        this->arquivo =  doc;
    }
    catch(const std::exception& e)
    {
        throw std::ifstream::failure("Erro ao abrir arquivo");
    }
    
    
}

std::vector<std::vector<std::string>> Arquivo::getConteudo() {
    std::vector<std::vector<std::string>> lines;

    for(int i = 0; i < this->arquivo.GetRowCount(); i++) {
        lines.push_back(this->arquivo.GetRow<std::string>(i));
    }


    return lines;


}

int Arquivo::setConteudo(std::vector<std::vector<std::string>> content){
    this->arquivo.Clear();
    for(int i = 0; i < content.size(); i++) {
        this->arquivo.SetRow(i, content[i]);
    }

    this->arquivo.Save(this->filename);

    return 0;
}
