#include <iostream>
#include <cmath>

const double PI = acos(-1.0);

class Point {
public:  
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual ~Point() {}
};

class BasicPoint : public Point {
private:
    double x, y;
public:
    BasicPoint(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double getX() const override { return x; }
    double getY() const override { return y; }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void setPosition(double newX, double newY) { x = newX; y = newY; }
};

class Shape {
protected:
    static void rotatePoint(double& x, double& y, double centerX, double centerY, double radians) {
        double dx = x - centerX;
        double dy = y - centerY;
        x = centerX + dx * cos(radians) - dy * sin(radians);
        y = centerY + dx * sin(radians) + dy * cos(radians);
    }
    
public:
    virtual void draw() const = 0;
    virtual void erase() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    virtual ~Shape() {}
};

class Line : public Shape {
private:
    BasicPoint start, end;
public:
    Line(double x1, double y1, double x2, double y2)
        : start(x1, y1), end(x2, y2) {}

    void draw() const override {
        std::cout << "Рисуется линия от точки (" << start.getX() << ", " << start.getY()
                  << ") до точки (" << end.getX() << ", " << end.getY() << ")" << std::endl;
    }

    void erase() const override {
        std::cout << "Стирается линия" << std::endl;
    }

    void move(double dx, double dy) override {
        start.move(dx, dy);
        end.move(dx, dy);
    }

    void rotate(double angle) override {
        double radians = angle * PI / 180.0;
        double centerX = (start.getX() + end.getX()) / 2.0;
        double centerY = (start.getY() + end.getY()) / 2.0;
        
        double x1 = start.getX();
        double y1 = start.getY();
        double x2 = end.getX();
        double y2 = end.getY();
        
        rotatePoint(x1, y1, centerX, centerY, radians);
        rotatePoint(x2, y2, centerX, centerY, radians);
        
        start.setPosition(x1, y1);
        end.setPosition(x2, y2);
    }
};

class Rectangle : public Shape {
protected:
    BasicPoint topLeft;
    double width, height;
public:
    Rectangle(double x, double y, double w, double h)
        : topLeft(x, y), width(w), height(h) {}

    void draw() const override {
        std::cout << "Рисуется прямоугольник с левой верхней точкой в (" 
                  << topLeft.getX() << ", " << topLeft.getY()
                  << "), ширина: " << width << ", высота: " << height << std::endl;
    }

    void erase() const override {
        std::cout << "Стирается прямоугольник" << std::endl;
    }

    void move(double dx, double dy) override {
        topLeft.move(dx, dy);
    }

    void rotate(double angle) override {
        double radians = angle * PI / 180.0;
        double centerX = topLeft.getX() + width / 2.0;
        double centerY = topLeft.getY() + height / 2.0;
        
        double x1 = topLeft.getX();
        double y1 = topLeft.getY();
        double x2 = x1 + width;
        double y2 = y1;
        double x3 = x2;
        double y3 = y1 + height;
        double x4 = x1;
        double y4 = y3;

        rotatePoint(x1, y1, centerX, centerY, radians);
        rotatePoint(x2, y2, centerX, centerY, radians);
        rotatePoint(x3, y3, centerX, centerY, radians);
        rotatePoint(x4, y4, centerX, centerY, radians);

        std::cout << "Координаты после поворота:" << std::endl;
        std::cout << "Верхняя левая: (" << x1 << ", " << y1 << ")" << std::endl;
        std::cout << "Верхняя правая: (" << x2 << ", " << y2 << ")" << std::endl;
        std::cout << "Нижняя правая: (" << x3 << ", " << y3 << ")" << std::endl;
        std::cout << "Нижняя левая: (" << x4 << ", " << y4 << ")" << std::endl;
topLeft.setPosition(x1, y1);
    }
};
class Square : public Rectangle {
    public:
        Square(double x, double y, double side)
            : Rectangle(x, y, side, side) {}
    
        void draw() const override {
            std::cout << "Рисуется квадрат с левой верхней точкой в (" 
                      << topLeft.getX() << ", " << topLeft.getY()
                      << "), сторона: " << width << std::endl;
        }
    
        void erase() const override {
            std::cout << "Стирается квадрат" << std::endl;
        }
    };
    
    class Parallelogram : public Shape {
    protected:
        BasicPoint topLeft;
        double base, height, offset;
    public:
        Parallelogram(double x, double y, double b, double h, double o)
            : topLeft(x, y), base(b), height(h), offset(o) {}
    
        void draw() const override {
            std::cout << "Рисуется параллелограмм с левой верхней точкой в (" 
                      << topLeft.getX() << ", " << topLeft.getY()
                      << "), основание: " << base << ", высота: " << height
                      << ", смещение: " << offset << std::endl;
        }
    
        void erase() const override {
            std::cout << "Стирается параллелограмм" << std::endl;
        }
    
        void move(double dx, double dy) override {
            topLeft.move(dx, dy);
        }
    
        void rotate(double angle) override {
            double radians = angle * PI / 180.0;
            double centerX = topLeft.getX() + base / 2.0;
            double centerY = topLeft.getY() + height / 2.0;
            
            double x1 = topLeft.getX();
            double y1 = topLeft.getY();
            double x2 = x1 + base;
            double y2 = y1;
            double x3 = x1 + offset;
            double y3 = y1 + height;
            double x4 = x2 + offset;
            double y4 = y3;
    
            rotatePoint(x1, y1, centerX, centerY, radians);
            rotatePoint(x2, y2, centerX, centerY, radians);
            rotatePoint(x3, y3, centerX, centerY, radians);
            rotatePoint(x4, y4, centerX, centerY, radians);
    
            std::cout << "Координаты после поворота:" << std::endl;
            std::cout << "Верхняя левая: (" << x1 << ", " << y1 << ")" << std::endl;
            std::cout << "Верхняя правая: (" << x2 << ", " << y2 << ")" << std::endl;
            std::cout << "Нижняя левая: (" << x3 << ", " << y3 << ")" << std::endl;
            std::cout << "Нижняя правая: (" << x4 << ", " << y4 << ")" << std::endl;
    
            topLeft.setPosition(x1, y1);
        }
    };
    
    class Rhombus : public Parallelogram {
    public:
        Rhombus(double x, double y, double d1, double d2)
            : Parallelogram(x, y, d1, d2, 0) {}
    
        void draw() const override {
            std::cout << "Рисуется ромб с левой верхней точкой в (" 
                      << topLeft.getX() << ", " << topLeft.getY()
                      << "), диагонали: " << base << " и " << height << std::endl;
        }
    
        void erase() const override {
            std::cout << "Стирается ромб" << std::endl;
        }
    };
    
    void demo(Shape* shape) {
        shape->draw();
        shape->move(5, 5);
        shape->rotate(45);
        shape->draw();
        shape->erase();
    }
    
    int main() {
        Square sq(0, 0, 10);
        Line ln(0, 0, 5, 5);
        Rectangle rect(1, 1, 8, 4);
        Parallelogram pg(2, 2, 6, 4, 3);
        Rhombus rh(3, 3, 5, 7);
    
        std::cout << "Демонстрация: Квадрат" << std::endl;
        demo(&sq);
    
        std::cout << "\nДемонстрация: Линия" << std::endl;
        demo(&ln);
    
        std::cout << "\nДемонстрация: Прямоугольник" << std::endl;
        demo(&rect);
    
        std::cout << "\nДемонстрация: Параллелограмм" << std::endl;
        demo(&pg);
    
        std::cout << "\nДемонстрация: Ромб" << std::endl;
        demo(&rh);
    
        return 0;
    }
