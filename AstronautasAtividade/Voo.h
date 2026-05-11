#ifndef VOO_H
#define VOO_H

#include <string>
#include <vector>

class Voo {
public:
    int codigo;
    std::vector<std::string> cpfs_passageiros;
    std::string estado = "planejado"; 
};

#endif