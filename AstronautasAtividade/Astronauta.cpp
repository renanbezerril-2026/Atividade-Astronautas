#include <iostream>
#include <vector>
#include <string>
#include "Astronauta.h"
#include "Voo.h"

using namespace std;

int achaAstronauta(vector<Astronauta>& astros, string cpf) {
    for (int i = 0; i < (int)astros.size(); i++) {
        if (astros[i].cpf == cpf) {
            return i;
        }
    }
    return -1;
}

int achaVoo(vector<Voo>& voos, int codigo) {
    for (int i = 0; i < (int)voos.size(); i++) {
        if (voos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<Astronauta> astros;
    vector<Voo> voos;
    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        }

        if (comando == "CADASTRAR_ASTRONAUTA") {
            Astronauta a;
            cin >> a.cpf >> a.idade;
            getline(cin >> ws, a.nome);
            
            if (achaAstronauta(astros, a.cpf) != -1) {
                cout << "Erro: CPF ja cadastrado.\n";
            } else {
                astros.push_back(a);
                cout << "Astronauta cadastrado.\n";
            }
        }
        else if (comando == "CADASTRAR_VOO") {
            Voo v;
            cin >> v.codigo;
            
            if (achaVoo(voos, v.codigo) != -1) {
                cout << "Erro: Voo ja existe.\n";
            } else {
                voos.push_back(v);
                cout << "Voo cadastrado.\n";
            }
        }
        else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf; 
            int cod;
            cin >> cpf >> cod;
            
            int posAstro = achaAstronauta(astros, cpf);
            int posVoo = achaVoo(voos, cod);

            if (posAstro == -1 || posVoo == -1) {
                cout << "Erro: Astronauta ou voo nao encontrado.\n";
            } else if (voos[posVoo].estado != "planejado") {
                cout << "Erro: Voo nao esta na fase de planejamento.\n";
            } else if (astros[posAstro].vivo == false) {
                cout << "Erro: Astronauta morto.\n";
            } else {
                bool ja_adicionado = false;
                for (int i = 0; i < (int)voos[posVoo].cpfs_passageiros.size(); i++) {
                    if (voos[posVoo].cpfs_passageiros[i] == cpf) {
                        ja_adicionado = true;
                    }
                }
                
                if (ja_adicionado) {
                    cout << "Erro: Astronauta ja esta no voo.\n";
                } else {
                    voos[posVoo].cpfs_passageiros.push_back(cpf);
                    cout << "Astronauta adicionado.\n";
                }
            }
        }
        else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf; 
            int cod;
            cin >> cpf >> cod;
            
            int posVoo = achaVoo(voos, cod);

            if (achaAstronauta(astros, cpf) == -1 || posVoo == -1 || voos[posVoo].estado != "planejado") {
                cout << "Erro ao remover (dados invalidos ou voo nao planejado).\n";
            } else {
                bool achou = false;
                for (int i = 0; i < (int)voos[posVoo].cpfs_passageiros.size(); i++) {
                    if (voos[posVoo].cpfs_passageiros[i] == cpf) {
                        voos[posVoo].cpfs_passageiros.erase(voos[posVoo].cpfs_passageiros.begin() + i);
                        achou = true;
                        break;
                    }
                }
                if (achou) cout << "Astronauta removido do voo.\n";
                else cout << "Erro: Nao estava na lista deste voo.\n";
            }
        }
        else if (comando == "LANCAR_VOO") {
            int cod; 
            cin >> cod;
            int posVoo = achaVoo(voos, cod);

            if (posVoo == -1 || voos[posVoo].estado != "planejado" || (int)voos[posVoo].cpfs_passageiros.size() == 0) {
                cout << "Erro: Nao e possivel lancar este voo.\n";
            } else {
                bool todos_ok = true;
                for (int i = 0; i < (int)voos[posVoo].cpfs_passageiros.size(); i++) {
                    int posAstro = achaAstronauta(astros, voos[posVoo].cpfs_passageiros[i]);
                    if (astros[posAstro].vivo == false || astros[posAstro].disponivel == false) {
                        todos_ok = false;
                    }
                }

                if (todos_ok) {
                    voos[posVoo].estado = "em curso";
                    for (int i = 0; i < (int)voos[posVoo].cpfs_passageiros.size(); i++) {
                        int posAstro = achaAstronauta(astros, voos[posVoo].cpfs_passageiros[i]);
                        astros[posAstro].disponivel = false;
                        astros[posAstro].voos_participados.push_back(cod);
                    }
                    cout << "Voo lancado com sucesso.\n";
                } else {
                    cout << "Erro: Ha astronautas indisponiveis ou mortos no voo.\n";
                }
            }
        }
        else if (comando == "EXPLODIR_VOO") {
            int cod; 
            cin >> cod;
            int posVoo = achaVoo(voos, cod);

            if (posVoo == -1 || voos[posVoo].estado != "em curso") {
                cout << "Erro: Apenas voos em curso podem explodir.\n";
            } else {
                voos[posVoo].estado = "explosao";
                for (int i = 0; i < (int)voos[posVoo].cpfs_passageiros.size(); i++) {
                    int posAstro = achaAstronauta(astros, voos[posVoo].cpfs_passageiros[i]);
                    astros[posAstro].vivo = false;
                }
                cout << "Tragedia: Voo explodiu.\n";
            }
        }
        else if (comando == "FINALIZAR_VOO") {
            int cod; 
            cin >> cod;
            int posVoo = achaVoo(voos, cod);

            if (posVoo == -1 || voos[posVoo].estado != "em curso") {
                cout << "Erro ao finalizar voo.\n";
            } else {
                voos[posVoo].estado = "sucesso";
                for (int i = 0; i < (int)voos[posVoo].cpfs_passageiros.size(); i++) {
                    int posAstro = achaAstronauta(astros, voos[posVoo].cpfs_passageiros[i]);
                    astros[posAstro].disponivel = true;
                }
                cout << "Voo finalizado com sucesso.\n";
            }
        }
        else if (comando == "LISTAR_VOOS") {
            string lista_estados[] = {"planejado", "em curso", "sucesso", "explosao"};
            for (int e = 0; e < 4; e++) {
                for (int i = 0; i < (int)voos.size(); i++) {
                    if (voos[i].estado == lista_estados[e]) {
                        cout << "Voo " << voos[i].codigo << " | Astronautas: ";
                        for (int j = 0; j < (int)voos[i].cpfs_passageiros.size(); j++) {
                            int posAstro = achaAstronauta(astros, voos[i].cpfs_passageiros[j]);
                            cout << astros[posAstro].cpf << " (" << astros[posAstro].nome << ") ";
                        }
                        cout << endl;
                    }
                }
            }
        }
        else if (comando == "LISTAR_MORTOS") {
            cout << "--- Astronautas Mortos ---" << endl;
            for (int i = 0; i < (int)astros.size(); i++) {
                if (astros[i].vivo == false) {
                    cout << astros[i].cpf << " - " << astros[i].nome << " | Voos: ";
                    for (int j = 0; j < (int)astros[i].voos_participados.size(); j++) {
                        cout << astros[i].voos_participados[j] << " ";
                    }
                    cout << endl;
                }
            }
        }
    }

    return 0;
}