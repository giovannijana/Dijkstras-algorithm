#include "Graph.hpp"
#include "Vertex.hpp"
#include "Path.hpp"
#include <string>
#include <vector>
#include <queue>
#include <climits>

Graph::Graph() : vSize(0), eSize(0) {}

Graph::~Graph() {

    // delete all edges, then all vertices

    unsigned long i;
    for (i = 0; i < eSize; i++)
    {
        delete edgeSeq.at(i);
    }

    for (i = 0; i < vSize; i++)
    {
        delete vertSeq.at(i);
    }

}

void Graph::addVertex(std::string label) {
    //create new vertex
    Vertex* newVertex = new Vertex(label);

    //add new vertex to graph vertex collection
    vertSeq.push_back(newVertex);

    //increment vector size
    vSize++;
}

//POSSIBLE FIXME: the eraser of the vector slots in this function may cause memory leak of vertex and edge pointers
void Graph::removeVertex(std::string label) {
    unsigned long i;

    //remove edges incident on vertex w/ label "label"
    for (i = 0; i < edgeSeq.size(); i++) {
        if (edgeSeq[i]->getVert1Label() == label ||
            edgeSeq[i]->getVert2Label() == label) {
            edgeSeq.erase(edgeSeq.begin() + i);
        }
    }
    eSize = edgeSeq.size();

    //remove vertex
    for (i = 0; i < vertSeq.size(); i++) {
        if (vertSeq[i]->getLabel() == label) {
            vertSeq.erase(vertSeq.begin() + i);
        }
    }
    vSize = vertSeq.size();
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    unsigned long i;

    //check to make sure both vertices exist
    bool v1 = false;
    bool v2 = false;
    for (i = 0; i < vertSeq.size(); i++) {
        if (vertSeq[i]->getLabel() == label1) {
            v1 = true;
        }
        if (vertSeq[i]->getLabel() == label2) {
            v2 = true;
        }
    }

    //throw error if one or both vertices don't exist
    if (!v1 || !v2) {
        throw VertexDNE("One or both vertices do not exist");
    }

    //make sure there is no existing edge with associated vertices
    bool ee = false;
    for (i = 0; i < edgeSeq.size(); i++) {
        if ((edgeSeq[i]->getVert1Label() == label1 && edgeSeq[i]->getVert2Label() == label2) ||
            (edgeSeq[i]->getVert2Label() == label2 && edgeSeq[i]->getVert1Label() == label1)) {
            ee = true;
        }
    }

    //throw error if there is existing edge between both vertices
    if (ee) {
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
void Graph::removeEdge(std::string label1, std::string label2) {
    unsigned long i;

    //check that both vertices exist
    bool v1 = false;
    bool v2 = false;
    for (i = 0; i < vertSeq.size(); i++) {
        if (vertSeq[i]->getLabel() == label1) {
            v1 = true;
        }
        if (vertSeq[i]->getLabel() == label2) {
            v2 = true;
        }
    }

    //throw error if one or both vertices don't exist
    if (!v1 || !v2) {
        throw VertexDNE("One or both vertices do not exist");
    }

    //check that an edge exists between the two vertices
    bool ee = false;
    for (i = 0; i < edgeSeq.size(); i++) {
        if ((edgeSeq[i]->getVert1Label() == label1 && edgeSeq[i]->getVert2Label() == label2) ||
            (edgeSeq[i]->getVert2Label() == label2 && edgeSeq[i]->getVert1Label() == label1)) {
            ee = true;
        }
    }

    //throw error if edge does not exist
    if (!ee) {
        throw EdgeExists("Edge does not exist between existing vertices");
    }

    //remove edge with end vertices label1 and label2
    for (i = 0; i < edgeSeq.size(); i++) {
        if ((edgeSeq[i]->getVert1Label() == label1 && edgeSeq[i]->getVert2Label() == label2) ||
            (edgeSeq[i]->getVert2Label() == label2 && edgeSeq[i]->getVert1Label() == label2)) {
            edgeSeq.erase(edgeSeq.begin() + i);
        }
    }
    eSize = edgeSeq.size();
}

struct distanceComparator {
    constexpr bool operator() (std::pair<Vertex*, long> const& a,
        std::pair<Vertex*, long> const& b) const noexcept
    {
        return a.second > b.second;
    }
};

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) {

    unsigned long i, j;
    long minimumDistance = LONG_MAX;

    Vertex* currentVertex;

    bool DzFound = false;

    /* Vector containing Path objects. A Path stores the path to a vertex, the distance of
       the path, and whether the vertex has been visited.
    */
    std::vector<Path*> paths;

    /* Priority queue containing each vertex not yet visited along with the currently
       stored distance to that vertex from startLabel.
       The queue is sorted in order of increasing distance.
    */
    std::priority_queue<std::pair<Vertex*, long>, std::vector<std::pair<Vertex*, long>>, distanceComparator> uncheckedVertices;

    for (i = 0; i < vertSeq.size(); i++)
    {
        currentVertex = vertSeq[i];
        if (vertSeq[i]->getLabel() == startLabel) //the starting vertex should have a distance of 0
        {
            Path* currentPath = new Path(0);
            currentPath->addToPath(vertSeq[i]->getLabel());
            paths.push_back(currentPath);
            uncheckedVertices.push(std::make_pair(currentVertex, 0));
        }

        else // other vertices should have a distance of infinity
        {
            Path* currentPath = new Path(LONG_MAX);
            currentPath->addToPath(vertSeq[i]->getLabel());
            paths.push_back(currentPath);
            uncheckedVertices.push(std::make_pair(currentVertex, LONG_MAX));
        }
    }

    while (uncheckedVertices.size() != 0)
    {
        DzFound = false;

        currentVertex = uncheckedVertices.top().first;  //pull a new vertex from the queue
        uncheckedVertices.pop();

        Path* Du;   // the currently stored distance to the current vertex
        Path* Dz;   // the currently stored distance to a vertex adjacent to u

        for (i = 0; i < paths.size(); i++)   //find u in Paths vector
        {
            if (paths[i]->getDestination() == currentVertex->getLabel())
            {
                Du = paths[i];
            }
        }

        if (Du->hasBeenVisited())
        {
            continue;
        }
        Du->visit();

        for (i = 0; i < edgeSeq.size(); i++)
        {
            if (edgeSeq[i]->getVert1Label() == currentVertex->getLabel()) //finding an edge incident to the current vertex
            {
                for (j = 0; j < paths.size(); j++)
                {
                    if (paths[j]->getDestination() == edgeSeq[i]->getVert2Label()) //find the distance to the adjacent vertex
                    {
                        DzFound = true;
                        Dz = paths[j];
                    }
                }

                //RELAXATION
                if (DzFound)
                {
                    if (Du->getDistance() + edgeSeq[i]->getWeight() < Dz->getDistance())
                    {
                        Vertex* updatedZ = new Vertex("");
                        for (j = 0; j < vertSeq.size(); j++)    //find the vertex to be updated
                        {
                            if (vertSeq[j]->getLabel() == edgeSeq[i]->getVert2Label())
                            {

                                updatedZ = vertSeq[j];  
                            }
                        }
                        std::string destination = Dz->getDestination();
                        Dz->setPath(Du->getPath());
                        Dz->addToEnd(destination);
                        Dz->setDistance(Du->getDistance() + edgeSeq[i]->getWeight());
                        uncheckedVertices.push(std::make_pair(updatedZ, Du->getDistance() + edgeSeq[i]->getWeight()));
                    }
                }
            }
            else if (edgeSeq[i]->getVert2Label() == currentVertex->getLabel())
            {
                for (j = 0; j < paths.size(); j++)
                {
                    if (paths[j]->getDestination() == edgeSeq[i]->getVert1Label())
                    {
                        DzFound = true;
                        Dz = paths[j];
                    }
                }
                //RELAXATION
                if (DzFound)
                {
                    if (Du->getDistance() + edgeSeq[i]->getWeight() < Dz->getDistance())
                    {
                        Vertex* updatedZ = new Vertex("");
                        for (j = 0; j < vertSeq.size(); j++)    //find the vertex to be updated
                        {
                            if (vertSeq[j]->getLabel() == edgeSeq[i]->getVert1Label())
                            {
                                updatedZ = vertSeq[j];
                            }
                        }
                        std::string destination = Dz->getDestination();
                        Dz->setPath(Du->getPath());
                        Dz->addToEnd(destination);
                        Dz->setDistance(Du->getDistance() + edgeSeq[i]->getWeight());
                        uncheckedVertices.push(std::make_pair(updatedZ, Du->getDistance() + edgeSeq[i]->getWeight()));
                    }
                }
            }
        }
    }
    for (i = 0; i < paths.size(); i++)  //find the minimum distance path that leads from the startLabel to endLabel
    {
        if (paths[i]->getStart() == startLabel && paths[i]->getDestination() == endLabel && paths[i]->getDistance() < minimumDistance)
        {
            path = paths[i]->getPath();
            minimumDistance = paths[i]->getDistance();
        }
    }
    return minimumDistance;
}