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
            if(ver==2) topologia.tabla_router(topologia.getTablaoriginal());
            cout << "-para VISUALIZAR el menu ingrese 0: "<<endl<<endl;
        }
        else if (opcion==2) {
            topologia.tabla_router(topologia.getTabla());
            cout<<"para voliver al menu ingrese 0: ";
        }
        else if(opcion==3){
            bool flag=true;
            int ir,decision;
            cout<<"Desea modificar costos ya existentes, ya sea modificar su costo o iliminar"<<endl<< "las conexion ingrese 1."<<endl;
            cout<<"Desea conectar routers ingrese 2."<<endl;
            cin>>ir;
            if(ir==1){
                while(flag==true){
                    cout<<"NOTA: si desea modificar la conexion ingrese un #>0 y si desa eliminarla"<<endl<<" ingrese como valor -1"<<endl;
                    nodo.ActualizarCostos(topologia.getConec_auxirouters(),ir);
                    topologia.setTablaoriginal(nodo.getNodo());//esta linea y la siguente atualizan la red con el costo modificado
                    topologia.modificar_enlaces(nodo.getCambiar_costo(),nodo.getCambiar_costoinvt(),nodo.getCosto_modificado(),ir);
                    cout<<"Desea actualizar otro costo?"<<endl;
                    cout<<"1.Si"<<endl<<"2.No"<<endl;
                    cin>>decision;
                    if(decision==1)
                        flag;
                    else {
                        flag=false;
                    }
                }
            }
            if(ir==2){
                //conectar routers
                nodo.ActualizarCostos(topologia.getConec_auxirouters(),ir);
                topologia.setTablaoriginal(nodo.getNodo());//esta linea y la siguente atualizan la red con el costo modificado
                topologia.modificar_enlaces(nodo.getCambiar_costo(),nodo.getCambiar_costoinvt(),nodo.getCosto_modificado(),ir);
            }
            cout<<"para volver al menu ingrese 0: ";
        }
        else if(opcion==4) {
            topologia.Imprimir_Red(topologia.getTabla());
            cout<<endl;
            cout<<"para volver al menu ingrese 0: ";
        }
        else if (opcion==5) {
            int ver=0;
            cout << "Desea saber la mejor ruta entre dos routers?. Ingrese 1." << endl;
            cout << "Desea saber el costo de envio (MAS EFICIENTE) entre dos routers?. Ingrese 2." << endl;
            cin >> ver;
            if(ver==1){
                topologia.mejor_camino();
            }
            if(ver==2){
                topologia.costo_puntual();
            }
            cout<<endl;
            cout<<"para volver al menu ingrese 0: ";
        }
        if (opcion==6){
            int opc=0;
            cout<<"si desea agrgar routers ingrese 1: "<<endl;
            cout<<"si desea eliminar routers ingrese2: "<<endl;
            cin>>opc;
            if(opc==1){
                topologia.agregar_routers();
                topologia.setTabla(topologia.getTablaoriginal()); //se atualizala red
                nodo.setNodo(topologia.getTablaoriginal());
                nodo.setNombre(topologia.getNombreNodos());
            }
            if(opc==2){
                topologia.eliminar_routers();
                topologia.setTabla(topologia.getTablaoriginal()); //se atualizala red
                nodo.setNodo(topologia.getTablaoriginal());
                nodo.setNombre(topologia.getNombreNodos());
            }
            cout<<"para voliver al menu ingrese 0: ";
        }
        else if(opcion==7){
            bandera=false;
        }
    }

    return 0;
}
