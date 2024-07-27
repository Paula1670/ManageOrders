#ifndef TADCOLA_H
#define TADCOLA_H
#define INCREMENTO 4
#include "TTipos.h"

using namespace std;

class cola
{
    TPedido *pedidos;
    int inicio, fin; //principio y fin de la cola
    int Tama; //Capacidad de la tabla
    int ne; //Nº de elementos
public:
    cola(); // constructor de la clase
    ~cola(); // destructor de la clase
    void encolar(TPedido p);
    void desencolar();
    bool esvacia();
    TPedido primero();
    int longitud();
    void vaciar();
    void clonar(cola &c);
};

#endif // TADCOLA_H
