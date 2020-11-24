#include "router.h"

void router::setNodo(const map<string, vector<int> > &value)
{
    nodo = value;
}

void router::setNombre(const vector<string> &value)
{
    nombre = value;
}

map<string, vector<int> > router::getNodo() const
{
    return nodo;
}

string router::getCambiar_costo() const
{
    return cambiar_costo;
}

string router::getCambiar_costoinvt() const
{
    return cambiar_costoinvt;
}

int router::getCosto_modificado() const
{
    return costo_modificado;
}

router::router()
{

}
void router::ActualizarCostos(map < string, int > conec_auxirouters, int opcion)
{
    string letra1,letra2;
    vector<int> Vcostos;
    vector<int> VcostosAux;
    cout<<"nodo a modificar o a conectar: ";
    cin>>letra1;

    if(nodo.find(letra1)!= nodo.end()){
        Vcostos = nodo.find(letra1)->second;   //modificamos los costos del no ingresado
        cout<<"Ingrese el nombre del enlace que desea modificar o conectar: ";
        cin>>letra2;
        if(opcion==1){
            if(conec_auxirouters.find(letra1+letra2) != conec_auxirouters.end()){
                opcion=2;
            }
            else{
                   cout<<"No hay conexion directa entre los routers, porfavor agregue primero la conexion "<<endl;
               }

        }
        if(opcion==2 && nodo.find(letra2)!= nodo.end()){
            cout<<"Ingrese nuevo costo: ";
            cin>>costo_modificado;
            cambiar_costo=letra1+letra2;
            cambiar_costoinvt=letra2+letra1;
            for (int k=0;k<Vcostos.size();k++) {
                if(nombre[k]==letra2){
                    VcostosAux.push_back(costo_modificado); //se agrga el nuevo costo
                }
                else {
                    VcostosAux.push_back(Vcostos[k]);  //de lo contrario se conserva el costo actual
                }
            }
            nodo[letra1]=VcostosAux;
            VcostosAux.clear();

        if(nodo.find(letra2)!= nodo.end()){
            Vcostos = nodo.find(letra2)->second;
            for (int k=0;k<Vcostos.size();k++) {
                if(nombre[k]==letra1){
                    VcostosAux.push_back(costo_modificado);
                }
                else {
                    VcostosAux.push_back(Vcostos[k]);
                }
            }
            nodo[letra2]=VcostosAux;
        }
        }
        else {
            cout<<endl;
            cout<<"enlace no existe"<<endl;
        }
    }
    else {
        cout<<endl;
        cout<<"nodo NO existe"<<endl<<endl;
    }
}
