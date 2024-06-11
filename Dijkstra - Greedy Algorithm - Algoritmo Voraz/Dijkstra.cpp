#include <iostream>
using namespace std;
float INF = 9999;

int elegirvertice_costemin(int* C,float* S,int n){
    int costemin = INF;
    int vertice_costemin = 0;
    for(int i=1;i<=n;i++){
        if(C[i] != 0 && S[i] < costemin){
            costemin = S[i];
            vertice_costemin = i;
        }

    }
    return vertice_costemin;
}
// Dijkstra's algorithm
            //vertices   matriz    costes
void Dijkstra(int* &C,int* &P,int* &C1,int* &P1, float** A, float* &S,int n,int origen){
    int i,j,x;
    i=j=x=0;

    //Copiamos valores de C en C1
    for(int i=0;i<=n;i++){
        C1[i] = C[i];
    }
    //Copiamos valores de P en P1
    for(int i=0;i<=n;i++){
        P1[i] = P[i];
    }

    // origen
    for (i = 1; i <= n; i++) {
        if (i == origen)
        {
            S[i] = 0;
        }else{  

            S[i] = A[origen][i]; // Copiamos los valores de la fila del origen
        }
    }

    //Trabajamos sobre las copias C1 y P1 para no modificar los originales
    //y así poder hacer multiples veces Dijkstra según el origen
    for(i=1;i<=n-1;i++){
        x = elegirvertice_costemin(C1,S,n);
        C1[x] = 0; //Visitado = 0
        for(j=1;j<=n;j++)
        {
            if(C1[j] != 0){
                float temp = S[j];
                if (S[x] + A[x][j] < S[j]) {
                    S[j] = S[x] + A[x][j];
                    P1[j] = x;
                }
            }
        }    
   }   
}
void printMatrix(float** matrix, int rows, int cols) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            cout << " |" << matrix[i][j] << "| ";
        }
        cout << endl;
    }
}

int main() {
    
    const int n = 4;
    int origen;

    float **A = new float*[n+1];
    for(int i=0;i<=n;i++){
        A[i] = new float[n+1];
     }

    float values[n+1][n+1] = {
        {0,   0,   0,   0,   0},
        {0,   0,  30, 120, INF},
        {0,  50,   0,  70,  50},
        {0, 140,  60,   0,  30},
        {0,  25, 100,  80,   0}
    };

    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            A[i][j] = values[i][j];
        }
    }


    int *C = new int[n+1];
    int *C1 = new int[n+1];
    for(int i=0;i<=n;i++){
        C[i] = i;
        C1[i] = 0;
    }

    int *P = new int[n+1];
    int *P1 = new int[n+1]; 
    for(int i=1;i<=n;i++){
        P[i] = 0;
        P1[i] = 0;
    }

    float *S = new float[n];
    for(int i=0;i<=n;i++){
        S[i] = INF;
    }

    origen = 1;
    Dijkstra(C,P,C1,P1,A,S,n,origen);

    cout<<"Predecesores:"<<endl;
    for (int i = 1; i <=n; i++)
    {
        if (P1[i] == 0){
            P1[i] = origen;
        }  
        cout<< " |" << P1[i] <<"| ";
    }
    cout<<endl;
    cout<<"Costos:"<<endl;
    for(int i=1;i<=n;i++){
   
        cout << " |" << S[i] << "| ";//precio de los destinos
    }

    cout <<endl;
    cout << "Matrix A:" << endl;
    printMatrix(A, n, n);
    system("pause");
    return 0;
}

