#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class router
{
private:
    map<string,vector<int>> nodo;
    vector<string> nombre;
    int costo_modificado;
    string cambiar_costo, cambiar_costoinvt;

public:
    router();
    void setNodo(const map<string, vector<int> > &value);
    void setNombre(const vector<string> &value);
    void ActualizarCostos(map < string, int >,int );
    map<string, vector<int> > getNodo() const;
    string getCambiar_costo() const;
    string getCambiar_costoinvt() const;
    int getCosto_modificado() const;
};

#endif // ROUTER_H
