#ifndef READFILE_H
#define READFILE_H

#include <vector>
#include "Sector.h"

std::vector<std::vector<Sector>> ReadDataFromFile(char* file);

#endif // READFILE_H