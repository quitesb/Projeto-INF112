#include "Paciente.h"
#include "Arquivo.h"
#include <ctype.h>
#include <regex>
#include <string>
#include "Leito.h"
#include "Status.h"

Arquivo arquivo_paciente("arquivo/paciente.csv");

Status status;

static std::vector<std::string> split(const std::string& str, char delim){
   auto i = 0;
   std::vector<std::string> list; 
   auto pos = str.find(delim);
   while (pos != std::string::npos){
      list.push_back(str.substr(i, pos - i));
      i = ++pos;
      pos = str.find(delim, pos);
   }
   list.push_back(str.substr(i, str.length()));
   return list;
}

int Paciente::listar()
{
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_paciente.getConteudo();

  //IMPRIMIR ARQUIVO TODO
  for (std::vector<std::string> line : data)
  {
    for (std::string colum : line)
    {
      std::cout << colum << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}

Paciente::Paciente()
{
}

int Paciente::cadastrar()
{
  std::string nome, data_nascimento, sexo, cpf, obs, tel, leito;
  std::vector<std::string> auxiliar;
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_paciente.getConteudo();
  
  //OS std::cout`s ABAIXO RECUPERAM CAMPOS PRO VETOR AUXILIAR
  int id = stoi(data[data.size() - 1][0]);
  while(true){
    std::cout << "Digite o nome do paciente: " << std::endl;
    while (std::getline(std::cin, nome))
    {
      if (nome != "")
      break;
    }

    bool verifica = false;
    std::regex re(R"(^[A-Za-záàâãéèêíïóôõöúçñÁÀÂÃÉÈÍÏÓÔÕÖÚÇÑ ]*$)");
    if (std::regex_match(nome, re)) {
      verifica = true;
    } else {
      verifica = false;
    }
    if(verifica == true)
      break;
    else
      std::cout << "Nome inválido!" << std::endl;
  }

  while(true){
    std::cout << "Digite o CPF do paciente(Somente números): " << std::endl ;
    std::cin >> cpf;

  //VERIFICA A QUANTIDADE DE DIGITOS E SE HÁ APENAS NUMEROS
    int aux=0;
    for(int i=0;i<cpf.size();i++){
      if(cpf[i]<'0' || cpf[i]>'9'){
        aux=0;
        break;
      }
      aux++;
    }
    if(aux==11)
      break;
    else
      std::cout<< "CPF inválido!" << std::endl;
  }
  
  std::cout << "Digite a data de nascimento do paciente (dd/mm/aaaa): " << std::endl;
  std::cin >> data_nascimento;

  while(true){
    std::cout << "Digite o sexo(M/F): " << std::endl ;
    std::cin >> sexo;

    //VERIFICA SE DIGITOU M OU F
    if((sexo[0]== 'M'  || sexo[0] == 'F' || sexo[0]=='m' || sexo[0]=='f') && sexo[1]=='\0'){
      if(sexo[0]=='m' || sexo[0]=='f')
        sexo[0]=toupper(sexo[0]);
      break;
    }
    else
      std::cout << "Sexo inválido" << std::endl;
  }

  std::cout << "Digite alguma observação sobre o paciente (opcional): " << std::endl;

  while (std::getline(std::cin, obs))
  {
    if (obs != "")
      break;
  }

  while(true)
  {
    std::cout << "Digite o telefone do paciente: " << std::endl;
    std::cin >> tel;
    
    //VERIFICA SE HÁ SOMENTE NUMEROS
    bool verifica_digito = true;
    for(int i=0;tel[i]!='\0';i++){
      if(tel[i]<'0' || tel[i]>'9'){
        verifica_digito = false;
        break;
      }
    }
    if(verifica_digito == true)
      break;
    else
      std::cout << "Telfone inválido!" << std::endl;
  }

  while(true){
    std::cout << "Digite o número do leito do paciente: " << std::endl;
    std::cin >> leito;
    if(stoi(leito)>=0 && stoi(leito)<=Leito::exibir())
      break;
    else 
      std::cout << "Número do leito inválido!" << std::endl;
  }

  //AUXILIAR RECEBE DADOS
  auxiliar.push_back(std::to_string(++id));
  auxiliar.push_back(nome);
  auxiliar.push_back(cpf);
  auxiliar.push_back(data_nascimento);
  auxiliar.push_back(sexo);
  auxiliar.push_back(obs);
  auxiliar.push_back(tel);
  auxiliar.push_back(leito);
  status.cadastrar(std::to_string(id));
  
  
  //JOGAR OS DADOS DO AUXILIAR PRA MATRIZ
  data.push_back(auxiliar);

  //ARQUIVO RECEBE A MATRIZ
  arquivo_paciente.setConteudo(data);
  return 0;
}

int Paciente::alterar(int id)
{
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_paciente.getConteudo();

  int campo = -1;
  bool verificar=false;

  std::cout << "Digite o digito do campo que você deseja alterar:" << std::endl;
  std::cout << "1 - Nome do paciente " << std::endl;
  std::cout << "2 - CPF do paciente " << std::endl;
  std::cout << "3 - Data de nascimento " << std::endl;
  std::cout << "4 - Sexo " << std::endl;
  std::cout << "5 - Observação " << std::endl;
  std::cout << "6 - Telefone " << std::endl;

  std::cin >> campo;
  std::cout << std::endl;
  
  std::string novo;
  
  for (int i = 1; i < data.size(); i++)
  {
    //FAZ A VERIFICAÇÃO DE ID
    int id_linha = stoi(data[i][0]);
    
    if (id_linha == id)
    {
      verificar = true;
      switch (campo)
      {
      case 1:
        while(true){
          std::cout << "Digite o novo nome: " << std::endl;
          while(std::getline(std::cin, novo))
          {
            if(novo != "")
              break;
          }
          bool verifica_nome = false;
          std::regex re(R"(^[A-Za-záàâãéèêíïóôõöúçñÁÀÂÃÉÈÍÏÓÔÕÖÚÇÑ ]*$)");
          if (std::regex_match(novo, re)) {
            verifica_nome = true;
          } else {
            verifica_nome = false;
          }
          if(verifica_nome == true)
            break;
          else
            std::cout << "Nome inválido!" << std::endl;
        }
        
        data[i][1] = novo;
        break;
        
      case 2:
      
        while(true){
          std::cout << "Digite o novo cpf: " << std::endl;
          std::cin >> novo;
          //VERIFICA A QUANTIDADE DE DIGITOS E SE HÁ APENAS NUMEROS
          int aux=0;
          for(int i=0;novo[i]!='\0';i++){
            if(novo[i]<'0' || novo[i]>'9'){
              aux=0;
              break;
            }
            aux++;
          }
          if(aux==11)
            break;
          else
            std::cout<< "CPF inválido!" << std::endl;
        }
        data[i][2] = novo;
        break;
      
      case 3:
        while(true){
          bool validacao =true;
          std::cout << "Digite a nova Data: " << std::endl;
          std::cin >> novo;

          //Verifica por Regex se a data está no formato: dd/mm/yyyy
          std::regex re(R"(^(0?[1-9]|[21][0-9]|3[01])[\/\-](0?[1-9]|1[012])[\/\-]\d{4}$)");
          while(!std::regex_match(novo, re)) {
            std::cout << "Data inválida, digite a nova Data: " << std::endl;
            std::cin >> novo;
          }



          //Verifica se a data está valida
          std::string dia = split(novo, '/')[0];
          std::string mes = split(novo, '/')[1];
          std::string ano = split(novo, '/')[2]; 
          if(stoi(mes)==1 || stoi(mes)==3 || stoi(mes)==5 || stoi(mes)==7
          ||stoi(mes)==8 || stoi(mes)==10 ||stoi(mes)==12 ){
            if(stoi(dia)>31 || stoi(dia)<1)
              validacao =false;
          }
          else if(stoi(mes)==4 || stoi(mes)==6 || stoi(mes)==9 || stoi(mes)==11){
            if(stoi(dia)>30 || stoi(dia)<1)
              validacao =false;
          }
          else if(stoi(mes)==2){
            if(stoi(dia)>28 || stoi(dia)<1)
              validacao =false;
          }
          else
            validacao =false;
          if(stoi(ano)<1)
            validacao=false;
          if(validacao == true)
            break;
          else 
            std::cout << "Data inválida" << std::endl;
        }
        data[i][3] = novo;
        break;
        
      case 4:
        while(true){  
          std::cout << "Digite o novo Sexo: " << std::endl;
          std::cin >> novo;
          //VERIFICA SE DIGITOU M OU F
          if((novo[0] == 'M'  || novo[0] == 'F' || novo[0]=='m' || novo[0]=='f') && novo[1]=='\0'){
            if(novo[0]=='m' || novo[0]=='f')
              novo[0]=toupper(novo[0]);
            break;
          }
          else
            std::cout << "Sexo inválido" << std::endl;
        }
        data[i][4] = novo;
        break;

      case 5:
        
        std::cout << "Observação: " << std::endl;
        std::cin >> novo;
        data[i][5] = novo;
        break;

      case 6:
        
        while(true)
        {
          std::cout << "Digite o telefone do paciente: " << std::endl;
          std::cin >> novo;
          
          //VERIFICA SE HÁ SOMENTE NUMEROS
          bool verifica_digito = true;
          for(int i=0;novo[i]!='\0';i++){
            if(novo[i]<='0' || novo[i]>='9'){
              verifica_digito = false;
              break;
            }
          }
          if(verifica_digito == true)
            break;
          else
            std::cout << "Telfone inválido!" << std::endl;
        }
        data[i][6] = novo;
        break;
      case 7:
      while(true){
        std::cout << "Digite o número do leito do paciente: " << std::endl;
        std::cin >> novo;
        if(stoi(novo)>=0 && stoi(novo)<=Leito::exibir())
          break;
        else 
          std::cout << "Número do leito inválido!" << std::endl;
      }
      data[i][7] = novo;
      break;
      default:
        break;
      }

    } 

  }
  
  if (verificar == false)
  {
    std::cout <<"ID não existe" << std::endl;
  }

  arquivo_paciente.setConteudo(data);  
  return 0; 
}

int Paciente::consultar(int id)
{
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_paciente.getConteudo();
  bool verificar = false;
  
  for (int i = 1; i < data.size(); i++)
  {
    //FAZ A VERIFICAÇÃO DE ID
    int id_linha = stoi(data[i][0]);
    if (id_linha == id)
    {
      verificar = true;
      //IMPRIMIR TODAS AS COLUNAS
      for (int k = 0; k < data[0].size(); k++)
      {
        std::cout << data[0][k] << " ";
      }
      std::cout << std::endl;

      //IMPRIMIR O DADO DESEJADO
      for (int j = 0; j < data[i].size(); j++)
      {
        std::cout << data[i][j] << " ";
      }
      std::cout << std::endl;
      break;
      }
  }

    if (verificar == false)
    {
      std::cout << "ID não existe" << std::endl;
    }

    


  
  return 0;
  
}

int Paciente::remover(int id)
{
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_paciente.getConteudo();
  bool verificar = false;

  for (int i = 1; i < data.size(); i++)
  {
    int id_linha = stoi(data[i][0]);

    if (id_linha == id)
    {
      verificar = true;  
      data.erase(data.begin() + i, data.begin() + i + 1);

      std::cout << std::endl;
      break;
    }

  }

  if (verificar == false)
  {
    std::cout << "ID não existe" << std::endl;
  }
  

  arquivo_paciente.setConteudo(data);
  return 0;
}

int Paciente::getLenght()
{
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_paciente.getConteudo();

  int count = 0;
  //IMPRIMIR ARQUIVO TODO
  for (int i = 1; i < data.size(); i++)
  {
      if(stoi(data[i][7]) != -1) {
        count++;
      }
  }


  return count;
}
