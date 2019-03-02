#ifdef __linux__ 
#include <string.h>
#elif _WIN32
#define _USE_MATH_DEFINES
#endif

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>

using namespace std;
//#define Pi 3.141569

/*
double get_PI()
{
    double pi;
    __asm
    {
        fldpi
        fstp pi
    }
    return pi;
}
*/

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


void PrintSetSectors(list<Sector> list_sectors)
{
    printf("Set of Sectors\n");
	
	for(std::list<Sector>::iterator it = list_sectors.begin(); it != list_sectors.end(); ++it)
    {
		printf("Sector: (%i ; %i)    Azimut - %lf     Phi = %lf    Diapazon === [%i - %i]\n", (*it).x, (*it).y, (*it).azim, (*it).phi, (*it).min, (*it).max);
    }
	
	printf("______________________________________________________________________\n\n");
}


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

//Создание случайной точки внутри заданного сектора...
Point CreateRandomPointInSector(Sector sect)
{
    int radius = sect.min + rand()%(sect.max - sect.min);
    double angle = (sect.azim + rand()% (2 * (int)sect.phi) - sect.phi);

    Point rez;
    rez.x = sect.x + radius * cos((90 - angle) * M_PI / 180);
    rez.y = sect.y + radius * sin((90 - angle) * M_PI / 180);


    return rez;
}


//Функция проверяет, принадлежит ли заданная точка списку секторов...
bool CheckPointToSetSectors(Point point, list<Sector> list_sector)
{
    bool flag = true;

    for(std::list<Sector>::iterator it = list_sector.begin(); it != list_sector.end(); ++it)
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

//Функция проверяет, есть ли существование пересечения списка секторов
//Если пересечение есть, то возвращается точка из пересечения
//если пеерсечения не обнаружено, то возвращается точка (0; 0)
Point CheckIntersectionSetOfSectors(list<Sector> list_sector)
{
    Point point;
    int count_point = 1000;

    list<Sector> last_sector;
    std::list<Sector>::iterator it = list_sector.begin();
    Sector init_sector = *it;

    ++it;
    for( ; it != list_sector.end(); ++it)
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

//Функция создает случайную точку вблизи границы области пеерсечения секторов
//Принимает в себя точку, которая должна лежать внтри этого пересечения
//и список секторов, чье пересение рассмтариваем...
//Функция порождает последовательнсоть случайных точек в случайном направлении от point
//пока не выйдет за пределы пересечения, эта точка и будет считаться границей...
Point CreateRandomPointToBorder(Point point, list<Sector> list_sectors)
{
    int step = 5;
    double angle = (rand() % 360 ) * M_PI / 180;

    Point current_point;
    current_point.x = point.x + step * cos(angle);
    current_point.y = point.y + step * sin(angle);

    while (CheckPointToSetSectors(current_point, list_sectors))
    {
        current_point.x = current_point.x + step * cos(angle);
        current_point.y = current_point.y + step * sin(angle);
    }

    return current_point;
}

//Функция находит центр коуржности, описывающей пересечения секторов...
//Кроме того, она считает и центр этой окружности,
//который подается как параметр по ссылке
//
Point CreateCircleFromArea(Point point, list<Sector> list_sectors, double *radius)
{
    int count_point_border = 100;
    //int sum_x = 0;
    //int sum_y = 0;
	double sum_x = 0;
	double sum_y = 0;
	
    list<Point> list_point_border;

    for(int i = 0; i < count_point_border; i++)
    {
        Point current_point = CreateRandomPointToBorder(point, list_sectors);
        sum_x = sum_x + current_point.x;
        sum_y = sum_y + current_point.y;
        list_point_border.push_back(current_point);

    }

    Point center_circle;
    center_circle.x = sum_x / count_point_border;
    center_circle.y = sum_y / count_point_border;

    *radius = 0;
    double sum_radius = 0;

    for(std::list<Point>::iterator it = list_point_border.begin(); it != list_point_border.end(); ++it)
    {
        sum_radius += sqrt(pow((*it).x - center_circle.x, 2.0) + pow((*it).y - center_circle.y, 2.0));
    }

    *radius = sum_radius / count_point_border;
    return center_circle;
}


//Чтение данных из файла...
//
list<list<Sector> > ReadDataFromFile(char* name)
{
    list<list<Sector> > data;
    ifstream fin(name);
    while (!fin.eof())
    {
        char buff[500];
        fin.getline(buff, 500);
        //cout << buff << endl;
        char * pch = strtok (buff," \t");
        list<Sector> temp_list_sectors;
        while (pch != NULL)
        {
            Sector temp_sector;


            temp_sector.x = atoi(pch);
            pch = strtok (NULL," \t");
            temp_sector.y = atoi(pch);
            pch = strtok (NULL," \t");
            temp_sector.azim = atof(pch);
            pch = strtok (NULL," \t");
            temp_sector.phi = atof(pch);
            pch = strtok (NULL," \t");
            temp_sector.min = atoi(pch);
            pch = strtok (NULL," \t");
            temp_sector.max = atoi(pch);
            pch = strtok (NULL," \t");
			
			
            temp_list_sectors.push_back(temp_sector);
        }

        data.push_back(temp_list_sectors);
    }

    return data;
}



int main()
{
    srand( time(NULL));
    int count_set = 0;
    int count_intersection = 0;
    list<list<Sector> > data;
	data = ReadDataFromFile((char*)"data.test");
	
    for(std::list<list<Sector> >::iterator it = data.begin(); it != data.end(); ++it)
    {
		printf("Number set == %i\n", count_set);
		
        PrintSetSectors(*it);
        Point temp_point;
        temp_point = CheckIntersectionSetOfSectors(*it);

        if (temp_point.x == 0 && temp_point.y == 0)
        {
			printf("Intesection of Sectors Not Found!\n");
        }
        else
        {
            double radius = 0;
            Point center_circle = CreateCircleFromArea(temp_point, *it, &radius);
			printf("Center Circle -- (%lf ; %lf ),    Radius = %lf\n", center_circle.x, center_circle.y, radius);
            count_intersection++;

        }
        printf("\n\n");
		
		count_set++;
    }
    printf("\n\nCount of Intersection === %i", count_intersection);
	
	return 0;
}
