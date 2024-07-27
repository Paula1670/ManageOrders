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

        void menuPrincipal(Cadena, Cadena, Cadena, Cadena);     //desarrollamos menú principal
        void menuAlmacenes(Cadena, Cadena);                     //desarrolamos menú de almacén
        void menuTienda(Cadena, Cadena);                        //desarrollamos menú de tienda
        void menuReposicion(Cadena, Cadena, Cadena, Cadena);    //desarrollamos menú de reposición
        void menuPedidos(Cadena, Cadena);                                     //desarrollamos menú de pedidos
        void menuEnvios();                                      //desarrollamos menú de envíos
};
void textcolor(int color);

#endif // MENUS_H
