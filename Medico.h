#ifndef TEAM_3_MEDICO_H
#define TEAM_3_MEDICO_H
#include <iostream>
#include "Pessoa.h"
#include <regex>


class Medico : public Pessoa
{
private:
public:
    //CONSTRUTOR
    Medico();


    //METODOS HERDADOS A SEREM IMPLEMENTADOS
    virtual int cadastrar() override;
    virtual int alterar(int id) override;
    virtual int consultar(int id) override; //LISTAR UM ÚNICO CADASTRO
    virtual int remover(int id) override;


    static int  listar(); //LISTAR TODOS OS CADASTROS      
};
#endif
