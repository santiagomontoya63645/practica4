#include <iostream>
#include "red.h"
using namespace std;

int main()
{
    red topologia;
    string Namefile;
    string cosa="../practica4/";

    cout<<"Ingrese el nombre con el que esta guardado la red: ";
    cin>>Namefile;
    Namefile=cosa+Namefile;
    topologia.setFileName(Namefile);
    topologia.iniciar_red();
    return 0;
}
