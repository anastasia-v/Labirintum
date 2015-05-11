

#ifndef __Labirintum__Leaf__
#define __Labirintum__Leaf__

#include "Rect.h"
#include <Vector>

class Leaf {
    int minSize = 5; //минимальный размер параметров (ширины и высоты) рамки листа
    public:
    Rect frame; //рамка листа
    Leaf *leftChild;
    Leaf *rightChild;
    Rect *room;
    Point hall[];
    
    ///описание экземпляра класса
    void description();
    ///конструктор листа
    Leaf(Rect r);
    ///разделить на дочерние листы
    bool split();
    ///рекурсивное создание комнат у листов, не имеющих дочерних листов
    void createRooms();
    
};

#endif 
