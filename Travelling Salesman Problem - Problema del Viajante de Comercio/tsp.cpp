#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const float INFINITO = 99999;

bool ciclos(const vector<vector<float>>& Coste, const vector<int>& V, int k) {
    for (int i = 1; i < k; ++i) {
        if (V[i] == V[k]) // Si hay un vértice repetido antes de k
            return true;
    }
    return false;
}

float calcularCoste(const vector<vector<float>>& Coste, const vector<int>& V) {
    float coste = 0;
    for (size_t i = 1; i <= V.size()-1; i++) {
        coste += Coste[V[i - 1]][V[i]];
    }
    coste += Coste[V.back()][V[1]]; // Añadir el costo de volver al inicio
    return coste;
}

void viajante_Iter(vector<vector<float>>& Coste, vector<int>& V, float& costeVoptimo, vector<int>& Voptimo,int n) {
    int k = 2;
    V[1] = 1;
    while (k > 1) {
        if (V[k] < n) {
            V[k] = V[k] + 1;
            //int z=V[k];
            if (Coste[V[k - 1]][V[k]] != INFINITO && !ciclos(Coste, V, k)) {
                if (k == n) {
                    if (Coste[V[k]][V[1]] != INFINITO) {
                        float costeV = calcularCoste(Coste, V);
                        if (costeV < costeVoptimo) {
                            costeVoptimo = costeV;
                            Voptimo = V;
                        }
                    }
                }
                else {
                    k++;
                    V[k] = 1;
                }
            } 
        }else{
             k--;
        }
       
    }
}

int main() {
    // Inicialización de la matriz de costos (Coste) y el vector de nodos (V)
    vector<vector<float>> Coste = {
        {0,    0,     0,     0,     0,     0,     0},//0
        {0,    0,     5,  7.07, 16.55, 15.52,    18},//1
        {0,    5,     0,     5, 11.70, 11.05, 14.32},//2
        {0, 7.07,     5,     0,    14, 14.32, 18.38},//3
        {0,16.55, 11.70,    14,     0,     3,  7.62},//4
        {0,15.52, 11.05, 14.32,     3,     0,     5},//5
        {0,   18, 14.32, 18.38,  7.62,     5,     0} //6
    };
    int n = Coste.size()-1;
    vector<int> V(n+1);
    for (int i = 1; i <= n; i++) {
        V[i] = i;
    }
    vector<int> Voptimo(n+1);
    float costeVoptimo = INFINITO;
    
    viajante_Iter(Coste, V, costeVoptimo, Voptimo,n);
    // Mostrar resultado
    cout << "Costo optimo: " << costeVoptimo << endl;
    cout << "Ruta óptima: ";
    for (int v : Voptimo) {
        cout << v << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
