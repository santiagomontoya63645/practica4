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
    string fileName;
    map<string,vector<int>> Tabla;
public:
    red();
    void setFileName(const string &value);
    void iniciar_red();
};

#endif // RED_H
