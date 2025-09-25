#include <iostream>
#include <string>

using namespace std;

int main() {
    int codigos[100] = {101, 102, 103, 104, 105};
    string nombres[100] = {"Martillo de bola", "Destornillador", "Cinta métrica", "Llave inglesa", "Taladro inalámbrico"};
    int stock[100] = {50, 120, 75, 45, 10};
    float precios[100] = {15.50, 8.75, 20.00, 25.99, 120.00};
    int totalProductos = 5;
    
    int opcion;
    
    cout << "--- Bienvenido al sistema de inventario de \"El Martillo\" ---" << endl;
    
    while(true) {
        cout << "\nSeleccione una opción:" << endl;
        cout << "1. Consultar un producto" << endl;
        cout << "2. Actualizar inventario" << endl;
        cout << "3. Generar reporte completo" << endl;
        cout << "4. Encontrar el producto más caro" << endl;
        cout << "5. Salir" << endl;
        cout << "\nOpción seleccionada: ";
        cin >> opcion;
        
        if(opcion == 1) {
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
        
        else if(opcion == 3) {
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
        
        else if(opcion == 4) {
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
        
        else if(opcion == 5) {
            cout << "Cerrando sesión.. " << endl;
            break;
        }
        
        else {
            cout << "Ingrese otra opción" << endl;
        }
    }
    
    return 0;
}
