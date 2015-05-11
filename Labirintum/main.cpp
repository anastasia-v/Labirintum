//клеток в лабиринте (n) >= 11 !!!

#include <iostream>
#include "Leaf.h"
#include "Utils.h"

unsigned const N = 25; // размер лабиринта NxN и размер основного (корневого) листа в графе.

int main() {
    int max_leaf_size = 10; //максимальный размер листа
    vector<Leaf*> leafs = *new vector<Leaf*>; //вектор указателей на вновь созданные листы
    Rect *frame = new Rect(0, 0, N, N); //наш основной размер листа, координаты (0;0), ширина-длина во все поле
    Leaf *root = new Leaf(*frame); //конструируем лист на основе его размеров (frame)
    leafs.push_back(root);
    
    bool did_split = true; //отражает, поделен лист или нет
    while (did_split) {
        did_split = false;
        long unsigned size = leafs.size(); //размер вектора, кол-во эл-тов в нем
        
        for (int i = 0; i < size; i ++) {
            Leaf *l = leafs[i];
            if (l->leftChild == nullptr && l->rightChild == nullptr) { //если нет дочерних листов, то
                if (l->frame.size.width > max_leaf_size || l->frame.size.height > max_leaf_size) {
                    if (l->split()) { //если получилось разделить лист, то
                        leafs.push_back(l->leftChild);
                        leafs.push_back(l->rightChild);
                        did_split = true;
                    }
                }
            }
        }
    }
    
    root->createRooms();
    
    printf("Вектор содержит %lu элементов\n", leafs.size());
    for (int i = 0; i < leafs.size(); i ++) {
        Leaf *l = leafs[i];
        l->description();
    }
    
    printLeafs(leafs);
    printRooms(leafs);
    
    return 0;
}