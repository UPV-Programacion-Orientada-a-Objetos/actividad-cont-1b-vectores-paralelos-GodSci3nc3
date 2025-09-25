#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int codigos[100] = {101, 102, 103, 104, 105};
string nombres[100] = {"Martillo de bola", "Destornillador", "Cinta métrica", "Llave inglesa", "Taladro inalámbrico"};
int stock[100] = {50, 120, 75, 45, 10};
float precios[100] = {15.50, 8.75, 20.00, 25.99, 120.00};

string ubicaciones[100] = {};
int totalProductos = 5;


void cargarInventario() {
    ifstream archivo("inventario.txt");
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
    cout << "Inventario cargado éxitosamente" << totalProductos << " productos en el inventario" << endl;
}

void guardarInventario () {
    ofstream archivo("inventario.txt");
    if(!archivo.is_open()) {
        cout << "No se ha podido guardar el archivo de texto" << endl;
        return;
    }
    
    for(int i = 0; i < totalProductos; i++) {
        archivo << codigos[i] << "," << nombres[i] << "," << stock[i] << "," << precios[i] << "," << ubicaciones[i] << endl;
    }
    archivo.close();
    cout << "Datos guardados en el inventario" << endl;
}


void mostrarMenu() {
    cout << "\nSeleccione una opción:" << endl;
    cout << "1. Consultar un producto" << endl;
    cout << "2. Actualizar inventario" << endl;
    cout << "3. Generar reporte completo" << endl;
    cout << "4. Encontrar el producto más caro" << endl;
    cout << "5. Salir" << endl;
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
    cout << "\n--- Reporte de Inventario ---" << endl;
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
    cout << "--- Fin del Reporte ---" << endl;
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

int main() {
    int opcion;
    
    cout << "--- Bienvenido al sistema de inventario de \"El Martillo\" ---" << endl;
    cout << "\nCargando inventario desde 'inventario.txt'..." << endl;
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
                generarReporte();
                break;
            case 4:
                encontrarMasCaro();
                break;
            case 5:
                guardarInventario();
                cout << "Cerrando sesión.. " << endl;
                return 0;
            default:
                cout << "Ingrese otra opción" << endl;
        }
    }
    
    return 0;
}
