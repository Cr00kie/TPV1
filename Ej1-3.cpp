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
    friend Matriz operator- (Matriz lm, const Matriz& rm){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                lm.datos[i][j] -= rm.datos[i][j];
            }
        }

        return lm;
    }


    friend Matriz operator* (const Matriz& lm, const Matriz& rm){
        int res[N][N] = {{0,0,0},{0,0,0},{0,0,0}};

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < N; k++){
                    res[i][j] += lm.datos[i][k] * rm.datos[k][j];
                }
            }
        }

        Matriz result(res);
        return result;
    }

    friend std::ostream& operator<< (std::ostream& os, const Matriz& m){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                os << m.datos[i][j] << " ";
            }
            os << std::endl;
        }

        return os;
    }

    Matriz& Traspuesta(){
        for(int i = 0; i < N; i++)
            for(int j = i; j < N; j++){
                int temp = datos[i][j];
                datos[i][j] = datos[j][i];
                datos[j][i] = temp;
            }
        return *this;
    }

private:
    int datos[N][N];

};



int main(){

    int datos1[N][N] = { {1, 2, 0}, 
                         {0, 1, 0}, 
                         {0, 0, 1}};

    int datos2[N][N] = { {1, 0, 0}, 
                         {1, 2, 0}, 
                         {2, 3, 3}};

    Matriz m1(datos1);
    Matriz m2(datos2);

    std::cout << m2.Traspuesta();
}