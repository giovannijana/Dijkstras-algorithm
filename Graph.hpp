#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <string>
#include <vector>


class Graph: public GraphBase{
    private:
        std::vector<Vertex*> vertSeq;
        std::vector<Edge*> edgeSeq;
        unsigned long vSize;
        unsigned long eSize;
    public:
        Graph(); //constructor
        ~Graph(); //destructor

        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
};

class GraphException {
    public:
        GraphException(const std::string& err) : errMsg(err) {}
        std::string getError() { return errMsg; }
    private:
        std::string errMsg;
};

class VertexDNE : public GraphException {
    public:
        VertexDNE(const std::string& err) : GraphException(err) {}
};

class EdgeExists: public GraphException{
    public:
        EdgeExists(const std::string & err) : GraphException(err) {}
};

#endif