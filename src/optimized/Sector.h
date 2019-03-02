#ifndef SECTOR_H
#define SECTOR_H

#include <vector>

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

bool CheckPointToSector(Point point, Sector sector);
Point CreateRandomPointInSector(Sector sect);
void PrintSector(Sector sector);
void PrintSetSectors(std::vector<Sector> vector_sectors);
Point CheckIntersectionSetOfSectors(std::vector<Sector> vector_sector);
Point CreateCircleFromArea(Point point, std::vector<Sector> vector_sectors, double *radius);
bool CheckPointToSetSectors(Point point, std::vector<Sector> vector_sector);
Point CreateRandomPointToBorder(Point point, std::vector<Sector> vector_sectors);

#endif // SECTOR_H