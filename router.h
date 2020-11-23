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
public:
    router();
    void setNodo(const map<string, vector<int> > &value);
    void setNombre(const vector<string> &value);
};

#endif // ROUTER_H
