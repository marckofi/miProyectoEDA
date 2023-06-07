#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//NOTAS

/*


 Modificar extrer inicio para que no vea tan fea. Usar variable de ayuda aux. 

 //Checa si no es necesario hacer el cast a lista_doble * cuando liberas el campo info de uno nodo de la cola de pedidos.

Revisar los fflush stdin , en especial en la funcion agregarPedido.



*/

//Estructura del Producto
typedef struct Producto{
    char nombre[30];
    float precio;
    int cantidad;
    int id;
}Producto;

//Nodo para lista doble
typedef struct nodo_doble {
    void * info;
    struct nodo_doble * next;
    struct nodo_doble * prev;
}nodo_doble;

//Estructura de acceso para lista doble.
typedef struct lista_doble {
    struct nodo_doble * head;
    struct nodo_doble * tail;
    char nombre[50];
    int size;
}lista_doble;

//Estructura para la ventas. La pila guardará direcciones de este tipo de estructuras.
typedef struct Venta{
    float total; 
    lista_doble * id_pedido;
}Venta;

//Estructuras de la pila de ventas.

typedef struct PilaVentas {
    int tope;           
    struct Venta** pila;   
    int max_tamanio;  //Tamaño maximo que puede tener la pila
}pila_ventas;




//Funciones para la pila de ventas

pila_ventas * crearPila();
int isFull(pila_ventas * pila);
int isEmpty(pila_ventas * pila);
int push(pila_ventas *pila_v, Venta * venta);//Retornará cero en caso de que no se haya podido redimensionar la pila.
void imprimirVenta(Venta * venta);
void imprimirPilaVentas(pila_ventas * pila_v);

float ObtenerTotalPedido(lista_doble * pedido);
void eliminarPilaVentas(pila_ventas * pila_de_ventas);



//Funciones para pasar de archivo a lista_productos y de lista_productos a archivo. 


// Función para guardar el inventario en un archivo
void guardarInventario(lista_doble * lista_productos);


//Función para cargar el inventario desde el archivo. 
lista_doble* cargarInventario();

//Funciones de lista doble.


lista_doble * crearListaDoble();
int listaVacia(lista_doble  * lista); 
void agregarInicioLD(lista_doble* lista_d, void * informacion);
void agregarFinalLD(lista_doble * lista_d, void * informacion); 
int eliminarInicioLD(lista_doble* lista_d); 
int eliminarFinalLD(lista_doble* lista_d);
nodo_doble * extraerInicioLD(lista_doble* lista_d);
nodo_doble * extraerFinalLD(lista_doble* lista_d); 
void eliminarListaD(lista_doble* lista_d);

//Funciones para lista de productos.
nodo_doble *  extraerEnMedioLDProductos(lista_doble * lista_d, int valor);
void imprimirListaDProducto(lista_doble* lista_d);  //Imprimir lista doblemente ligada de productos.
Producto * buscarNodoPorId(lista_doble* lista_d, int idBuscado);

//Funciones para el producto.
void llenarProducto(Producto * producto, char nombre[], float precio, int cantidad, int id); 
void imprimirProducto(Producto p); 
Producto * crearProducto(void); //Función que retorna una dirección que apunta a una structura Producto.


void actualizarProducto(Producto * producto, int nueva_cantidad, float nuevo_precio);  //Función para actualizar cantidad y precio del producto. 

//Funciones para la cola de pedidos

void imprimirColaPedidos(lista_doble * cola_pedidos); /*La cola de pedidos es una lista doblemente ligada implementada como cola. 
En el campo  de los nodos se almacena una lista_doble la cual representa un pedido.*/

void eliminarColaPedidos(lista_doble * cola_pedidos);
//Funciones para el menu y para leer entrada desde el teclado. 

/*Función para evaluar si hay existencia de al menos un producto. 
Retornara valor entero equivalente a verdadero si hay al menos un producto que tenga más de 0 existencias. 
*/
int existenciaInventario(lista_doble * lista_productos);

//Imprime de qué productos ya no hay existencia
void imprimirNoExistencia(lista_doble * lista_productos);

//Funciones del menú.

void mostrarMenu(lista_doble * lista_productos, lista_doble * cola_pedidos, pila_ventas * pila_de_ventas);
void mostrarSubMenuInventario(lista_doble * lista_productos);
void mostrarSubMenuPedido(lista_doble * cola_pedidos, lista_doble * lista_productos, pila_ventas * pila_de_ventas);
void mostrarSubMenuVentas( lista_doble * lista_productos ,pila_ventas * pila_de_ventas);

void leerEntero(char prompt[], int *k);

void leerFloat(char prompt[], float *f);
void leerEnteroRango(char prompt[], int* k, int min, int max); 



// Funciones para las opciones del menú
void verInventario(lista_doble * lista_productos);

void actualizarInventario(lista_doble * lista_productos);

void buscarInventario(lista_doble * lista_productos);

void agregarPedido(lista_doble * lista_productos, lista_doble * cola_pedidos);

void liberarPedido(lista_doble * cola_pedidos, pila_ventas * pila_de_ventas);

void registrarVentas(lista_doble * lista_productos, pila_ventas * pila_v);




int main(){
    
    lista_doble * cola_pedidos = crearListaDoble();
    lista_doble *lista_productos = cargarInventario();
    pila_ventas * pila_de_ventas = crearPila(); 

    strcpy(lista_productos->nombre, "Lista productos" );
    strcpy(lista_productos->nombre, "Cola pedido" );

    imprimirListaDProducto(lista_productos);
    
    mostrarMenu(lista_productos, cola_pedidos, pila_de_ventas);

    guardarInventario(lista_productos);

    eliminarListaD(lista_productos);
    eliminarColaPedidos(cola_pedidos);
    eliminarPilaVentas(pila_de_ventas);

    return 0; 
}


lista_doble * crearListaDoble(){

    lista_doble * listaD = (lista_doble*)malloc(sizeof(lista_doble)); 
    listaD->head =NULL; 
    listaD->tail=NULL; 
    listaD->size=0;

    strcpy(listaD->nombre, "");
    
    return listaD;
}

//retorna entero con valor de verdadero si la lista está vacía.  
int listaVacia(lista_doble* lista){
    return lista->head == NULL;
}




//Funcion para agregar al inicio en una lista doble.
void agregarInicioLD(lista_doble * lista_d, void *informacion){
    //Creamos nodo y agregamos la info.
    nodo_doble* nodo_nuevo = (nodo_doble*)malloc(sizeof(nodo_doble));
    nodo_nuevo->info=informacion;

    if(listaVacia(lista_d)){
        //Cuando la lista esté vacia.
        nodo_nuevo->next = NULL;
        nodo_nuevo->prev = NULL;
        lista_d->head = nodo_nuevo;
        lista_d->tail = nodo_nuevo;

    }else{
        //Cuando no.
        nodo_nuevo->prev = NULL;
        nodo_nuevo->next = lista_d->head;
        lista_d->head->prev = nodo_nuevo;
        lista_d->head = nodo_nuevo;

    }

    lista_d->size += 1; //Agregamos 1 al control del tamaño de la lista.

}


//Agregar al final en una lista doblemente ligada. 
void agregarFinalLD(lista_doble * lista_d, void * informacion){

    nodo_doble * nodo_nuevo = (nodo_doble*)malloc(sizeof(nodo_doble));
    nodo_nuevo->info = informacion;


    if(listaVacia(lista_d)){
        nodo_nuevo->next = NULL;
        nodo_nuevo->prev = NULL;
        lista_d->head = nodo_nuevo;
        lista_d->tail = nodo_nuevo;

    }else{
        nodo_nuevo->next = NULL;
        nodo_nuevo->prev = lista_d->tail;
        lista_d->tail->next = nodo_nuevo;
        lista_d->tail = nodo_nuevo;
    }

    lista_d->size += 1;
}
//Función para liberar espacio de una lista doble. 
void eliminarListaD(lista_doble* lista_d) {

    //Si está vacía entonces lista_d->head es NULL y no entrará al ciclo while. 
    nodo_doble* actual = lista_d->head;
    nodo_doble* siguiente=NULL;

    while (actual != NULL) {
        siguiente = actual->next;
        free(actual->info);
        free(actual);
        
        actual = siguiente;
    }

    lista_d->head = NULL;
    lista_d->tail = NULL;


    free(lista_d);

}


//Funcion para eliminar el nodo final de una lista doble.
int eliminarFinalLD(lista_doble * lista_d){
    
    if(listaVacia(lista_d)){
        printf("---LA LISTA ESTA VACIA---");
        return 0;
    }

    nodo_doble * aux;
    if(lista_d->head ==  lista_d->tail){
        //Si solo hay un nodo.
        aux = lista_d->head;
        lista_d->head = lista_d->tail = NULL;

        lista_d->size -= 1;
        free(aux->info);
        free(aux);
        return 1;
    }

    //Si hay más nodos.

    aux= lista_d->tail; 

    lista_d->tail->prev->next=NULL; 
    lista_d->tail= lista_d->tail->prev;

    lista_d->tail->next =NULL;

    lista_d->size -= 1;
    free(aux->info);
    free(aux);

    return 1;


}

//Eliminar el inicio de una lista doble
int eliminarInicioLD(lista_doble * lista_d){

    if(listaVacia(lista_d)){
        printf("---LA LISTA ESTA VACIA---");
        return 0;
    }

    if(lista_d->head ==  lista_d->tail){
        //Si solo hay un nodo.
        nodo_doble * aux;

        aux = lista_d->head;
        lista_d->head = lista_d->tail = NULL;

        lista_d->size -= 1;
        free(aux->info);
        free(aux);
        return 1;
    }

    lista_d->head = lista_d->head->next;
    lista_d->head->prev->next = NULL;

    free(lista_d->head->prev->info);
    free(lista_d->head->prev);
    lista_d->head->prev = NULL;

    lista_d->size -= 1;

    return 1;
}

//Imprimir lista de productos.
void imprimirListaDProducto(lista_doble* lista_d) {

    if(listaVacia(lista_d)){
        printf("\n--- La lista esta vacia---\n");
        return;
    }

    nodo_doble*    actual = lista_d->head;
    Producto* producto=NULL;
    while (actual != NULL) {
         producto = (Producto*)actual->info;
        imprimirProducto(*producto);
        actual = actual->next;
    }
    
}
//Función para extraer el nodo final de una lista de productos. Ojo que no lo elimina sino lo retorna. 
nodo_doble * extraerFinalLD(lista_doble * lista_d){
    
    if(listaVacia(lista_d)){
        printf("---LA LISTA ESTA VACIA---");
        return NULL;
    }

    nodo_doble * aux;
    if(lista_d->head ==  lista_d->tail){
        //Si solo hay un nodo.
        aux = lista_d->head;
        lista_d->head = lista_d->tail = NULL;

        lista_d->size -= 1;
        return aux;
    }

    //Si hay más nodos.

    aux= lista_d->tail; 

    lista_d->tail->prev->next=NULL; 
    lista_d->tail= lista_d->tail->prev;

    lista_d->tail->next =NULL;

    lista_d->size -= 1;

    aux->next=NULL; 
    aux->prev=NULL;
 
    return aux;


}

//Extrae el nodo incio(head) de una lista doble. Ojo que no lo elimina sino lo retorna.
nodo_doble* extraerInicioLD(lista_doble * lista_d){

    if(listaVacia(lista_d)){
        printf("---LA LISTA ESTA VACIA---");
        return NULL;
    }

    if(lista_d->head ==  lista_d->tail){
        //Si solo hay un nodo.
        nodo_doble * aux;

        aux = lista_d->head;
        lista_d->head = lista_d->tail = NULL;

        lista_d->size -= 1;
        
        return aux;
    }

    lista_d->head = lista_d->head->next;
    lista_d->head->prev->next = NULL;

    nodo_doble * aux = lista_d->head->prev;
    lista_d->head->prev = NULL;

    lista_d->size -= 1;

    aux->next=NULL; 
    aux->prev=NULL;
    return aux;
}

/* Para extraer el nodo con cierto producto con cierto ID de una lista doble sin importar su posicón. 
La lista doble pasada a esta función debe de ser una lista donde sus nodos en su campo Info tengan la
dirección de una estructura Producto
*/
nodo_doble *  extraerEnMedioLDProductos(lista_doble * lista_d, int id){


    if(listaVacia(lista_d)){
        return NULL;
    }

    nodo_doble* actual = lista_d->head;
    Producto* producto=NULL;
    while (actual != NULL) {
         producto = (Producto*)actual->info;
        if (producto->id == id) {
            break;  // Se encontró el nodo con el ID buscado
        }

        actual = actual->next;
    }


    //printf("\n \n----ACTUAL: %d \n\n", actual);

    if(actual==NULL){
        return NULL;
    }

    
    if(actual->prev== NULL){
        //El nodo a extraer está en el head.

        lista_d->size -= 1;

        return extraerInicioLD(lista_d);
    }

    if(actual->next==NULL){

        //El nodo a extraer está en la tail.
        lista_d->size -= 1;

        return extraerFinalLD(lista_d);
    }

    //Si realmente está en medio. 


    actual->prev->next=actual->next; 

    actual->next->prev=actual->prev;

    actual->next=NULL; 
    actual->prev=NULL;

    lista_d->size -= 1;

    return actual; 


}

//Función para llenar los campos de una estructura Producto. 
void llenarProducto(Producto * producto, char nombre[], float precio, int cantidad, int id){

        producto->id=id; 
        producto->cantidad=cantidad; 
        producto->precio=precio;
        strcpy(producto->nombre, nombre); 

}

//Función para imprimir una estructura Producto.
void imprimirProducto(Producto p){
    printf("\n Nombre: %s", p.nombre); 
    printf("\n Precio: %.4f", p.precio); 
    printf("\n Cantidad: %d", p.cantidad); 
    printf("\n ID: %d \n", p.id); 
}


//Función para crear una estructura Producto. Retorna dirección a estructura Producto.
Producto * crearProducto(void){
    Producto *p=NULL;
    p = (Producto *)malloc(sizeof(Producto));
    return p;
}
//Actualiza  los campos cantidad y precio de una estructura Producto.
void actualizarProducto(Producto * producto, int nueva_cantidad, float nuevo_precio){

    producto->cantidad= nueva_cantidad; 
    producto->precio= nuevo_precio;

}

// Funciones para las opciones del menú


//Imprimir la lista de productos.
void verInventario(lista_doble * lista_productos) {
    printf("Opcion: Ver Inventario\n"); 
    imprimirListaDProducto(lista_productos);
}


//Actualizar cantidad y precio del producto que el usuario desee.
void actualizarInventario(lista_doble * lista_productos) {

    int id_cambiar=0;
    Producto * producto_cambiar = NULL;
    //Leemos ID para saber qué producto se cambiará. 
    leerEntero("Ingresa la ID del producto que quieres modificar: \n", &id_cambiar); 
    producto_cambiar= buscarNodoPorId(lista_productos, id_cambiar);

    //En caso de que no se encuntre producto con ID solicitada.
    if(producto_cambiar==NULL){
        printf("\n ----NO SE ENCONTRO PRODUCTO CON ESA ID");
        return;
    }

    //Leemos nuevos valores.
    int nueva_cantidad=0; 
    float nuevo_precio =1; 

    printf("\n El producto que quieres cambiar es: \n"); 
    imprimirProducto(*producto_cambiar);

    do{
        if(nueva_cantidad < 0){
            printf("\n Ingresa un valor valido.");
        }
        printf("\n Ingresa la nueva cantidad del producto con ID %d: ", id_cambiar);
        leerEntero("", &nueva_cantidad);

    }while(nueva_cantidad < 0);


    do{
        if(nuevo_precio <= 0){
            printf("\n Ingresa un valor valido.");
        }
         printf("\n Ingresa el nuevo precio  del producto con ID %d: ", id_cambiar);
        leerFloat("", &nuevo_precio);
    }while(nuevo_precio <=  0);
    //Actualizamos.
    actualizarProducto(producto_cambiar, nueva_cantidad, nuevo_precio);

}


//Buscar producto en la lista de productos por ID.
void buscarInventario(lista_doble * lista_productos) {

    int idBuscado=0;
    leerEntero("\nIngrese el ID del producto que desea buscar: ", &idBuscado);

    Producto* productoEncontrado = buscarNodoPorId(lista_productos, idBuscado);

    if (productoEncontrado != NULL) {
        printf("\nProducto encontrado:\n");
        imprimirProducto(*productoEncontrado);
    } else {
        printf("Producto con ID %d encontrado.\n", idBuscado);
    }
}


//Generar un pedido y agregarlo a la cola de pedidos.
void agregarPedido(lista_doble * lista_productos, lista_doble * cola_pedidos) {
    //Si lista de productos está vacía o no hay existencias de ningún producto.
    if(existenciaInventario(lista_productos) == 0){
        printf("\n \n--- Ya no hay existencias de ningun producto \n\n");
        return;
    }
    if(listaVacia(lista_productos)){
        printf("\n--- No hay productos disponibles en el inventario ---\n");
        return;

    }
    int id_producto_pedido=0; 
    int cantidad_producto_pedido=0;

    //El pedido será una lista doble de productos. Como el inventario.
    lista_doble * pedido = crearListaDoble(); 

   

    Producto * producto_pedido= NULL; //Producto que se agregará a la lista pedido.

    Producto * producto_pedido_aux = NULL; //Servirá para saber si un producto ya se ha agregado al pedido.

    //Dirección del productos del inventario del cual se quiere añadir al pedido 
    //Solo es para inicializarlo en algun valor diferente de NULL
    Producto *  producto_pedido_lista= (Producto *)lista_productos->head->info ; 

    int pregunta=1; 

    while(pregunta ==1){

        //En cada iteración del ciclo se agregará un producto nuevo.
        if(existenciaInventario(lista_productos) == 0){
            printf("\n\n --- Ya no hay existencias de ningun producto \n\n");
            break;
        }
        
        //Leera ID hasta que se encuentre producto con esa ID.
        do{
            imprimirListaDProducto(lista_productos);
            imprimirNoExistencia(lista_productos); //Funcion para mostrar de qué producto ya no hay existencias.

            if(producto_pedido_lista==NULL){
                printf("\nIngresa un valor valido de ID: ");
            }

            leerEntero("\n Ingresa el ID del producto que quieres agregar: ", &id_producto_pedido);
            producto_pedido_lista = buscarNodoPorId(lista_productos, id_producto_pedido);  // Producto que se quiere comprar. 
    
        }while(producto_pedido_lista==NULL || producto_pedido_lista->cantidad==0);

        cantidad_producto_pedido=1;

        printf("\n Este es el producto que quieres agregar");

        imprimirProducto(*producto_pedido_lista);

        do{

            if(cantidad_producto_pedido < 0 || cantidad_producto_pedido > producto_pedido_lista->cantidad){
                printf("\n Ingresa una cantidad valida");
            }
            leerEntero("\n Escribe la cantidad que quieres de ese producto: ", &cantidad_producto_pedido);


        }while(cantidad_producto_pedido > producto_pedido_lista->cantidad || cantidad_producto_pedido<0 );

/*
        Es posible que el usuario se haya equivocado de producto entonces está la opcion de agregar cantidad 0. 
            Lo que significa que no se añadirá nada al pedido.
*/
        
        if(cantidad_producto_pedido > 0){

            producto_pedido_lista->cantidad = producto_pedido_lista->cantidad - cantidad_producto_pedido; //Restamos la cantidad 

            producto_pedido_aux = buscarNodoPorId(pedido, id_producto_pedido);
            if(producto_pedido_aux != NULL){
                producto_pedido_aux->cantidad += cantidad_producto_pedido;

            }else{

                producto_pedido = crearProducto();  // Producto cola es el que se añadirá a cada pedido. 

                llenarProducto(producto_pedido, producto_pedido_lista->nombre, producto_pedido_lista->precio, cantidad_producto_pedido, id_producto_pedido);

                agregarFinalLD(pedido, producto_pedido);


            }


        }


        leerEntero("1. Agregar otro producto.\n2. Salir\n", &pregunta); 
    }

    //Es posible que aqui llegue un pedido vacio pues si el usuario ingresa puro 0 entonces no se añadirá nada a la lista pedido

    if(listaVacia(pedido)){
        printf("\n --- No se realizo ningun pedido --- \n");
        free(pedido);
        return;
    }

    //Imprimimos pedido y lo agregamos a la cola de pedidos.
    printf("\n --- Se ha agregado el pedido ---\n");
    imprimirListaDProducto(pedido);
    agregarFinalLD(cola_pedidos,pedido);
}


//Liberar un pedido de la cola de pedidos para añadirlo a la pila de ventas. 
void liberarPedido(lista_doble * cola_pedidos, pila_ventas * pila_de_ventas) {
    printf("Opcion: Liberar Pedido\n");


    if(listaVacia(cola_pedidos)){

        printf("\n --- La cola de pedidos esta vacia. No se puede liberar ningun pedido --- \n");
        return;
    }

    nodo_doble * nodo_pedido_liberado=NULL;

    Venta * venta = (Venta *)malloc(sizeof(Venta));
    //Verificamos que se haya reservado correctamente la memoria.
    if(venta==NULL){
        printf("\n --- No se pudo liberar el pedido --- \n");
        return;
    }
    //extraemo el nodo de inicio de la cola de pedidos.
    nodo_pedido_liberado= extraerInicioLD(cola_pedidos);
    //Recordemos que en el campo info de la cola de pedidos se almacenan listas dobles
    lista_doble * pedido_liberado= (lista_doble *) nodo_pedido_liberado->info;

    // En el campo id_pedido de la venta estará la dirección de memoria de la lista doble pedido_liberado.
    venta->id_pedido = pedido_liberado; 
    venta->total = ObtenerTotalPedido(pedido_liberado); 


    int prueba = push(pila_de_ventas, venta);

    if(prueba == 0){
        printf("\n--- No se pudo liberar el pedido --- \n");
        free(venta);
        agregarInicioLD(cola_pedidos, nodo_pedido_liberado);

        return;
    }
    //Imprime el pedido liberado y la venta que se generó. 
    printf("\n --- Se ha liberado el pedido y se ha agregado a la pila de ventas:");
    printf("\n Nombre : %s ", pedido_liberado->nombre); 
    imprimirListaDProducto(pedido_liberado);
    printf("\n Venta: ");
    imprimirVenta(venta);
    free(nodo_pedido_liberado); //Se libera la memoria del nodo extraido de cola de pedidos.

}

//Registrar una venta y agregarla a la pila de ventas. En esta función se genera un pedido y después a partir de ese pedido se genera la venta
void registrarVentas(lista_doble * lista_productos, pila_ventas * pila_v) {


if (existenciaInventario(lista_productos) == 0) {
    printf("\n--- No hay productos disponibles en el inventario ---\n");
    return;
}
if(existenciaInventario(lista_productos) == 0){
        printf("\n \n--- Ya no hay existencias de ningun producto \n\n");
        return;
    }

int id_producto_venta = 0;
int cantidad_producto_venta = 0;


lista_doble * venta = crearListaDoble();
Producto *producto_venta = NULL;
Producto * producto_venta_auxiliar=NULL;
Producto *producto_venta_lista = (Producto *)lista_productos->head->info;

int pregunta = 1;

while (pregunta == 1) {

    if (listaVacia(lista_productos)) {
        printf("\n--- No hay productos disponibles en el inventario ---\n");
        break;
    }

    do {
        imprimirListaDProducto(lista_productos);
        imprimirNoExistencia(lista_productos);

        if (producto_venta_lista == NULL) {
            printf("\nIngresa un valor valido de ID: ");
        }

        leerEntero("\nIngresa el ID del producto que quieres vender: ", &id_producto_venta);
        producto_venta_lista = buscarNodoPorId(lista_productos, id_producto_venta);

    } while (producto_venta_lista == NULL || producto_venta_lista->cantidad == 0);

    cantidad_producto_venta = 1;

    printf("\nEste es el producto que quieres vender:\n");
    imprimirProducto(*producto_venta_lista);

    do {
        if (cantidad_producto_venta < 0 || cantidad_producto_venta > producto_venta_lista->cantidad) {
            printf("\nIngresa una cantidad valida");
        }
        leerEntero("\nIngresa la cantidad que quieres vender de ese producto: ", &cantidad_producto_venta);

    } while (cantidad_producto_venta > producto_venta_lista->cantidad || cantidad_producto_venta < 0);

    //Se verifica si ya se ha añadido el producto antes, si sí solo se modifica la cantidad en la lista venta y si no se crea un nuevo producto para añadirlo a la venta
    if (cantidad_producto_venta > 0) {
        producto_venta_lista->cantidad -= cantidad_producto_venta; // Restamos la cantidad vendida
        producto_venta_auxiliar = buscarNodoPorId(venta, id_producto_venta);
            
        if(producto_venta_auxiliar != NULL){
            producto_venta_auxiliar += cantidad_producto_venta;

        }else{
            producto_venta = crearProducto();
            llenarProducto(producto_venta, producto_venta_lista->nombre, producto_venta_lista->precio, cantidad_producto_venta, id_producto_venta);
            agregarFinalLD(venta, producto_venta);   

        }

        
    }

    leerEntero("1. Agregar otra venta.\n2. Salir\n", &pregunta);
}


//Puede que se llegue aquí con una venta con ningún producto, entonces se evalua si está vacia. 
if (listaVacia(venta)) {
    free(venta);
    printf("\n--- No se ha realizado ninguna venta ---\n");
    return;
}

//Creamos la venta que se agregará a la pila y la llenamos.
Venta * venta_a_pila= (Venta *)malloc(sizeof(Venta)); 
venta_a_pila->id_pedido=NULL;
venta_a_pila->total=0;

venta_a_pila->id_pedido = venta;
venta_a_pila->total = ObtenerTotalPedido(venta);

//Hacemos el push. 
int prueba= push(pila_v, venta_a_pila);

//Comprobamos que se haya hecho correctamente el push.
if(prueba == 0){
        printf("\n--- No se pudo agregar la venta --- \n");
        free(venta); 
        free(venta_a_pila);
        return;
    }

//Se registró la venta y se imprime.
    printf("\n --- Se ha registrado la venta ---");
    imprimirVenta(venta_a_pila);


}

void mostrarSubMenuInventario(lista_doble * lista_productos) {
    int opcion=0;

    while (1) {
        printf("\n----- Submenu de Inventario -----\n");
        printf("1. Ver Inventario\n");
        printf("2. Actualizar Inventario\n");
        printf("3. Buscar en Inventario\n");
        printf("4. Volver al Menu Principal\n");

        leerEnteroRango("Ingrese su opcion: ", &opcion, 1, 4);

        switch (opcion) {
            case 1:
                printf("Opcion: Ver Inventario\n");
                verInventario(lista_productos);
                break;
            case 2:
                printf("Opcion: Actualizar Inventario\n");
                actualizarInventario(lista_productos);
                break;
            case 3:
                printf("Opcion: Buscar en Inventario\n");
                buscarInventario(lista_productos);
                break;

            case 4: 
                printf("\nVolviendo al Menu Principal...\n");
                return;  // Salir de la función y volver al menú principal


        }
    }
}

void mostrarSubMenuPedido(lista_doble * cola_pedidos, lista_doble * lista_productos, pila_ventas * pila_de_ventas) {
    int opcion=0;

    while (1) {
        printf("\n----- Submenu de Pedido -----\n");
        printf("1. Agregar pedido\n");
        printf("2. Liberar Pedido\n");
        printf("3. Ver Colas de Pedido\n");
        printf("4. Volver al Menu Principal\n");
        leerEnteroRango("Ingrese su opcion: ", &opcion, 1, 4);

        switch (opcion) {
            case 1: 
                printf("\n ---Opcion agregarPedido ---\n");
                agregarPedido(lista_productos, cola_pedidos);
                break;
            case 2:
                printf("\n --- Opcion: Liberar Pedido ---\n");
                liberarPedido(cola_pedidos, pila_de_ventas);
                break;
            case 3:
                printf("\n ---Opcion: Ver Colas de Pedido ---\n");
                imprimirColaPedidos(cola_pedidos);
                break;
            case 4:
                printf("\nVolviendo al Menu Principal...\n");
                return;  // Salir de la función y volver al menú principal
        }
    }
}

void mostrarSubMenuVentas(lista_doble * lista_productos, pila_ventas * pila_de_ventas) {
    int opcion=0;

    while (1) {
        printf("\n----- Submenu de Ventas -----\n");
        printf("1. Registrar Ventas\n");
        printf("2. Ver Ventas Realizadas\n");
        printf("3. Volver al Menu Principal\n");
        leerEnteroRango("Ingrese su opcion: ", &opcion, 1, 3);

        switch (opcion) {
            case 1:
                printf("Opcion: Registrar Ventas\n");
                registrarVentas(lista_productos, pila_de_ventas);
                break;
            case 2:
                printf("Opcion: Ver Ventas Realizadas\n");
                imprimirPilaVentas(pila_de_ventas);
                break;
            case 3:
                printf("\nVolviendo al Menu Principal...\n");
                return;  // Salir de la función y volver al menú principal
        }
    }
}


void mostrarMenu(lista_doble* lista_productos, lista_doble * cola_pedidos, pila_ventas * pila_de_ventas) {
    int opcion=0;

    while (1) {
        printf("\n----- Menu Principal -----\n");
        printf("1. Inventario\n");
        printf("2. Pedido\n");
        printf("3. Ventas\n");
        printf("4. Salir\n");
        leerEnteroRango("Ingrese su opcion: ", &opcion, 1, 4);

        switch (opcion) {
            case 1:
                mostrarSubMenuInventario(lista_productos);
                break;
            case 2:
                mostrarSubMenuPedido(cola_pedidos, lista_productos, pila_de_ventas);
                break;
            case 3:
                mostrarSubMenuVentas(lista_productos,pila_de_ventas);
                break;
            case 4:
                printf("\nSaliendo del programa...\n");
                return;  // Finalizar el programa
        }
    }
}

//Función para leer un etero.
void leerEntero(char prompt[], int *k){
    int prueba=1;

    printf("%s", prompt);
    
    do {
        if (prueba ==0 ) {
            printf("\nIngrese un dato valido: ");
        }

        prueba = scanf("%d", k);
        fflush(stdin);

    } while (prueba == 0);
    
}
//ller un float.
void leerFloat(char prompt[], float *f){
    int prueba = 1;

    printf("%s: ", prompt);
    do {
        if (prueba == 0) {
            printf("\nIngrese un dato valido: ");
        }


        prueba = scanf("%f", f);
        fflush(stdin);
    } while (prueba == 0);
}

/*

 Lee un entero en el rango entre min y max. No lee el entero hasta que el entero leido se encuentre en ese rango. Se usará mucho
 para leer las opciones del menú


*/
void leerEnteroRango(char prompt[], int* k, int min, int max) {
    int prueba = 1;
    printf("%s", prompt);
    
    do {
        if (prueba == 0 || *k < min || *k > max) {
            printf("\nIngrese un dato valido entre %d y %d: ", min, max);
        }

        prueba = scanf("%d", k);
        fflush(stdin);
    } while (prueba == 0 || *k < min || *k > max);
}

/*Sirve para listas dobles que tengan como nodo una estructura Producto. Retorna el nodo que coincida con el id solicitada. 
Retorna NULL si no se encontró nodo con la id buscada.
*/
Producto * buscarNodoPorId(lista_doble* lista_d, int idBuscado) {

    if(listaVacia(lista_d)){
        return NULL;
    }

    int id_actual=0;
    Producto * producto=NULL;
    nodo_doble * actual = lista_d->head;
    while (actual != NULL) {
         producto = (Producto*)actual->info;
        id_actual = producto->id;
        if (id_actual == idBuscado) {
            break;
        }
        actual= actual->next;
    }

    if(actual == NULL){
        return NULL;
        // No se encontró el nodo con el ID buscado
    }
    Producto * aux = (Producto*)actual->info;
    return aux; 
}


//Libera la memoria reservada en una cola de pedidos. Como
void eliminarColaPedidos(lista_doble * cola_pedidos){
    //Si está vacía entonces lista_d->head es NULL y no entrará al ciclo while. 
    nodo_doble* actual = cola_pedidos->head;
    nodo_doble* siguiente=NULL;

    lista_doble * pedido =NULL; //Nos servirá para eliminar la lista doble que se encuentra en el campo info de cada nodo de la cola.

    while (actual != NULL) {
        siguiente = actual->next;

        pedido = (lista_doble*) actual->info;
         eliminarListaD(pedido);

       // eliminarListaD(actual->info);
        free(actual);
        actual = siguiente;
    }

    cola_pedidos->head = NULL;
    cola_pedidos->tail = NULL;

    free(cola_pedidos);
}


void imprimirColaPedidos(lista_doble * cola_pedidos){

    if(listaVacia(cola_pedidos)){
        printf("\n--- La cola de pedidos esta vacia---\n");
        return;
    }


    nodo_doble* actual = cola_pedidos->head;

    lista_doble *pedido=NULL;

    int k=1; 
    while (actual != NULL) {
        pedido = (lista_doble*)actual->info;
        printf("\n Pedido %d", k); 
        printf("\n Nombre pedido: %s",pedido->nombre );
        imprimirListaDProducto(pedido);
        actual = actual->next;
        k++;
    }

}

//Función que verifica si hay al menos una existencia de algún producto en la lista de productos.
//Retorna 0 si no hay existencias o sí está vacía y retorna 1 sí al menos hay existencia de un producto.

int existenciaInventario(lista_doble * lista_productos){

    if(listaVacia(lista_productos)){
        printf("\n--- La lista esta vacia---\n");
        return 0;
    }

    nodo_doble* actual = lista_productos->head;
    Producto * producto=NULL;
    while (actual != NULL) {
         producto = (Producto*)actual->info;
        
        if(producto->cantidad >= 1){
            return 1;
        }
        actual = actual->next;
    }
    return 0;
    
}

//. Recorre toda la lista de productos e imprime el nombre del producto y su ID de los productos para los cuales no hay existencias.

void imprimirNoExistencia(lista_doble * lista_productos){

    if(listaVacia(lista_productos)){
        printf("\n--- La lista esta vacia---\n");
    }


    nodo_doble* actual = lista_productos->head;
    Producto * producto=NULL;
    while (actual != NULL) {
         producto = (Producto*)actual->info;

        if(producto->cantidad == 0){

            printf("\n Ya no hay existencias de %s con ID : %d", producto->nombre, producto->id);
        }
        actual = actual->next;
    }
    
}



void guardarInventario(lista_doble * lista_productos) {
    FILE* archivo = fopen("inventario.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo. \n");
        return;
    }

    nodo_doble * current = lista_productos->head;
    Producto * current_product=NULL;
    while (current != NULL) {
        current_product = (Producto *)current->info;
        fprintf(archivo, "%s,%d,%.2f,%d\n",  current_product->nombre, current_product->id, current_product->precio, current_product->cantidad);
        current = current->next;
    }

    fclose(archivo);
    printf("Inventario guardado en el archivo.\n");
}


lista_doble* cargarInventario() {
    FILE* archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return NULL;
    }

    lista_doble * lista_productos = crearListaDoble();
    char linea[200];
    Producto * producto =NULL;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        producto = crearProducto();
        sscanf(linea, "%[^,],%d,%f,%d", producto->nombre, &(producto->id), &(producto->precio), &(producto->cantidad));
        agregarFinalLD(lista_productos, producto);
    }

    fclose(archivo);
    printf("Inventario cargado desde el archivo.\n");
    return lista_productos;
}



pila_ventas * crearPila(){
    pila_ventas * pila_v =(pila_ventas*) malloc(sizeof(pila_ventas));
    pila_v->tope=-1;
    pila_v->pila = (Venta **)malloc(sizeof(Venta*)*5);
    pila_v->max_tamanio=5;
    return pila_v;
}

//Retorna 1 si la pila esta llena y cero si no.
int isFull(pila_ventas * pila){
    if(pila->max_tamanio <= (pila->tope +1)){
        return 1;
    }
    return 0;
}

//Para ver si la pila está vacía.
int isEmpty(pila_ventas * pila){
    return pila->tope == -1;
}

int push(pila_ventas *pila_v, Venta * venta) {
    if (isFull(pila_v)) {
        pila_v->max_tamanio = pila_v->max_tamanio +5; 
        pila_v->pila = realloc(pila_v->pila, pila_v->max_tamanio * sizeof(Venta *));
    }

    //Verifica que se haya redimensionado correctamente
    if(pila_v->pila == NULL){
        printf("\n--- No se pudo registrar otra venta --- \n");
        return 0;
    }

    pila_v->tope++;
    pila_v->pila[pila_v->tope] = venta;
    return 1;
}

//Imprime una estrutura de venta. 
void imprimirVenta(Venta * venta){
    printf("\n Total de la venta= %.4f", venta->total);
    printf("\n ID del pedido = %p \n", venta->id_pedido);
}

void imprimirPilaVentas(pila_ventas * pila_v){
    if (isEmpty(pila_v)) {
        printf("\n--- La pila de ventas  esta vacia --- \n");
        return;
    }

    printf("\n Pila de ventas:\n");
    for (int j =pila_v->tope; j >= 0; j--) {
        printf("\n Venta %d", j+1 );
        imprimirVenta(pila_v->pila[j]);
    }
}

// Obtiene el total de todo un pedido al multiplicar la cantidad y el precio de cada producto, para esto recorre todo el pedido.
float ObtenerTotalPedido(lista_doble * pedido){

    if(listaVacia(pedido)){
        printf("\n--- La lista esta vacia---\n");
    }

    float total=0;

    nodo_doble* actual = pedido->head;
    Producto* producto=NULL;
    while (actual != NULL) {
         producto = (Producto*)actual->info;

         total = total  + (producto->cantidad * producto->precio);
        actual = actual->next;
    }

    return total;

}

//Liberar memoria de la pila de ventas.
void eliminarPilaVentas(pila_ventas * pila_de_ventas){

    if (isEmpty(pila_de_ventas)) {
        free(pila_de_ventas->pila);
        free(pila_de_ventas);
        return;
    }

    for (int j =pila_de_ventas->tope; j >= 0; j--) {
        eliminarListaD(pila_de_ventas->pila[j]->id_pedido);
        free(pila_de_ventas->pila[j]);    
    }

    free(pila_de_ventas->pila);
    free(pila_de_ventas);

}




 









 



