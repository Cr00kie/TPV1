#include <iostream>

bool CompruebaAnagrama(const char* cad1, const char* cad2){
    int i = 0;
    int count1 = 0, count2 = 0;
    while(cad1[i] && count1 == count2){
        for(int j = 0; cad1[j]; j++){
            if(cad1[i] == cad1[j]) count1++;
            if(cad1[i] == cad2[j]) count2++;
        }
        i++;
    }

    return !cad1[i];
}

int main(){
    std::cout << "== Comprobador de anagramas ==\n" <<
        "Escribe la primera palabra: " << std::endl;
    
    char cad1[32], cad2[32];
    std::cin >> cad1;

    std::cout << "Escribe la segunda palabra: " << std::endl;
    std::cin >> cad2;

    if(CompruebaAnagrama(cad1, cad2))
        std::cout << "Son anagramas!" << std::endl;
    else
        std::cout << "No son anagramas." << std::endl;
}