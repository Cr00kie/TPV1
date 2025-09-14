#include <iostream>

constexpr int N = 5;

class Secuencia
{
public:
	Secuencia(){

	}
	Secuencia(const int sec[N])
	{
		for (int i = 0; i < N; i++)
		{
			enteros[i] = sec[i];
		}
	}

	friend std::ostream& operator<< (std::ostream& os, const Secuencia& sec);
	friend std::istream& operator>> (std::istream& os, Secuencia& sec);
	int enteros[N];
	
};

std::ostream& operator<< (std::ostream& os, const Secuencia& sec)
{
	for (int i = 0; i < N; i++)
	{
		os << sec.enteros[i] << " ";
	}
	return os;
}

std::istream& operator>> (std::istream& is, Secuencia& sec)
{
	for(int i = 0; i < N; ++i){
		std::cin >> sec.enteros[i];
	}
	return is;
}

void RotaDer(Secuencia& sec){
	for(int i = N-1; i > 0; --i){
		int temp = sec.enteros[i];
		sec.enteros[i] = sec.enteros[i-1];
		sec.enteros[i-1] = temp;
	}
}

int SumaPares(Secuencia& sec){
	int nSum = 0;
	for(int i = 0; i < N; i += 2){
		nSum += sec.enteros[i];
	}
	return nSum;
}

int EncuentraMayor(Secuencia& sec){
	int max = 0;
	for(int i = 0; i < N; ++i){
		if(sec.enteros[i] > max)
			max = sec.enteros[i];
	}
	return max;
}

bool SonIguales(Secuencia& sec1, Secuencia& sec2){
	int i = 0;
	while(i < N && sec1.enteros[i] == sec2.enteros[i])
		i++;
	return i >= N;
}

int main()
{
	Secuencia sec1;

	std::cin >> sec1;

	Secuencia sec2;

	std::cin >> sec2;	

	std::cout << SonIguales(sec1, sec2);
}

