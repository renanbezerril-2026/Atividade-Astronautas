#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <string>
#include <vector>

class Astronauta {
public:
    std::string cpf;
    std::string nome;
    int idade;
    bool vivo = true;
    bool disponivel = true;
    std::vector<int> voos_participados;
};

#endif