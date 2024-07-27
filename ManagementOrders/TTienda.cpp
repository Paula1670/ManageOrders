#include "TTienda.h"

using namespace std;

//  Constructor que debe inicializar los atributos de la clase.
TTienda::TTienda()
{
    //ctor
    strcpy(Nombre, "");
    strcpy(Direccion, "");
    strcpy(NomFiche, "");
    Estantes = NULL;
    NEstan = -1;
    Tamano = -1;
}//fin del constructor

//  Destructor que cerrar� la tienda en caso de que el usuario no lo haya hecho.
TTienda::~TTienda()
{
    //dtor
    CerrarTienda();
    if(Estantes!= NULL){
        delete [] Estantes;
    }
    Estantes = NULL;
    NEstan = Tamano = -1;
}//fin del destructor

//  Devuelve los atributos nombre y direcci�n por par�metro.
void TTienda::DatosTienda(Cadena pNombTienda, Cadena pDirTienda){
    strcpy(pNombTienda, Nombre);
    strcpy(pDirTienda, Direccion);
}//fin del m�todo DatosTienda

//Devuelve el atributo del nombre del fichero de la tienda
void TTienda::NombreFicheroTienda(Cadena NomF){
    strcpy(NomF, NomFiche);
}//fin del m�todo NombreFicheroTienda

/*  Crea un fichero binario vac�o con el nombre pasado por par�metro e inicializa los atributos nombre y
    direcci�n mediante los par�metros y a continuaci�n lo cerrar�. Devolver� true si ha podido crear el
    fichero.
*/

bool TTienda::CrearTienda(Cadena pNombTienda, Cadena pDirTienda, Cadena pNomFiche){
    bool estaCreada = false;
    strcpy(Nombre, pNombTienda);
    strcpy(Direccion, pDirTienda);
    Tamano = Incremento;
    NEstan = 0;
    Estantes = new TEstante[Tamano];
    fstream ficheTienda;
    ficheTienda.open(pNomFiche, ios::in | ios::out | ios::binary);
    if(ficheTienda.fail()){
        ficheTienda.close();
        ficheTienda.clear();
        ficheTienda.open(pNomFiche, ios::out | ios::binary); // se crea el fichero
        if(ficheTienda.fail()){ // si no se puede crear
            ficheTienda.clear();
            ficheTienda.close();
            estaCreada;
        }
        else{
            Estantes = new TEstante[Tamano];
            NEstan = 0;
            ficheTienda.seekp(0);
            ficheTienda.write((char*) Nombre, sizeof(Cadena));
            ficheTienda.write((char*) Direccion, sizeof(Cadena));
            estaCreada = true;
        }
    }
    else{
        Estantes = new TEstante[Tamano];
        NEstan = 0;
        ficheTienda.seekp(0);
        ficheTienda.write((char*) Nombre, sizeof(Cadena));
        ficheTienda.write((char*) Direccion, sizeof(Cadena));
        estaCreada = true;
    }
    ficheTienda.close();

    return estaCreada;
}//fin del m�todo CrearTienda

/*  Abre un fichero y lo carga a memoria. Si ya hab�a un fichero previamente cargado, guardar� los datos
    de la tienda y proceder� a cargar el nuevo fichero. Si el fichero es el mismo que el que est� en
    memoria, eliminar� los datos y proceder� a cargar nuevamente los datos del fichero. Devolver� true
    si se ha podido cargar el fichero.
*/
bool TTienda::AbrirTienda(Cadena pNomFiche){
    bool estaAbierta = false;
    fstream FicheTienda;
    if (EstaAbierta()){
        if(strcmp(pNomFiche,NomFiche)!=0){
            GuardarTienda();
        }
    }
    else{
        FicheTienda.open(pNomFiche, ios::in|ios::out|ios::binary);
        if(!FicheTienda.fail()){
            FicheTienda.seekg(0,ios::beg);
            FicheTienda.read((char*)Nombre, sizeof(Cadena));
            FicheTienda.read((char*)Direccion, sizeof(Cadena));
            FicheTienda.seekg(0,ios::end);
            NEstan=(FicheTienda.tellg()-sizeof(Cadena)*2)/sizeof(TEstante);

            Tamano=NEstan+Incremento;
            Estantes=new TEstante[Tamano];

            if (Estantes!=NULL){
                FicheTienda.seekg(sizeof(Cadena)*2,ios::beg);
                FicheTienda.read((char*) Estantes, NEstan*sizeof(TEstante));
                estaAbierta= true;
                strcpy(NomFiche,pNomFiche);
            }
        }
        FicheTienda.close();
    }
    return estaAbierta;
}//fin del m�todo AbrirTienda

//  Vuelca los datos de la memoria al fichero. Devolver� true si se han guardado los datos.
bool TTienda::GuardarTienda(){
    bool estaGuardada = false;
    fstream FicheTienda;
    if (EstaAbierta()){
        FicheTienda.open(NomFiche, ios::binary|ios::out);
        if (!FicheTienda.fail()){
            //FicheTienda.seekp(sizeof(Cadena)*2, ios::beg);
            FicheTienda.seekp(0, ios::beg);
            FicheTienda.write((char*)Nombre, sizeof(Cadena));
            FicheTienda.write((char*)Direccion, sizeof(Cadena));
            FicheTienda.write((char*)Estantes,NEstan*sizeof(TEstante));
            estaGuardada=true;
            FicheTienda.close();
        }
    }
    return estaGuardada;
}//fin del m�todo GuardarTienda

/*  Guarda los datos de la memoria en el fichero y borra todos los atributos del objeto. Devuelve true
    si se ha podido guardar los datos.
*/
bool TTienda::CerrarTienda(){
    bool estaCerrada = false;
    fstream ficheTienda;
    GuardarTienda();
    strcpy(Nombre, "");
    strcpy(Direccion, "");
    strcpy(NomFiche, "");
    if(Estantes!= NULL){
        delete [] Estantes;
        Estantes = NULL;
    }
    NEstan = -1;
    Tamano = -1;
    ficheTienda.close();
    estaCerrada = true;
    return estaCerrada;
}//fin del m�todo CerrarTienda

//  Devuelve true si la tienda est� abierta.
bool TTienda::EstaAbierta(){
    bool estaAbierta = false;
    if(Estantes != NULL){
        estaAbierta = true;
    }
    return estaAbierta;
}//fin del m�todo EstaAbierta

//  Devuelve el n�mero de estantes de la tienda.
int TTienda::NoEstantes(){
    return NEstan;
}//fin del m�todo NoEstantes

/*  Dado un c�digo de estante, devuelve la posici�n dentro del vector donde se encuentra. Si no lo
    encuentra devuelve -1.
*/
int TTienda::BuscarEstante(int pCodEstante){
    int pos = -1, i=0;
    bool encontrado = false;
    while(i<NEstan && !encontrado){
        if(pCodEstante==Estantes[i].CodEstante){
            pos = i;
            encontrado = true;
        }
        else{
            i++;
        }
    }
    return pos;
}//fin del m�todo BuscarEstante

//  Dado la posici�n el estante que est� en la posici�n indicada por par�metro.
TEstante TTienda::ObtenerEstante(int pPos){
    if((pPos >=0) && (pPos < NEstan)){
        return Estantes[pPos];
    }
}//fin del m�todo ObtenerEstante

/*A�ade un estante nuevo al vector siempre que el estante no est� previamente almacenado en memoria.
El vector de estantes debe siempre estar ordenado. Devolver� true si se ha a�adido el estante.
*/
bool TTienda::AnadirEstante(TEstante pEstante){
    bool estaAnadido = false;
    if (EstaAbierta()){
        int pos=BuscarEstante(pEstante.CodEstante);
        if (pos==-1){
            if(NEstan==Tamano){
                Tamano=Tamano+Incremento;
                TEstante *aux= new TEstante[Tamano];
                for (int i=0; i<NEstan; i++){
                    aux[i]=Estantes[i];
                }
                delete [] Estantes;
                Estantes=aux;
            }
            Estantes[NEstan]=pEstante;
            NEstan++;
            estaAnadido=true;
        }
        OrdenarProductos();
    }
    return estaAnadido;
}//fin del m�todo AnadirEstante

/*  Dado la posici�n de un estante lo borra desplazando el resto de estantes una posici�n hacia abajo.
    Se debe verificar previamente que la posici�n sea correcta. Devuelve true si se ha eliminado el
    estante.
    */
bool TTienda::EliminarEstante(int pPos){
    bool estaEliminado = false;
    if(EstaAbierta()){
        if(pPos>=0 && pPos<NEstan){
            for(int i=pPos;i<NEstan;i++){
                Estantes[i] = Estantes[i+1];
            }
            NEstan--;
            if(Tamano-NEstan>=Incremento && Tamano>Incremento){
                Tamano -= Incremento;
                TEstante *temp = new TEstante[Tamano];
                for(int i=0;i<NEstan;i++){
                    temp[i] = Estantes[i];
                }
                delete [] Estantes;
                Estantes = temp;
            }
            estaEliminado = true;
        }
        OrdenarProductos();
    }

    return estaEliminado;
}//fin del m�todo EliminarEstante

/*  Dada la posici�n de un estante, lo actualiza con los datos pasados por par�metros. Se debe verificar
    previamente que la posici�n sea correcta Devuelve true si se actualiza el estante.
*/
bool TTienda::ActualizarEstante(int pPos, TEstante pEstante){
    bool estaActualizado = false;
    if(pPos >= 0 && pPos <= NEstan){
        Estantes[pPos] = pEstante;
        OrdenarProductos();
        estaActualizado = true;;
    }
    return estaActualizado;
}//fin del m�todo ActualizarEstante

/*  Dada la posici�n de un estante y un producto del almac�n, actualizar� el n�mero de productos del
    estante a su m�xima capacidad si hay suficientes unidades en el producto, en caso contrario se
    a�adir�n al estante la totalidad de unidades que est�n en el producto del almac�n. El mismo n�mero
    de unidades a�adidas en el estante deben reducirse del producto. Se debe verificar previamente que
    la posici�n sea correcta. El m�todo devuelve:
    0 si la posici�n es incorrecta.
    1 si se ha repuesto unidades hasta llegar a la capacidad m�xima del estante.
    2 si no se ha completado el estante al completo.
*/
int TTienda::ReponerEstante(int pPos, TProducto &pProduc){
    int repu = 0;
    if(pPos>=0 && pPos<NEstan){
        int diferencia = Estantes[pPos].Capacidad - Estantes[pPos].NoProductos;
        if(diferencia<=pProduc.Cantidad){
            pProduc.Cantidad -= diferencia;
            Estantes[pPos].NoProductos += diferencia;
            repu = 1;
        }
        if(diferencia>pProduc.Cantidad){
            Estantes[pPos].NoProductos += pProduc.Cantidad;
            pProduc.Cantidad = 0;
            repu = 2;
        }
    }
    return repu;
}//fin del m�todo ReponerEstante

/*  M�todo privado para ordenar los estantes del vector. La ordenaci�n se realizar� por el c�digo de
    producto en orden ascendente. En caso de tener el mismo c�digo se ordenar� por la posici�n del
    producto en el estante en orden ascendente.
*/

/*)
    Este m�todo devuelve el c�digo del estante cuyo c�digo de producto coincide con el pasado por el par�metro pCodProd.
    En caso de no existir ning�n estante que contenga el producto, el m�todo devolver� -1;

int TTienda::BuscarProducto(Cadena pCodPro){
        int pos, i=0, codEstDevolver;
    bool encontrado = false;
    while(i<NEstan && !encontrado){
        if(strcmp(pCodPro, Estantes[i].CodProd)==0){
            pos = i;
            encontrado = true;
        }
        else{
            i++;
        }
    }
    if(encontrado){
        codEstDevolver = Estantes[i].CodEstante;
    }
    else{
        codEstDevolver = -1;
    }
    return codEstDevolver;
}
*/


void TTienda::OrdenarProductos(){
    TEstante aux;
    for(int i=0; i<NEstan; i++){
        for(int j=i+1; j<NEstan; j++){
            if (strcmp(Estantes[i].CodProd,Estantes[j].CodProd)>0){
                aux=Estantes[i];
                Estantes[i]=Estantes[j];
                Estantes[j]=aux;
            }
            else{
                if(strcmp(Estantes[i].CodProd,Estantes[j].CodProd)==0){
                    if(Estantes[i].Posicion>Estantes[j].Posicion){
                        aux=Estantes[i];
                        Estantes[i]=Estantes[j];
                        Estantes[j]=aux;
                    }
                }
            }
        }
    }
}//fin del men� OrdenarProductos
