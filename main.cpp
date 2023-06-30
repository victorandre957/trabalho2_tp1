#include <string.h>
#include <stdexcept>

#include "Interfaces.hpp"
#include "Controladoras.hpp"
#include "Builders.hpp"

using namespace std;

int main() {

    BuilderSistema* builder;
    builder = new BuilderSistema();

    CntrApresentacaoPrincipal* cntrApresentacaoControle;
    cntrApresentacaoControle = builder->construir();

    cntrApresentacaoControle->executar();
    
    delete builder;

    return 0;
}
