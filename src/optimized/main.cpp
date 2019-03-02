#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "ReadFile.h"
#include "Sector.h"

using namespace std;
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

int main()
{
    srand( time(NULL));
    int count_set = 0;
    int count_intersection = 0;
    //list<list<Sector>> data;
	//data = ReadDataFromFile((char*)"data.test");
	vector<vector<Sector>> data;
	data = ReadData((char*)"data.test");
	
    //for(std::list<list<Sector> >::iterator it = data.begin(); it != data.end(); ++it)
	for(vector<vector<Sector> >::iterator it = data.begin(); it != data.end(); ++it)
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
