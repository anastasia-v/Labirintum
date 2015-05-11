

#include "Utils.h"

int randomBetween(int x, int y) {
    if (x > y) return 0;
    return arc4random_uniform(y - x) + x;
}

void printLeafs(vector<Leaf*> leafs)
{
    if (leafs.size() > 1) {
        Leaf *root = leafs[0];
        int columns = root->frame.size.width; //кол-во колонок = ширина
        int rows = root->frame.size.height; //кол-во рядов = высота
        
        char array[columns][rows];
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                array[i][j] = 0;
            }
        }
        
        for (int k = 1; k < leafs.size(); k++) { //перебор листов кроме корня
            Leaf *l = leafs[k];
            int x = l->frame.origin.x;
            int y = l->frame.origin.y;
            int w = l->frame.size.width;
            int h = l->frame.size.height;
            
            for (int i = x; i < x+w; i++) {
                for (int j = y; j < y+h; j++) {
                    array[i][j] = k+60;
                }
            }
        }
        printf("\n");
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                printf("%c ", array[i][j]);
            }
            printf("\n");
        }
    }
}

void printRooms(vector<Leaf*> leafs) {
    if (leafs.size() > 1) {
        Leaf *root = leafs[0];
        int columns = root->frame.size.width;
        int rows = root->frame.size.height;
        
        bool array[columns][rows];
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                array[i][j] = true; //стенка
            }
        }
        
        for (int k = 1; k < leafs.size(); k++) {
            Leaf *l = leafs[k];
            if (l->room != nullptr) {
                Rect *room = l->room;
                int x = room->origin.x;
                int y = room->origin.y;
                int w = room->size.width;
                int h = room->size.height;
                
                for (int i = x; i < x+w; i++) {
                    for (int j = y; j < y+h; j++) {
                        array[i][j] = false; //не стенка
                    }
                }
            }
        }
        
        printf("\n");
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                bool wall = array[i][j];
                if (wall) printf("⬛️");
                else printf("⬜️");
            }
            printf("\n");
        }
    }
}
