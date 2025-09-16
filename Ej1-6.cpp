#include <iostream>
#include <tuple>
#include <string>

int romanoAEntero(const char* numRomano){
    int i = 0;
    int resultado = 0;
    bool error = false;
    int valorASumar = 0;
    int valorAnterior = 1000;
    while(numRomano[i] && !error){
        switch(numRomano[i]){
            case 'M': valorASumar = 1000; break;
            case 'D': valorASumar = 500; break;
            case 'C': valorASumar = 100; break;
            case 'L': valorASumar = 50; break;
            case 'X': valorASumar = 10; break;
            case 'V': valorASumar = 5; break;
            case 'I': valorASumar = 1; break;
            default: error = true; break;
        }

        resultado += valorASumar;

        if(valorAnterior < valorASumar)
            error = true;
        
        valorAnterior = valorASumar;
        
        i++;
    }
    if(error){
        return -1;
    }
    else{
        return resultado;
    }
}
std::string enteroARomano(int entero){
    std::string sResultado = "";
    int nEnteros[] {1, 5, 10, 50, 100, 500, 1000};
    std::string cRomanos[] {"I", "V", "X", "L", "C", "D", "M"};

    for(int i = 6; i >= 0; i--){
        int n = entero/nEnteros[i];
        for(int j = 0; j < n; j++)
            sResultado.append(cRomanos[i]);
        entero %= nEnteros[i];
    }
    return sResultado;
}

int main(){
    std::cout << enteroARomano(1989) << std::endl;
}