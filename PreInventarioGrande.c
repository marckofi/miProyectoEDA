#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//NOTAS

/*

Crear función para imprimir inventario.
AgregarInicioLD se usará como push a la hora de usar pilas.
EliminarInicioLD se usará como pop a la hora de usar pilas.
lista Vacia se usará como isEmpty. 
 ExtraerInicioLd se usará como top al implementar la cola. 

 Recuerda que al extraer un nodo, al finalizar tendrás que liberar tanto el nodo como su campo info.

 Modificar extrer inicio para que no vea tan fea. Usar variable de ayuda aux. 

 //Checa si no es necesario hacer el cast a lista_doble * cuando liberas el campo info de uno nodo de la cola de pedidos.

Revisar los fflush stdin , en especial en la funcion agregarPedido.


*/


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


typedef struct pila_ventas{
    int tope;

    lista_doble * pila[10];

}pila_ventas;


//Estructura que guardará tres dos arreglos. Y la cantidad de productos en el Pedido. 
typedef struct Pedido {
  int * idsProductos;
  int * cantidadesProductos;
  int   numProductos;
} Pedido;


/*
//Estructura que trabaja en conjunto con lista_doble para registrar una venta 
typedef struct venta {
    float total;
    lista_doble* pedido;
} venta;

*/

//Funciones para pasar de archivo a lista_productos y de lista_productos a archivo. 


// Función para guardar el inventario en un archivo
void guardarInventario(lista_doble * lista_productos);


//Función para cargar el inventario desde el archivo. 
lista_doble* cargarInventario();


lista_doble * crearListaDoble();


int listaVacia(lista_doble  * lista);


//Funciones de lista doble.

void agregarInicioLD(lista_doble* lista_d, void * informacion);
void agregarFinalLD(lista_doble * lista_d, void * informacion); 


int eliminarInicioLD(lista_doble* lista_d); 
int eliminarFinalLD(lista_doble* lista_d);

nodo_doble * extraerInicioLD(lista_doble* lista_d);
nodo_doble * extraerFinalLD(lista_doble* lista_d); 


//Funciones para producto
nodo_doble *  extraerEnMedioLDProductos(lista_doble * lista_d, int valor);


void imprimirListaDProducto(lista_doble* lista_d);  //Imprimir lista doblemente ligada de productos.
void eliminarListaD(lista_doble* lista_d);

Producto * buscarNodoPorId(lista_doble* lista_d, int idBuscado);


//Funciones para el producto.
void llenarProducto(Producto * producto, char nombre[], float precio, int cantidad, int id); 
void imprimirProducto(Producto p); 

Producto * crearProducto(void); //Función que retorna una dirección que apunta a una structura Producto.


void actualizarProducto(Producto * producto, int nueva_cantidad, float nuevo_precio);  //Función para actualizar cantidad y precio del producto. 

//Funciones para la cola de pedidos


/*
void imprimirColaPedidos(lista_doble * cola_pedidos); La cola de pedidos es una lista doblemente ligada implementada como cola. 
En el campo  de los nodos se almacena una lista_doble la cual representa un pedido.
*/

void imprmirColaPedidos(lista_doble * cola_pedidos, lista_doble * lista_productos);

void eliminarColaPedidos(lista_doble * cola_pedidos);
//Funciones para el menu y para leer entrada desde el teclado. 

/*Función para evaluar si hay existencia de al menos un producto. 
Retornara valor entero equivalente a verdadero si hay al menos un producto que tenga más de 0 existencias. 
*/
int existenciaInventario(lista_doble * lista_productos);

//Imprime de que productos ya no hay existencia
void imprimirNoExistencia(lista_doble * lista_productos);

//Funciones de pedidos de Sandra. 

Pedido *crearPedido(lista_doble *lista_productos, lista_doble * cola_pedidos);
void imprimirPedido(Pedido * pedido, lista_doble * lista_productos);

void mostrarMenu(lista_doble * lista_productos, lista_doble * cola_pedidos);
void mostrarSubMenuInventario(lista_doble * lista_productos, lista_doble * cola_pedidos);
void mostrarSubMenuPedido(lista_doble * cola_pedidos, lista_doble * lista_productos);
void mostrarSubMenuVentas();

void leerEntero(char prompt[], int *k);

void leerFloat(char prompt[], float *f);
void leerEnteroRango(char prompt[], int* k, int min, int max); 

void leerCadena(char prompt[], char cadena[], int longitud);






// Funciones para las opciones del menú
void verInventario(lista_doble * lista_productos);

void actualizarInventario(lista_doble * lista_productos);

void agregarProducto(lista_doble * lista_productos); 
void quitarProducto(lista_doble * lista_productos); 

void buscarInventario();

void agregarPedido(lista_doble * lista_productos, lista_doble * cola_pedidos);

void liberarPedido();

void verColaPedidos();

void registrarVentas();

void verVentasRealizadas();


//Funciones de ventas de Mariana. 

/*
nodo_doble* crearNodo(void* info) {
    nodo_doble* nuevo = (nodo_doble*)malloc(sizeof(nodo_doble));
    nuevo->info = info;
    nuevo->next = NULL;
    nuevo->prev = NULL;
    return nuevo;
}

//Función para insertar un nodo al final de la lista 
void insertarNodo(lista_doble* lista, nodo_doble* nodo) {
    if (lista->head == NULL) {
        lista->head = nodo;
        lista->tail = nodo;
    } else {
        nodo->prev = lista->tail;
        lista->tail->next = nodo;
        lista->tail = nodo;
    }
    lista->size++;
}
*/

int main(){
    

/*


    Producto * tambores = crearProducto(); 
    Producto * picafresas= crearProducto();
    Producto * chicles= crearProducto();
    Producto * paletas= crearProducto();

    llenarProducto(tambores, "Tambores", 2.5, 10, 12345);
    llenarProducto(picafresas, "Picafresas", 1, 10, 01234);
    llenarProducto(chicles, "Chicles", 0.5, 10, 78945);
    llenarProducto(paletas, "Paletas", 0.5, 10, 45612);

    agregarFinalLD(lista_productos, tambores);
    agregarFinalLD(lista_productos, picafresas);
    agregarFinalLD(lista_productos, chicles);
    agregarInicioLD(lista_productos, paletas); 

    
*/  



   // lista_doble * pila_ventas = crearListaDoble();
    lista_doble * cola_pedidos = crearListaDoble();
    lista_doble *lista_productos = cargarInventario();

    strcpy(lista_productos->nombre, "Lista productos" );
    strcpy(lista_productos->nombre, "Cola pedido" );



    
    imprimirListaDProducto(lista_productos);
    

    mostrarMenu(lista_productos, cola_pedidos);

   


    guardarInventario(lista_productos);

    //Liberar espacio del inventario.

    //Liberar la memoria utilizada para el registro de ventas
	//liberarVentas(&listaVentas);

    eliminarListaD(lista_productos);
    eliminarColaPedidos(cola_pedidos);




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
    }


    nodo_doble* actual = lista_d->head;
    Producto * producto;
    while (actual != NULL) {
         producto = (Producto*)actual->info;
        imprimirProducto(*producto);
        actual = actual->next;
    }
    


}



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

// Para extraer nodos que sean productos 
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

void llenarProducto(Producto * producto, char nombre[], float precio, int cantidad, int id){

        producto->id=id; 
        producto->cantidad=cantidad; 
        producto->precio=precio;

        strcpy(producto->nombre, nombre); 

}


void imprimirProducto(Producto p){
    printf("\n Nombre: %s", p.nombre); 
    printf("\n Precio: %.4f", p.precio); 
    printf("\n Cantidad: %d", p.cantidad); 
    printf("\n ID: %d \n", p.id); 


}

Producto * crearProducto(void){

    Producto * p = (Producto *)malloc(sizeof(Producto));
    return p;
}


void actualizarProducto(Producto * producto, int nueva_cantidad, float nuevo_precio){

    producto->cantidad= nueva_cantidad; 
    producto->precio= nuevo_precio;


}






// Funciones para las opciones del menú
void verInventario(lista_doble * lista_productos) {
    printf("Opcion: Ver Inventario\n"); 
    imprimirListaDProducto(lista_productos);
}

void actualizarInventario(lista_doble * lista_productos) {

    int id_cambiar=0;
    Producto * producto_cambiar = NULL;
    

    leerEntero("Ingresa la ID del producto que quieres modificar: \n", &id_cambiar); 
    producto_cambiar= buscarNodoPorId(lista_productos, id_cambiar);

    if(producto_cambiar==NULL){
        printf("\n ----NO SE ENCONTRO PRODUCTO CON ESA ID");
        return;
    }

    int nueva_cantidad=0; 
    float nuevo_precio =1; //Aqui duda. Se puede inicializar en 0 o debe de ser 0.0?

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

    actualizarProducto(producto_cambiar, nueva_cantidad, nuevo_precio);

}

void agregarProducto(lista_doble * lista_productos){


}

void quitarProducto(lista_doble * lista_productos){
    if(listaVacia(lista_productos)){
        printf("\n--- LA LISTA DE PRODUCTOS ESTA VACIA. NO PUEDES QUITAR PRODUCTOS ---\n");
        return ; 
    }
    int id_quitar=0;

    leerEntero("Ingresa la ID del producto que quieres quitar: \n", &id_quitar);

    nodo_doble * nodo_quitar = extraerEnMedioLDProductos(lista_productos, id_quitar);

    if(nodo_quitar==NULL){
        printf("\n ---NO HAY PRODUCTO CON ESA ID--- \n");
        return ;

    }

    Producto * producto_quitar =(Producto *) nodo_quitar->info; 

    printf("El producto que quieres quitar es : \n"); 
    imprimirProducto(*producto_quitar);

    printf("Presione  dos veces Enter para quitar el producto... ");
    getchar(); // Pausa la ejecución hasta que el usuario presione Enter
    // Descartar el carácter de retorno de carro ('\n')
    getchar();

    free(nodo_quitar->info);
    free(nodo_quitar);

    printf("\n Se ha eliminado el producto. ");
}

void buscarInventario() {
    printf("Opcion: Buscar en Inventario\n");
}


//Agregar Pedido Sandra. 


void agregarPedido(lista_doble *lista_productos, lista_doble *cola_pedidos) {
  printf("Opcion: Agregar Pedido\n");

  if(existenciaInventario(lista_productos) == 0){
    printf("\n\n --- Ya no hay existencias de ningun producto \n\n");
    return;

  }
  Pedido * pedido = (Pedido * )crearPedido(lista_productos,cola_pedidos);

  if(pedido == NULL){
    printf("\n --- No fue posible  hacer  el pedido ---\n" );
    return;
  }


  printf("\n Creando pedido: %p\n", pedido);

  imprimirPedido(pedido, lista_productos);

  //Imprimir se ha creado el pedido he imprimir el pedido. 

  agregarFinalLD(cola_pedidos, pedido);
}

//Crear Pedido Sandra. 
Pedido *crearPedido(lista_doble *lista_productos, lista_doble * cola_pedidos) {


  int i=0, id=0, num_productos=0, cantidad_producto_pedido=0, pregunta=0; 
  Producto *producto_pedido_lista =NULL;

  //pregunta servirá para preguntarle si quiere seguir añadiendo productos. 

    


    do{
        if(num_productos<0){
            printf("\n Ingresa una cantidad valida.");
        }
        leerEntero("\n Numero de productos a pedir: ", &num_productos);
    }while(num_productos<0);


    if(num_productos==0){
        return NULL;
    }

    Pedido *pedido =(Pedido * ) malloc(sizeof(pedido));

    if(pedido == NULL){
        printf("\n --- NO FUE POSIBLE CREAR EL PEDIDO --- \n");
        return NULL;
    }

    pedido->numProductos = num_productos;
    // checar función
    // printf("pre:%p\t%d\n",pedido,pedido->numProductos);
    pedido->idsProductos =(int *) malloc(sizeof(int) * num_productos);
    pedido->cantidadesProductos = (int *)malloc(sizeof(int) * num_productos);

    if(pedido->idsProductos == NULL || pedido->cantidadesProductos == NULL){
        printf("\n --- NO FUE POSIBLE CREAR EL PEDIDO --- \n");
        return NULL;
        
    }

   i=0;
   while(i< pedido->numProductos){

    if(existenciaInventario(lista_productos) == 0){
        printf("\n\n --- Ya no hay existencias de ningun producto \n\n");
        break; 
    }
    
    
    do{
            // Añadiremos funcion para que muestre de que productos ya no hay existencia

            imprimirNoExistencia(lista_productos);

            if(producto_pedido_lista==NULL){
                printf("\nIngresa un valor valido de ID: ");
            }
            leerEntero("\n Ingresa el ID del producto que quieres agregar: ", &id);
            producto_pedido_lista = buscarNodoPorId(lista_productos, id);  // Producto que se quiere comprar. 
    
        }while(producto_pedido_lista==NULL || producto_pedido_lista->cantidad==0);

    printf("\n Este es el producto que agregaras: ");
    imprimirProducto(*producto_pedido_lista);

   
     do{

            if(cantidad_producto_pedido < 0 || cantidad_producto_pedido > producto_pedido_lista->cantidad){
                printf("\n Ingresa una cantidad valida");
            }
            leerEntero("\n Escribe la cantidad que quieres de ese producto: ", &cantidad_producto_pedido);


        }while(cantidad_producto_pedido > producto_pedido_lista->cantidad || cantidad_producto_pedido<0 );

        if(cantidad_producto_pedido == 0){
            //El usuario decide no agregar cantidad de ese producto. Entonces reiniciamos el ciclo con continue sin aumentar i. 
            continue;
        }

        


    
    pedido->idsProductos[i] = id;

    pedido->cantidadesProductos[i] = cantidad_producto_pedido;

    producto_pedido_lista->cantidad = producto_pedido_lista->cantidad - cantidad_producto_pedido;

    leerEnteroRango("1. Agregar otro producto.\n2. Salir\n", &pregunta, 1,2); 

        if(pregunta == 2 || i+1 == num_productos){
            break;
        }


    i++;
    //Al salir del ciclo i+1 será igual a la cantidad de productos que realmente se añadieron.

  }

  pedido->numProductos = i+1;


  pedido->cantidadesProductos = realloc(pedido->cantidadesProductos, sizeof(int) *(i+1));
  pedido->idsProductos = realloc(pedido->idsProductos, sizeof(int) * (i+1));


  return pedido;
}


void imprimirPedido(Pedido * pedido, lista_doble * lista_productos){

    printf("\n Cantidad de productos= %d",pedido->numProductos ); 
    int j=0;
    Producto * producto_actual = NULL; 
    while(j<pedido->numProductos){

       producto_actual = buscarNodoPorId(lista_productos, pedido->idsProductos[j]);

        if(producto_actual==NULL){
            printf("\n --- NO SE PUDO IMPRIMIR ESTE PRODUCTO --- \n");
            j++;
            continue;

        }


        printf("\n Nombre: %s", producto_actual->nombre); 
        printf("\n Precio: %.4f", producto_actual->precio); 
        printf("\n Cantidad: %d", pedido->cantidadesProductos[j]); 
        printf("\n ID: %d \n", pedido->idsProductos[j]); 

        //Ojo que no se deben de quitar productos de la lista de productos, pues si lo quitamos puede que no se impriman bien los pedidos.
        j++;
    }


}

void imprimirColaPedidos(lista_doble * cola_pedidos, lista_doble * lista_productos){
if(listaVacia(cola_pedidos)){
        printf("\n--- La cola de pedidos esta vacia---\n");
    }


    nodo_doble* actual = cola_pedidos->head;

    int k=1; 
    Pedido * pedido =NULL;
    while (actual != NULL) {
        pedido = (Pedido*)actual->info;
        printf("\n Pedido %d", k); 
        imprimirPedido(pedido, lista_productos);
        actual = actual->next;
        k++;
    }
}

void eliminarColaPedidos(lista_doble * cola_pedidos){

    //Si está vacía entonces lista_d->head es NULL y no entrará al ciclo while. 
    nodo_doble* actual = cola_pedidos->head;
    nodo_doble* siguiente;

    Pedido * pedido =NULL; //Nos servirá para eliminar la estructura pedido que se encuentra en el campo info de cada nodo de la cola.

    while (actual != NULL) {
        siguiente = actual->next;

        //pedido = (lista_doble*) actual->info;
        //eliminarListaD(pedido);

        pedido = (Pedido *)actual->info; 

        free(pedido->idsProductos);
        free(pedido->cantidadesProductos); 
        free(pedido);
        actual->next=NULL; 
        actual->prev=NULL;
        free(actual);
        actual = siguiente;
    }

    cola_pedidos->head = NULL;
    cola_pedidos->tail = NULL;

    free(cola_pedidos);

}

//Terminan funciones de pedidos de Sandra.




void liberarPedido() {
    printf("Opcion: Liberar Pedido\n");
}

void verColaPedidos() {
    printf("Opcion: Ver Colas de Pedido\n");
}

void registrarVentas() {
    printf("Opcion: Registrar Ventas\n");
}



void verVentasRealizadas() {
    printf("Opcion: Ver Ventas Realizadas\n");
}//Función para registrar una venta, ingresando el total de la venta 



void mostrarSubMenuInventario(lista_doble * lista_productos, lista_doble * cola_pedidos) {
    int opcion=0;

    while (1) {
        printf("\n----- Submenu de Inventario -----\n");
        printf("1. Ver Inventario\n");
        printf("2. Actualizar Inventario\n");
        printf("3. Buscar en Inventario\n");
        printf("4. Agregar Producto\n"); 
        printf("5. Quitar Producto\n");
        printf("6. Agregar pedido\n");
        printf("7. Volver al Menu Principal\n");

        leerEnteroRango("Ingrese su opcion: ", &opcion, 1, 7);

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
                break;
            case 4:
                printf("Agregar Producto \n"); 
                break; 
                
            case 5: 
                    printf("Quitar Producto\n"); 
                    quitarProducto(lista_productos);
                    break; 
                
            case 6: 
                    printf("Agregar pedido \n");
                    agregarPedido(lista_productos, cola_pedidos);
                    break;
            case 7: 
                printf("\nVolviendo al Menu Principal...\n");
                return;  // Salir de la función y volver al menú principal


        }
    }
}

void mostrarSubMenuPedido(lista_doble * cola_pedidos, lista_doble * lista_productos) {
    int opcion=0;

    while (1) {
        printf("\n----- Submenu de Pedido -----\n");
        printf("1. Liberar Pedido\n");
        printf("2. Ver Colas de Pedido\n");
        printf("3. Volver al Menu Principal\n");
        leerEnteroRango("Ingrese su opcion: ", &opcion, 1, 3);

        switch (opcion) {
            case 1:
                printf("Opcion: Liberar Pedido\n");
                break;
            case 2:
                printf("Opcion: Ver Colas de Pedido\n");
                imprimirColaPedidos(cola_pedidos, lista_productos);

                break;
            case 3:
                printf("\nVolviendo al Menu Principal...\n");
                return;  // Salir de la función y volver al menú principal
        }
    }
}

void mostrarSubMenuVentas() {
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
                break;
            case 2:
                printf("Opcion: Ver Ventas Realizadas\n");
                break;
            case 3:
                printf("\nVolviendo al Menu Principal...\n");
                return;  // Salir de la función y volver al menú principal
        }
    }
}


void mostrarMenu(lista_doble* lista_productos, lista_doble * cola_pedidos) {
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
                mostrarSubMenuInventario(lista_productos, cola_pedidos);
                break;
            case 2:
                mostrarSubMenuPedido(cola_pedidos, lista_productos);
                break;
            case 3:
                mostrarSubMenuVentas();
                break;
            case 4:
                printf("\nSaliendo del programa...\n");
                return;  // Finalizar el programa
        }
    }
}

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

void leerCadena(char prompt[], char cadena[], int longitud) {
    printf("%s", prompt);
    fflush(stdout); // Vaciar el búfer de salida para mostrar el prompt inmediatamente

    fgets(cadena, longitud, stdin);

    // Eliminar el carácter de nueva línea si está presente
    int longitudCadena = strlen(cadena);
    if (longitudCadena > 0 && cadena[longitudCadena - 1] == '\n') {
        cadena[longitudCadena - 1] = '\0';
    }
}


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


Producto * buscarNodoPorId(lista_doble* lista_d, int idBuscado) {
    nodo_doble* actual = lista_d->head;
    	
    Producto * producto=NULL;
    while (actual != NULL) {
         producto = (Producto*)actual->info;
        if (producto->id == idBuscado) {
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

/*
void eliminarColaPedidos(lista_doble * cola_pedidos){
    //Si está vacía entonces lista_d->head es NULL y no entrará al ciclo while. 
    nodo_doble* actual = cola_pedidos->head;
    nodo_doble* siguiente;

    lista_doble * pedido =NULL; //Nos servirá para eliminar la lista doble que se encuentra en el campo info de cada nodo de la cola.

    while (actual != NULL) {
        siguiente = actual->next;

        //pedido = (lista_doble*) actual->info;
        //eliminarListaD(pedido);

        eliminarListaD(actual->info);
        free(actual);
        actual = siguiente;
    }

    cola_pedidos->head = NULL;
    cola_pedidos->tail = NULL;

    free(cola_pedidos);
}
*/
/*
void imprimirColaPedidos(lista_doble * cola_pedidos){

    if(listaVacia(cola_pedidos)){
        printf("\n--- La cola de pedidos esta vacia---\n");
    }


    nodo_doble* actual = cola_pedidos->head;

    int k=1; 
    while (actual != NULL) {
        lista_doble* pedido = (lista_doble*)actual->info;
        printf("\n Pedido %d", k); 
        printf("\n Nombre pedido: %s",pedido->nombre );
        imprimirListaDProducto(pedido);
        actual = actual->next;
        k++;
    }

}

*/

int existenciaInventario(lista_doble * lista_productos){

    if(listaVacia(lista_productos)){
        printf("\n--- La lista esta vacia---\n");
        return 0;
    }

    nodo_doble* actual = lista_productos->head;
    Producto * producto;
    while (actual != NULL) {
         producto = (Producto*)actual->info;
        
        if(producto->cantidad >= 1){
            return 1;
        }
        actual = actual->next;
    }
    return 0;
    
}

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
    Producto * producto=NULL;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        producto = crearProducto();
        sscanf(linea, "%[^,],%d,%f,%d", producto->nombre, &(producto->id), &(producto->precio), &(producto->cantidad));
        agregarFinalLD(lista_productos, producto);
    }

    fclose(archivo);
    printf("Inventario cargado desde el archivo.\n");
    return lista_productos;
}









 



