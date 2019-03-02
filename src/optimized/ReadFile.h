#ifndef READFILE_H
#define READFILE_H

#include <list>
#include <vector>
#include "Sector.h"

std::list<std::list<Sector>> ReadDataFromFile(char* name);
std::vector<std::vector<Sector>> ReadData(char* file);

#endif // READFILE_H