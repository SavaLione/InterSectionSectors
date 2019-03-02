#ifndef SECTOR_H
#define SECTOR_H

#include <list>

//структура данных, которая хранит в себе всю информацию о секторе
//
struct Sector
{
    //координаты вершины сектора
    int x;
    int y;
    //Азимут, направление биссектриссы сектора
    double azim;
    //Угол обзора сектора
    double phi;
    //Минимально ерасстояние от центра
    int min;
    //максимально возможно расстояние от центра
    int max;
};

//Структура данных - точка на плоскости
struct Point
{
    //int x;
    //int y;
	double x;
	double y;
};

void PrintSetSectors(std::list<Sector> list_sectors);
bool CheckPointToSector(Point point, Sector sector);
Point CreateRandomPointInSector(Sector sect);
bool CheckPointToSetSectors(Point point, std::list<Sector> list_sector);
void PrintSector(Sector sector);
Point CheckIntersectionSetOfSectors(std::list<Sector> list_sector);
Point CreateRandomPointToBorder(Point point, std::list<Sector> list_sectors);
Point CreateCircleFromArea(Point point, std::list<Sector> list_sectors, double *radius);

#endif // SECTOR_H