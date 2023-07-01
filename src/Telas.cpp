#include "Telas.hpp"
#include "Entidades.hpp"
#include "Dominios.hpp"

#ifdef WIN32
    #include "curses.hpp"
#else
    #include <ncurses.h>
#endif  // WIN32

using namespace std;

void Tela::mostrarLinhas(vector<string> linhas, int linha, int coluna, int p) {
    for (pair<vector<string>::iterator, int> it(linhas.begin(), p); it.first != linhas.end(); ++it.first, it.second++) {
        mvprintw(linha / 2 - 4 + (2 * it.second), (coluna - it.first->length()) / 2, "%s", it.first->c_str());
    }
}

void Tela::mostrarLinhas(vector<string> linhas, int linha, int coluna) {
    mostrarLinhas(linhas, linha, coluna, 0);
}

string TelaMenu::apresentar(string titulo, vector<string> opcoes) {
    int linha, coluna;
    char dado[LIMITE_CHAR];
    string campo = "Selecione uma opcao: ";

    initscr();
    getmaxyx(stdscr, linha, coluna);
    mvprintw(linha / 2 - 6, (coluna - titulo.length()) / 2, "%s", titulo.c_str());
    mostrarLinhas(opcoes, linha, coluna);
    mvprintw(linha / 2 - 4 + 2 * (opcoes.size() + 1), (coluna - campo.length()) / 2, "%s", campo.c_str());
    getstr(dado);
    clear();
    endwin();

    return dado;
}

string TelaCampo::apresentar(string titulo, string campo) {
    int linha, coluna;
    char dado[LIMITE_CHAR];
    initscr();
    getmaxyx(stdscr, linha, coluna);
    
    mvprintw(linha/3,(coluna-strlen(campo.c_str()))/2,"%s", campo.c_str());
    getstr(dado);

    clear();
    endwin();

    return dado;
}


void TelaAutenticacao::apresentar(Desenvolvedor* desenvolvedor) {

    char campo1[]="Digite a matricula : ";
    char campo2[]="Digite a senha     : ";
    char dado1[80];
    char dado2[80];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2,(coluna-strlen(campo1))/2,"%s",campo1);
    getstr(dado1);
    mvprintw(linha/2 + 2,(coluna-strlen(campo2))/2,"%s",campo2);
    getstr(dado2);
    clear();
    endwin();

    Matricula matricula;
    matricula.setDado(dado1);

    Senha senha;
    senha.setDado(dado2);

    desenvolvedor->setMatricula(matricula);
    desenvolvedor->setSenha(senha);
}

void TelaFormulario::apresentar(string titulo, vector<string> campos, string * entradas) {
    int linha, coluna;
    char dado[LIMITE_CHAR];
    initscr();
    getmaxyx(stdscr, linha, coluna);
    mvprintw(linha / 2 - 6, (coluna - titulo.length()) / 2, "%s", titulo.c_str());
    for (pair<vector<string>::iterator, int> it(campos.begin(), 0); it.first != campos.end(); ++it.first, it.second++) {
        mvprintw(linha / 2 - 4 + (2 * it.second), (coluna - it.first->length()) / 2, "%s", it.first->c_str());
        getstr(dado);
        entradas[it.second] = dado;
    }
    clear();
    endwin();
}

void TelaMensagem::apresentar(string mensagem) {
    int linha, coluna;

    initscr();                                                                            // Iniciar curses.
    getmaxyx(stdscr, linha, coluna);                                                      // Armazenar quantidade de linhas e de colunas.
    mvprintw(linha / 2, (coluna - mensagem.length()) / 2, "%s", mensagem.c_str()); // Imprimir dado.
    noecho();                                                                             // Desabilitar eco.
    getch();                                                                              // Ler caracter digitado.
    echo();                                                                               // Habilitar eco.
    clear();
}

void TelaMensagens::apresentar(vector<string> mensagens) {
    int linha, coluna;

    initscr();                                                                          
    getmaxyx(stdscr, linha, coluna);                            
    
    mostrarLinhas(mensagens, linha, coluna);

    noecho();                                                                           
    getch();                                                                            
    echo();                                                                             
    clear();                                                                            
    endwin();
}

bool TelaConfirmarDescadastrar::apresentar() {
    string campo1 = "Deseja confimar o descadastramento? (S/N) ";
    char dado1[LIMITE_CHAR];
    bool confirmou;
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);
    while (true) {
        mvprintw(linha/2,(coluna-campo1.length())/2,"%s",campo1.c_str());
        getstr(dado1);
        if (dado1[0] == 's' || dado1[0] == 'S') {
            confirmou = true;
            break;
        }
        if (dado1[0] == 'n' || dado1[0] == 'N') {
            confirmou = false;
            break;
        }
        clear();
    }
    clear();
    endwin();

    return confirmou;
}

char TelaControle::apresentar() {

    char campo1[]="Seja bem-vindo";
    char campo2[]="1 - Acessar sistema.";
    char campo3[]="2 - Cadastrar usuario.";
    char campo4[]="3 - Sair.";
    char campo5[]="Selecione uma opcao: ";
    char dado1[10];
    int linha,coluna;

    initscr();
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2,"%s",campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2))/2,"%s",campo2);
    mvprintw(linha/2,(coluna-strlen(campo3))/2,"%s",campo3);
    mvprintw(linha/2 + 2,(coluna-strlen(campo4))/2,"%s",campo4);
    mvprintw(linha/2 + 4,(coluna-strlen(campo5))/2,"%s",campo5);
    getstr(dado1);
    clear();
    endwin();

    return dado1[0];
}

void TelaConsultarDesenvolvedor::apresentar(Desenvolvedor desenvolvedor) {
    char campo1[] ="Consultar Desenvolvedor";
    char campo2[]="Matricula: ";
    char campo3[]="Nome: ";
    char campo4[]="Senha: ";
    char campo5[]="Telefone: ";
    char campo6[]="Aperte qualquer tecla para retornar";

    string matricula = desenvolvedor.getMatricula().getDado();
    string nome = desenvolvedor.getNome().getDado();
    string senha = desenvolvedor.getSenha().getDado();
    string telefone = desenvolvedor.getTelefone().getDado();

    int linha,coluna;

    initscr();

    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2, campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2)-matricula.length())/2, "Matricula: %s", matricula.c_str());
    mvprintw(linha/2,(coluna-strlen(campo3)-nome.length())/2, "Nome: %s", nome.c_str());
    mvprintw(linha/2 + 2,(coluna-strlen(campo4)-senha.length())/2, "Senha: %s", senha.c_str());
    mvprintw(linha/2 + 4,(coluna-strlen(campo5)-telefone.length())/2, "Telefone: %s", telefone.c_str());
    mvprintw(linha/2 + 6,(coluna-strlen(campo6))/2, campo6);
    getch();
    clear();
    endwin();
}

void TelaConsultarTeste::apresentar(Teste teste) {
    char campo1[] ="Consultar Teste";
    char campo2[]="Codigo: ";
    char campo3[]="Nome: ";
    char campo4[]="Classe: ";
    char campo5[]="Aperte qualquer tecla para retornar";

    string codigo = teste.getCodigo().getDado();
    string nome = teste.getNome().getDado();
    string classe = teste.getClasse().getDado();

    int linha,coluna;

    initscr();
    
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2, campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2)-codigo.length())/2, "Codigo: %s", codigo.c_str());
    mvprintw(linha/2,(coluna-strlen(campo3)-nome.length())/2, "Nome: %s", nome.c_str());
    mvprintw(linha/2 + 2,(coluna-strlen(campo4)-classe.length())/2, "Classe: %s", classe.c_str());
    mvprintw(linha/2 + 4,(coluna-strlen(campo5))/2, campo5);
    getch();
    clear();
    endwin();
}

void TelaConsultarCasoDeTeste::apresentar(CasoDeTeste casoDeTeste) {
    char campo1[] ="Consultar Teste";
    char campo2[]="Codigo: ";
    char campo3[]="Nome: ";
    char campo4[]="Data: ";
    char campo5[]="Acao: ";
    char campo6[]="Resposta: ";
    char campo7[]="Resultado: ";
    char campo8[]="Aperte qualquer tecla para retornar";

    string codigo = casoDeTeste.getCodigo().getDado();
    string nome = casoDeTeste.getNome().getDado();
    string data = casoDeTeste.getData().getDado();
    string acao = casoDeTeste.getAcao().getDado();
    string resposta = casoDeTeste.getResposta().getDado();
    string resultado = casoDeTeste.getResultado().getDado();

    int linha,coluna;

    initscr();
    
    getmaxyx(stdscr,linha,coluna);

    mvprintw(linha/2 - 4,(coluna-strlen(campo1))/2, campo1);
    mvprintw(linha/2 - 2,(coluna-strlen(campo2)-codigo.length())/2, "Codigo: %s", codigo.c_str());
    mvprintw(linha/2,(coluna-strlen(campo3)-nome.length())/2, "Nome: %s", nome.c_str());
    mvprintw(linha/2 + 2,(coluna-strlen(campo4)-data.length())/2, "Data: %s", data.c_str());
    mvprintw(linha/2 + 4,(coluna-strlen(campo4)-acao.length())/2, "Acao: %s", acao.c_str());
    mvprintw(linha/2 + 6,(coluna-strlen(campo4)-resposta.length())/2, "Resposta: %s", resposta.c_str());
    mvprintw(linha/2 + 8,(coluna-strlen(campo4)-resultado.length())/2, "Resultado: %s", resultado.c_str());
    mvprintw(linha/2 + 12,(coluna-strlen(campo8))/2, campo8);

    getch();
    clear();
    endwin();
}

int TelaConsultarTestes::apresentar(vector<Teste> testes, bool select) {
    const string TITULO = "Testes";
    vector<string> DADOS;
    int index = 1;
    char dado1[LIMITE_CHAR];

    for (vector<Teste>::iterator it = testes.begin(); it != testes.end(); ++it) {
        DADOS.insert(DADOS.end(), "Nome: " + it->getNome().getDado());
        DADOS.insert(DADOS.end(), "ID: " + to_string(index));
        index += 1;
    }
    if (select)
        DADOS.insert(DADOS.end(), "Selecione uma opcao ou digite 0 para voltar: ");
    else
        DADOS.insert(DADOS.end(), "Digite 0 para voltar: ");
        
    int linha,coluna;

    initscr();

    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2 - 6,(coluna-TITULO.length())/2,"%s",TITULO.c_str());
    mostrarLinhas(DADOS, linha, coluna);

    getstr(dado1);

    clear();
    endwin();

    return stoi(dado1);
}


int TelaConsultarCasosDeTeste::apresentar(vector<CasoDeTeste> casosTeste, bool select) {
    const string TITULO = "Casos de teste";
    vector<string> DADOS;
    int index = 1;
    char dado1[LIMITE_CHAR];

    for (vector<CasoDeTeste>::iterator it = casosTeste.begin(); it != casosTeste.end(); ++it) {
        DADOS.insert(DADOS.end(), "Nome: " + it->getNome().getDado());
        DADOS.insert(DADOS.end(), "ID: " + to_string(index));
        index += 1;
    }
    if (select)
        DADOS.insert(DADOS.end(), "Selecione uma opcao ou digite 0 para voltar: ");
    else
        DADOS.insert(DADOS.end(), "Digite 0 para voltar: ");
    int linha,coluna;

    initscr();

    getmaxyx(stdscr,linha,coluna);
    mvprintw(linha/2 - 6,(coluna-TITULO.length())/2,"%s",TITULO.c_str());
    mostrarLinhas(DADOS, linha, coluna);

    getstr(dado1);

    clear();
    endwin();

    return stoi(dado1);
}