#include <iostream>

bool BuscaLetraEnString(char letra, const char* const v){
    int i = 0;
    while(v[i] != 0 && v[i] != letra){
        ++i;
    }
    return v[i] != 0;
}

bool CompruebaInclusion(const char* const v1, const char* const v2){
    int i = 0;
    while(v1[i] != 0 && BuscaLetraEnString(v1[i], v2))
        ++i;
    return v1[i] == 0;
}


int main(){
    std::cout << CompruebaInclusion("kaka", "buenas hola, que tal");
}