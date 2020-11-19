#include "red.h"

void red::setFileName(const string &value)
{
    fileName = value;
}

map<string, vector<int> > red::getTabla() const
{
    return Tabla;
}

red::red()
{

}
void red::iniciar_red(){
    ifstream archivo;
    Num_nodos=0;
    Num_enlaces=0;
    string linea,linea2,Sublinea,Sublinea2;
    archivo.open(fileName);
    if (!archivo.is_open()){
        cout<<endl;
        cout<<"la red no existe"<<endl;
    }
    while (!archivo.eof())
    {
            getline(archivo,linea);
            for (int k=0;k<2;k++) {
                costosNodo.push_back(-1);  //no se saben los costos
                Sublinea=linea[k];
                if(Tabla.find(Sublinea) == Tabla.end()){
                    Tabla[Sublinea]=costosNodo;  //se inicializala RED pero no se cono ce el numero de enlaces
                    costosNodo.clear();
                    Num_nodos++;
                   }
                Num_enlaces++;
            }
    }
    archivo.close();
}
void red::cargar_costos()
{
    fstream archivo;
    vector <int> vectorauxi;
    string letra,linea2,Sublinea1,Sublinea2,Sublinea3;
    int costo=0,pos1=0,pos2=0,posaux1=0,posaux2=0;
    archivo.open(fileName,ios::in);
    if (!archivo.is_open()){
        cout<<endl;
        cout<<"la red no existe"<<endl;
    }
    while (!archivo.eof())
    {
        for (int i=0;i<Num_nodos;i++) {  //itera el numero de routers existentes
            costosNodo.clear();
            for (auto jt=Tabla.begin(); jt != Tabla.end(); jt++) {
                costosNodo.push_back(-1);
                if(i==0){
                    NombreNodos.push_back(jt->first); //una sola iteracion
                }
            }
            letra=NombreNodos[i];
            costosNodo[i]=0;         //el costo de comunicacion entre el mismo router es cero
            Tabla[letra]=costosNodo;        //inicializacion del la RED con sus cantidad total de en laces
        }

    }
}
