#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct ScoreReg{
    int score;
    std::string user;

    bool operator< (const ScoreReg& r) const{
        return this->score < r.score;
    }

    bool operator> (const ScoreReg& r) const{
        return this->score < r.score;
    }
};

class Scores{
public:
    void Load(const std::string& fileName){
        std::ifstream archivo;
        archivo.open(fileName);

        if(!archivo.is_open())
            throw "[Error]: No se encuentra el archivo";

        ScoreReg registro;
        archivo >> registro.user >> registro.score;
        while(!archivo.fail()){
            m_Scores.push_back(registro);
            archivo >> registro.user >> registro.score;
        }
        archivo.close();

        std::sort(m_Scores.begin(), m_Scores.end());
        std::reverse(m_Scores.begin(), m_Scores.end());
    }

    void PrintTopNScores(int n) const{
        int i = 0;
        while(i < m_Scores.size() && i < n){
            std::cout << "#" << i+1 << " " << m_Scores[i].user << ": " << m_Scores[i].score << std::endl;
            ++i;
        }
    }

    void AddScore(const std::string& name, int score){
        int i = 0;
        while(i < m_Scores.size() && m_Scores[i].score > score)
            ++i;
        ScoreReg r{score, name};
        m_Scores.insert(m_Scores.begin()+i, r);
    }

    void Save(const std::string& fileName){
        std::ofstream archivo(fileName);
        for(ScoreReg& reg : m_Scores){
            archivo << reg.user << "\n" << reg.score << "\n";
        }
        archivo.close();
    }
private:
    std::vector<ScoreReg> m_Scores;
};

int main(){
    Scores scores;
    scores.Load("scores.txt");
    std::cout << "All scores: " << std::endl;
    scores.PrintTopNScores(5);

    std::cout << "Top 3 scores: " << std::endl;
    scores.PrintTopNScores(3);

    bool fin = false;
    while(!fin){
        std::string name;
        int score;
        std::cout << "Introduce una nueva puntuacion [user score]: ";
        std::cin >> name;
        if(name == "") fin = true;
        else{
            std::cin >> score;
            scores.AddScore(name, score);
        }

        std::cout << "Escribe cuantas puntuaciones quieres ver: ";
        int n;
        std::cin >> n;
        scores.PrintTopNScores(n);
    }
    scores.Save("scores.txt");
}