

#include "Leaf.h"
#include "Utils.h"

void Leaf::description() {
    printf("Рамка листа:{{%d, %d}, {%d х %d}}; ", frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
    if (leftChild || rightChild){
        printf("имеет дочерние листы");
    }
    else printf("не имеет дочерних листов;");
    if (room) {
        printf(" есть комната");
    }
    printf("\n");
}

Leaf::Leaf(Rect r) {
    frame = r;
    room = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
}

bool Leaf::split() {
    if (leftChild != nullptr && rightChild != nullptr) return false; //уже поделено
    bool splitH = arc4random_uniform(2); //делить горизонтально
    float wdt = frame.size.width;
    float hgt = frame.size.height;
    if (wdt > hgt ) {
        splitH = false;
    } else if (hgt > wdt) {
        splitH = true;
    }
    int max;
    if (splitH) max = hgt - minSize;
    else max = wdt - minSize;
    
    if (max <= minSize) { //если так, то делить нельзя
        return false;
    }
    int split = randomBetween(minSize, max); //определяем место, в котором будем делить
    if (splitH) { //если делим горизонтально, то
        Rect lf; //рамка для левого дочернего листа
        lf.origin = frame.origin;
        lf.size.width = wdt;
        lf.size.height = split;
        leftChild = new Leaf(lf);
        
        Rect rf; //рамка для правого дочернего листа
        rf.origin.x = frame.origin.x;
        rf.origin.y = frame.origin.y + split;
        rf.size.width = wdt;
        rf.size.height = (int)hgt - split;
        rightChild = new Leaf(rf);
    } else {//если делим вертикально, то
        Rect lf;
        lf.origin = frame.origin;
        lf.size.width = split;
        lf.size.height = hgt;
        leftChild = new Leaf(lf);
        
        Rect rf;
        rf.origin.x = frame.origin.x + split;
        rf.origin.y = frame.origin.y;
        rf.size.width = wdt - split;
        rf.size.height = hgt;
        rightChild = new Leaf(rf);
    }
    return true;
}

void Leaf::createRooms() {
    if (leftChild != nullptr || rightChild != nullptr) { //рекурсивный спуск (у листа есть потомки)
        if (leftChild != nullptr) {
            leftChild->createRooms();
        }
        if (rightChild != nullptr) {
            rightChild->createRooms();
        }
        if (leftChild != nullptr && rightChild != nullptr) {
            createHall(*leftChild->getRoom(), *rightChild->getRoom());
        }
    } else { //если нет потомков, то создаем комнату в этом конкретном листе
        int wdt = frame.size.width;
        int hgt = frame.size.height;
        int x = frame.origin.x;
        int y = frame.origin.y;
        Point roomSize;
        Point roomPos;
        roomSize.x = randomBetween(3, wdt-2);
        roomSize.y = randomBetween(3, hgt-2);
        roomPos.x = randomBetween(1, wdt-roomSize.x-1);
        roomPos.y = randomBetween(1, hgt-roomSize.y-1);
        room = new Rect(x+roomPos.x, y+roomPos.y, roomSize.x, roomSize.y);
    }
}

Rect *Leaf::getRoom() {
    if (room != nullptr) {
        return room;
    } else {
        Rect *lRoom = nullptr;
        Rect *rRoom = nullptr;
        if (leftChild != nullptr) {
            lRoom = leftChild->getRoom();
        }
        if (rightChild != nullptr) {
            rRoom = rightChild->getRoom();
        }
        if (lRoom == nullptr && rRoom == nullptr) {
            return nullptr;
        } else if (rRoom == nullptr) {
            return lRoom;
        } else if (lRoom == nullptr) {
            return rRoom;
        } else if (arc4random_uniform(2)) {
            return lRoom;
        } else return rRoom;
    }
}

void createHall(Rect l, Rect r) {
    vector<Rect*> halls = *new vector <Rect*>;
    Point point1;
    point1.x = randomBetween(l.left()+1, l.right()-2);
    point1.y = randomBetween(l.top()+1, l.bottom()-2);
    Point point2;
    point2.x = randomBetween(l.left()+1, l.right()-2);
    point2.y = randomBetween(l.top()+1, l.bottom()-2);
    int w = point2.x-point1.x;
    int h = point2.y-point1.y;
    if (w < 0) {
        if (h < 0) {
            if (arc4random_uniform(2)) {
                halls.push_back(new Rect(point2.x, point1.y, abs(w), 1));
                halls.push_back(new Rect(point2.x, point2.y, 1, abs(h)));
            } else {
                halls.push_back(new Rect(point2.x, point2.y, abs(w), 1));
                halls.push_back(new Rect(point1.x, point2.y, 1, abs(h)));
            }
        } else if (h > 0) {
            if (arc4random_uniform(2)) {
                halls.push_back(new Rect(point2.x, point1.y, abs(w), 1));
                halls.push_back(new Rect(point2.x, point1.y, 1, abs(h)));
            } else {
                halls.push_back(new Rect(point2.x, point2.y, abs(w), 1));
                halls.push_back(new Rect(point1.x, point1.y, 1, abs(h)));
            }
        } else { //if (h == 0)
            halls.push_back(new Rect(point2.x, point2.y, abs(w), 1));
        }
    } else if (w > 0) {
        if (h < 0) {
            if (arc4random_uniform(2)) {
                halls.push_back(new Rect(point1.x, point2.y, abs(w), 1));
                halls.push_back(new Rect(point1.x, point2.y, 1, abs(h)));
            } else {
                halls.push_back(new Rect(point1.x, point1.y, abs(w), 1));
                halls.push_back(new Rect(point2.x, point2.y, 1, abs(h)));
            }
        } else if (h > 0) {
            if (arc4random_uniform(2)) {
                halls.push_back(new Rect(point1.x, point1.y, abs(w), 1));
                halls.push_back(new Rect(point2.x, point1.y, 1, abs(h)));
            } else {
                halls.push_back(new Rect(point1.x, point2.y, abs(w), 1));
                halls.push_back(new Rect(point1.x, point1.y, 1, abs(h)));
            }
        } else { //if (h == 0)
            halls.push_back(new Rect(point1.x, point1.y, abs(w), 1));
        }
    } else { //if (w == 0)
        if (h < 0) {
            halls.push_back(new Rect(point2.x, point2.y, 1, abs(h)));
        } else if (h > 0) {
            halls.push_back(new Rect(point1.x, point1.y, 1, abs(h)));
        }
    }
}
