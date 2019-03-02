#ifndef READFILE_H
#define READFILE_H

#include <list>
#include "Sector.h"

std::list<std::list<Sector>> ReadDataFromFile(char* name);

#endif // READFILE_H