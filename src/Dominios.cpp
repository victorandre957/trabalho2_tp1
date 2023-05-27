#include "Dominios.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include <unordered_set>
#include <regex>

using namespace std;

void Dominio::setDado(string dado) {
    validar(dado);
    this->dado = dado;
};

void Classe::validar(string dado) {

    unordered_set<string> opcoes = {
        "UNIDADE", 
        "INTEGRACAO", 
        "FUMACA", 
        "SISTEMA", 
        "REGRESSAO", 
        "ACEITACAO"
    };

    if (opcoes.count(dado) == 0) {
        throw invalid_argument("Opção inválida.");
    }
};

void Codigo::validar(string dado) {
    if (dado.length() != 6) {
        throw invalid_argument("Código com tamanho inválido.");
    }
    
    for (int i = 0; i < 3; i++) {
        char c = dado[i];
        if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')) {
            throw invalid_argument("Os 3 primeiros caracteres devem ser letras maiúsculas ou minúsculas.");
        }
    }
    
    for (int i = 3; i < 6; i++) {
        char c = dado[i];
        if (!(c >= '0' && c <= '9')) {
            throw invalid_argument("Os 3 últimos caracteres devem ser um número de 0 a 9.");
        }
    }
};

void Data::validar(string dado) {

    map<string, int> meses = {{"JAN", 1}, {"FEV", 2}, {"MAR", 3}, {"ABR", 4}, {"MAI", 5}, {"JUN", 6},
    {"JUL", 7}, {"AGO", 8}, {"SET", 9}, {"OUT", 10}, {"NOV", 11}, {"DEZ", 12}};

    if (dado.length() != 11) {
        throw invalid_argument("Data com tamanho inválido.");
    }
    
    int dia = stoi(dado.substr(0, 2));
    string mesStr = dado.substr(3, 3);
    int ano = stoi(dado.substr(7, 4));
    
    if (dia < 1 || dia > 31) {
        throw invalid_argument("Dia inválido.");
    }
    
    auto it = meses.find(mesStr);
    if (it == meses.end()) {
        throw invalid_argument("Mês inválido.");
    }
    int mes = it->second;
    
    if (ano < 2000 || ano > 2999) {
        throw invalid_argument("Ano inválido.");
    }

    bool ehBissexto = (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0;
    
    if ((mes == 2 && ehBissexto && dia > 29) || (mes == 2 && !ehBissexto && dia > 28)
        || ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
        || ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && dia > 31)) {
        throw invalid_argument("Dia inválido para o mês correspondente.");
    }
};

void Matricula::validar(string dado) {
    if (dado.length() != 10) {
        throw invalid_argument("Número com quantidade de dígitos inválida.");
    }
    
    int soma = 0;
    int tamanho = dado.length();
    int multiplicador = 2;
    
    for (int i = tamanho - 1; i >= 0; i--) {
        int digito = dado[i] - '0';
        int resultado = digito * multiplicador;
        multiplicador = (multiplicador == 2) ? 1 : 2;
        
        if (resultado >= 10) {
            resultado = (resultado % 10) + (resultado / 10);
        }
        
        soma += resultado;
    }
    
    int resto = soma % 10;
    int digitoVerificador = (resto == 0) ? 0 : 10 - resto;
    
    if (digitoVerificador != (dado[tamanho - 1] - '0')) {
        throw invalid_argument("Dígito verificador inválido.");
    }
};

void Resultado:: validar(string dado){
    unordered_set<string> resultados = {
        "APROVADO", 
        "REPROVADO"
    };
    if (resultados.count(dado) == 0) {
        throw invalid_argument("Opção inválida.");
    }
    
};

void Senha::validar(string dado){
    regex pattern(R"((?!.*(.).*\1)^[A-Za-z0-9@$#\$%&]{6})");

    if (!regex_match(dado, pattern)){
        throw invalid_argument("Senha inválida.");
    }
};

void Telefone::validar(string dado){
    regex pattern("\\+\\d{7,15}"); 

    if(!regex_match(dado, pattern)){
        throw invalid_argument("Número inválido.");
    }
};

void Texto::validar(string dado){
    
    regex pattern("^(?=.{10,20}$)[a-zA-Z0-9.,;?!:\\-@#$%&]*(\\s+[a-zA-Z0-9.,;?!:\\-@#$%&]+)*\\s*$");

    if (!regex_match(dado, pattern)){
        throw invalid_argument("Texto inválido.");
    }
}
