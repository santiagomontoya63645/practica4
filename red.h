#ifndef RED_H
#define RED_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
class red
{
private:
    map<string,vector<int>> Tabla;
    string fileName;
    int Num_nodos;
    int Num_enlaces;
    vector<int> costosNodo;
    vector<string> NombreNodos;
public:
    red();
    void setFileName(const string &value);
    void iniciar_red();
    void cargar_costos();
    map<string, vector<int> > getTabla() const;
};

#endif // RED_H
