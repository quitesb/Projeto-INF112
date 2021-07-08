#include "Medico.h"
#include "Arquivo.h"
#include <regex>
#include <ctype.h>

Arquivo arquivo_medico("arquivo/medico.csv");

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

int Medico::listar() {
  std::vector<std::vector<std::string>> data = arquivo_medico.getConteudo();

  for(std::vector<std::string> line : data) {
       for(std::string colum : line) {
           std::cout << colum << " ";
       } 
       std::cout << std::endl;
    }
  return 0;
}

Medico::Medico()
{

} 

int Medico::cadastrar() 
{
  std::string nome,cpf,data_nascimento,sexo,crm,esp,disp;
  std::vector<std::string> auxiliar;

  std::vector<std::vector<std::string>> data = arquivo_medico.getConteudo();

  int id = stoi(data[data.size()-1][0]);
  

  while(true){
    std::cout << "Digite o nome do medico: " << std::endl;
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
    std::cout << "Digite o CPF do medico (Somente números): " << std::endl ;
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
  
 while(true){
    bool validacao =true;
    std::cout << "Digite a nova data (mm/dd/aaaa): " << std::endl;
    std::cin >> data_nascimento;

    //Verifica por Regex se a data está no formato: dd/mm/yyyy
    std::regex re(R"(^(0?[1-9]|[21][0-9]|3[01])[\/\-](0?[1-9]|1[012])[\/\-]\d{4}$)");
    while(!std::regex_match(data_nascimento, re)) {
      std::cout << "Data inválida, digite a nova Data: " << std::endl;
      std::cin >> data_nascimento;
    }



    //Verifica se a data está valida
    std::string dia = split(data_nascimento, '/')[0];
    std::string mes = split(data_nascimento, '/')[1];
    std::string ano = split(data_nascimento, '/')[2]; 
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
  while(true){
    std::cout << "Digite o sexo (M/F): " << std::endl ;
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

  std::cout << "Digite a especialidade do medico: " << std::endl;

  while (std::getline(std::cin, esp))
  {
    if (esp != "")
      break;
  }

 while(true){
    std::cout << "Digite a disponibilidade do medico (S/N): " << std::endl ;
    std::cin >> disp;

    //VERIFICA SE DIGITOU M OU F
    if((disp[0]== 'S'  || disp[0] == 'N' || disp[0]=='s' || disp[0]=='n') && disp[1]=='\0'){
      if(disp[0]=='s' || disp[0]=='n')
        disp[0]=toupper(disp[0]);
      break;
    }
    else
      std::cout << "Sexo inválido" << std::endl;
  }


  auxiliar.push_back(std::to_string(++id));
  auxiliar.push_back(nome);
  auxiliar.push_back(cpf);
  auxiliar.push_back(data_nascimento);
  auxiliar.push_back(sexo);
  auxiliar.push_back(crm);
  auxiliar.push_back(esp);
  auxiliar.push_back(disp);
  
  data.push_back(auxiliar);

  arquivo_medico.setConteudo(data);  
  return 0;
}

int Medico::alterar(int id) {
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_medico.getConteudo();

  int campo = -1;
  std::string novo;
  bool verificar = false;

  std::cout << "Digite o digito do campo que você deseja alterar:" << std::endl;
  std::cout << "1 - Nome" << std::endl;
  std::cout << "2 - CPF" << std::endl;
  std::cout << "3 - Data" << std::endl;
  std::cout << "4 - Sexo" << std::endl;
  std::cout << "5 - CRM" << std::endl;
  std::cout << "6 - Especialidade" << std::endl;
  std::cout << "7 - Disponibilidade" << std::endl;

  std::cin >> campo;
  std::cout << std::endl;
  
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
          bool verifica = false;
          std::regex re(R"(^[A-Za-záàâãéèêíïóôõöúçñÁÀÂÃÉÈÍÏÓÔÕÖÚÇÑ ]*$)");
          if (std::regex_match(novo, re)) {
            verifica = true;
          } else {
            verifica = false;
          }
          if(verifica == true)
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
        
        std::cout << "Digite o novo CRM: " << std::endl;
        std::cin >> novo;
        data[i][5] = novo;
        break;

      case 6:
        
        std::cout << "Digite a  Especialidade: " << std::endl;
        std::cin >> novo;
        data[i][6] = novo;
        break;

      case 7:
        while(true){
          std::cout << "Digite a  Disponibilidade: " << std::endl;
          std::cin >> novo;
          //VERIFICA SE DIGITOU S OU N
          if((novo[0]== 'S'  || novo[0] == 'N' || novo[0]=='s' || novo[0]=='n') && novo[1]=='\0'){
            if(novo[0]=='s' || novo[0]=='n')
              novo[0]=toupper(novo[0]);
            break;
          }
          else
            std::cout << "Disponibilidade inválida" << std::endl;
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
    std::cout << "ID não existe" << std::endl;
  }
  
  arquivo_medico.setConteudo(data);  
  return 0; 
}

int Medico::consultar(int id) {
   //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_medico.getConteudo();

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

int Medico::remover(int id) {
  //JOGAR ARQUIVO NA MATRIZ
  std::vector<std::vector<std::string>> data = arquivo_medico.getConteudo();

  bool verificar = false;
  for (int i = 1; i < data.size(); i++)
  {
    //FAZ A VERIFICAÇÃO DE ID
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
  
  arquivo_medico.setConteudo(data);

  return 0;
  
}


