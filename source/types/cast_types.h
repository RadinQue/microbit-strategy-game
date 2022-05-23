#ifndef CAST_TYPES_H
#define CAST_TYPES_H

#include <vector>
#include "../object.h"

struct FHitResult
{
    class Object* object;
    
};

struct FCastQuery
{
    FCastQuery()
    {}

    std::vector<Object*> filteredObjects;
};


#endif