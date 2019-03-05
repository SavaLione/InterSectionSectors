#include <stdio.h>
#include <math.h>

#include "Sector.h"
#include "rand_sse.h"

using namespace std;

//srand_sse(time(NULL));

void PrintSetSectors(vector<Sector> vector_sectors)
{
    printf("Set of Sectors\n");
	for(vector<Sector>::iterator it = vector_sectors.begin(); it != vector_sectors.end(); ++it)
    {
		printf("Sector: (%i ; %i)    Azimut - %lf     Phi = %lf    Diapazon === [%i - %i]\n", (*it).x, (*it).y, (*it).azim, (*it).phi, (*it).min, (*it).max);
    }
	printf("______________________________________________________________________\n\n");
}
/*
void PrintSetSectors(vector<Sector> vector_sectors)
{
#if DATA_OUTPUT
    #pragma omp parallel
    {
        auto it = vector_sectors.begin();
        #pragma openmp for
        for(; it != vector_sectors.end(); ++it)
        {
            printf("Sector: (%i ; %i)    Azimut - %lf     Phi = %lf    Diapazon === [%i - %i]\n", (*it).x, (*it).y, (*it).azim, (*it).phi, (*it).min, (*it).max);
        }
    }
    printf("______________________________________________________________________\n\n");
#endif
}
*/

//Проверка, принадлежит ли точка сектору...
bool CheckPointToSector(Point point, Sector sector)
{
    Point v1;
    v1.x = point.x - sector.x;
    v1.y = point.y - sector.y;

    double temp_x, temp_y;
    temp_x = cos((90 - sector.azim) * M_PI / 180);
    temp_y = sin((90 - sector.azim) * M_PI / 180);

    double r = sqrt((pow(v1.x, 2.0) + pow(v1.y, 2.0)));
    double angle = acos((v1.x * temp_x + v1.y * temp_y) / r) * 180 / M_PI;

    if ((r >= sector.min && r <= sector.max) && (angle >= -sector.phi && angle <= sector.phi))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Создание случайной точки внутри заданного сектора... */
Point CreateRandomPointInSector(Sector sect)
{
	unsigned int u_i_random[4];
	rand_sse(u_i_random);

	int radius = sect.min + u_i_random[0]%(sect.max - sect.min);
    double angle = (sect.azim + u_i_random[1]% (2 * (int)sect.phi) - sect.phi);

    Point rez;
    rez.x = sect.x + radius * cos((90 - angle) * M_PI / 180);
    rez.y = sect.y + radius * sin((90 - angle) * M_PI / 180);


    return rez;
}

/* Функция проверяет, принадлежит ли заданная точка списку секторов... */
bool CheckPointToSetSectors(Point point, vector<Sector> vector_sector)
{
    bool flag = true;

    for(vector<Sector>::iterator it = vector_sector.begin(); it != vector_sector.end(); ++it)
    {
        if (!CheckPointToSector(point, *it))
            flag = false;
    }

    return flag;
}

void PrintSector(Sector sector)
{
	printf("Sector: (%i ; %i)\nAzimut - %lf     Phi = %lf\nDiapazon === [%i - %i]\n", sector.x, sector.y, sector.azim, sector.phi, sector.min, sector.max);
}

/* 
	Функция проверяет, есть ли существование пересечения списка секторов
	Если пересечение есть, то возвращается точка из пересечения
	если пеерсечения не обнаружено, то возвращается точка (0; 0)
*/
Point CheckIntersectionSetOfSectors(vector<Sector> vector_sector)
{
    Point point;
    int count_point = 1000;

    vector<Sector> last_sector;
    vector<Sector>::iterator it = vector_sector.begin();
    Sector init_sector = *it;

    ++it;
    for( ; it != vector_sector.end(); ++it)
    {
        last_sector.push_back(*it);
    }
	
	#pragma openmp for
	for (int i = 0; i < count_point; i++)
	{
		point = CreateRandomPointInSector(init_sector);
		if (CheckPointToSetSectors(point, last_sector))
            return point;
	}
	
    point.x = point.y = 0;
    return point;
}
/*
Point CheckIntersectionSetOfSectors(vector<Sector> vector_sector)
{
    Point point;
    int count_point = 1000;

    vector<Sector> last_sector;
    vector<Sector>::iterator it = vector_sector.begin();
    Sector init_sector = *it;

    ++it;
    for( ; it != vector_sector.end(); ++it)
    {
        last_sector.push_back(*it);
    }

    int i = 0;
    while (i < count_point)
    {
        point = CreateRandomPointInSector(init_sector);

        if (CheckPointToSetSectors(point, last_sector))
            return point;
        i++;
    }
    point.x = point.y = 0;
    return point;
}
*/

/* 
	Функция создает случайную точку вблизи границы области пеерсечения секторов
	Принимает в себя точку, которая должна лежать внтри этого пересечения
	и список секторов, чье пересение рассмтариваем...
	Функция порождает последовательнсоть случайных точек в случайном направлении от point
	пока не выйдет за пределы пересечения, эта точка и будет считаться границей...
*/
Point CreateRandomPointToBorder(Point point, vector<Sector> vector_sectors)
{
	unsigned int u_i_random[4];
	rand_sse(u_i_random);
    int step = 5;
    //double angle = (rand() % 360 ) * M_PI / 180;
	double angle = (u_i_random[0] % 360 ) * M_PI / 180;
	
    Point current_point;
    current_point.x = point.x + step * cos(angle);
    current_point.y = point.y + step * sin(angle);

    while (CheckPointToSetSectors(current_point, vector_sectors))
    {
        current_point.x = current_point.x + step * cos(angle);
        current_point.y = current_point.y + step * sin(angle);
    }

    return current_point;
}

/* 
	Функция находит центр коуржности, описывающей пересечения секторов...
	Кроме того, она считает и центр этой окружности,
	который подается как параметр по ссылке
*/
Point CreateCircleFromArea(Point point, vector<Sector> vector_sectors, double *radius)
{
    int count_point_border = 100;
	double sum_x = 0;
	double sum_y = 0;

    vector<Point> vector_point_border;
	Point current_point;

    for(int i = 0; i < count_point_border; i++)
    {
        //Point current_point = CreateRandomPointToBorder(point, vector_sectors);
		current_point = CreateRandomPointToBorder(point, vector_sectors);
        sum_x = sum_x + current_point.x;
        sum_y = sum_y + current_point.y;
        vector_point_border.push_back(current_point);

    }

    Point center_circle;
    center_circle.x = sum_x / count_point_border;
    center_circle.y = sum_y / count_point_border;

    *radius = 0;
    double sum_radius = 0;

	#pragma omp parallel
	{
		auto it = vector_point_border.begin();
		#pragma openmp for
		for(; it != vector_point_border.end(); ++it)
		{
			sum_radius += sqrt(pow((*it).x - center_circle.x, 2.0) + pow((*it).y - center_circle.y, 2.0));
		}
	}
	
    *radius = sum_radius / count_point_border;
    return center_circle;
}
