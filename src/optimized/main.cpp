#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "ReadFile.h"
#include "Sector.h"

using namespace std;

int main()
{
    srand( time(NULL));
    int count_set = 0;
    int count_intersection = 0;
	vector<vector<Sector>> data;
	data = ReadDataFromFile((char*)"data.test");
	
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
