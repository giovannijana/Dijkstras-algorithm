#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>

class Vertex{
    public:
        Vertex(std::string l) : label(l) {};

        void setLabel(std::string l){ this->label = l; };
        std::string getLabel(){ return label; };
    private:
        std::string label;
};

#endif