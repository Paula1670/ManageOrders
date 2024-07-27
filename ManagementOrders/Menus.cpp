#include "Menus.h"
#include "TAlmacen.h"
#include "TTienda.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "TTipos.h"

using namespace std;

Menus::Menus(){

}
Menus::~Menus(){


}
void Menus::menuPrincipal(Cadena nombreAlmacen, Cadena dirAlm, Cadena nombreTienda, Cadena dirTienda){
    int opc;

    do{
        system("cls");
        alm.DatosAlmacen(nombreAlmacen, dirAlm);
        tienda.DatosTienda(nombreTienda, dirTienda);
        cout << endl;
        cout << setw(70) << "----- Menú Principal ----- " << nombreAlmacen << (strcmp(nombreTienda,"")==0 ?"":", ") << nombreTienda << endl;
        cout << setw(70) << "1.- Gestión de Almacenes." << endl;
        cout << setw(70) << "2.- Gestión de la Tienda." << endl;
        cout << setw(82) << "3.- Reposición de productos en Tienda" << endl;
        cout << setw(55) << "0.- Salir." << endl << endl;
        cout << setw(68) << " .- Escriba una opción: ";
        cin >> opc;

        switch(opc){
            case 1:
                menuAlmacenes(nombreAlmacen, dirAlm);
                break;
            case 2:
                menuTienda(nombreTienda, dirTienda);
                break;
            case 3:
                menuReposicion(nombreAlmacen, dirAlm, nombreTienda, dirTienda);
                break;
            case 0:
                cout << endl << setw(76) << "GRACIAS POR USAR MI APLICACIÓN." << endl;
                break;
            default:
                cout << endl << setw(83) << "Opción equivocada, inténtalo de nuevo." << endl << endl;
                system("pause");
                break;
        }
        cout << endl;
    }while(opc !=0);
}//fin del menuPrincipal

//desarrollamos nuestro menú de gestión de almacén
void Menus::menuAlmacenes(Cadena nombreAlmacen, Cadena dirAlm){
    int opc, pos;
    TProducto producto;
    Cadena nombreFich;
    bool resul;

    do{
        system("cls");
        alm.DatosAlmacen(nombreAlmacen, dirAlm);
        cout << endl;
        cout << setw(70) << "----- Menú Almacén ----- " << nombreAlmacen << endl;
        cout << setw(72) << "1.- Crear un almacén vacío." << endl;
        cout << setw(77) << "2.- Abrir un fichero de almacén." << endl;
        cout << setw(67) << "3.- Cerrar un almacén." << endl;
        cout << setw(78) << "4.- Listar productos del almacén." << endl;
        cout << setw(68) << "5.- Añadir un producto." << endl;
        cout << setw(72) << "6.- Actualizar un producto." << endl;
        cout << setw(71) << "7.- Consultar un producto." << endl;
        cout << setw(70) << "8.- Eliminar un producto." << endl;
        cout << setw(68) << "9.- Gestión de pedidos." << endl;
        cout << setw(68) << "10.- Gestión de envíos." << endl;
        cout << setw(55) << "0.- Salir." << endl << endl;
        cout << setw(68) << ".-  Escriba una opción: ";
        cin >> opc;

        switch(opc){
            case 1:
                //Crear un almacén vacío
                if(alm.EstaAbierto()){
                    cout << "Hay un almacén abierto" << endl;
                }
                else{
                    cout << endl;
                    fflush(stdin);
                    cout << "\tEscriba el nombre del Almacen: ";
                    cin.getline(nombreAlmacen, 90, '\n');
                    cout << "\tEscriba la dirección del Almacen: ";
                    cin.getline(dirAlm, 90, '\n');
                    cout << "\tEscriba el nombre del fichero: ";
                    cin.getline(nombreFich, 90, '\n');
                    alm.CrearAlmacen(nombreAlmacen, dirAlm, nombreFich);
                    cout << "\tAlmacén " << nombreAlmacen << " creado" << endl;
                    }
                cout << endl;
                system("pause");
                break;
            case 2:
                //Abrir un fichero de almacén
                cout << endl;
                fflush(stdin);
                cout << "\tEscriba el nombre del fichero: ";
                cin.getline(nombreFich, 90, '\n');
                resul = alm.AbrirAlmacen(nombreFich);
                alm.DatosAlmacen(nombreAlmacen, dirAlm);
                if(resul){
                    cout << "\tAlmacén " << nombreAlmacen << " abierto." << endl;
                }
                else{
                    cout << "\tNo se ha abierto el almacén" << endl;
                }
                system("pause");
                break;
            case 3:
                //Cerrar un almacén
                cout << endl;
                if(alm.EstaAbierto()){
                    cout << "\tSe va a cerrar el almacén" << endl;
                    alm.CerrarAlmacen();
                    cout << "\n\tAlmacén cerrado" << endl;
                }
                else{
                    cout << "\tNo hay ningún almacén abierto" << endl;
                }
                alm.DatosAlmacen(nombreAlmacen, dirAlm);
                system("pause");
                break;
            case 4:
                //Listar productos del almacén
                Cadena nProd, cod, nom, cant, pre, fec;

                if(alm.NProductos()==0){
                    cout << "\n\tNo has añadido ningún producto." << endl;
                }
                else{
                    int num;
                    strcpy(nProd, "NProduc");
                    strcpy(cod, "CODIGO");
                    strcpy(nom, "NOMBRE");
                    strcpy(pre, "PRECIO");
                    strcpy(cant, "CANTIDAD");
                    strcpy(fec, "FECHA CADUCIDAD");
                    cout << endl;
                    cout << setw(29) << "Listado del almacén \"" << nombreAlmacen << "\" localizado en \"" << dirAlm << "\"" << endl;
                    cout << setw(100) << "*******************************************************************************************\n";
                    cout.setf(ios::left, ios::adjustfield);
                    cout.width(8);
                    cout << " ";
                    cout.width(8);
                    cout << nProd;
                    cout.width(9);
                    cout << cod;
                    cout.width(32);
                    cout << nom;
                    cout.width(10);
                    cout << pre;
                    cout.width(17);
                    cout << cant;
                    cout << fec;
                    cout << endl;

                    for(int i=0;i<alm.NProductos();i++){


                        producto = alm.ObtenerProducto(i);
                        num = i+1;
                        cout.setf(ios::left, ios::adjustfield);
                        cout.width(10);
                        cout << " ";
                        cout.width(6);
                        cout << num;
                        cout.width(9);
                        cout << producto.CodProd;
                        cout.width(32);
                        cout << producto.NombreProd;
                        cout.width(12);
                        cout << fixed << setprecision(2) << producto.Precio;
                        cout.width(17);
                        cout << producto.Cantidad;
                        cout << producto.Caducidad.Dia <<"/" << producto.Caducidad.Mes << "/" << producto.Caducidad.Anyo << endl;
                    }

                    cout.setf(ios::right, ios::adjustfield);
                }
                cout << endl;
                system("pause");
                break;
            case 5:
                //Añadir un producto
                cout << endl;
                fflush(stdin);
                cout << "\tEscriba el código del producto: ";
                cin.getline(producto.CodProd, 90, '\n');
                cout << "\tEscriba el nombre del producto: ";
                cin.getline(producto.NombreProd, 90, '\n');
                cout << "\tEscriba el precio del producto: ";
                cin >> producto.Precio;
                cout << "\tEscriba la cantidad del producto: ";
                cin >> producto.Cantidad;
                cout << "\tEscriba el día que caduca el producto: ";
                cin >> producto.Caducidad.Dia;
                cout << "\tEscriba el mes que caduca el producto: ";
                cin >> producto.Caducidad.Mes;
                cout << "\tEscriba el año que caduca el producto: ";
                cin >> producto.Caducidad.Anyo;
                resul = alm.AnadirProducto(producto);
                if(resul){
                    cout << "\tEl producto se ha añadido" << endl;
                }
                else{
                    cout << "\tEl producto NO se ha añadido" << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 6:
                //Actualizar un producto
                cout << endl;
                fflush(stdin);
                cout << "\tEscriba el código del producto que quieres actualizar: ";
                cin.getline(producto.CodProd, 90, '\n');
                if(alm.BuscarProducto(producto.CodProd)==-1){
                    cout << "\n\tProducto no encontrado" << endl;
                }
                else{
                    producto = alm.ObtenerProducto(alm.BuscarProducto(producto.CodProd));
                    Cadena cod;
                    strcpy(cod, "CODIGO");
                    Cadena nom;
                    strcpy(nom, "NOMBRE");
                    Cadena pre;
                    strcpy(pre, "PRECIO");
                    Cadena cant;
                    strcpy(cant, "CANTIDAD");
                    Cadena fec;
                    strcpy(fec, "FECHA CADUCIDAD");
                    cout << endl;
                    cout.setf(ios::left, ios::adjustfield);
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << cod;
                    cout.width(32);
                    cout << nom;
                    cout.width(10);
                    cout << pre;
                    cout.width(17);
                    cout << cant;
                    cout << fec;
                    cout << endl;
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << producto.CodProd;
                    cout.width(32);
                    cout << producto.NombreProd;
                    cout.width(12);
                    cout << fixed << setprecision(2) << producto.Precio;
                    cout.width(17);
                    cout << producto.Cantidad;
                    cout << producto.Caducidad.Dia <<"/" << producto.Caducidad.Mes << "/" << producto.Caducidad.Anyo << "/" << endl;
                    cout.setf(ios::right, ios::adjustfield);
                }
                fflush(stdin);
                int opc;
                do{
                    cout << "\n\t1.- Actualizar el código del producto: " << endl;
                    cout << "\t2.- Actualizar el nombre del producto: " << endl;
                    cout << "\t3.- Actualizar el precio del producto: " << endl;
                    cout << "\t4.- Actualizar la cantidad del producto: " << endl;
                    cout << "\t5.- Actualizar la fecha de caducidad del producto: " << endl;
                    cout << "\t0.- Salir" << endl;
                    cout << "\t .- Ingrese una opción: ";
                    cin >> opc;

                    switch(opc){
                        case 1:
                            fflush(stdin);
                            cout << "\tEscriba el código del producto: ";
                            cin.getline(producto.CodProd, 90, '\n');
                            break;
                        case 2:
                            fflush(stdin);
                            cout << "\tEscriba el nombre del producto: ";
                            cin.getline(producto.NombreProd, 90, '\n');
                            break;
                        case 3:
                            fflush(stdin);
                            cout << "\tEscriba el precio del producto: ";
                            cin >> producto.Precio;
                            break;
                        case 4:
                            fflush(stdin);
                            cout << "\tEscriba la cantidad del producto: ";
                            cin >> producto.Cantidad;
                            break;
                        case 5:
                            fflush(stdin);
                            cout << "\tEscriba el día que caduca el producto: ";
                            cin >> producto.Caducidad.Dia;
                            cout << "\tEscriba el mes que caduca el producto: ";
                            cin >> producto.Caducidad.Mes;
                            cout << "\tEscriba el año que caduca el producto: ";
                            cin >> producto.Caducidad.Anyo;
                            break;
                        case 0:
                            break;
                        default:
                            cout << "\n\t\t\tOpción equivocada, inténtalo de nuevo." << endl << endl;
                            system("pause");
                            break;
                    }
                }while(opc !=0);
                resul = alm.ActualizarProducto(pos, producto);
                if(resul){
                    cout << "\n\tProducto actualizado" << endl;
                }
                else{
                    cout << "\n\tProducto NO actualizado" << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 7:
                //Consultar un producto
                cout << endl;
                fflush(stdin);
                cout << "\tEscriba el código del producto: ";
                cin.getline(producto.CodProd, 90, '\n');
                if(alm.BuscarProducto(producto.CodProd)==-1){
                    cout << "\n\tProducto no encontrado" << endl;
                }
                else{
                    producto = alm.ObtenerProducto(alm.BuscarProducto(producto.CodProd));
                    Cadena cod;
                    strcpy(cod, "CODIGO");
                    Cadena nom;
                    strcpy(nom, "NOMBRE");
                    Cadena pre;
                    strcpy(pre, "PRECIO");
                    Cadena cant;
                    strcpy(cant, "CANTIDAD");
                    Cadena fec;
                    strcpy(fec, "FECHA CADUCIDAD");
                    cout << endl;
                    cout.setf(ios::left, ios::adjustfield);
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << cod;
                    cout.width(32);
                    cout << nom;
                    cout.width(10);
                    cout << pre;
                    cout.width(17);
                    cout << cant;
                    cout << fec;
                    cout << endl;
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << producto.CodProd;
                    cout.width(32);
                    cout << producto.NombreProd;
                    cout.width(12);
                    cout << fixed << setprecision(2) << producto.Precio;
                    cout.width(17);
                    cout << producto.Cantidad;
                    cout << producto.Caducidad.Dia <<"/" << producto.Caducidad.Mes << "/" << producto.Caducidad.Anyo << "/" << endl;
                    cout.setf(ios::right, ios::adjustfield);
                }
                cout << endl;
                system("pause");
                break;
            case 8:
                //Eliminar un producto
                cout << endl;
                cout << "\tEscriba el código del producto: ";
                cin >> producto.CodProd;
                pos = alm.BuscarProducto(producto.CodProd);
                if(pos < 0 || pos > (alm.NProductos())){
                    cout << "El producto no existe." << endl;
                }
                else{
                    cout << "\n\tEl siguiente producto será eliminado: " << endl;
                    producto = alm.ObtenerProducto(pos);
                    strcpy(cod, "CODIGO");
                    strcpy(nom, "NOMBRE");
                    strcpy(pre, "PRECIO");
                    strcpy(cant, "CANTIDAD");
                    strcpy(fec, "FECHA CADUCIDAD");
                    cout << endl;
                    cout.setf(ios::left, ios::adjustfield);
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << cod;
                    cout.width(32);
                    cout << nom;
                    cout.width(10);
                    cout << pre;
                    cout.width(17);
                    cout << cant;
                    cout << fec;
                    cout << endl;
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << producto.CodProd;
                    cout.width(32);
                    cout << producto.NombreProd;
                    cout.width(12);
                    cout << fixed << setprecision(2) << producto.Precio;
                    cout.width(17);
                    cout << producto.Cantidad;
                    cout << producto.Caducidad.Dia <<"/" << producto.Caducidad.Mes << "/" << producto.Caducidad.Anyo << "/" << endl;
                    cout.setf(ios::right, ios::adjustfield);
                    resul = alm.EliminarProducto(pos);
                    cout << "\n\tProducto elminado correctamente" << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 9:
                //Gestión de pedidos
                menuPedidos(nombreAlmacen, dirAlm);
                break;
            case 10:
                //Gestión de envíos
                menuEnvios();
                break;
            case 0:
                break;
            default:
                cout << "\n\t\t\tOpción equivocada, inténtalo de nuevo." << endl << endl;
                system("pause");
                break;
        }
    }while(opc !=0);
}//fin del menuAlmacenes

//desarrollamos nuestro menú de gestión de tiendas
void Menus::menuTienda(Cadena nombreTienda, Cadena dirTienda){
    int opc;
    char rpt;
    TEstante est;
    TProducto producto;
    TPedido ped;
    Cadena nombreFich;
    bool resul;

    do{
        system("cls");
        tienda.DatosTienda(nombreTienda, dirTienda);
        cout << endl;
        cout << setw(70) << "----- Menú Tienda ----- " << nombreTienda << endl;
        cout << setw(73) << "1.- Crear una tienda vacía." << endl;
        cout << setw(74) << "2.- Abrir un fichero tienda." << endl;
        cout << setw(67) << "3.- Cerrar la tienda." << endl;
        cout << setw(79) << "4.- Actualizar el fichero tienda." << endl;
        cout << setw(80) << "5.- Listar productos de la tienda." << endl;
        cout << setw(68) << "6.- Añadir un estante." << endl;
        cout << setw(72) << "7.- Actualizar un estante." << endl;
        cout << setw(71) << "8.- Consultar un estante." << endl;
        cout << setw(70) << "9.- Eliminar un estante." << endl;
        cout << setw(56) << "0.- Salir." << endl <<  endl;
        cout << setw(69) << ".-  Escriba una opción: ";
        cin >> opc;

        switch(opc){
            case 1:
                //Crear una tienda vacía
                if(tienda.EstaAbierta()){
                    cout << "Hay una tienda abierta" << endl;
                }
                else{
                    cout << endl;
                    fflush(stdin);
                    cout << "\tEscriba el nombre de la Tienda: ";
                    cin.getline(nombreTienda, 90, '\n');
                    cout << "\tEscriba la dirección de la Tienda: ";
                    cin.getline(dirTienda, 90, '\n');
                    cout << "\tEscriba el nombre del fichero: ";
                    cin.getline(nombreFich, 90, '\n');
                    tienda.CrearTienda(nombreTienda, dirTienda,nombreFich);
                    cout << "\n\tTienda " << nombreTienda << " creada" << endl;
                    }
                cout << endl;
                system("pause");
                break;
            case 2:
                //Abrir un fichero tienda
                cout << endl;
                fflush(stdin);
                cout << "\tEscriba el nombre del fichero: ";
                cin.getline(nombreFich, 90, '\n');
                resul = tienda.AbrirTienda(nombreFich);
                tienda.DatosTienda(nombreTienda, dirTienda);
                if(resul){
                    cout << "\tTienda " << nombreTienda << " abierta." << endl;
                }
                else{
                    cout << "\tNo se ha abierto la tienda" << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 3:
                //Cerrar la tienda
                cout << endl;
                if(tienda.EstaAbierta()){
                    cout << "\tSe va a cerrar la tienda" << endl;
                    tienda.CerrarTienda();
                    cout << "\n\tTienda cerrada" << endl;
                }
                else{
                    cout << "\tNo hay ninguna tienda abierta" << endl;
                }
                tienda.DatosTienda(nombreTienda,dirTienda);
                system("pause");
                break;
            case 4:
                //Actualizar el fichero tienda
                if(tienda.EstaAbierta()){
                    cout << "\n\tSe va a actualizar el fichero tienda." << endl;
                    tienda.GuardarTienda();
                    if(tienda.GuardarTienda()){
                        cout << "\n\tFichero tienda actualizado." << endl;
                    }
                    else{
                        cout << "\n\tFichero tienda NO se ha actualizado." << endl;
                    }
                }
                else{
                    cout << "\n\tNO hay ninguna tienda abierta." << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 5:
                //Listar productos de la tienda
                if(tienda.EstaAbierta() && alm.EstaAbierto()){
                    Cadena cod;
                    Cadena posicion;
                    Cadena capac;
                    Cadena codProducto;
                    Cadena nombProducto;
                    Cadena precioProducto;
                    Cadena noProducto;
                    Cadena valorTotal;
                    if(tienda.NoEstantes()==0){
                        cout << "\n\tNo has añadido ningún estante." << endl;
                    }
                    else{
                        strcpy(cod, "CODIGO");
                        strcpy(posicion, "POSICIÓN");
                        strcpy(capac, "CAPACIDAD");
                        strcpy(codProducto, "PRODUCTO");
                        strcpy(nombProducto, "NOMBRE DEL PRODUCTO");
                        strcpy(precioProducto, "PRECIO");
                        strcpy(noProducto, "NoPRODUCTO");
                        strcpy(valorTotal, "VALOR TOTAL");
                        float valorT;
                        cout << endl;
                        cout << "\tListado de la tienda \"" << nombreTienda << "\" localizada en \"" << dirTienda << "\"" << endl;
                        printf("\t***************************************************************************************************************************\n");
                        cout.setf(ios::left, ios::adjustfield);
                        cout.width(8);
                        cout << " ";
                        cout.width(9);
                        cout << cod;
                        cout.width(15);
                        cout << posicion;
                        cout.width(17);
                        cout << capac;
                        cout.width(16);
                        cout << codProducto;
                        cout.width(31);
                        cout << nombProducto;
                        cout.width(8);
                        cout << precioProducto;
                        cout.width(16);
                        cout << noProducto;
                        cout << valorTotal;
                        cout << endl;
                        for(int i=0;i<tienda.NoEstantes();i++){
                            if(i%2==0){
                                textcolor(1);
                            }
                            else{
                                textcolor(2);
                            }
                            est = tienda.ObtenerEstante(i);
                            producto = alm.ObtenerProducto(alm.BuscarProducto(est.CodProd));
                            valorT = producto.Precio * est.NoProductos;
                            cout.width(8);
                            cout << " ";
                            cout.width(9);
                            cout << est.CodEstante;
                            cout.width(15);
                            cout << est.Posicion;
                            cout.width(17);
                            cout << est.Capacidad;
                            cout.width(16);
                            cout << est.CodProd;
                            cout.width(31);
                            cout << producto.NombreProd;
                            cout.width(10);
                            cout << fixed << setprecision(2) << producto.Precio;
                            cout.width(16);
                            cout << est.NoProductos;
                            cout << valorT;
                            cout << endl;
                        }
                        textcolor(7);
                        cout.setf(ios::right, ios::adjustfield);
                    }
                }
                else{
                    cout << "\n\tPara poder actualizar tienes que tener abierto un almacén y una tienda." << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 6:
                //Añadir un estante
                cout << endl;
                fflush(stdin);
                cout << "\tEscriba el código del estante: ";
                cin >> est.CodEstante;
                cout << "\tEscriba la posición del estante: ";
                cin >> est.Posicion;
                cout << "\tEscriba la capacidad del estante: ";
                cin >> est.Capacidad;
                fflush(stdin);
                cout << "\tEscriba el código del producto: ";
                cin.getline(est.CodProd, 90, '\n');
                do{
                    cout << "\tEscriba la cantidad de productos: ";
                    cin >> est.NoProductos;
                    if(est.NoProductos>est.Capacidad){
                        cout.width(10);
                        cout << " ";
                        cout << "No hay capacidad para tantos productos, vuelve a insertar." << endl;
                        system("pause");
                    }
                }while(est.NoProductos>est.Capacidad);
                if(est.NoProductos > alm.ObtenerProducto(alm.BuscarProducto(est.CodProd)).Cantidad){
                    strcpy(ped.CodProd, est.CodProd);
                    ped.CantidadPed = est.NoProductos - alm.ObtenerProducto(alm.BuscarProducto(est.CodProd)).Cantidad;
                    est.NoProductos = alm.ObtenerProducto(alm.BuscarProducto(est.CodProd)).Cantidad;
                    strcpy(ped.Nomtienda, nombreTienda);
                    alm.AnadirPedido(ped);
                    cout.width(10);
                    cout << " ";
                    cout << "Se ha pedido " << ped.CantidadPed << ((ped.CantidadPed == 1) ? " unidad":" unidades") << " del producto " <<
                            alm.ObtenerProducto(alm.BuscarProducto(ped.CodProd)).NombreProd << endl;
                }
                producto = alm.ObtenerProducto(alm.BuscarProducto(est.CodProd));
                producto.Cantidad -= est.NoProductos;
                alm.ActualizarProducto(alm.BuscarProducto(est.CodProd), producto);
                resul = tienda.AnadirEstante(est);
                if(resul){
                    cout << "\n\tEl estante se ha añadido" << endl;
                }
                else{
                    cout << "\n\tEl estante NO se ha añadido" << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 7:
                //Actualizar un estante
                cout << endl;
                if(tienda.EstaAbierta() && alm.EstaAbierto()){
                    fflush(stdin);
                    cout << "\tEscriba el código del estante que quieres actualizar: ";
                    cin >> est.CodEstante;
                    if(tienda.BuscarEstante(est.CodEstante)==-1){
                        cout << "\n\tEstante no encontrado" << endl;
                    }
                    else{
                        est = tienda.ObtenerEstante(tienda.BuscarEstante(est.CodEstante));
                        producto = alm.ObtenerProducto(alm.BuscarProducto(est.CodProd));
                        cout.width(10);
                        cout << " ";
                        cout << "Producto: " << producto.NombreProd << ", Cantidad: " << est.NoProductos << ", Capacidad: " << est.Capacidad <<  endl;
                        cout << "¿Quieres actualizar el estante (S/N)?: ";
                        cin >> rpt;

                        if(rpt == 's' || rpt == 'S'){
                            int nuevaCantidad, diferencia;
                            do{
                                cout << "\n\tEscriba la nueva cantidad de productos para el estante: ";
                                cin >> nuevaCantidad;
                                if(nuevaCantidad<0){
                                    cout << "\n\tTienes que introducir una cantidad mayor que 0" << endl;
                                }
                            }while(nuevaCantidad<0);

                            if(nuevaCantidad < est.NoProductos){
                                diferencia = est.NoProductos-nuevaCantidad;
                                producto.Cantidad += diferencia;
                                est.NoProductos = nuevaCantidad;
                                cout << "\n\tSe han devuelto " << diferencia << " productos al almacén" << endl;
                            }
                            else{
                                if(nuevaCantidad > est.Capacidad){
                                    diferencia = est.Capacidad-est.NoProductos;
                                    est.NoProductos += diferencia;
                                    producto.Cantidad-= diferencia;
                                    cout << "\n\tSe han añadido " << diferencia << " productos a la tienda" << endl;
                                }
                                else if(nuevaCantidad <= est.Capacidad && nuevaCantidad > producto.Cantidad){
                                    est.NoProductos = producto.Cantidad;
                                    nuevaCantidad -= producto.Cantidad;
                                    producto.Cantidad = 0;
                                    strcpy(ped.CodProd, est.CodProd);
                                    ped.CantidadPed = nuevaCantidad;
                                    strcpy(ped.Nomtienda, nombreTienda);
                                    alm.AnadirPedido(ped);
                                    cout.width(10);
                                    cout << " ";
                                    cout << "Se ha pedido " << ped.CantidadPed << ((ped.CantidadPed == 1) ? " unidad":" unidades") << " del producto " <<
                                     alm.ObtenerProducto(alm.BuscarProducto(ped.CodProd)).NombreProd << endl;
                                }
                                else{
                                    diferencia = nuevaCantidad-est.NoProductos;
                                    est.NoProductos += diferencia;
                                    producto.Cantidad -=diferencia;
                                    cout << "\n\tSe han añadido " << diferencia << " productos a la tienda" << endl;
                                }
                                cout << "\n\tEl estante se ha actualizado" << endl;
                                Cadena cod;
                                Cadena posicion;
                                Cadena capac;
                                Cadena codProducto;
                                Cadena noProducto;
                                strcpy(cod, "CODIGO");
                                strcpy(posicion, "POSICIÓN");
                                strcpy(capac, "CAPACIDAD");
                                strcpy(codProducto, "PRODUCTO");
                                strcpy(noProducto, "NoPRODUCTO");
                                printf("\n\t%s\t %s\t %-10s\t %-10s\t %-10s\n", cod, posicion, capac, codProducto, noProducto);
                                printf("\t%d\t %-10d\t %-8d\t %-15s %-15d\n", est.CodEstante, est.Posicion, est.Capacidad, est.CodProd,
                                           est.NoProductos);
                                cout << endl;
                                system("pause");
                            }
                            alm.ActualizarProducto(alm.BuscarProducto(producto.CodProd), producto);
                            tienda.ActualizarEstante(tienda.BuscarEstante(est.CodEstante),est);
                            tienda.GuardarTienda();
                        }
                        else{
                            cout << "\n\tNO actualizas ningún estante." << endl;
                        }
                    }
                }
                else{
                    cout << "\n\tPara poder actualizar tienes que tener abierto un almacén y una tienda." << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 8:
                //Consultar un estante
                cout << endl;
                fflush(stdin);
                cout << "\tEscriba el código del estante que quieres consultar: ";
                cin >> est.CodEstante;
                if(tienda.BuscarEstante(est.CodEstante)==-1){
                    cout << "\n\tEstante no encontrado" << endl;
                }
                else{
                    Cadena cod;
                    Cadena posicion;
                    Cadena capac;
                    Cadena codProducto;
                    Cadena noProducto;
                    strcpy(cod, "CODIGO");
                    strcpy(posicion, "POSICIÓN");
                    strcpy(capac, "CAPACIDAD");
                    strcpy(codProducto, "PRODUCTO");
                    strcpy(noProducto, "NoPRODUCTO");
                    printf("\n\t%s\t %s\t %-10s\t %-10s\t %-10s\n", cod, posicion, capac, codProducto, noProducto);
                    est = tienda.ObtenerEstante(tienda.BuscarEstante(est.CodEstante));
                    printf("\t%d\t %-10d\t %-8d\t %-15s %-15d\n", est.CodEstante, est.Posicion, est.Capacidad, est.CodProd,
                               est.NoProductos);
                }
                cout << endl;
                system("pause");
                break;
            case 9:
                //Eliminar un estante
                cout << endl;
                if(tienda.EstaAbierta() && alm.EstaAbierto()){
                    fflush(stdin);
                    cout << "\tEscriba el código del estante que quieres eliminar: ";
                    cin >> est.CodEstante;
                    if(tienda.BuscarEstante(est.CodEstante)==-1){
                        cout << "\n\tEstante no encontrado" << endl;
                    }
                    else{
                        est = tienda.ObtenerEstante(tienda.BuscarEstante(est.CodEstante));
                        producto = alm.ObtenerProducto(alm.BuscarProducto(est.CodProd));
                        Cadena cod;
                        Cadena posicion;
                        Cadena capac;
                        Cadena codProducto;
                        Cadena noProducto;
                        strcpy(cod, "CODIGO");
                        strcpy(posicion, "POSICIÓN");
                        strcpy(capac, "CAPACIDAD");
                        strcpy(codProducto, "PRODUCTO");
                        strcpy(noProducto, "NoPRODUCTO");
                        printf("\n\t%s\t %s\t %-10s\t %-10s\t %-10s\n", cod, posicion, capac, codProducto, noProducto);
                        printf("\t%d\t %-10d\t %-8d\t %-15s %-15d\n", est.CodEstante, est.Posicion, est.Capacidad, est.CodProd,
                                   est.NoProductos);
                        producto.Cantidad += est.NoProductos;
                        alm.ActualizarProducto(alm.BuscarProducto(producto.CodProd), producto);
                        tienda.EliminarEstante(tienda.BuscarEstante(est.CodEstante));
                        tienda.GuardarTienda();
                        cout << "\n\tEl estante ha sido eliminado" << endl;

                    }
                }
                else{
                    cout << "\n\tPara poder actualizar tienes que tener abierto un almacén y una tienda." << endl;
                }
                cout << endl;
                system("pause");
                break;
            case 0:
                //Salir
                break;
            default:
                cout << "\n\t\t\tOpción equivocada, inténtalo de nuevo." << endl << endl;
                system("pause");
                break;
        }
    }while(opc !=0);
}//fin del menuTienda

void Menus::menuReposicion(Cadena nombreAlmacen, Cadena dirAlm, Cadena nombreTienda, Cadena dirTienda){
    TEstante est;
    TProducto producto;
    int estado;

    alm.DatosAlmacen(nombreAlmacen, dirAlm);
    tienda.DatosTienda(nombreTienda, dirTienda);

    if(tienda.EstaAbierta() && alm.EstaAbierto()){
        Cadena cod;
        Cadena capac;
        Cadena nomProducto;
        Cadena estad, estadillo;
        Cadena porcentaje;
        strcpy(cod, "CODIGO");
        strcpy(capac, "CAPACIDAD");
        strcpy(nomProducto, "PRODUCTO");
        strcpy(estad, "ESTADO");
        strcpy(porcentaje, "Porcentaje");
        printf("\n\t%s\t %s\t %-30s\t %-20s\t %-10s\n", cod, capac, nomProducto, estad, porcentaje);
        cout << "\t*******************************************************************************************" << endl;
        for(int i=0;i<tienda.NoEstantes();i++){
            if(i%2==0){
                textcolor(1);
            }
            else{
                textcolor(2);
            }
            est = tienda.ObtenerEstante(i);
            producto = alm.ObtenerProducto(alm.BuscarProducto(est.CodProd));
            estado = tienda.ReponerEstante(i, producto);
            est = tienda.ObtenerEstante(i);

            float porcent = float(est.NoProductos * 100)/est.Capacidad;

            switch(estado){
                case 0:
                    strcpy(estadillo, "NO REPUESTO");
                    break;
                case 1:
                    strcpy(estadillo, "REPUESTO TOTALMENTE");
                    break;
                case 2:
                    strcpy(estadillo, "REPUESTO PARCIALMENTE");
                    break;
                default:
                    break;
            }

            printf("\t%d\t %-10d\t %-30s\t %-15s %10.2f%-5s\n", est.CodEstante, est.Capacidad, producto.NombreProd, estadillo,
                       porcent,"%");
            alm.ActualizarProducto(alm.BuscarProducto(producto.CodProd), producto);
            tienda.ActualizarEstante(tienda.BuscarEstante(est.CodEstante),est);
        }
        textcolor(7);
    }
    else{
        cout << "\n\tPara poder actualizar tienes que tener abierto un almacén y una tienda." << endl;
    }
    cout << endl;
                system("pause");
}//fin del menusReposicion

void Menus::menuPedidos(Cadena nombreAlmacen, Cadena dirAlm){
    int opc;
    bool resul;
    Cadena nombreFich;
    TPedido ped;
    TProducto prod;

    if(alm.EstaAbierto()){
        do{
            system("cls");
            alm.DatosAlmacen(nombreAlmacen, dirAlm);
            cout << endl;
            cout << setw(76) << "----- Gestión de Pedidos ----- " << endl;
            cout << setw(75) << "1.- Cargar pedidos de fichero." << endl;
            cout << setw(63) << "2.- Añadir pedido." << endl;
            cout << setw(64) << "3.- Atender pedido." << endl;
            cout << setw(97) << "4.- Listar pedidos completos de todos los productos." << endl;
            cout << setw(79) << "5.- Listar pedidos de un producto." << endl;
            cout << setw(88) << "6.- Listar todas las cantidades pendientes." << endl;
            cout << setw(93) << "7.- Listar cantidades pendientes de un producto." << endl;
            cout << setw(75) << "8.- Guardar pedidos a fichero." << endl;
            cout << setw(55) << "0.- Salir." << endl << endl;
            cout << setw(68) << ".-  Escriba una opción: ";
            cin >> opc;

            switch(opc){
                case 1:
                    //Cargar pedidos de fichero
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el nombre del fichero: ";
                    cin.getline(nombreFich, 90, '\n');
                    resul = alm.CargarColaPedidos(nombreFich);
                    if(resul){
                        cout.width(10);
                        cout << " ";
                        cout << "Pedido " << nombreFich << " cargado." << endl;
                    }
                    else{
                        cout.width(10);
                        cout << " ";
                        cout << "No se ha cargado el pedido" << endl;
                    }
                    cout << endl;
                    system("pause");
                    break;
                case 2:
                    //Añadir pedido
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el código del producto: ";
                    cin.getline(ped.CodProd, 90, '\n');
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba la cantidad del producto: ";
                    cin >> ped.CantidadPed;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el nombre de la tienda: ";
                    cin.getline(ped.Nomtienda, 90, '\n');
                    alm.AnadirPedido(ped);
                    cout.width(10);
                    cout << " ";
                    cout << "Pedido añadido correctamente";
                    cout << endl;
                    system("pause");
                    break;
                case 3:
                    //Atender pedido
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el código del producto: ";
                    cin.getline(ped.CodProd, 90, '\n');
                    if(alm.BuscarProducto(ped.CodProd)!=-1){
                        cout.width(10);
                        cout << " ";
                        cout << "Escriba la cantidad del producto: ";
                        cin >> ped.CantidadPed;
                        alm.AtenderPedidos(ped.CodProd, ped.CantidadPed);
                    }
                    else{
                        cout.width(10);
                        cout << " ";
                        cout << "El producto que buscas no existe." << endl;
                    }
                    cout << endl;
                    system("pause");
                    break;
                case 4:
                    //Listar pedidos completos de todos los productos
                    alm.ListarPedidosCompleto("");
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    //Listar pedidos de un producto
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el código del producto: ";
                    cin.getline(ped.CodProd, 90, '\n');
                    cout << endl;
                    alm.ListarPedidosCompleto(ped.CodProd);
                    cout << endl;
                    system("pause");
                    break;
                case 6:
                    //Listar todas las cantidades pendientes
                    alm.ListarCantidadesPendientes("");
                    cout << endl;
                    system("pause");
                    break;
                case 7:
                    //Listar cantidades pendientes de un producto
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el código del producto: ";
                    cin.getline(ped.CodProd, 90, '\n');
                    cout << endl;
                    alm.ListarCantidadesPendientes(ped.CodProd);
                    cout << endl;
                    system("pause");
                    break;
                case 8:
                    //Guardar pedidos a fichero
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el nombre del fichero para guardar los pedidos: ";
                    cin.getline(nombreFich, 90, '\n');
                    alm.SalvarColaPedidos(nombreFich);
                    cout.width(10);
                    cout << " ";
                    cout << "Lista de pedidos guardada correctamente en " << nombreFich << endl;
                    cout << endl;
                    system("pause");
                    break;
                case 0:
                    break;
                default:
                    cout << endl << setw(83) << "Opción equivocada, inténtalo de nuevo." << endl << endl;
                    system("pause");
                    break;
            }
        }while(opc !=0);
    }
    else{
        cout.width(10);
        cout << " ";
        cout << "Antes de cargar los pedidos tienes que tener un almacen abierto." << endl;
        system("pause");
    }

}

void Menus::menuEnvios(){
    int opc;
    Cadena nombreFich;
    bool resul;
    TPedido ped;

    if(alm.EstaAbierto()){
        do{
            system("cls");
            cout << endl;
            cout << setw(76) << "----- Gestión de Envíos ----- " << endl;
            cout << setw(75) << "1.- Cargar envíos de fichero." << endl;
            cout << setw(74) << "2.- Insertar un nuevo envío." << endl;
            cout << setw(77) << "3.- Reparto de envíos a tienda." << endl;
            cout << setw(74) << "4.- Listar todos los envíos." << endl;
            cout << setw(81) << "5.- Listar los envíos a una tienda." << endl;
            cout << setw(75) << "6.- Guardar envíos a fichero." << endl;
            cout << setw(56) << "0.- Salir." << endl << endl;
            cout << setw(69) << ".-  Escriba una opción: ";
            cin >> opc;

            switch(opc){
                case 1:
                    //Cargar envíos de fichero
                    cout << endl;
                    fflush(stdin);
                    cout << "\tEscriba el nombre del fichero: ";
                    cin.getline(nombreFich, 90, '\n');
                    resul = alm.CargarListaEnvios(nombreFich);
                    if(resul){
                        cout.width(10);
                        cout << " ";
                        cout << "Envios " << nombreFich << " cargado." << endl;
                    }
                    else{
                        cout.width(10);
                        cout << " ";
                        cout << "No se ha cargado el envío" << endl;
                    }
                    cout << endl;
                    system("pause");
                    break;
                case 2:
                    //Insertar un nuevo envío
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el código del producto: ";
                    cin.getline(ped.CodProd, 90, '\n');
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba la cantidad del producto: ";
                    cin >> ped.CantidadPed;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el nombre de la tienda: ";
                    cin.getline(ped.Nomtienda, 90, '\n');
                    if(alm.InsertarEnvios(ped)){
                        cout.width(10);
                        cout << " ";
                        cout << "Envío añadido correctamente";
                    }
                    else{
                        cout.width(10);
                        cout << " ";
                        cout << "Envío no se ha añadido correctamente";
                    }
                    cout << endl;
                    system("pause");
                    break;
                case 3:
                    //Reparto de envíos a tienda
                    fflush(stdin);
                    cout << "\tEscriba el nombre de la tienda: ";
                    cin.getline(nombreFich, 90, '\n');
                    alm.SalidaCamionTienda(nombreFich);
                    cout << endl;
                    system("pause");
                    break;
                case 4:
                    //Listar todos los envíos
                    alm.ListarListaEnvios("");
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    //Listar los envíos a una tienda
                    fflush(stdin);
                    cout << "\tEscriba el nombre de la tienda: ";
                    cin.getline(nombreFich, 90, '\n');
                    alm.ListarListaEnvios(nombreFich);
                    cout << endl;
                    system("pause");
                    break;
                case 6:
                    //Guardar envíos a fichero
                    cout << endl;
                    fflush(stdin);
                    cout.width(10);
                    cout << " ";
                    cout << "Escriba el nombre del fichero para guardar los envíos: ";
                    cin.getline(nombreFich, 90, '\n');
                    alm.SalvarListaEnvios(nombreFich);
                    cout.width(10);
                    cout << " ";
                    cout << "Lista de envíos guardada correctamente." << endl;
                    cout << endl;
                    system("pause");
                    break;
                case 0:
                    break;
                default:
                    cout << endl << setw(83) << "Opción equivocada, inténtalo de nuevo." << endl << endl;
                    system("pause");
                    break;
            }
        }while(opc !=0);
    }
}

/*
    Función textcolor() para cambiar el color de fondo y el de escritura (letra) al mismo tiempo
    (fondo en los 4 bits altos, escritura en los 4 bits bajos):
*/
void textcolor(int color){
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}
