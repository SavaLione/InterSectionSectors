#ifdef __linux__ 
#include <string.h>
#elif __MINGW32__
#include <string.h>
#endif

#include <fstream>
#include <stdlib.h>
//#include <cstdlib>

#include <vector>

#include "ReadFile.h"

using namespace std;

//Чтение данных из файла...
//
list<list<Sector>> ReadDataFromFile(char* name)
{
    list<list<Sector>> data;
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

vector<vector<Sector>> ReadData(char* file)
{
	vector<vector<Sector>> data;
	char buff[500];
	
	ifstream fin(file);
	while (!fin.eof())
	{
		fin.getline(buff, 500);
		char * pch = strtok (buff," \t");
		vector<Sector> temp_list_sectors;
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