#include <iostream>
#include "red.h"
#include "router.h"
using namespace std;

int main()
{
    red topologia;
    router nodo;
    string Namefile;
    string cosa="../practica4/";
    int opcion=0;
    bool bandera=true;

    cout<<"Ingrese el nombre con el que esta guardado la red: ";
    cin>>Namefile;
    Namefile=cosa+Namefile;
    topologia.setFileName(Namefile);
    topologia.iniciar_red();
    topologia.cargar_costos();
    topologia.setTablaoriginal(topologia.getTabla());
    nodo.setNodo(topologia.getTabla());
    nodo.setNombre(topologia.getNombreNodos());
    opcion=0;
    while(bandera){
        switch (opcion) {
        case 0:
            cout << endl << endl;
            cout << "-Desea ver la tabla de enrutamiento general de la red o de un router especifico?. Ingrese 1"<<endl<<endl;
            cout << "-Desea ver la tabla de enrutamiento atualizada de cada router?. Ingrese 2" <<endl<<endl;
            cout << "-Desea modificar costos ya existentes o conectar routers?. Ingrese 3" <<endl<<endl;
            cout << "-Desea ver la tabla de enrutamiendo general  atualiza con 'los mejores caminos'?. Ingrese 4" <<endl<<endl;
            cout << "-Desea saber la 'mejor ruta' entre dos routers o su costo?. Ingrese 5"<<endl<<endl;
            cout << "-Desea agregar/eliminar routers?. Ingrese 6" <<endl<<endl;
            cout << "-para VISUALIZAR el menu ingrese 0: "<<endl<<endl;
            cout << "-Desea salir del menu?. Ingrese 7. " <<endl<<endl;
            break;
        default:
            break;
        }
        topologia.actualizar();
        cin >> opcion;
        if(opcion==1){
            int ver=0;
            cout<<"para ver la tabla de la red ingrese 1: "<<endl;
            cout<< "para ver la tabla de un router ingrese 2: "<<endl;
            cin>>ver;
            if(ver==1) topologia.Imprimir_Red(topologia.getTablaoriginal());
        }
    }
    return 0;
}
