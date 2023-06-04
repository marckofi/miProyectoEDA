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


//Funciones para el menu y para leer entrada desde el teclado. 

void mostrarMenu(lista_doble * lista_productos);
void mostrarSubMenuInventario(lista_doble * lista_productos);
void mostrarSubMenuPedido();
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

void verColasPedido();

void registrarVentas();

void verVentasRealizadas();

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


    
    lista_doble * cola_pedidos = crearListaDoble();
    lista_doble *lista_productos = cargarInventario();

    strcpy(lista_productos->nombre, "Lista productos" );
    strcpy(lista_productos->nombre, "Cola pedido" );



    
    imprimirListaDProducto(lista_productos);

    mostrarMenu(lista_productos);


    guardarInventario(lista_productos);



    eliminarListaD(lista_productos);




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
    nodo_doble* siguiente;

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

    while (actual != NULL) {
        Producto* producto = (Producto*)actual->info;
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

    while (actual != NULL) {
        Producto* producto = (Producto*)actual->info;
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

        return extraerInicioLD(lista_d);
    }

    if(actual->next==NULL){

        //El nodo a extraer está en la tail.
        return extraerFinalLD(lista_d);
    }

    //Si realmente está en medio. 


    actual->prev->next=actual->next; 

    actual->next->prev=actual->prev;

    actual->next=NULL; 
    actual->prev=NULL;


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
    float nuevo_precio =0; //Aqui duda. Se puede inicializar en 0 o debe de ser 0.0?

    printf("\n El producto que quieres cambiar es: \n"); 
    imprimirProducto(*producto_cambiar);

    printf("\n Ingresa la nueva cantidad del producto con ID %d: ", id_cambiar);
    leerEntero("", &nueva_cantidad);

    printf("\n Ingresa el nuevo precio  del producto con ID %d: ", id_cambiar);
    leerFloat("", &nuevo_precio);

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

void agregarPedido(lista_doble * lista_productos, lista_doble * cola_pedidos) {
    printf("Opcion: Agregar Pedido\n");
    char nombre_pedido[50]; 
    int id_producto_pedido=0; 
    int cantidad_producto_pedido=0;

    lista_doble * pedido = crearListaDoble(); 
    leerCadena("\nIngresa el nombre del pedido : ", nombre_pedido, 50); 

    Producto * producto_cola= NULL;

    Producto *  producto_pedido_lista=  lista_productos->head->info ; //Solo es para inicializarlo en algun valor.
    do{

        if(producto_pedido_lista==NULL){
            printf("\nIngresa un valor valido de ID");
        }
        leerEntero("\n Ingresa el ID del producto que quieres agregar: ", &id_producto_pedido);
        Producto * producto_pedido_lista = buscarNodoPorId(lista_productos, id_producto_pedido);  // Producto que se quiere comprar. 
    
    }while(producto_pedido_lista==NULL);

    cantidad_producto_pedido=1;

    do{

        if(cantidad_producto_pedido <= 0 || cantidad_producto_pedido > producto_pedido->cantidad){
            printf("\n Ingresa una cantidad valida");
        }
        leerEntero("\n Escribe la cantidad que quieres de ese producto ", &cantidad_producto_pedido);


    }while(cantidad_producto_pedido > producto_pedido->cantidad || cantidad_producto_pedido<=0);

    producto_pedido_lista->cantidad = producto_pedido_lista->cantidad - cantidad_producto_pedido; //Restamos la cantidad 

    producto_pedido = crearProducto();  // Producto cola es el que se añadirá a cada pedido. 

    llenarProducto(producto_pedido, producto_pedido_lista->nombre, producto_pedido_lista->precio, cantidad_producto_pedido, id_producto_pedido);

    agregarFinalLD(pedido, producto_pedido);



    agregarFinalLD(cola_pedidos,pedido);

    




}

void liberarPedido() {
    printf("Opcion: Liberar Pedido\n");
}

void verColasPedido() {
    printf("Opcion: Ver Colas de Pedido\n");
}

void registrarVentas() {
    printf("Opcion: Registrar Ventas\n");
}

void verVentasRealizadas() {
    printf("Opcion: Ver Ventas Realizadas\n");
}


void mostrarSubMenuInventario(lista_doble * lista_productos) {
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
                    break;
            case 7: 
                printf("\nVolviendo al Menu Principal...\n");
                return;  // Salir de la función y volver al menú principal


        }
    }
}

void mostrarSubMenuPedido() {
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


void mostrarMenu(lista_doble* lista_productos) {
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
                mostrarSubMenuPedido();
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

    while (actual != NULL) {
        Producto* producto = (Producto*)actual->info;
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

void guardarInventario(lista_doble * lista_productos) {
    FILE* archivo = fopen("inventario.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo. \n");
        return;
    }

    nodo_doble * current = lista_productos->head;
    
    while (current != NULL) {
        Producto * current_product = (Producto *)current->info;
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
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        Producto * producto = crearProducto();
        sscanf(linea, "%[^,],%d,%f,%d", producto->nombre, &(producto->id), &(producto->precio), &(producto->cantidad));
        agregarFinalLD(lista_productos, producto);
    }

    fclose(archivo);
    printf("Inventario cargado desde el archivo.\n");
    return lista_productos;
}









 



