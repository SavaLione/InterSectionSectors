#ifndef SECTOR_H
#define SECTOR_H

#include <vector>

/*
	Структура данных, которая хранит в себе всю информацию о секторе
*/
struct Sector
{
    /* Координаты вершины сектора */
    int x;
    int y;
	
    /* Азимут, направление биссектриссы сектора */
    double azim;
	
    /* Угол обзора сектора */
    double phi;
	
    /* Минимальное расстояние от центра */
    int min;
	
    /* Максимально возможно расстояние от центра */
    int max;
};

/* Структура данных - точка на плоскости */
struct Point
{
	double x;
	double y;
};

/* Вывод секторов в консоль */
/* void PrintSetSectors(std::vector<Sector> vector_sectors); */
void PrintSetSectors(std::vector<Sector> *vector_sectors);


/* Проверка, принадлежит ли точка сектору... */
/* bool CheckPointToSector(Point point, Sector sector); */
bool CheckPointToSector(Point *point, Sector *sector);

/* Создание случайной точки внутри заданного сектора... */
/* Point CreateRandomPointInSector(Sector sect); */
Point CreateRandomPointInSector(Sector *sect);


/* Функция проверяет, принадлежит ли заданная точка списку секторов... */
/* bool CheckPointToSetSectors(Point point, std::vector<Sector> vector_sector); */
bool CheckPointToSetSectors(Point *point, std::vector<Sector> *vector_sector);

/*
void PrintSector(Sector sector);
*/

/* 
	Функция проверяет, есть ли существование пересечения списка секторов
	Если пересечение есть, то возвращается точка из пересечения
	если пеерсечения не обнаружено, то возвращается точка (0; 0)
*/
/* Point CheckIntersectionSetOfSectors(std::vector<Sector> vector_sector); */
Point CheckIntersectionSetOfSectors(std::vector<Sector> *vector_sector);

/* 
	Функция создает случайную точку вблизи границы области пеерсечения секторов
	Принимает в себя точку, которая должна лежать внтри этого пересечения
	и список секторов, чье пересение рассмтариваем...
	Функция порождает последовательнсоть случайных точек в случайном направлении от point
	пока не выйдет за пределы пересечения, эта точка и будет считаться границей...
*/
/* Point CreateRandomPointToBorder(Point point, std::vector<Sector> vector_sectors); */
Point CreateRandomPointToBorder(Point *point, std::vector<Sector> *vector_sectors);

/* 
	Функция находит центр коуржности, описывающей пересечения секторов...
	Кроме того, она считает и центр этой окружности,
	который подается как параметр по ссылке
*/
/* Point CreateCircleFromArea(Point point, std::vector<Sector> vector_sectors, double *radius); */
Point CreateCircleFromArea(Point *point, std::vector<Sector> *vector_sectors, double *radius);

#endif // SECTOR_H
