

#ifndef __Labirintum__Utils__
#define __Labirintum__Utils__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Leaf.h"

using namespace std;
///возвращает рандомное число в промежутке от х до у-1
int randomBetween(int x, int y);
///функции распечатки (визуализации) для контроля происходящего (можно особо не вникать ;) )
void printLeafs(std::vector<Leaf*> leafs);
void printRooms(std::vector<Leaf*> leafs);

#endif 
