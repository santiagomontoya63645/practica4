#include "buscar.h"
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include "red.h"
int stringtoint(string numero)// transforma una cadena de numeros a un dato tipo int.
{
    int costo=0,multi=1;
    for (int i=numero.size()-1; i >= 0 ; i--)
    {
        costo=costo+((char)numero[i]-48)*multi;// toma cada digito y lo multiplica por 1,10,100 segun sea su posicion
        multi=multi*10;
    }
    return costo;
}

bool comprobar(string buscar,string caracter)//funcion creada para comparar el camino que se esta tomando y no devolverse,
//es buscar la posible ruta y en caracter el destino a la que apunta la nueva direccion, si ya esta en posible ruta lo unico que haria
// es devolverse, como no es lo que se desea entonces se crea esta funcion.
{
    bool esta=false;
    if (buscar.find(caracter) < buscar.size())//find cuando la encuentra devuelve su posicion, cuando no un numero aleatorio, mayor al tamaño
        //del string en el que se busco.
    {
        esta=true;
    }
    return esta;
}

bool compvector (const vector < string > &ruta, string palabra)//compara la posible ruta con las rutas ya tomadas, si es una nueva ruta
// devuelve false, pero si la ruta ya esta y como no se quiere volver a tomar devuelve true.
{
    bool respuesta=false;
    vector < string >::iterator pos;

    for (unsigned int i = 0 ; i < ruta.size() ; i++)//recorre el vector de rutas (tipo string).
    {
        if (palabra.compare(ruta[i]) == 0 )//compara el contenido de la posicion vector con la nueva ruta, en el caso de ser iguales
            //devuelve 0.
        {
            respuesta=true;
        }
    }
    return respuesta;
}
