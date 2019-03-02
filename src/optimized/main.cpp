#define DATA_OUTPUT 0
#define TIME_TEST 1

#if TIME_TEST
#include <chrono>
#endif

#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "ReadFile.h"
#include "Sector.h"

using namespace std;

int main()
{
#if TIME_TEST
	std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
#endif
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
	
#if TIME_TEST
	end = std::chrono::system_clock::now();
 
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	printf("\n\n\n\nTIME\t%i", elapsed_seconds);
#endif
	
	return 0;
}
