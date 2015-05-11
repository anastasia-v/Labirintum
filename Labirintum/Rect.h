

#ifndef Labirintum_Rect_h
#define Labirintum_Rect_h

struct Point {
    int x, y;
};

struct Size {
    int width, height;
};

struct Rect {
    Point origin; //координата верхнего левого угла прямоугольника
    Size size; //размеры прямоугольника
    Rect(int x, int y, int width, int height) {
        origin.x = x;
        origin.y = y;
        size.width = width;
        size.height = height;
    }
    Rect(){};
};

#endif
