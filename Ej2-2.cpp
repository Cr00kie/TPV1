#include <iostream>
#include <cmath>

class Point2{
public:
    Point2(double x, double y){
        m_dX = x;
        m_dY = y;
    }

    double X () const {return m_dX;}
    double Y () const {return m_dY;}

    void Translate(double moveX, double moveY){
        m_dX += moveX;
        m_dY += moveY;
    }
private:
    double m_dX, m_dY;
};

class Circle{
public:
    Circle(double x, double y, double radius)
        :m_Center(x, y)
    {
        m_dRadius = radius; 
    }

    Circle(Circle&) = delete;
    Circle operator= (const Circle&) = delete;

    double Area(){
        return PI * pow(m_dRadius, 2);
    }

    void Translate(double moveX, double moveY){
        m_Center.Translate(moveX, moveY);
    }

    friend std::ostream& operator<< (std::ostream& os, const Circle& circle);

private:
    Point2 m_Center;
    double m_dRadius;
    static constexpr double PI = 3.141592653;

};

std::ostream& operator<< (std::ostream& os, const Circle& circle){
    return os << "X: " << circle.m_Center.X() << ", Y: " << circle.m_Center.Y() << ", Radius: " << circle.m_dRadius;
}
