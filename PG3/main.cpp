#include <stdio.h>
#include <cstdlib>
#include <Windows.h>

const double PI = 3.14159265358979323846;

class IShape {
public:
    virtual void Size() = 0;
    virtual void Draw() = 0;
    virtual ~IShape() {}
};

class Circle : public IShape {
private:
    double radius;
public:
    Circle(double r) {
        radius = r;
    }
    void Size() override {
        double area = PI * radius * radius;
        printf("円の面積: %.2f\n", area);
    }
    void Draw() override {
        printf("図形: 円、半径: %.2f\n", radius);
    }
};

class MyRectangle : public IShape {
private:
    double width;
    double height;
public:
    MyRectangle(double w, double h) {
        width = w;
        height = h;
    }
    void Size() override {
        double area = width * height;
        printf("矩形の面積: %.2f\n", area);
    }
    void Draw() override {
        printf("図形: 矩形、幅: %.2f、高さ: %.2f\n", width, height);
    }
};

int main()
{
    system("chcp 65001 > nul");
    IShape* shape1 = new Circle(5.0);
    IShape* shape2 = new MyRectangle(4.0f, 6.0f);

    shape1->Draw();
    shape1->Size();
    printf("\n");
    shape2->Draw();
    shape2->Size();

    delete shape1;
    delete shape2;

    return 0;
}