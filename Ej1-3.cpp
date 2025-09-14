#include <iostream>

constexpr int N = 3;

class Matriz{
public:
    Matriz(int iniDatos[N][N]){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                datos[i][j] = iniDatos[i][j];
            }
        }
    } 

    friend Matriz operator+ (Matriz lm, const Matriz& rm){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                lm.datos[i][j] += rm.datos[i][j];
            }
        }

        return lm;
    }

    friend std::ostream& operator<< (std::ostream& os, const Matriz& m){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                os << m.datos[i][j];
            }
        }

        return os;
    }

private:
    int datos[N][N];

};



int main(){
    int datos1[N][N] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int datos2[N][N] = { {3, 2, 1}, {6, 4, 5}, {9, 7, 8}};

    Matriz m1(datos1);
    Matriz m2(datos2);

    Matriz m3 = m1 + m2;

    std::cout << m3;
}