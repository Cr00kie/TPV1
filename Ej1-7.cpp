#include <iostream>

struct Tablero
{
public:
    Tablero(){
        //for(int& e : casillas) e = 0;
    }
    
    friend std::ostream& operator<< (std::ostream& os, const Tablero& tab){
        os << "+-+-+-+" << std::endl;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                os << "|" << tab.casillas[3*i+j];
            }
            os << "|" << std::endl;
            os << "+-+-+-+" << std::endl;
        }
        return os;
    }

    bool TableroCompleto(){
        int i = 0;
        while(i < 9 && casillas[i] != 0) i++;
        return i >= 9;
    }

    bool TresEnRaya(int pieza){
        bool enc = false;
        int i = 2;
        while(i < 9 && !enc)
        {
            enc = CompruebaDireccion(i, -1, -1, pieza);
            enc = CompruebaDireccion(i, 0, -1, pieza);
            enc = CompruebaDireccion(i, -1, 0, pieza);
            i++;
        }
        return i < 9;
    }

    private:
    int casillas[9] = {-1,0,0,
                        1,0,-1,
                       -1,0,-1};

    bool CompruebaDireccion(int posIni, int dirX, int dirY, int pieza){
        int count = 0;
        while(posIni < 9 && posIni >= 0 && casillas[posIni] == pieza && count != 3){ 
            posIni += dirX;
            posIni += 3 * dirY;
            count++;
        }
        return count == 3;
    }
};

int main(){
    Tablero tab;
    std::cout << tab << std::endl;

    std::cout << "Solucionado? " << tab.TresEnRaya(-1) << std::endl;
}