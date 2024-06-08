#include <iostream>
using namespace std;
void  eliminarFila(int** &panel,int n);
void  asignarCeros(int** &panel,int n);
void torneo(int** &panel,int numParejas);
static int n;
int main() {
    n = 5; // example value, you can change it to any desired value
    bool esImpar=false;
    if(n%2!=0){
        esImpar=true;
        n=n+1;//6
    }
    int dias = n-1;//5
    int** panel = new int*[n+1];

    for (int i = 0; i <= n; i++) {
        panel[i] = new int[dias+1];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=dias;j++){
            panel[i][j] = -1;
        }
    }
    torneo(panel,n);
    if(esImpar){
        for(int j=1;j<=n-1;j++){
            int fila=panel[n][j];
            panel[fila][j]=0;
            panel[n][j]=-1;
        }
        n=n-1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=dias;j++){
            cout <<panel[i][j] << " | ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
void torneo(int** &panel,int numParejas){
    int m;

    if(numParejas==2){
        panel[1][1] = 2;
        panel[2][1] = 1;
    }
    else{
        if(numParejas%2!=0){
            torneo(panel,numParejas+1);
            eliminarFila(panel,numParejas+1);
            asignarCeros(panel,numParejas+1);
        }
        else{
            m=numParejas/2;
            torneo(panel,m);
            //SI M ES PAR
            if(m%2==0){

                //COMPLETAR Inf-Izq 
                for(int j=1;j<=numParejas/2;j++){// "[i-m,j]"+ n/2= el valor de fila-m en la columna j + (n/2)
                    for(int i=m+1;i<=numParejas;i++){
                        panel[i][j] = panel[i-m][j]+(numParejas/2);
                    }
                }

                //COMPLETAR Sup-Der
                for(int j=numParejas-m;j<=numParejas-1;j++){//((n/2)+"1")= para la posicion i,j se le asigna n/2+i -> i=valor de la fila {1,2,3..n/2}
                    for(int i=1;i<=m;i++){
                        if(j==numParejas-m){
                            panel[i][j] = (numParejas/2)+i;
                        }
                        else if (i != m) {
                            panel[i][j] = (i + j > numParejas) ? (m + 1) : (j + i);
                        } else {
                            panel[i][j] = j;
                        }
                    }
                }

                //COMPLETAR Inf-Der Pot2
                for(int j=numParejas/2;j<=numParejas-1;j++){
                    for(int i=m+1;i<=numParejas;i++){
                        if(j==numParejas/2){
                            if(i==m+1){// 1. pos i,j = 1. Siempre
                                panel[i][j] = 1;
                            }
                            else{//2. en la misma columna, los siguientes valores en la posicion i+1,j = al valor de la fila anterior+1
                                panel[i][j] =panel[i-1][j]+1;
                            }
                        }
                        else{//3. si hemos iterado a la siguiente columna
                            if(i==m+1){//4. el valor la primera fila de la siguiente columna toma el valor de la ultima fila de la columna anterior
                                panel[i][j] = panel[numParejas][j-1] ;
                            }
                            else{//5. los valores de la siguiente columna corresponden a los valores de una columna anterior y la fila anterior a la actual 
                                panel[i][j] = panel[i-1][j-1] ;
                            }
                        }
                    }
                }
            }

            //SI M ES IMPAR
            else{
                //completar Inf-Izq: sumar n/2, pero no a los que valen 0
                for(int j=1;j<=numParejas/2;j++){//OK
                    for(int i=m+1;i<=numParejas;i++){
                       if(panel[i-m][j]!=0){
                            panel[i][j]=panel[i-m][j]+(numParejas/2);
                       }else{
                            panel[i][j]=0;
                       }
                    }
                }

                //COMPLETAR Sup-Der y generar columna 0 Sup-Izq
                for(int j=numParejas-m;j<=numParejas-1;j++){//1. Como m impar, nos colocamos en la columan n-m
                    for(int i=1;i<=m;i++){
                        if(j==numParejas-m){//si estamos en la columna de partida
                            if(i==1){//fila de partida
                                panel[i][j] = (numParejas/2)+i;//se asigna el valor igual que en Sup-Der cuando m es par
                            }
                            else if(panel[i][j-(i-1)]==0){//aqui se comprueba si existen 0's en la misma fila pero para una columna menos la fila actual-1
                                panel[i][j-(i-1)] = (numParejas/2)+i;//se asigna el valor a la posicion si esta vale 0, de la misma forma que Sup-Der m par
                            }
                            else{
                                panel[i][i-j] = (numParejas/2)+i;
                            }
                        }
                        else{//si no estamos en la columna de partida
                            if(i!=m){
                                if(i+j>numParejas)
                                    panel[i][j] = m+1;
                                else
                                    panel[i][j] = j+i;
                            }
                            else{
                                panel[i][j] = j;
                            }
                        }
                    }
                }

                //COMPLETAR Inf-Der y generar columna 0 Inf-Izq
                for(int j=(numParejas/2);j<=numParejas-1;j++){
                    for(int i=m+1;i<=numParejas;i++){//m=3   i=4,5,6   j=3,4,5
                        if(j==(numParejas/2)){//fila 3 para n=6
                            int aux = i-(m+1);
                            if(i==m+1){
                                panel[i][j] = 1;//siempre 1
                            }                           //5-3... 6-3                                 // 1
                            else if(panel[i][j-aux]==0){//1,2,3..
                                panel[i][j-aux] = i-m;
                            }
                            else{
                                panel[i][j] =panel[i-1][j]+1;
                            }
                        }
                        else if(j==(numParejas/2)+1){
                            int aux = i-(m+1);
                            if(i==m+1){
                                panel[i][j] = n-m;
                            }                                                          // 1
                            else{                
                                panel[i][j] = i-(m+1);
                            }

                        }
                        else{
                            if(i==m+1){
                                panel[i][j] = panel[numParejas][j-1] ;
                            }
                            else{
                                panel[i][j] = panel[i-1][j-1] ;
                            }
                        }
                    }
                }
            }
        }
    }   
}

void  eliminarFila(int** &panel,int numParejas){//poner a -1 la fila n hasta la columna n-1
    for(int j=1;j<=numParejas-1;j++){
        panel[numParejas][j] = -1;
    }
}
void  asignarCeros(int** &panel,int numParejas){//asigna 0 a los valores de la matriz que sean iguales a n, desde la fila i hasta la ultima fila de la matriz original, y desde la columna 1 hasta la columna n-1
    //parte superior
    for(int j=1;j<=(numParejas-1);j++){
        for(int i=1;i<=numParejas-1;i++){
            if(panel[i][j]==numParejas){
                panel[i][j] = 0;//parte superior
            }  
        }
    }
}
//COMPLETAR Sup-Der y generar columna 0 Sup-Izq
                /* for(int j=numParejas-m;j<=numParejas-1;j++){//1. Como m impar, nos colocamos en la columan n-m
                    for(int i=1;i<=m;i++){
                        if(j==numParejas-m){//si estamos en la columna de partida
                            if(i==1){//fila de partida
                                panel[i][j] = (numParejas/2)+i;//se asigna el valor igual que en Sup-Der cuando m es par
                            }
                            else if(panel[i][j-(i-1)]==0){//aqui se comprueba si existen 0's en la misma fila pero para una columna menos la fila actual-1
                                panel[i][j-(i-1)] = (numParejas/2)+i;//se asigna el valor a la posicion si esta vale 0, de la misma forma que Sup-Der m par
                            }
                            else{
                                panel[i][i-j] = (numParejas/2)+i;
                            }
                        }
                        else{//si no estamos en la columna de partida
                            if(i!=m){
                                if(i+j>numParejas)
                                    panel[i][j] = m+1;
                                else
                                    panel[i][j] = j+i;
                            }
                            else{
                                panel[i][j] = j;
                            }
                        }
                    }
                } */