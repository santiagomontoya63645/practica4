#include "red.h"

void red::setFileName(const string &value)
{
    fileName = value;
}

red::red()
{

}
void red::iniciar_red(){
    ifstream archivo;
    archivo.open(fileName);
    if (!archivo.is_open()){
        cout<<endl;
        cout<<"la red no existe"<<endl;
    }
    else{
        cout<<"saludos perro"<<endl;
    }
}
