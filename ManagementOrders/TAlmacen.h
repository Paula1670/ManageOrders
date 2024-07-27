#ifndef TALMACEN_H
#define TALMACEN_H
#include "TTipos.h"
#include "TADcola.h"
#include "TADlista.h"

using namespace std;

class TAlmacen
{
    Cadena Nombre; //Nombre del almacén.
    Cadena Direccion; //Dirección del almacén.
    fstream FicheProductos; //Fichero que almacena los productos del almacén.
    int NProduc; //Número de productos que hay en el almacén. Si el almacén está cerrado
                //deberá tener el valor -1.
    cola Pedidos;    //estructura de tipo cola que almacena los pedidos
    lista Envios;    //estructura de tipo lista que almacena los pedidos a enviar
public:
    TAlmacen(); //Constructor que debe inicializar los atributos de la clase.
    ~TAlmacen(); //Destructor que cerrará el almacén en caso de que el usuario no lo haya hecho.
    //Devuelve los atributos nombre y dirección por parámetro.
    void DatosAlmacen(Cadena pNombAlmacen, Cadena pDirAlmacen);
    //Crea un fichero binario vacío con el nombre pasado por parámetro. Crea la cabecera del fichero
    //y lo deja abierto para su utilización. Devuelve true si se ha creado.
    bool CrearAlmacen(Cadena pNomFiche);
    //Igual que el método anterior, pero actualizando los atributos nombre y dirección con los valores
    //pasados por parámetro. Devuelve true si ha podido crear el fichero.
    bool CrearAlmacen(Cadena pNombAlmacen, Cadena pDirAlmacen, Cadena pNomFiche);
    //Abre un fichero y actualiza los atributos de la clase con los datos de cabecera del fichero y lo
    //lo deja abierto. No se puede abrir un fichero si previamente el almacén está abierto. Devuelve true
    //si ha podido abrir el fichero.
    bool AbrirAlmacen(Cadena pNomFiche);
    //Cierra el fichero e inicializa los atributos a valores iniciales. Devuelve true si se ha cerrado el
    //almacén.
    bool CerrarAlmacen();
    bool EstaAbierto(); //Devuelve true si el fichero está abierto.
    int NProductos(); //Devuelve el número de productos.
    //Dado un código de producto, devuelve la posición dentro del fichero donde se encuentra. Si no
    //lo encuentra devuelve -1.
    int BuscarProducto(Cadena pCodProd);
    //Dado la posición devuelve el producto del fichero situado en dicha posición. Debe verificar
    //previamente que la posición sea correcta. Si la posición no es correcta devolverá un producto cuyo
    //código tendrá el valor “NULO”.
    TProducto ObtenerProducto(int pPos);
    //Dado un producto, lo busca en el fichero y si no lo encuentra lo añade al final del fichero.
    //Devuelve true si se ha añadido el producto.
    bool AnadirProducto(TProducto pProduc);
    //Dada la posición de un producto en el fichero lo actualiza con la información del producto pasado
    //por parámetro. Devuelve true si se ha actualizado el producto. Se debe verificar previamente que la
    //posición sea correcta.
    bool ActualizarProducto(int pPos, TProducto pProduc);
    //Dado la posición de un producto en el fichero lo borra. Devuelve true si se ha podido borrar. Se
    //debe verificar que la posición sea correcta.
    bool EliminarProducto(int pPos);

    //Método que carga la lista de envíos a partir del nombre del fichero que se le pasa por parámetro.
    //El fichero tiene una sucesión de elementos de tipo TPedido
    bool CargarListaEnvios(Cadena Nomf);

    //Método que carga la cola de pedidos a partir del nombre del fichero que se le pasa por parámetro.
    //El fichero tiene una sucesión de elementos de tipo TPedido
    bool CargarColaPedidos(Cadena Nomf);

    //Añadirá un nuevo pedido a la cola de pedidos
    void AnadirPedido (TPedido p);

    //Método que atiende los pedidos del producto en cuestión pendientes de suministrar con la cantidad
    //comprada por el almacén, los incorpora a la lista de Envíos, eliminando de la cola de pedidos los
    //pedidos atendidos.
    //Si algún pedido es atendido parcialmente por que se acabe el producto, la cola se modificará
    //modificando y dejando pendiente la cantidad correspondiente, introduciendo en la lista de Envios
    //la cantidad que se puede suministrar.
    //Si el producto comprado excede de la cantidad pendiente de servir en los pedidos, la cantidad
    //sobrante, entra en el Almacén.
    bool AtenderPedidos(Cadena CodProd,int cantidadcomprada);

    //Muestra el contenido completo, con todos los datos de los productos leídos del almacén, de la cola
    //si CodProd es '' o muestra los pedidos del Codprod pasado con todos sus datos del almacén.
    //pasado por parámetro
    void ListarPedidosCompleto(Cadena CodProd);

    //Muestra la cantidad pendiente de cada tipo de producto si CodProd es '' o del producto concreto
    //que se pase por parámetro
    void ListarCantidadesPendientes(Cadena CodProd);

    //Se encarga de meter en la lista de envíos, de forma ordenada, por nombre del fichero de tienda, el
    //pedido a enviar
    bool InsertarEnvios(TPedido p);

    //Se encarga de sacar de la lista los envíos que tienen por destino la tienda que se le pasa por
    //parámetro mostrando por pantalla los envíos que van en el camión
    bool SalidaCamionTienda(Cadena NomTienda);

    //Si recibe Nomtienda a '' muestra por pantalla todo el contenido de la lista de envíos.
    //Si se le pasa el nombre de una tienda muestra por pantalla los envíos a dicha tienda
    void ListarListaEnvios(Cadena Nomtienda);

    //Método que vuelca en el fichero nomf la cola de pedidos
    bool SalvarColaPedidos(Cadena Nomf);

    //Método que vuelca en el fichero nomf la lista de envíos
    bool SalvarListaEnvios(Cadena Nomf);

    //Método para leer la cabecera del Almacen.
    void cabecera(Cadena pNombAlmacen, Cadena pDirAlmacen);
    void generarpedidosporstockminimo(int stockminimo);
};
#endif // TALMACEN_H
