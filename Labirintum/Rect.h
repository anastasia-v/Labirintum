

#ifndef Labirintum_Rect_h
#define Labirintum_Rect_h

#include <cstdio>

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
    int bottom() {return origin.y+size.height;}
    int top() {return origin.y;}
    int left() {return origin.x;}
    int right() {return origin.x+size.width;}
    
    void description(){printf("Рамка листа:{{%d, %d}, {%d х %d}}; ", origin.x, origin.y, size.width, size.height);}
};

#endif
