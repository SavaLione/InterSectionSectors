#define DATA_OUTPUT 0
#define PARALLEL 1


#ifdef __GNUC__
#define TIME_TEST 1
#endif

#if TIME_TEST
#include <chrono>
#endif

#include <stdio.h>
#include <time.h>
#include <iostream>

#include "cxxopts.hpp"
#include "ReadFile.h"
#include "Sector.h"
#include "rand_sse.h"

using namespace std;

void InterSectionSectors();

int main(int argc, char *argv[])
{
	bool hide_log = false, time_test = false;
	int i_accuracy = 1000;
	
	cxxopts::Options options("InterSectionSectors", " - Inter Section Sectors");
	options.add_options()
		("h,help", 		"Help"											)
		("l,log", 		"Log", 			cxxopts::value<bool>(hide_log)	)
		("a,accuracy", 	"Accuracy", 	cxxopts::value<int>(), "N"		)
		("t,time", 		"Time test", 	cxxopts::value<bool>(time_test)	)
		("p,parallel", 	"Parallel info"									);
	
	auto result = options.parse(argc, argv);
	
	if(result.count("help"))
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }
	
	if(hide_log)
	{
		std::cout << "HIDE LOG" << std::endl;
	}
	
	if(time_test)
	{
		std::cout << "TIME TEST" << std::endl;
	}
	
	if(result.count("parallel"))
	{
	#ifdef _OPENMP
		#pragma omp parallel
		{
			printf("PARALLEL\n");
		}
		printf("Compiled by an OpenMP-compliant implementation.\n");
	#else
		printf("Compiled without OpenMP\n");
	#endif
	exit(0);
	}
	
	if(result.count("accuracy"))
	{
		i_accuracy = result["accuracy"].as<int>();
		std::cout << "Accuracy = " << i_accuracy << std::endl;
	}
	
	InterSectionSectors();
	
	return 0;
}

void InterSectionSectors()
{
#if TIME_TEST
	std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
#endif
	srand_sse(time(NULL)); // seed

    int count_set = 0;
    int count_intersection = 0;
	Point temp_point;
#if DATA_OUTPUT
	double radius = 0;
#endif

	vector<vector<Sector>> data;
	data = ReadDataFromFile((char*)"data.test");

	for(vector<vector<Sector> >::iterator it = data.begin(); it != data.end(); ++it)
    {
#if DATA_OUTPUT
		printf("Number set == %i\n", count_set);
        PrintSetSectors(*it);
#endif
        temp_point = CheckIntersectionSetOfSectors(*it);

        if (temp_point.x == 0 && temp_point.y == 0)
        {
#if DATA_OUTPUT
			printf("Intesection of Sectors Not Found!\n");
#endif
        }
        else
        {
#if DATA_OUTPUT
			radius = 0;
            Point center_circle = CreateCircleFromArea(temp_point, *it, &radius);
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
	printf("\n\n\n\nTIME\t%i\n\n", elapsed_seconds);
#endif
}

/* DO NOT DELETE */
/*
int main()
{
#if PARALLEL
	#pragma omp parallel
	{
		printf("PARALLEL\n");
	}
#endif
#ifdef _OPENMP
	printf("Compiled by an OpenMP-compliant implementation.\n");
#endif

#if TIME_TEST
	std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
#endif
	srand_sse(time(NULL)); // seed

    int count_set = 0;
    int count_intersection = 0;
	Point temp_point;
#if DATA_OUTPUT
	double radius = 0;
#endif

	vector<vector<Sector>> data;
	data = ReadDataFromFile((char*)"data.test");

	for(vector<vector<Sector> >::iterator it = data.begin(); it != data.end(); ++it)
    {
#if DATA_OUTPUT
		printf("Number set == %i\n", count_set);
        PrintSetSectors(*it);
#endif
        temp_point = CheckIntersectionSetOfSectors(*it);

        if (temp_point.x == 0 && temp_point.y == 0)
        {
#if DATA_OUTPUT
			printf("Intesection of Sectors Not Found!\n");
#endif
        }
        else
        {
#if DATA_OUTPUT
			radius = 0;
            Point center_circle = CreateCircleFromArea(temp_point, *it, &radius);
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
	printf("\n\n\n\nTIME\t%i\n\n", elapsed_seconds);
#endif
	return 0;
}
*/