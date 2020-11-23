#include "router.h"

void router::setNodo(const map<string, vector<int> > &value)
{
    nodo = value;
}

void router::setNombre(const vector<string> &value)
{
    nombre = value;
}

router::router()
{

}
