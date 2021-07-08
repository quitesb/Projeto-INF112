#ifndef TEAM_3_PESSOA_H
#define TEAM_3_PESSOA_H
#include <iostream>

class Pessoa
{
private:
public:
    //METODOS A SEREM UTILIZADOS NAS CLASSES FILHAS
    virtual int cadastrar() = 0; 
    virtual int alterar(int id) = 0;
    virtual int consultar(int id) = 0; // LISTAR UM ÚNICO CADASTRO
    virtual int remover(int id) = 0;
};
#endif

