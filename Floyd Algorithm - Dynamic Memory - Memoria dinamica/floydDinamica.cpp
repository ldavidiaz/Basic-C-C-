// Luis David Mesa, Javier Crespo

#include <iostream>
#include <fstream>
using namespace std;
const long INFINITY=9999;
const long NEGATIVE=-1;

// Función para imprimir una matriz
void printMatrix(double **matrix, int rows, int cols) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void floyd(double **D, double **P,int n);
int main() {
    // Definir el tamaño de la matriz
    int rows = 3;
    int cols = 3;

    // Definir la matriz de números reales
    double **P = new double*[rows+1];
    for (int i = 1; i <= rows; ++i) {
        P[i] = new double[cols+1];
    }

    // Asignar valores a la matriz
    double values[4][4] = {
        {0,0,0,0},
        {0,0,INFINITY,20},
        {0,10,0,5},
        {0,INFINITY,5,0}
    };

    // Copiar los valores a la matriz
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            P[i][j] = values[i][j];
        }
    }

    // Imprimir la matriz original
    cout << "Matriz original:" << endl;
    printMatrix(P, rows, cols);

    // Definir la matriz de adyacencia de pesos
    double **D = new double*[rows+1];
    for (int i = 1; i <= rows; i++) {
        D[i] = new double[cols+1];
    }
    // Asignar valores a la matriz de adyacencia de pesos
    // Por simplicidad, asignamos los mismos valores que la matriz original
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            D[i][j] = 0;
        }
    }

    // Imprimir la matriz de adyacencia de pesos

    floyd(D,P,rows);
    cout<<"\nSolucion:\n";
    printMatrix(D,rows,cols);

    // Liberar la memoria
    for (int i = 0; i < rows; ++i) {
        delete[] P[i];
        delete[] D[i];
    }
    delete[] P;
    delete[] D;
    system("pause");
    return 0;
}
void floyd(double **D, double **P,int n){

    int i,j,k;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            double v= P[i][j];
            D[i][j] = P[i][j];
        }
    }

    for(i=1;i<=n;i++){
        D[i][i] = 0;
    }
    //printMatrix(D,n,n);
    for(k=1;k<=n;k++){
        cout << "Iteracion " << k << endl;
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                if((D[i][k]+D[k][j]) < D[i][j])
                    D[i][j] = D[i][k]+D[k][j];   

                cout << D[i][j] << " ";           
            }
            cout << endl;
        }
        cout << endl;
    }
}