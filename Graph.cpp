#include "Graph.hpp"
#include "Vertex.hpp"
#include <string>
#include <vector>

Graph::Graph() : vSize(0), eSize(0) {}

Graph::~Graph() {}

void Graph::addVertex(std::string label){
    //create new vertex
    Vertex *newVertex = new Vertex(label);

    //add new vertex to graph vertex collection
    vertSeq.push_back(newVertex);

    //increment vector size
    vSize++;
}

//POSSIBLE FIXME: the eraser of the vector slots in this function may cause memory leak of vertex and edge pointers
void Graph::removeVertex(std::string label){
    unsigned long i;

    //remove edges incident on vertex w/ label "label"
    for(i = 0; i < edgeSeq.size(); i++){
        if(edgeSeq[i]->getVert1Label() == label || 
           edgeSeq[i]->getVert2Label() == label){
               edgeSeq.erase(edgeSeq.begin() + i);
           }
    }
    eSize = edgeSeq.size();

    //remove vertex
    for(i = 0; i < vertSeq.size(); i++){
        if(vertSeq[i]->getLabel() == label){
            vertSeq.erase(vertSeq.begin() + i);
        }
    }
    vSize = vertSeq.size();
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    unsigned long i;

    //check to make sure both vertices exist
    bool v1 = false;
    bool v2 = false;
    for(i = 0; i < vertSeq.size(); i++){
        if(vertSeq[i]->getLabel() == label1){
            v1 = true;
        }
        if(vertSeq[i]->getLabel() == label2){
            v2 = true;
        }
    }

    //throw error if one or both vertices don't exist
    if(!v1 || !v2){
        throw VertexDNE("One or both vertices do not exist");
    }

    //make sure there is no existing edge with associated vertices
    bool ee = false;
    for(i = 0; i < edgeSeq.size(); i++){
        if((edgeSeq[i]->getVert1Label() == label1 && edgeSeq[i]->getVert2Label() == label2) ||
           (edgeSeq[i]->getVert2Label() == label2 && edgeSeq[i]->getVert1Label() == label1)){
               ee = true;
           }
    }

    //throw error if there is existing edge between both vertices
    if(ee){
        throw EdgeExists("Edge already exists between existing vertices");
    }

    //create new edge
    Edge* newEdge = new Edge(label1, label2, weight);

    //add edge to edge vector
    edgeSeq.push_back(newEdge);

    //increment edge vector size variable
    eSize++;
}

//POSSIBLE FIXME: the eraser of the vector slots in this function may cause memory leak of edge pointers
//FIXME: update to include checking for existing vertices and edge to remove
void Graph::removeEdge(std::string label1, std::string label2){
    unsigned long i;

    //check that both vertices exist
    bool v1 = false;
    bool v2 = false;
    for(i = 0; i < vertSeq.size(); i++){
        if(vertSeq[i]->getLabel() == label1){
            v1 = true;
        }
        if(vertSeq[i]->getLabel() == label2){
            v2 = true;
        }
    }

    //throw error if one or both vertices don't exist
    if(!v1 || !v2){
        throw VertexDNE("One or both vertices do not exist");
    }
    
    //check that an edge exists between the two vertices
    bool ee = false;
    for(i = 0; i < edgeSeq.size(); i++){
        if((edgeSeq[i]->getVert1Label() == label1 && edgeSeq[i]->getVert2Label() == label2) ||
           (edgeSeq[i]->getVert2Label() == label2 && edgeSeq[i]->getVert1Label() == label1)){
               ee = true;
           }
    }

    //throw error if edge does not exist
    if(!ee){
        throw EdgeExists("Edge does not exist between existing vertices");
    }

    //remove edge with end vertices label1 and label2
    for(i = 0; i < edgeSeq.size(); i++){
        if((edgeSeq[i]->getVert1Label() == label1 && edgeSeq[i]->getVert2Label() == label2) ||
           (edgeSeq[i]->getVert2Label() == label2 && edgeSeq[i]->getVert1Label() == label2)){
               edgeSeq.erase(edgeSeq.begin() + i);
           }
    }
    eSize = edgeSeq.size();
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    //code here
}