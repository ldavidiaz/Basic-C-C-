#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    char alfabeto_letras[] = "abcdefghijklmn\xA4opqrstuvwxyz";
    char alfabeto_con_digitos[] = "abcdefghijklmn\xA4opqrstuvwxyz0123456789";

    int tipoClave;
    cout << "Tipo de clave: \n-[1] Alfabeticas\n-[2] Alfanumericas" << endl;
    cin >> tipoClave;

    char* alfabeto = (tipoClave == 1) ? alfabeto_letras : alfabeto_con_digitos;

    int tamKey;
    do{
        cout << "Ingrese el tamano de la clave: ";
        try{
            cin >> tamKey;
            if (cin.fail() || tamKey <= 0 || tamKey > 4) {
                throw runtime_error("El tamano de la clave debe ser mayor que 0 y menor o igual a 4.");
            }
        }catch(exception& e){
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    
    }while(tamKey<=4);
    string clave;
    bool claveValida = false;
    do{
        cout << "Elige una clave: ";
        cin >> clave;
        if(clave.length() != tamKey){
            cout << "La clave debe tener " << tamKey << " caracteres." << endl;
        }else{
            claveValida = true;
        }
    }while(!claveValida);
    char *key;
    bool keyEncontrada = false;
    int contador = 0;

    for (int k = 1; k <= tamKey; k++) {
        for (int i = 0; i < strlen(alfabeto); i++) {
            if (k > 1 && keyEncontrada==false) {
                for (int j = 0; j < strlen(alfabeto); j++) {
                    if (k > 2 && keyEncontrada==false) {
                        for (int y = 0; y < strlen(alfabeto); y++) {
                            if (k > 3 && keyEncontrada==false) {
                                for (int z = 0; z < strlen(alfabeto); z++) {
                                    contador++;
                                    key = new char[5];
                                    key[0] = alfabeto[i];
                                    key[1] = alfabeto[j];
                                    key[2] = alfabeto[y];
                                    key[3] = alfabeto[z];
                                    key[4] = '\0'; // Añadir el terminador nulo al final de la cadena

                                    if (strcmp(key, clave.c_str()) == 0) {
                                        keyEncontrada = true;
                                        //break;
                                        goto found;
                                    } else {
                                        delete[] key;
                                        key = nullptr;
                                    }
                                }
                            } else {
                                contador++;
                                key = new char[4];
                                key[0] = alfabeto[i];
                                key[1] = alfabeto[j];
                                key[2] = alfabeto[y];
                                key[3] = '\0'; // Añadir el terminador nulo al final de la cadena

                                if (strcmp(key, clave.c_str()) == 0) {
                                    keyEncontrada = true;
                                    //break;
                                    goto found;
                                } else {
                                    delete[] key;
                                    key = nullptr;
                                }
                            }
                        }
                    } else {
                        contador++;
                        key = new char[3];
                        key[0] = alfabeto[i];
                        key[1] = alfabeto[j];
                        key[2] = '\0'; // Añadir el terminador nulo al final de la cadena

                        if (strcmp(key, clave.c_str()) == 0) {
                            keyEncontrada = true;
                            //break;
                            goto found;
                        } else {
                            delete[] key;
                            key = nullptr;
                        }
                    }
                }
            } else {
                contador++;
                key = new char[2];
                key[0] = alfabeto[i];
                key[1] = '\0'; // Añadir el terminador nulo al final de la cadena

                if (strcmp(key, clave.c_str()) == 0) {
                    keyEncontrada = true;
                    //break;
                    goto found;
                } else {
                    delete[] key;
                    key = nullptr;
                }
            }
            /* if (keyEncontrada) {
                break;
            } */
        }
       /*  if (keyEncontrada) {
                break;
        } */
        
    }
    found:
    if (keyEncontrada) {
        cout << "Clave encontrada: " << key << endl;
    } else {
        cout << "No se ha podido encontrar la clave." << endl;
    }

    cout << "Numero de claves intentadas: " << contador << endl;
    system("pause");
    return 0;
}
