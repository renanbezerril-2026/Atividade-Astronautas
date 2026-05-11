#ifndef PROCESSAMENTO_H
#define PROCESSAMENTO_H

#include <vector>
#include <string>
#include "Astronauta.h"
#include "Voo.h"

int achaAstronauta(std::vector<Astronauta>& astros, std::string cpf);
int achaVoo(std::vector<Voo>& voos, int codigo);

#endif