constexpr int MAX_NUM = 3;
constexpr int MAX_ATTEMPS = 10;

#include <random>
std::mt19937_64 generador; // Generador Mersenne Twister de 64 bits
std::uniform_int_distribution<int> distrib(0, MAX_NUM - 1); // [0, MAX_NUM)

#include <iostream>

#pragma region Matriz
class Matrix{
public:
    Matrix(unsigned row, unsigned int col){
        m_nRow = row;
        m_nCol = col;
        m_Elementos = new int*[row];
        for (int i = 0; i < row; ++i){
            m_Elementos[i] = new int[col];
        }
    }

    ~Matrix(){
        for(int i = 0; i < m_nRow; ++i){
            delete [] m_Elementos[i];
        }
        delete [] m_Elementos;
    }

    int get(unsigned int row, unsigned int col) const{
        return m_Elementos[row][col];
    }

    void set(unsigned int row, unsigned int col, int v){
        m_Elementos[row][col] = v;
    }

    bool search(int v){
        for(int i = 0; i < m_nRow; ++i)
            for(int j = 0; j < m_nCol; ++j){
                if(m_Elementos[i][j] == v) return true;
            }
        return false;
    }

    friend std::ostream& operator<< (std::ostream& os, const Matrix& m){
        for(int i = 0; i < m.m_nRow; ++i){
            for(int j = 0; j < m.m_nCol; ++j)
                std::cout << m.m_Elementos[i][j] << " ";
            std::cout << std::endl;
        }
        return os;
    }

private:
    int** m_Elementos;
    unsigned int m_nRow, m_nCol;
};
#pragma endregion



class Game{
    public:
    Game()
    : m_GameMatrix(MAX_NUM, MAX_NUM), m_VisibleMatrix(MAX_NUM, MAX_NUM){
        for(int i = 0; i < MAX_NUM; ++i)
            for(int j = 0; j < MAX_NUM; ++j){
                m_GameMatrix.set(i, j, distrib(generador));
            }

        for(int i = 0; i < MAX_NUM; ++i)
            for(int j = 0; j < MAX_NUM; ++j){
                m_VisibleMatrix.set(i, j, -1);
            }

        m_nNumSearched = m_GameMatrix.get(distrib(generador), distrib(generador));
    }

    void Play(){
        std::cout << "Busca el numero.... " << m_nNumSearched << std::endl;
        std::cout << m_VisibleMatrix << std::endl;
        for(int i = 0; i < MAX_ATTEMPS; ++i){
            std::cout << "Dame las cordenadas [row col]: ";
            int r, c;
            std::cin >> r >> c;
            int numAdivinado = m_GameMatrix.get(r, c);
            m_VisibleMatrix.set(r, c, numAdivinado);
            std::cout << m_VisibleMatrix << std::endl;
            if(numAdivinado == m_nNumSearched){
                std::cout << "Has ganado! Intentos: " << i+1 << std::endl;
                i = MAX_ATTEMPS;
            }
        }
    }

    private:
    Matrix m_GameMatrix, m_VisibleMatrix;
    int m_nNumSearched;
};

int main(){
    Game game;
    game.Play();
}