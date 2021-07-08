#ifndef TEAM_3_PACIENTE_H
#define TEAM_3_PACIENTE_H
#include <iostream>
#include "Status.h"
#include "Pessoa.h"
#include <stdlib.h>

class Paciente : public Pessoa
{
    private:

    public:
        //-1 em leito = vazio;
        //CONSTRUTOR
        Paciente();

        //METODOS HERDADOS A SEREM IMPLEMENTADOS
        virtual int cadastrar() override;
        virtual int alterar(int id) override;
        virtual int consultar(int id) override; //LISTAR UM ÚNICO CADASTRO
        virtual int remover(int id) override;

        static int getLenght();

        static int  listar(); //LISTAR TODOS OS CADASTROS
};
#endif
