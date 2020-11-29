#ifndef PATH_H
#define PATH_H

#include "Vertex.hpp"
#include <string>

class Path {
    public:

    Path(long dist): distance(dist) {};

    long getDistance();
    void setDistance(long dist);

    std::vector<std::string> getPath();
    void setPath(std::vector<std::string> newPath);
    void addToEnd(std::string s);   //append to the path
    void addToPath(std::string s);  //insert at the front of the path

    std::string getStart();         //returns the first vertex in the path
    std::string getDestination();   //returns the last vertex in the path

    void visit();
    bool hasBeenVisited();

    private:

    bool visited = false;
    long distance;
    std::vector<std::string> path;

};

#endif