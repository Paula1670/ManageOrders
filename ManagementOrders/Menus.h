#ifndef MENUS_H
#define MENUS_H

#include "TTipos.h"
#include "TTienda.h"
#include "TAlmacen.h"
#include <windows.h>

class Menus
{
    TAlmacen alm;
    TTienda tienda;
    public:
        Menus();
        virtual ~Menus();

        void menuPrincipal(Cadena, Cadena, Cadena, Cadena);     //desarrollamos men� principal
        void menuAlmacenes(Cadena, Cadena);                     //desarrolamos men� de almac�n
        void menuTienda(Cadena, Cadena);                        //desarrollamos men� de tienda
        void menuReposicion(Cadena, Cadena, Cadena, Cadena);    //desarrollamos men� de reposici�n
        void menuPedidos(Cadena, Cadena);                                     //desarrollamos men� de pedidos
        void menuEnvios();                                      //desarrollamos men� de env�os
};
void textcolor(int color);

#endif // MENUS_H
