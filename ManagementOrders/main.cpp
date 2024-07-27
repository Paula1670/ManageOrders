#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <wchar.h>
#include <locale.h>
#include <windows.h>
#include "Menus.h"

using namespace std;

int main(){

    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(CP_UTF8);
    system("mode con: cols=150");
    setlocale(LC_ALL, "spanish");
    Cadena nombreAlmacen;
    strcpy(nombreAlmacen, "");
    Cadena dirAlm;
    strcpy(dirAlm, "");
    Cadena nombreTienda;
    strcpy(nombreTienda, "");
    Cadena dirTienda;
    strcpy(dirTienda, "");
    Menus menu;

    menu.menuPrincipal(nombreAlmacen, dirAlm, nombreTienda, dirTienda);

    system("pause");
    return 0;
}
