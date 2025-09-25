#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int codigos[100];
string nombres[100];
int stock[100];
float precios[100];
string ubicaciones[100];
int totalProductos = 0;


void cargarInventario() {
    ifstream archivo("/data/inventario.txt");
    if(!archivo.is_open()) {
        cout << "Ha habido un error, no se encuentra el archivo de texto" << endl;
        return;
    }
    
    totalProductos = 0;
    string linea;
    getline(archivo, linea);
    while(getline(archivo, linea) && totalProductos < 100) {
        int comaCodigo = linea.find(',');
        int comaNombre = linea.find(',', comaCodigo + 1);
        int comaStock = linea.find(',', comaNombre + 1);
        int comaPrecio = linea.find(',', comaStock + 1);
        
        if(comaCodigo != string::npos && comaNombre != string::npos && comaStock != string::npos && comaPrecio != string::npos) {
            codigos[totalProductos] = stoi(linea.substr(0, comaCodigo));
            nombres[totalProductos] = linea.substr(comaCodigo + 1, comaNombre - comaCodigo - 1);
            stock[totalProductos] = stoi(linea.substr(comaNombre + 1, comaStock - comaNombre - 1));
            precios[totalProductos] = stof(linea.substr(comaStock + 1, comaPrecio - comaStock - 1));
            ubicaciones[totalProductos] = linea.substr(comaPrecio + 1);
            totalProductos++;
        }
    }
    archivo.close();
    cout << "Inventario cargado éxitosamente, hay" << totalProductos << " productos en el inventario" << endl;
}

void guardarInventario () {
    ofstream archivo("/data/inventario.txt");
    if(!archivo.is_open()) {
        cout << "No se ha podido guardar lo registrado nuevo" << endl;
        return;
    }
    
    archivo << "Código,Nombre,Cantidad,Precio,Ubicación" << endl;
    
    for(int i = 0; i < totalProductos; i++) {
        archivo << codigos[i] << "," << nombres[i] << "," << stock[i] << "," << precios[i] << "," << ubicaciones[i] << endl;
    }
    archivo.close();
    cout << "Datos guardados en el inventario" << endl;
}


void mostrarMenu() {
    cout << "\nSeleccione una opción:" << endl;
    cout << "1. Consultar un producto" << endl;
    cout << "2. Actualizar inventario por código" << endl;
    cout << "3. Actualizar inventario por ubicación" << endl;
    cout << "4. Registrar nuevo producto" << endl;
    cout << "5. Generar reporte completo" << endl;
    cout << "6. Generar reporte de bajo stock" << endl;
    cout << "7. Encontrar el producto más caro" << endl;
    cout << "8. Encontrar el producto más barato" << endl;
    cout << "9. Salir" << endl;
    cout << "\nOpción seleccionada: ";
}

void consultarProducto() {
    int codigoBuscar;
    cout << "\nIngrese el código del producto a consultar: ";
    cin >> codigoBuscar;
    
    bool encontrado = false;
    for(int i = 0; i < totalProductos; i++) {
        if(codigos[i] == codigoBuscar) {
            cout << "\nInformación del Producto:" << endl;
            cout << "Código: " << codigos[i] << endl;
            cout << "Nombre: " << nombres[i] << endl;
            cout << "Cantidad en stock: " << stock[i] << endl;
            cout << "Precio unitario: $" << precios[i] << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado) {
        cout << "No se ha encontrado el producto" << endl;
    }
}

void generarReporte() {
    cout << "\n--- Reporte del inventario ---" << endl;
    cout << "Código    | Nombre             | Stock | Precio" << endl;
    cout << "-------------------------------------------------" << endl;
    
    for(int i = 0; i < totalProductos; i++) {
        cout << codigos[i] << "       | " << nombres[i];
        for(int j = nombres[i].length(); j < 18; j++) {
            cout << " ";
        }
        cout << " | " << stock[i];
        for(int j = to_string(stock[i]).length(); j < 5; j++) {
            cout << " ";
        }
        cout << " | $" << precios[i] << endl;
    }
    cout << "-------------------------------------------------" << endl;
    cout << "--- Fin del reporte ---" << endl;
}

void generarReporteBajoStock() {
    int umbral = 10;
    cout << "\n--- Reporte de Productos con Bajo Stock ---" << endl;
    cout << "Productos con menos de " << umbral << " unidades:" << endl;
    cout << "-------------------------------------------------" << endl;
    
    bool hayProductosBajoStock = false;
    for(int i = 0; i < totalProductos; i++) {
        if(stock[i] < umbral) {
            cout << "Nombre: " << nombres[i] << ", Stock: " << stock[i] << endl;
            hayProductosBajoStock = true;
        }
    }
    
    if(!hayProductosBajoStock) {
        cout << "No hay productos con bajo stock." << endl;
    }
    cout << "-------------------------------------------------" << endl;
}

void encontrarMasCaro() {
    float precioMayor = precios[0];
    int indiceMayor = 0;
    
    for(int i = 1; i < totalProductos; i++) {
        if(precios[i] > precioMayor) {
            precioMayor = precios[i];
            indiceMayor = i;
        }
    }
    
    cout << "\nEl producto más caro es: " << nombres[indiceMayor] 
         << " con un precio de $" << precioMayor << endl;
}

void encontrarMasBarato() {
    if(totalProductos == 0) {
        cout << "\nNo hay productos en el inventario." << endl;
        return;
    }
    
    float precioMenor = precios[0];
    int indiceMenor = 0;

    for(int i = 1; i < totalProductos; i++) {
        if(precios[i] < precioMenor) {
            precioMenor = precios[i];
            indiceMenor = i;
        }
    }

    cout << "\nEl producto más barato es: " << nombres[indiceMenor] 
         << " con un precio de $" << precioMenor << endl;
}


void actualizarInventario () {
    int codigoActualizar, nuevaCantidad;
    cout << "\nIngrese el código del producto a actualizar: ";
    cin >> codigoActualizar;
    
    bool encontrado = false;
    for(int i = 0; i < totalProductos; i++) {
        if(codigos[i] == codigoActualizar) {
            cout << "Producto encontrado: " << nombres[i] << endl;
            cout << "Cantidad actual en stock: " << stock[i] << endl;
            cout << "Ingrese la nueva cantidad en stock: ";
            cin >> nuevaCantidad;
            if(nuevaCantidad >= 0) {
                stock[i] = nuevaCantidad;
                cout << "Stock actualizado correctamente." << endl;
            } else {
                cout << "La cantidad no puede ser negativa." << endl;
            }
            encontrado = true;
            break;
        }
    }
    if(!encontrado) {
        cout << "No se ha encontrado el producto" << endl;
    }
}

void actualizarPorUbicacion() {
    string ubicacionBuscar;
    int nuevaCantidad;
    cout << "\nIngrese la ubicación del producto a actualizar: ";
    cin >> ubicacionBuscar;
    
    bool encontrado = false;
    for(int i = 0; i < totalProductos; i++) {
        if(ubicaciones[i] == ubicacionBuscar) {
            cout << "Producto encontrado: " << nombres[i] << endl;
            cout << "Ubicación: " << ubicaciones[i] << endl;
            cout << "Cantidad actual en stock: " << stock[i] << endl;
            cout << "Ingrese la nueva cantidad en stock: ";
            cin >> nuevaCantidad;
            if(nuevaCantidad >= 0) {
                stock[i] = nuevaCantidad;
                cout << "Stock actualizado correctamente." << endl;
            } else {
                cout << "La cantidad no puede ser negativa." << endl;
            }
            encontrado = true;
            break;
        }
    }
    if(!encontrado) {
        cout << "No se encontró ningún producto en esa ubicación" << endl;
    }
}

void registrarNuevoProducto() {
    if(totalProductos >= 100) {
        cout << "No se pueden agregar más productos. Inventario lleno." << endl;
        return;
    }
    
    int nuevoCodigo;
    cout << "\nIngrese el código del nuevo producto: ";
    cin >> nuevoCodigo;
    
    bool codigoExiste = false;
    for(int i = 0; i < totalProductos; i++) {
        if(codigos[i] == nuevoCodigo) {
            codigoExiste = true;
            break;
        }
    }
    
    if(codigoExiste) {
        cout << "Error: Ya existe un producto con ese código." << endl;
        return;
    }
    
    cout << "Ingrese el nombre del producto: ";
    cin.ignore();
    getline(cin, nombres[totalProductos]);
    
    cout << "Ingrese la cantidad en stock: ";
    cin >> stock[totalProductos];
    
    if(stock[totalProductos] < 0) {
        cout << "Error: La cantidad no puede ser negativa." << endl;
        return;
    }
    
    cout << "Ingrese el precio unitario: ";
    cin >> precios[totalProductos];
    
    if(precios[totalProductos] < 0) {
        cout << "Error: El precio no puede ser negativo." << endl;
        return;
    }
    
    cout << "Ingrese la ubicación en almacén: ";
    cin >> ubicaciones[totalProductos];
    
    codigos[totalProductos] = nuevoCodigo;
    totalProductos++;
    
    cout << "Producto registrado exitosamente." << endl;
}

int main() {
    int opcion;
    
    cout << "--- Bienvenido al sistema de inventario de \"El Martillo\" ---" << endl;
    cout << "\nCargando inventario.. " << endl;
    cargarInventario();
    
    while(true) {
        mostrarMenu();
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                consultarProducto();
                break;
            case 2:
                actualizarInventario();
                break;
            case 3:
                actualizarPorUbicacion();
                break;
            case 4:
                registrarNuevoProducto();
                break;
            case 5:
                generarReporte();
                break;
            case 6:
                generarReporteBajoStock();
                break;
            case 7:
                encontrarMasCaro();
                break;
            case 8:
                encontrarMasBarato();
                break;
            case 9:
                guardarInventario();
                cout << "Cerrando sesión.. " << endl;
                return 0;
            default:
                cout << "Ingrese otra opción que sí sea válida" << endl;
        }
    }
    
    return 0;
}
