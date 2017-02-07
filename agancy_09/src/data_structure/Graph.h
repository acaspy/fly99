#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <tr1/unordered_map>
#include "../geo/city.h"
#include "../transport/transport.h"
#include <fstream>


namespace dataStracture {

class Vertex;
class Grapgh;

class Edge {
	friend class Graph;
public:
	virtual ~Edge() {}
    Vertex* getFrom() {return from;}
    Vertex* getDestination() {return destination;}
    tran::transport* getTran() {return _obj;}
    void printEdge (std::ostream& fd = std::cout) {_obj->print(fd);}
private:
    Edge(Vertex* org, Vertex* dest, tran::transport* obj) : from(org), destination(dest), _obj (obj) {}

    Vertex* from;
    Vertex* destination;
    tran::transport* _obj;
};


class Vertex {
	friend class Graph;
public:
	~Vertex();
    void addEdge(Edge* e) {edges[e->getDestination()] = e;}
    void printVertex(std::ostream& fd = std::cout);
    geo::city* getId() {return _id;}
    std::vector<Edge*> getEdges();
    Edge* getEdge(Vertex* to);

private:
    Vertex( geo::city* id) : _id (id) {}
    Vertex(const Vertex* v) : _id (v->_id) {}
    geo::city* _id;
    std::tr1::unordered_map<Vertex*,Edge*> edges;
};

class Graph {
public:

    Graph() : id(counter) { counter++; }
    ~Graph();
    Graph (const Graph* g) :  id(counter), _vertices (g->_vertices) { counter++; }
    //Graph (const Graph* g, std::vector<int>);
    void CloneFilteredGraph(Graph* g, std::vector<int>, int addEdges = 1, int addDummyEdges = 0);
    void AddDummyEdges();
    void addVertex(geo::city* id) {CreateVertex(id);}
    std::vector<Vertex* > getNeighbours(Vertex* id);
    std::vector<geo::city* > getNeighbours(geo::city* id);
    void addEdge( geo::city* from, geo::city* to, tran::transport* tran);
    void updateEdge( geo::city* from, geo::city* to, tran::transport* tran) ;
    int vertexExist(geo::city* id) ;
    void printGraph(std::string file) ;
    std::vector<Vertex*> getVertices ();
    Vertex* getVertex( geo::city* id ) ;
    tran::transport* getTran( geo::city* from, geo::city* to);


protected:
    Vertex* CreateVertex(geo::city* id);

private:
    int id;
    std::tr1::unordered_map<geo::city*,Vertex*> _vertices;
	static int counter;
	static tran::transport* dummyTran;
	static geo::city* dummyCity;
};


}
