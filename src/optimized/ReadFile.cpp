#ifdef __GNUC__
#include <string.h>
#endif

#include <fstream>
#include <stdlib.h>

#include <vector>

#include "ReadFile.h"

using namespace std;

//Чтение данных из файла...
//
vector<vector<Sector>> ReadDataFromFile(char* file)
{
	vector<vector<Sector>> data;
	char buff[500];
	char * pch;
	
	ifstream fin(file);
	while (!fin.eof())
	{
		fin.getline(buff, 500);
		//char * pch = strtok (buff," \t");
		pch = strtok (buff," \t");
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