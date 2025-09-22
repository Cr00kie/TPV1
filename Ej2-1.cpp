#include <iostream>
#include <cmath>

class Circle{
public:
    Circle(double x, double y, double radius){
        m_dX = x;
        m_dY = y;
        m_dRadius = radius; 
    }

    Circle(Circle&) = delete;
    Circle operator= (const Circle&) = delete;

    double Area(){
        return PI * pow(m_dRadius, 2);
    }

    void Translate(double moveX, double moveY){
        m_dX += moveX;
        m_dY += moveY;
    }

    friend std::ostream& operator<< (std::ostream& os, const Circle& circle);

private:
    double m_dX, m_dY, m_dRadius;
    static constexpr double PI = 3.141592653;

};

std::ostream& operator<< (std::ostream& os, const Circle& circle){
    return os << "X: " << circle.m_dX << ", Y: " << circle.m_dY << ", Radius: " << circle.m_dRadius;
}


int main(){
    std::cout << "Enter circle [X Y Radius]: ";
    double x, y, radius;
    std::cin >> x >> y >> radius;

    Circle userCircle(x, y, radius);

    std::cout << "Circle Area: " << userCircle.Area() << std::endl;
    std::cout << "Circle Info: " << userCircle << std::endl;
    
    double mX, mY;
    std::cout << "Enter a displacement vector [X Y]: ";
    std::cin >> mX >> mY;

    userCircle.Translate(mX, mY);
    std::cout << "[Update] Circle Info: " << userCircle << std::endl;

}