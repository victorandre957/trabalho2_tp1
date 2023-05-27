#include "Dominios.hpp"
#include "TestesUnitarios.hpp"

#include <iostream>

using namespace std;

int main() {
    TestClasse t_u_classe;
    cout << "Teste Unitario de Classe: ";
    if (t_u_classe.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;

    TestCodigo t_u_codigo;
    cout << "Teste Unitario de Codigo: ";
    if (t_u_codigo.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;

    TestData t_u_data;
    cout << "Teste Unitario de Data: ";
    if (t_u_data.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;
    
    TestMatricula t_u_matricula;
    cout << "Teste Unitario de Matricula: ";
    if (t_u_matricula.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;

    TestResultado t_u_resultado;
    cout << "Teste Unitario de Resultado: ";
    if (t_u_resultado.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;
    
    TestSenha t_u_senha;
    cout << "Teste Unitario de Senha: ";
    if (t_u_senha.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;

    TestTelefone t_u_telefone;
    cout << "Teste Unitario de Telefone: ";
    if (t_u_telefone.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;

    TestTexto t_u_texto;
    cout << "Teste Unitario de Texto: ";
    if (t_u_texto.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;

    TestDesenvolvedor t_u_desenvolvedor;
    cout << "Teste Unitario de desenvolvedor: ";
    if (t_u_desenvolvedor.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;
    
    TestTeste t_u_teste;
    cout << "Teste Unitario de teste: ";
    if (t_u_teste.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;
    
    TestCasoDeTeste t_u_caso_de_teste;
    cout << "Teste Unitario de Caso de Teste: ";
    if (t_u_caso_de_teste.run())
        cout << "\tSUCESSO." << endl;
    else
        cout << "\tFRACASSO" << endl;
}
