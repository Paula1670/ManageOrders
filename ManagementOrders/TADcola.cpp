#include "TADcola.h"

cola::cola()
{
    pedidos = new TPedido[INCREMENTO];//crear el tipo
    if (pedidos!=NULL)
    {


        ne=fin=inicio=0;
        Tama=INCREMENTO;
    }
    else
    {
        ne=fin=inicio=-1;
        Tama=-1;
    }
}
cola::~cola()
{
    if (pedidos!=NULL)
        delete [] pedidos;
    pedidos=NULL;
    ne=fin=inicio=-1;
    Tama=0;
}
TPedido cola::primero()
{
    return pedidos[inicio];
}
bool cola::esvacia()
{
    return (ne==0);
}
int cola::longitud()
{
    return ne;
}
void cola::encolar(TPedido p)
{
    if (ne==Tama)
    {
        TPedido *NuevaZona=new TPedido[Tama+INCREMENTO];
        if (NuevaZona!=NULL)
        {
            for (int i=0; i<ne; i++)
            {
                NuevaZona[i]=pedidos[inicio];
                inicio++;
                if (inicio==Tama) // inicio=(inicio+1)%Tama
                    inicio=0;
            }
            inicio=0;
            fin=ne;
            Tama+=INCREMENTO;
            delete pedidos;
            pedidos = NuevaZona;
        }
    };
    if (ne<Tama)
    {
        pedidos[fin]=p;
        fin=(fin+1)%Tama;
        ne++;
    }
}
void cola::desencolar()
{
    inicio++; // inicio=(inicio+1)%Tama;
    if (inicio==Tama)
        inicio=0;
    ne--;
    if (Tama-ne>=INCREMENTO && Tama>INCREMENTO)
    {
        TPedido *NuevaZona=new TPedido[Tama-INCREMENTO];
        if (NuevaZona!=NULL)
        {
            for (int i=0; i<ne; i++)
            {
                NuevaZona[i]=pedidos[inicio++];
                if (inicio==Tama)
                    inicio=0;
            }
            Tama-=INCREMENTO;
            inicio=0;
            fin=0;
            delete [] pedidos;
            pedidos=NuevaZona;
        };
    };
}

void cola::vaciar(){
    if(pedidos!=NULL){
        delete [] pedidos;
    }
    pedidos = new TPedido[INCREMENTO];
    ne = fin = inicio = 0;
    Tama = INCREMENTO;
}

void cola::clonar(cola &c){
    vaciar();
    cola colaTemp;
    while(!c.esvacia()){
        encolar(c.primero());
        colaTemp.encolar(c.primero());
        c.desencolar();
    }
    while(!colaTemp.esvacia()){
        c.encolar(colaTemp.primero());
        colaTemp.desencolar();
    }
}
