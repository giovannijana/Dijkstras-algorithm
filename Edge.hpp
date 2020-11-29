#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <vector>

class Edge {
    public:
        Edge(std::string l1, std::string l2, unsigned long weight): a(l1), b(l2), w(weight) {};

        void setWeight(unsigned long weight) { this->w = weight; };
        unsigned long getWeight(){ return w; };
        void setVert1Label(std::string l) { this->a = l; };
        void setVert2Label(std::string l) { this->b = l; };
        std::string getVert1Label(){ return a; };
        std::string getVert2Label(){ return b; };
    private:
        std::string a;
        std::string b;
        unsigned long w;
};

#endif