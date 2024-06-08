#include <iostream>
using namespace std;
void  eliminarFila(int** &panel,int n);
void  asignarCeros(int** &panel,int n);
void torneo(int** &panel,int numParejas);
void printMatrix(int** panel,int num);
static int n,dias;
int main() {
    n = 5; // example value, you can change it to any desired value
    int esImpar=false;
    if(n%2!=0){
        esImpar=true;
        n=n+1;//6
    }
    dias = n-1;//5
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
    printMatrix(panel,n);
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
        else{//AQUI ESTA MAL CUANDO M ES PAR Y MAYOR QUE 2
            m=numParejas/2;
            torneo(panel,m);
            //SI M ES PAR
            if(m%2==0){
                //(2) COMPLETAR Inf-Izq 
                for(int j=1;j<=numParejas/2;j++){// "[i-m,j]"+ n/2= el valor de fila-m en la columna j + (n/2)
                    for(int i=m+1;i<=numParejas;i++){
                        panel[i][j] = panel[i-m][j]+(numParejas/2);
                    }
                }
                //(3) COMPLETAR Sup-Der//por filas
                for(int i=1;i<=m;i++){//((n/2)+"1")= para la posicion i,j se le asigna n/2+i -> i=valor de la fila {1,2,3..n/2}
                    for(int j=numParejas-m;j<=numParejas-1;j++){
                        if(i==1)    panel[i][j] = j+1;
                        else {
                            panel[i][j] = (panel[i-1][j]==numParejas) ? m+1 : panel[i-1][j]+1;
                        } 
                    }
                }
                //(4) COMPLETAR Inf-Der Pot2  //por filas
                for(int i=m+1;i<=numParejas;i++){
                    for(int j=numParejas/2;j<=numParejas-1;j++){
                        int v=(numParejas-j)+1;
                        if(i==m+1){
                            if(j==numParejas/2) panel[i][j]=1;
                            else panel[i][j]=v;
                        }
                        else{
                            if(panel[i-1][j]==m) panel[i][j]=panel[i-1][j-1];//fila anterior igual a m
                            else panel[i][j] = panel[i-1][j]+1;
                        }
                    }
                }   
            }//Si M es IMPAR
            else{
                //(2) COMPLETAR Inf-Izq: sumar n/2, pero no a los que valen 0 //por filas
                for(int j=1;j<=numParejas/2;j++){//OK
                    for(int i=m+1;i<=numParejas;i++){
                       if(panel[i-m][j]!=0)  panel[i][j]=panel[i-m][j]+(numParejas/2);
                       else  panel[i][j]=0;
                    }
                }
                //(3) COMPLETAR Sup-Der y generar columna 0 Sup-Izq  //por filas
                for(int i=1;i<=m;i++){//((n/2)+"1")= para la posicion i,j se le asigna n/2+i -> i=valor de la fila {1,2,3..n/2}
                    for(int j=numParejas-m;j<=numParejas-1;j++){
                        if(i==1)    panel[i][j] = j+1;
                        else {
                        //1. ¿Estamos en la columna de partida?
                            if(j==numParejas-m){
                                if(panel[i][(j-i)+1]==0)   panel[i][(j-i)+1] = (numParejas/2)+i;  
                            }
                            else   panel[i][j] = (panel[i-1][j]==numParejas) ? m+1 : panel[i-1][j]+1;
                        } 
                    }
                }     
                //(4) COMPLETAR Inf-Der: Fijar 1, asignar valores a las casillas de la parte Inf-Izq que valen 0    
                for(int i=m+1;i<=numParejas;i++){
                    for(int j=numParejas/2;j<=numParejas-1;j++){
                        int v=numParejas-(j-1);
                        if(i==m+1){
                            if(j==numParejas/2) panel[i][j]=1;
                            else panel[i][j]=v;
                        }
                        else{
                            if(j==numParejas-m){
                                if(panel[i][(numParejas-i)+1]==0) panel[i][(numParejas-i)+1]=i-m;
                            } 
                            else{
                                if(panel[i-1][j]==m) panel[i][j]=panel[i-1][j-1];
                                else panel[i][j] = panel[i-1][j]+1;
                            }
                        }
                    }
                }    
              //printMatrix(panel,numParejas);
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
    for(int j=1;j<=(numParejas-1);j++){
        for(int i=1;i<=numParejas-1;i++){
            if(panel[i][j]==numParejas){
                panel[i][j] = 0;
            }  
        }
    }
}
void printMatrix(int** panel,int num){
    for(int i=1;i<=num;i++){
        for(int j=1;j<=dias;j++){
            cout << panel[i][j] << " | ";
        }
        cout <<endl;
    }
}