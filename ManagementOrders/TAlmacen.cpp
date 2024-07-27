#include "TAlmacen.h"
#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//  Constructor que debe inicializar los atributos de la clase.
TAlmacen::TAlmacen()
{
    //ctor
    strcpy(Nombre, "");
    strcpy(Direccion, "");
    NProduc = -1;
}// fin del constructor

//  Destructor que cerrar� el almac�n en caso de que el usuario no lo haya hecho.
TAlmacen::~TAlmacen()
{
    //dtor
    CerrarAlmacen();
}//fin del destructor

//  Devuelve los atributos nombre y direcci�n por par�metro.
void TAlmacen::DatosAlmacen(Cadena pNombAlmacen, Cadena pDirAlmacen){
    strcpy(pNombAlmacen, Nombre);
    strcpy(pDirAlmacen, Direccion);
}//fin del m�todo DatosAlmacen

/*  Crea un fichero binario vac�o con el nombre pasado por par�metro. Crea la cabecera del fichero
    y lo deja abierto para su utilizaci�n. Devuelve true si se ha creado.
*/
bool TAlmacen::CrearAlmacen(Cadena pNomFiche){
    bool estaCreado = true;
    FicheProductos.open(pNomFiche, ios::in | ios::out | ios::binary);//vemos si el fichero exist�a previamente
    if(FicheProductos.fail()){
        FicheProductos.close();
        FicheProductos.clear();
        FicheProductos.open(pNomFiche, ios::out | ios::binary); // se crea el fichero
        if(FicheProductos.fail()){ // si no se puede crear
            FicheProductos.clear();
            FicheProductos.close();
            estaCreado = false;
        }
        else{
            FicheProductos.seekp(0);
            NProduc = 0;
            FicheProductos.write((char*) &NProduc, sizeof(int));
            FicheProductos.write((char*) Nombre, sizeof(Cadena));
            FicheProductos.write((char*) Direccion, sizeof(Cadena));
            estaCreado;
        }
    }
    else{
        FicheProductos.seekp(0);
        NProduc = 0;
        FicheProductos.write((char*) &NProduc, sizeof(int));
        FicheProductos.write((char*) Nombre, sizeof(Cadena));
        FicheProductos.write((char*) Direccion, sizeof(Cadena));
        estaCreado;
    }
    return estaCreado;
}//fin del m�todo CrearAlmacen

/*  Igual que el m�todo anterior, pero actualizando los atributos nombre y direcci�n con los valores
    pasados por par�metro. Devuelve true si ha podido crear el fichero.
*/
bool TAlmacen::CrearAlmacen(Cadena pNombAlmacen, Cadena pDirAlmacen, Cadena pNomFiche){
    bool estaCreado;
    strcpy(Nombre, pNombAlmacen);
    strcpy(Direccion, pDirAlmacen);
    estaCreado = CrearAlmacen(pNomFiche);
    return estaCreado;
}//fin del m�todo CrearAlmacen

/*  Abre un fichero y actualiza los atributos de la clase con los datos de cabecera del fichero y lo
    lo deja abierto. No se puede abrir un fichero si previamente el almac�n est� abierto. Devuelve true
    si ha podido abrir el fichero.
*/
bool TAlmacen::AbrirAlmacen(Cadena pNomFiche){
    bool estaAbierto = false;
    if(!EstaAbierto()){
        FicheProductos.open(pNomFiche, ios::in | ios::out | ios::binary);
        if(!FicheProductos.fail()){
            FicheProductos.seekg(0, ios::beg);
            FicheProductos.read((char*)&NProduc, sizeof(int));
            FicheProductos.read((char*)Nombre, sizeof(Cadena));
            FicheProductos.read((char*)Direccion, sizeof(Cadena));
            estaAbierto = true;
        }
    }
    else{
        estaAbierto;
    }
    return estaAbierto;
}//fin del m�todo AbrirAlmacen

/*  Cierra el fichero e inicializa los atributos a valores iniciales. Devuelve true si se ha cerrado el
    almac�n.
*/
bool TAlmacen::CerrarAlmacen(){
    bool estaCerrado;
    FicheProductos.close();
    FicheProductos.clear();
    strcpy(Nombre, "");
    strcpy(Direccion, "");
    NProduc = -1;
    estaCerrado = true;

    return estaCerrado;
}//fin del m�todo CerrarAlmacen

//  Devuelve true si el fichero est� abierto.
bool TAlmacen::EstaAbierto(){
    bool estaAbierto = false;
    if(NProduc !=-1){
        estaAbierto = true;
    }
    else{
        estaAbierto;
    }
    return estaAbierto;
}//fin del m�todo Est�Abierto

//  Devuelve el n�mero de productos.
int TAlmacen::NProductos(){
    return NProduc;
}//fin del m�todo NProductos

/*  Dado un c�digo de producto, devuelve la posici�n dentro del fichero donde se encuentra. Si no
    lo encuentra devuelve -1.
*/
int TAlmacen::BuscarProducto(Cadena pCodProd){
    int pos = -1, i = 0;
    TProducto prod;
    bool encontrado = false;
    if(EstaAbierto()){
        FicheProductos.seekg(sizeof(int) + 2 * sizeof(Cadena), ios::beg);
        while((i<NProduc) && (!encontrado)){
            FicheProductos.read((char*)&prod, sizeof(TProducto));
            if(strcmp(pCodProd, prod.CodProd)==0){
                pos = i;
                encontrado = true;
            }
            else{
                i++;
            }
        }
    }
    if(encontrado){
        pos;
    }
    else{
        pos = -1;
    }
    return pos;
}//fin del m�todo BuscarProducto

/*  Dado la posici�n devuelve el producto del fichero situado en dicha posici�n. Debe verificar
    previamente que la posici�n sea correcta. Si la posici�n no es correcta devolver� un producto cuyo
    c�digo tendr� el valor �NULO�.
*/
TProducto TAlmacen::ObtenerProducto(int pPos){
    TProducto prod;
    if(pPos >=0 && pPos < NProduc){
        if(EstaAbierto())
        {
            FicheProductos.seekg(sizeof(int)+sizeof(Cadena)*2 + pPos*sizeof(TProducto), ios::beg);
            FicheProductos.read((char*) &prod, sizeof(TProducto));
            if(FicheProductos.fail())
            {
                cout<< "Error de fichero."<<endl;
                strcpy(prod.CodProd, "NULO");
            }
        }
    }
    else{
        strcpy(prod.CodProd,"NULO");
    }
    return prod;
}//fin del m�todo ObtenerProducto

/*  Dado un producto, lo busca en el fichero y si no lo encuentra lo a�ade al final del fichero.
    Devuelve true si se ha a�adido el producto.
*/
bool TAlmacen::AnadirProducto(TProducto pProduc){
    bool estaAnadido = false;
    int tamano;
    if(BuscarProducto(pProduc.CodProd)!= -1){
        estaAnadido;
    }
    else{
        tamano = sizeof(int) +  sizeof(Cadena) * 2 + sizeof(TProducto) * NProduc;
        FicheProductos.clear();
        FicheProductos.seekp(tamano, ios::beg);
        FicheProductos.write((char*)&pProduc, sizeof(TProducto));

        NProduc = NProductos();
        NProduc++;
        FicheProductos.seekp(0, ios::beg);
        FicheProductos.write((char*)&NProduc, sizeof(int));
        estaAnadido = true;
    }
    return estaAnadido;
}//fin del m�todo AnadirProducto

/*  Dada la posici�n de un producto en el fichero lo actualiza con la informaci�n del producto pasado
    por par�metro. Devuelve true si se ha actualizado el producto. Se debe verificar previamente que la
    posici�n sea correcta.
*/
bool TAlmacen::ActualizarProducto(int pPos, TProducto pProduc){
    bool estaActualizado = false;

    if(pPos < 0 || pPos > NProduc){
        estaActualizado;
    }
    else{
        FicheProductos.seekp(sizeof(int)+ sizeof(Cadena) * 2 + sizeof(TProducto) * pPos, ios::beg);
        FicheProductos.write((char*)&pProduc,sizeof(TProducto));
        estaActualizado = true;
    }

    return estaActualizado;
}//fin del m�todo ActualizarProducto

/*  Dado la posici�n de un producto en el fichero lo borra. Devuelve true si se ha podido borrar. Se
    debe verificar que la posici�n sea correcta.
*/
bool TAlmacen::EliminarProducto(int pPos){
    bool estaEliminado = false;
    TProducto prod;
    if(pPos == -1 || (pPos < 0) || pPos > NProduc){
        estaEliminado;
    }
    else{
        if(FicheProductos.is_open()){
            FicheProductos.seekg(0, ios::beg);
            FicheProductos.read((char*)&NProduc, sizeof(int));
            for(int i=pPos;i < NProduc; i++){
                FicheProductos.seekg((sizeof(TProducto)*(i+1)), ios::beg);
                FicheProductos.read((char*)&prod, sizeof(TProducto));
                FicheProductos.seekg((sizeof(TProducto)*(i)), ios::beg);
                FicheProductos.write((char*)&prod, sizeof(TProducto));
            }
            NProduc--;
            FicheProductos.seekp(0, ios::beg);
            FicheProductos.write((char*)&NProduc, sizeof(int));
            estaEliminado = true;
        }
    }
    return estaEliminado;
}//fin del m�todo EliminarProducto

/*
    M�todo que carga la lista de env�os a partir del nombre del fichero que se le pasa por par�metro.
    El fichero tiene una sucesi�n de elementos de tipo TPedido
*/
bool TAlmacen::CargarListaEnvios(Cadena Nomf){
    bool estaCargado = false;
    ifstream ficheEnvios;
    while(!Envios.esvacia()){
        Envios.eliminarIzq();
    }
    TPedido pedido;
    ficheEnvios.open(Nomf,ios::in | ios::binary);
    if(!ficheEnvios.fail()){
        ficheEnvios.read((char*)&pedido, sizeof(TPedido));
        while(!ficheEnvios.eof()){
            Envios.anadirDch(pedido);
            ficheEnvios.read((char*)&pedido, sizeof(TPedido));
        }
        estaCargado = true;
        ficheEnvios.close();
    }
    return estaCargado;
}//fin del m�todo CargarListaEnvios

/*
    M�todo que carga la cola de pedidos a partir del nombre del fichero que se le pasa por par�metro.
    El fichero tiene una sucesi�n de elementos de tipo TPedido
*/
bool TAlmacen::CargarColaPedidos(Cadena Nomf){
    bool estaCargado = false;
    ifstream fichePedido;
    while(!Pedidos.esvacia()){
        Pedidos.desencolar();
    }
    TPedido pedido;
    fichePedido.open(Nomf, ios::binary);
    if(!fichePedido.fail()){
        fichePedido.read((char*)&pedido, sizeof(TPedido));
        while(!fichePedido.eof()){
            Pedidos.encolar(pedido);
            fichePedido.read((char*)&pedido, sizeof(TPedido));
        }
        estaCargado = true;
        fichePedido.close();
    }
    return estaCargado;
}//fin del m�todo CargarColaPedidos

//A�adir� un nuevo pedido a la cola de pedidos
void TAlmacen::AnadirPedido (TPedido p){
    TPedido aux;
  bool anadido=false;
    int i=1;
  while(i<=Pedidos.longitud() && !anadido)
	{
		aux=Pedidos.primero();
		if(strcmp(aux.CodProd,p.CodProd)==0)
		{
			if(strcmp(aux.Nomtienda,p.Nomtienda)==0)
			{
				aux.CantidadPed=p.CantidadPed+aux.CantidadPed;
				Pedidos.encolar(aux);
				anadido=true;
			}
			else{i++;Pedidos.encolar(aux);Pedidos.desencolar();}

		}
		else{i++;Pedidos.encolar(aux);Pedidos.desencolar();}
	}


if(!anadido)  Pedidos.encolar(p);
}//fin del m�todo AnadirPedido

/*
    M�todo que atiende los pedidos del producto en cuesti�n pendientes de suministrar con la cantidad
    comprada por el almac�n, los incorpora a la lista de Env�os, eliminando de la cola de pedidos los
    pedidos atendidos.
    Si alg�n pedido es atendido parcialmente por que se acabe el producto, la cola se modificar�
    modificando y dejando pendiente la cantidad correspondiente, introduciendo en la lista de Envios
    la cantidad que se puede suministrar.
    Si el producto comprado excede de la cantidad pendiente de servir en los pedidos, la cantidad
    sobrante, entra en el Almac�n.
*/
bool TAlmacen::AtenderPedidos(Cadena CodProd,int cantidadcomprada){
    bool atendido = true;
    cola auxCola;
    TPedido pedido;
    TProducto prod;
    if(BuscarProducto(CodProd)!=-1){
        while(!Pedidos.esvacia() && cantidadcomprada!=0){
            pedido = Pedidos.primero();
            if(strcmp(CodProd, pedido.CodProd)== 0){
                if(cantidadcomprada<=pedido.CantidadPed){
                    pedido.CantidadPed = (pedido.CantidadPed-cantidadcomprada);
                    if(pedido.CantidadPed>0){
                        auxCola.encolar(pedido);
                    }
                    pedido.CantidadPed = cantidadcomprada;
                    InsertarEnvios(pedido);
                    cantidadcomprada = 0;
                }
                else{
                    InsertarEnvios(pedido);
                    cantidadcomprada = cantidadcomprada-pedido.CantidadPed;
                }
            }
            else{
                auxCola.encolar(pedido);
            }
            Pedidos.desencolar();
        }
        if(cantidadcomprada>0){
            prod = ObtenerProducto(BuscarProducto(CodProd));
            prod.Cantidad = prod.Cantidad + cantidadcomprada;
            ActualizarProducto(BuscarProducto(CodProd), prod);
        }
        while(!auxCola.esvacia()){
            Pedidos.encolar(auxCola.primero());
            auxCola.desencolar();
        }
    }
    else{
        atendido = false;
    }
    return atendido;
}//fin del m�todo AtenderPedidos

/*
    Muestra el contenido completo, con todos los datos de los productos le�dos del almac�n, de la cola
    si CodProd es '' o muestra los pedidos del Codprod pasado con todos sus datos del almac�n.
    pasado por par�metro
*/
void TAlmacen::ListarPedidosCompleto(Cadena CodProd){
    if(Pedidos.longitud()<=0){
        cout.width(10);
        cout << " ";
        cout << "No hay ning�n pedido a listar" << endl;
    }
    else{
        TPedido pedido;
        cola auxCola;
        TProducto prod;
        while(!Pedidos.esvacia()){
            pedido = Pedidos.primero();
            auxCola.encolar(pedido);
            prod = ObtenerProducto(BuscarProducto(pedido.CodProd));
            Pedidos.desencolar();
            if(strcmp("", CodProd)== 0 || strcmp(CodProd, pedido.CodProd)==0){
                Cadena cod;
                strcpy(cod, "CODIGO");
                Cadena nom;
                strcpy(nom, "NOMBRE");
                Cadena pre;
                strcpy(pre, "PRECIO");
                Cadena cantAlm;
                strcpy(cantAlm, "CANTIDAD ALMAC�N");
                Cadena cantPed;
                strcpy(cantPed, "CANTIDAD PEDIDO");
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
                cout.width(13);
                cout << pre;
                cout.width(20);
                cout << cantAlm;
                cout.width(20);
                cout << cantPed;
                cout << fec;
                cout << endl;
                if(strcmp(prod.CodProd, "NULO")!=0){
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << prod.CodProd;
                    cout.width(32);
                    cout << prod.NombreProd;
                    cout.width(19);
                    cout << fixed << setprecision(2) << prod.Precio;
                    cout.width(19);
                    cout << prod.Cantidad;
                    cout.width(18);
                    cout << pedido.CantidadPed;
                    cout << prod.Caducidad.Dia <<"/" << prod.Caducidad.Mes << "/" << prod.Caducidad.Anyo << endl;
                }
                else{
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << pedido.CodProd;
                    cout.width(32);
                    cout << "?????";
                    cout.width(19);
                    cout << "?????";
                    cout.width(19);
                    cout << "?????";
                    cout.width(18);
                    cout << pedido.CantidadPed;
                    cout << "?????" << endl;
                }

                cout.setf(ios::right, ios::adjustfield);
            }
        }
        while(!auxCola.esvacia()){
            pedido = auxCola.primero();
            Pedidos.encolar(pedido);
            auxCola.desencolar();
        }
    }

}//fin del m�todo ListarPedidosCompleto

/*
    Muestra la cantidad pendiente de cada tipo de producto si CodProd es '' o del producto concreto
    que se pase por par�metro
*/
void TAlmacen::ListarCantidadesPendientes(Cadena CodProd){
    int cantTotal = 0;
    cola auxCola1, auxCola2;
    TPedido pedido, auxPedido;
    cout.setf(ios::left, ios::adjustfield);
    cout.width(8);
    cout << " ";
    cout.width(20);
    cout << "C�DIGO PEDIDO";
    cout.width(20);
    cout << "NOMBRE PRODUCTO";
    cout << "CANTIDAD TOTAL" << endl;
    if(strcmp(CodProd, "")==0){
        while(!Pedidos.esvacia()){
            auxCola1.encolar(Pedidos.primero());
            auxCola2.encolar(Pedidos.primero());
            Pedidos.desencolar();
        }
        while(!Pedidos.esvacia() || !auxCola2.esvacia()){
            cantTotal = 0;
            strcpy(pedido.CodProd, auxCola2.primero().CodProd);
            while(!auxCola2.esvacia()){
                if(strcmp(pedido.CodProd, auxCola2.primero().CodProd)==0){
                    cantTotal += auxCola2.primero().CantidadPed;
                }
                else{
                    Pedidos.encolar(auxCola2.primero());
                }
                auxCola2.desencolar();
            }
            while(!Pedidos.esvacia()){
                auxCola2.encolar(Pedidos.primero());
                Pedidos.desencolar();
            }
            cout.width(8);
            cout << " ";
            cout.width(20);
            cout << pedido.CodProd;
            cout.width(25);
            if(BuscarProducto(pedido.CodProd)!=-1){
                cout << ObtenerProducto(BuscarProducto(pedido.CodProd)).NombreProd;
            }
            else{
                cout << "?????";
            }
            cout << cantTotal << endl;
        }
    }
    else{
        while(!Pedidos.esvacia()){
            pedido = Pedidos.primero();
            if(strcmp(pedido.CodProd, CodProd)==0){
                cantTotal += pedido.CantidadPed;
            }
            auxCola1.encolar(pedido);
            Pedidos.desencolar();
        }
        cout.width(8);
        cout << " ";
        cout.width(20);
        cout << CodProd;
        cout.width(25);
        cout << ObtenerProducto(BuscarProducto(CodProd)).NombreProd;
        cout << cantTotal << endl;
    }
    cout.setf(ios::right, ios::adjustfield);
    while(!auxCola1.esvacia()){
        Pedidos.encolar(auxCola1.primero());
        auxCola1.desencolar();
    }

}//fin del m�todo ListarCantidadesPendientes

/*
    Se encarga de meter en la lista de env�os, de forma ordenada, por nombre del fichero de tienda, el
    pedido a enviar
*/
bool TAlmacen::InsertarEnvios(TPedido p){
    bool insertado = false;
    int i = 1;
    while(i<=Envios.longitud() && !insertado){
        if(strcmp(Envios.observar(i).Nomtienda, p.Nomtienda) == 1){
            Envios.insertar(i, p);
            insertado = true;
        }
        i++;
    }
    return insertado;
}//fin del m�todo InsertarEnvios

/*
    Se encarga de sacar de la lista los env�os que tienen por destino la tienda que se le pasa por
    par�metro mostrando por pantalla los env�os que van en el cami�n
*/
bool TAlmacen::SalidaCamionTienda(Cadena NomTienda){
    bool estaFuera = false;
    TProducto prod;
    TPedido pedido;
    int i = 1;
    Cadena tien;
    strcpy(tien, "TIENDA");
    Cadena cod;
    strcpy(cod, "CODIGO");
    Cadena nom;
    strcpy(nom, "NOMBRE");
    Cadena pre;
    strcpy(pre, "PRECIO");
    Cadena cantAlm;
    strcpy(cantAlm, "CANTIDAD ALMAC�N");
    Cadena cantPed;
    strcpy(cantPed, "CANTIDAD PEDIDO");
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
    cout.width(13);
    cout << pre;
    cout.width(20);
    cout << cantAlm;
    cout.width(20);
    cout << cantPed;
    cout.width(20);
    cout << fec;
    cout << tien;
    cout << endl;
    while(i<=Envios.longitud()){
        pedido = Envios.observar(i);
        if(strcmp(Envios.observar(i).Nomtienda, NomTienda) == 0){
            prod = ObtenerProducto(BuscarProducto(pedido.CodProd));
            if(strcmp(prod.CodProd, "NULO")!=0){
                cout.setf(ios::left, ios::adjustfield);
                cout.width(8);
                cout << " ";
                cout.width(10);
                cout << prod.CodProd;
                cout.width(32);
                cout << prod.NombreProd;
                cout.width(19);
                cout << fixed << setprecision(2) << prod.Precio;
                cout.width(19);
                cout << prod.Cantidad;
                cout.width(18);
                cout << pedido.CantidadPed;
                cout << prod.Caducidad.Dia <<"/" << prod.Caducidad.Mes << "/";
                cout.width(12);
                cout << prod.Caducidad.Anyo;
                cout << pedido.Nomtienda << endl;
            }
            else{
                cout.width(8);
                cout << " ";
                cout.width(10);
                cout << pedido.CodProd;
                cout.width(32);
                cout << "?????";
                cout.width(19);
                cout << "?????";
                cout.width(19);
                cout << "?????";
                cout.width(18);
                cout << pedido.CantidadPed;
                cout.width(12);
                cout << "?????";
                cout << pedido.Nomtienda << endl;
            }
            cout.setf(ios::right, ios::adjustfield);
            Envios.eliminar(i);
            i--;
            estaFuera = true;
        }
        i++;
    }
    return estaFuera;
}//fin del m�todo SalidaCamionTienda

/*
    Si recibe Nomtienda a '' muestra por pantalla todo el contenido de la lista de env�os.
    Si se le pasa el nombre de una tienda muestra por pantalla los env�os a dicha tienda
*/
void TAlmacen::ListarListaEnvios(Cadena Nomtienda){
    if(Envios.longitud()<=0){
        cout.width(10);
        cout << " ";
        cout << "No hay ning�n env�o a listar" << endl;
    }
    else{
        TPedido pedido;
        TProducto prod;
        for(int i=1;i<=Envios.longitud();i++){
            pedido = Envios.observar(i);
            prod = ObtenerProducto(BuscarProducto(pedido.CodProd));
            if(strcmp("", Nomtienda)== 0 || strcmp(Nomtienda, pedido.Nomtienda)==0){
                Cadena tien;
                strcpy(tien, "TIENDA");
                Cadena cod;
                strcpy(cod, "CODIGO");
                Cadena nom;
                strcpy(nom, "NOMBRE");
                Cadena pre;
                strcpy(pre, "PRECIO");
                Cadena cantAlm;
                strcpy(cantAlm, "CANTIDAD ALMAC�N");
                Cadena cantPed;
                strcpy(cantPed, "CANTIDAD PEDIDO");
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
                cout.width(13);
                cout << pre;
                cout.width(20);
                cout << cantAlm;
                cout.width(20);
                cout << cantPed;
                cout.width(20);
                cout << fec;
                cout << tien;
                cout << endl;
                if(strcmp(prod.CodProd, "NULO")!=0){
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << prod.CodProd;
                    cout.width(32);
                    cout << prod.NombreProd;
                    cout.width(19);
                    cout << fixed << setprecision(2) << prod.Precio;
                    cout.width(19);
                    cout << prod.Cantidad;
                    cout.width(18);
                    cout << pedido.CantidadPed;
                    cout << prod.Caducidad.Dia <<"/" << prod.Caducidad.Mes << "/";
                    cout.width(12);
                    cout << prod.Caducidad.Anyo;
                    cout << pedido.Nomtienda << endl;
                }
                else{
                    cout.width(8);
                    cout << " ";
                    cout.width(10);
                    cout << pedido.CodProd;
                    cout.width(32);
                    cout << "?????";
                    cout.width(19);
                    cout << "?????";
                    cout.width(19);
                    cout << "?????";
                    cout.width(18);
                    cout << pedido.CantidadPed;
                    cout.width(12);
                    cout << "?????";
                    cout << pedido.Nomtienda << endl;
                }
                cout.setf(ios::right, ios::adjustfield);
            }
        }
        if(strcmp(Nomtienda,"")!=0 && strcmp(Nomtienda, pedido.Nomtienda)!=0){
            cout.width(10);
            cout << " ";
            cout << "No hay ning�n env�o para " << Nomtienda << endl;
        }
    }

}//fin del m�todo ListarListaEnvios

//M�todo que vuelca en el fichero nomf la cola de pedidos
bool TAlmacen::SalvarColaPedidos(Cadena Nomf){
    bool estaSalvada = false;
    TPedido pedido;
    ofstream fichePedidos;
    fichePedidos.open(Nomf,ios::binary);
    if(!fichePedidos.fail()){
        fichePedidos.seekp(0, ios::beg);
        while(!Pedidos.esvacia()){
            pedido = Pedidos.primero();
            fichePedidos.write((char*)&pedido, sizeof(TPedido));
            Pedidos.desencolar();
        }
        estaSalvada = true;
        fichePedidos.close();
    }
    return estaSalvada;
}//fin del m�todo SalvarColaPedidos

//M�todo que vuelca en el fichero nomf la lista de env�os
bool TAlmacen::SalvarListaEnvios(Cadena Nomf){
    bool estaSalvada = false;
    TPedido pedido;
    ofstream ficheEnvios;
    ficheEnvios.open(Nomf, ios::binary);
    if(!ficheEnvios.fail()){
        ficheEnvios.seekp(0, ios::beg);
        while(!Envios.esvacia()){
            pedido = Envios.observarIzq();
            ficheEnvios.write((char*)&pedido, sizeof(TPedido));
            Envios.eliminarIzq();
        }
        estaSalvada = true;
        ficheEnvios.close();
    }
    return estaSalvada;
}//fin del m�todo SalvarListaEnvios

void TAlmacen::generarpedidosporstockminimo(int stockminimo){
   /* TPedido ped;
    TProducto pr;
    ofstream f;
    f.open(FicheProductos,ios::binary);
    if(!f.fail()){
        f.seekg(sizeof(int)+sizeof(Cadena)*2  , ios::beg);
        f.read((char*) &pr, sizeof(TProducto));
    while(!f.eof){
        if(pr.Cantidad < stockminimo)
        {
            strcpy(ped.CodProd, pr.CodProd);
            ped.CantidadPed = stockminimo - pr.Cantidad;
            AnadirPedido(ped);
        }
	f.read((char*) &pr, sizeof(TProducto));
    }
}*/
}



