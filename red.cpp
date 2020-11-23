#include "red.h"
#include "buscar.h"

void red::setFileName(const string &value)
{
    fileName = value;
}

map<string, vector<int> > red::getTabla() const
{
    return Tabla;
}

map<string, vector<int> > red::getTablaoriginal() const
{
    return Tablaoriginal;
}

void red::setTablaoriginal(const map<string, vector<int> > &value)
{
    Tablaoriginal = value;
}

vector<string> red::getNombreNodos() const
{
    return NombreNodos;
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
void red::actualizar()
{
    //actualiza la tabla de cada en router, sacando el mejor camino en general teniendo en cuenta su mejor costo.
    vector < string > rutas;     // se crea un vector temporal de rutas para ir comparando y tomar siempre rutas diferentes.
    map < string, string > ruta_auxi;
    ruta=ruta_auxi;               //se vacia las rutas para volver a recalcular los caminos.
    conec_routers=conec_auxirouters; //volover a atualizar la red se la si las conexiones auxiliares de los routers fueron modificados
    string origen,destino,posicion,posibleruta,par,alrevez;// se inicializan las variables a utilizar.
    int costoparcial=0;//donde se hace la suma de cada camino y se compara luego para saber cual es optimo.
    unsigned int dest= 0;// se inicializa la variable que recorrera los nombres de los routers mas adelante.

    for (unsigned int i = 0 ; i< NombreNodos.size() ; i++)// toma el origen (cada posicion del vector nombres se toma como un origen).
    {
        origen=NombreNodos[i];

        for( unsigned int ii=0 ; ii < NombreNodos.size() ; ii++)// se toma un destino ejm a-a , a-b , a-c , a-d , etc.
        {
            destino= NombreNodos[ii];

            if(origen.compare(destino)==false)//mira si la conexion es hacia el mismo router
            {
                //si es el mismo router no se hace nada
            }
            else
            {
                while(true)//ciclo infinito para verificar todos los posibles caminos.


                {
                    posicion = origen;// posicion que siempre va ir variando dependiendo la ruta que se este eligiendo

                    posibleruta = origen;// la posible ruta siempre empieza desde el origen hacia el destino ejm a-p, el origen, siempre empieza desde a.

                    alrevez=origen;// para guardar la posible ruta de a-c y de c-a, se guarda cada paso pero en reversa.

                    for ( dest= 0 ; dest < NombreNodos.size() ;  )
                        // recorre cada nombre de router para verificar si tiene una conexion o no.
                    {

                        par=posicion+NombreNodos[dest];//siempre se toma un nodo , si origen es A y destino F,
                        //y la ruta es ABCDEF, se tomara AB, despues BC... por utlimo EF.

                        if(destino.compare(NombreNodos[dest])==false && compvector( rutas , (posibleruta+NombreNodos[dest]) ) == false && conec_routers[par]!= 0 ) //la ultima comparacion es que exista ese conexion

                            //Destino=F y nombre[dest] tambien es F, se comprueba que esa posible ruta
                            //no se haya tomado antes (compvector) y que el ultimo nodo exista, osea que tenga un valor diferente de cero.

                        {
                            costoparcial=costoparcial + conec_routers[par]; // se actualiza el costo parcial con el valor de cada nodo hasta llegar al destino.

                            posibleruta=posibleruta+NombreNodos[dest];//se guarda el paso dado a la ruta posible (como se toma por nodos se agrega siempre el segundo termino)
                            // BC se guarda la C para que la nueva ruta posible sea ABC.

                            alrevez=NombreNodos[dest] + alrevez;// se guarda la posible ruta de reversa.

                            if(conec_routers[origen+destino]==0 )//si la conexion no existia, osea que es igual cero en mi caso -1 y no no coloco las conexiones entre los mismo nodos


                            {
                                conec_routers[origen+destino]=costoparcial;// se actualiza su costo de forma normal AF

                                conec_routers[destino+origen]=costoparcial;// y de reversa FA

                                ruta[origen+destino]=posibleruta;//se guardan las posible ruta optima con clave AF y FA.

                                ruta[destino+origen]=alrevez;
                            }
                            else if(conec_routers[origen+destino]>costoparcial)
                                // si la ruta ya existe, se comprueba que el costo sea menor.
                            {
                                // se hace lo mismo que en el if pasado.
                                conec_routers[origen+destino]=costoparcial;

                                conec_routers[destino+origen]=costoparcial;

                                ruta[origen+destino]=posibleruta; // la poisible ruta en este caso de ab, ruta es un map de string

                                ruta[destino+origen]=alrevez;     //si se guardo la ruta de ab entoces se guarda la de de ba
                            }

                            //se reinician los valores para buscar una nueva posible ruta y ademas, se agrega la nueva ruta para no ser repetida.
                            costoparcial=0;

                            rutas.push_back(posibleruta);

                            posibleruta="";
                            alrevez="";


                            break;// se sale del ciclo for para que entre otra vez pero buscando una nueva ruta.
                        }



                        else if(conec_routers[par] != 0 && comprobar( posibleruta , NombreNodos[dest] ) == false && compvector( rutas , (posibleruta+NombreNodos[dest]) ) == false)
                        {

                            //Que no tome un camino ya usado (comprobar), ademas si toma ese nodo, esa posible ruta no se haya tomado antes (compvector).

                            posicion=NombreNodos[dest];// se actualiza la posicion del nodo ABD posicion=D y se busca un DA,DB, DC ...
                            //hasta que no se oponga y no se haya tomado en cuenta antes.

                            costoparcial=costoparcial+conec_routers[par];//se va actualizando el costo parcial conforme avanza los nodos.

                            posibleruta=posibleruta+NombreNodos[dest]; // se va agregando la siguiente posicion a la posible ruta , Ab.

                            alrevez= NombreNodos[dest] + alrevez;// siempre se tiene en cuenta la posible ruta al revez.

                            dest=0;// se vuelven a recorrer los nombres de los routers en el vector nombres desde la posicion cero.
                        }
                        else{ dest++;}// siempre se va moviendo de posicion siempre y cuando no se haya encontrado un nuevo nodo o se haya llegado al destino.

                    }
                    if (dest == NombreNodos.size())// cuando se acaba el ciclo for y no se encontro una posible ruta (camino sin salida)
                    {
                        if (posibleruta.compare(origen)==false)// todas las conexiones ya se tomaron desde el origen entonces se sale del while
                            //para buscar una nueva direccion. ejm a-b , a-d y ya se tomaron esas dos entonces la que queda es AA pero como no nos sirve, entonces:
                        {
                            // se reinicia las rutas ya tomadas (rutas), la posible ruta , alrevez y costo parcial para empezar a buscar una nueva direccion.
                            rutas.clear();
                            posibleruta="";
                            alrevez="";
                            costoparcial=0;
                            break;
                        }
                        else// si solo acabo el ciclo for pero no esta parado en AA entonces agrega la ruta que nos sirve y reinicia los valores para buscar una diferente.
                        {
                            rutas.push_back(posibleruta);
                            posibleruta="";
                            alrevez="";
                            costoparcial=0;
                        }
                    }
                }
            }

        }
    }
    for (int i = 0; i < NombreNodos.size() ; ++i) {   //atualiazar topologia
        for ( int j=0; j <NombreNodos.size(); j++) {
            costosNodo[j]=conec_routers[NombreNodos[i]+NombreNodos[j]];
        }
        Tabla[NombreNodos[i]]=costosNodo;
    }
}
void red::Imprimir_Red(map<string,vector<int>> Tabla)
{
    cout<<"\t"; //tabulador
    for (auto it =Tabla.begin(); it != Tabla.end(); ++it) {   //iterador que recorre el tablero
        cout<<it->first<<"\t";    //imprime la clave del tablero
    }
    cout<<"\n";

    for (auto it = Tabla.begin(); it != Tabla.end(); ++it) {  //iterador que recorre el tablero
        cout<<it->first<<"\t"; //imprime la clave del tablero
        for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) { //iterador que toma los valores de nodo atraves de it que y a la ves el map nodo son los  valores son del diccionario tabla
                cout<<*jt<<"\t";        //imprimo el valor de nodo
            }

        cout<<endl;

    }
}
