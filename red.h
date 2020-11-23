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
    map<string,vector<int>> Tablaoriginal;
    map<string,vector<int>> Tabla;
    string fileName;
    int Num_nodos;
    int Num_enlaces;
    vector<int> costosNodo;
    vector<string> NombreNodos;
    map < string, int > conec_routers;
     map < string, int > conec_auxirouters;
     map < string, string > ruta;
public:
    red();
    void setFileName(const string &value);
    void iniciar_red();
    void cargar_costos();
    map<string, vector<int> > getTabla() const;
    map<string, vector<int> > getTablaoriginal() const;
    void setTablaoriginal(const map<string, vector<int> > &value);
    vector<string> getNombreNodos() const;
    void actualizar();
    void Imprimir_Red(map<string,vector<int>>);
};

#endif // RED_H
