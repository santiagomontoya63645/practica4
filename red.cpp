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
        for (int j=0;j<Num_enlaces;j++){ //itera el numero de conexiones existentes
            getline(archivo,linea2);       //linea por linea
            Sublinea1=linea2[0];      //primera letra
            Sublinea2=linea2[1];      //segunda letra
            costosNodo = Tabla.find(Sublinea1)->second;   //copiamos los costos
            vectorauxi= Tabla.find(Sublinea2)->second;   //copiamos los costos
            Sublinea3=linea2[2];      //costo
            costo=Sublinea3[0]-48;
            if (linea2.length()>3) {
                Sublinea3+=linea2[3];
                costo=costo*10+(Sublinea3[1]-48);    //conversion a entero
            }

            for (int p=0;p<Num_nodos;p++) {
                if(Sublinea1==NombreNodos[p]){
                    pos1=posaux1;
                }
                if(Sublinea2==NombreNodos[p]){       //guarda la posicion del enlace
                    pos2=posaux2;
                }
                posaux1++;
                posaux2++;
            }
            costosNodo[pos2]=costo;  // posicion del enlace para saber la posicio del costo del el nodo con este enlace
            vectorauxi[pos1]=costo;  // posicion del enlace para saber la posicio del costo del el nodo con este enlace                                             //SI las letras son minusculas cambiar 65 po 97
            Tabla[Sublinea1]=costosNodo; //costos de xy
            Tabla[Sublinea2]=vectorauxi; //costos de yx
            conec_auxirouters[Sublinea1+Sublinea2]=costo;  //conexion entre xy
            conec_auxirouters[Sublinea2+Sublinea1]=costo;  //conexion entre yx
            posaux1=0;
            posaux2=0;
        }
    archivo.close();
    }
}
