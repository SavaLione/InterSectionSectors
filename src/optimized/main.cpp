#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "ReadFile.h"
#include "Sector.h"

#define DATA_OUTPUT 0

using namespace std;

int main()
{
    srand(time(NULL));
	
    int count_set = 0;
    int count_intersection = 0;
	Point temp_point;
	double radius = 0;
	
	vector<vector<Sector>> data;
	data = ReadDataFromFile((char*)"data.test");
	
	for(vector<vector<Sector> >::iterator it = data.begin(); it != data.end(); ++it)
    {
#if DATA_OUTPUT
		printf("Number set == %i\n", count_set);
#endif
        PrintSetSectors(*it);
        //Point temp_point;
        temp_point = CheckIntersectionSetOfSectors(*it);

        if (temp_point.x == 0 && temp_point.y == 0)
        {
#if DATA_OUTPUT
			printf("Intesection of Sectors Not Found!\n");
#endif
        }
        else
        {
			radius = 0;
            Point center_circle = CreateCircleFromArea(temp_point, *it, &radius);
#if DATA_OUTPUT
			printf("Center Circle -- (%lf ; %lf ),    Radius = %lf\n", center_circle.x, center_circle.y, radius);
#endif
            count_intersection++;

        }
#if DATA_OUTPUT
        printf("\n\n");
#endif
		
		count_set++;
    }
    printf("\n\nCount of Intersection === %i", count_intersection);
	
	return 0;
}
