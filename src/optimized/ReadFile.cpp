#ifdef __linux__ 
#include <string.h>
#endif

#include <fstream>
#include <stdlib.h>
//#include <cstdlib>

#include "ReadFile.h"

using namespace std;

//Чтение данных из файла...
//
std::list<std::list<Sector>> ReadDataFromFile(char* name)
{
    std::list<std::list<Sector>> data;
    ifstream fin(name);
    while (!fin.eof())
    {
        char buff[500];
        fin.getline(buff, 500);
        //cout << buff << endl;
        char * pch = strtok (buff," \t");
        std::list<Sector> temp_list_sectors;
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