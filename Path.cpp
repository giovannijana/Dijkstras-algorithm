#include "Path.hpp"

long Path::getDistance()
{
    return distance;
}

void Path::setDistance(long dist)
{
    distance = dist;
}

std::string Path::getDestination()
{
    return path.back();
}

void Path::visit()
{
    visited = true;
}

bool Path::hasBeenVisited()
{
    return visited;
}

std::vector<std::string> Path::getPath()
{
    return path;
}

void Path::setPath(std::vector<std::string> newPath)
{
    path = newPath;
}

void Path::addToEnd(std::string s)
{
    path.insert(path.end(), s);
}

void Path::addToPath(std::string s)
{
    path.insert(path.begin(), s);
}

std::string Path::getStart()
{
    return path.at(0);
}