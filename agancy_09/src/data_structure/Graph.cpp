
#include "graph.h"

namespace dataStracture {

Vertex::~Vertex() {
	for (std::tr1::unordered_map<Vertex*,Edge*>::iterator it = edges.begin();it != edges.end(); it++) {
		 delete (it->second);
	 }
}

std::vector<Edge*> Vertex::getEdges() {
	 std::vector<Edge*> res;
	 for (std::tr1::unordered_map<Vertex*,Edge*>::iterator it = edges.begin();it != edges.end(); it++) {
		 res.push_back(it->second);
	 }
	return res;
}

Edge* Vertex::getEdge(Vertex* to) {
	if (edges.count(to) != 0) {
		return edges[to];
	}
	return 0;
}

void Vertex::printVertex(std::ostream& fd) {
	fd << "Printing vertex " << _id->getName() << " , date: " << _id->getDate() << std::endl;
	std::vector<Edge*> edges = getEdges();
	for (unsigned int i=0; i< edges.size();i++) {
		edges[i]->printEdge(fd);
	}
	fd  << std::endl  << std::endl;
}


int Graph::counter = 0;
tran::transport* Graph::dummyTran = new tran::transport(0,0,-1);

Graph::~Graph() {
	for (std::tr1::unordered_map<geo::city*,Vertex*>::iterator it = _vertices.begin();it!=_vertices.end();it++) {
		delete (it->second);
	}
}

void Graph::CloneFilteredGraph(Graph* g, std::vector<int> dates, int addEdges, int addDummyEdges) {
	std::vector<std::tr1::unordered_map<std::string,geo::city*> > dummy (dates.size());
	unsigned int i;
	for (std::tr1::unordered_map<geo::city*,Vertex*>::iterator it = g->_vertices.begin();it!=g->_vertices.end();it++) {
			int flag = 0;
			int d;
			for (i=0;i<dates.size();i++) {
				d = it->first->getDate();
				if (d == dates[i]) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				this->addVertex(it->second->getId());
				if (addDummyEdges) {
					dummy[i][it->first->getName()] = it->second->getId();
				}
			}
		}
	if (addEdges) {
		for (std::tr1::unordered_map<geo::city*,Vertex*>::iterator it = _vertices.begin();it!=_vertices.end();it++) {
			geo::city* city = it->first;
			std::vector<geo::city*> neighbours = g->getNeighbours(city);
			for (unsigned int i=0; i<neighbours.size();i++) {
				addEdge(city,neighbours[i],g->getTran(city,neighbours[i]));
			}
		}
	}
	if (addDummyEdges) {
		for (i=0;i<dummy.size()-1;i++) {
			for (std::tr1::unordered_map<std::string,geo::city*>::iterator it=dummy[i].begin();it!=dummy[i].end();it++) {
				if (dummy[i+1].count(it->first) != 0) {
					addEdge(it->second,dummy[i+1][it->first],new tran::transport(dummy[i][it->first],dummy[i+1][it->first],-1));
				}
			}
		}
	}
}

std::vector<Vertex*> Graph::getVertices () {
	std::vector<Vertex*> res;
	for (std::tr1::unordered_map<geo::city*,Vertex*>::iterator it = _vertices.begin();it!=_vertices.end();it++) {
		res.push_back(_vertices[it->first]);
	}
	return res;
}

std::vector<Vertex* > Graph::getNeighbours(Vertex* id) {
	std::vector<Edge*> edges = id->getEdges();
	std::vector<Vertex* > res (edges.size());
	for(unsigned int i=0;i<edges.size();i++) {
		res[i] = edges[i]->getDestination();
	}
	return res;
}


std::vector<geo::city* > Graph::getNeighbours(geo::city* id) {
	std::vector<Vertex*> tmp = getNeighbours(_vertices[id]);
	std::vector<geo::city* > res ( tmp.size());
	for(unsigned int i=0; i<tmp.size(); i++) {
		res[i] = tmp[i]->getId();
	}
	return res;
}


void Graph::addEdge( geo::city* from, geo::city* to, tran::transport* tran) {
	Vertex* v1 = CreateVertex(from);
	Vertex* v2 = CreateVertex(to);
	Edge* e = new Edge(v1,v2,tran);
	v1->addEdge(e);
}
void Graph::updateEdge( geo::city* from, geo::city* to, tran::transport* tran) {
	Vertex* v1 = CreateVertex(from);
	Vertex* v2 = CreateVertex(to);
	Edge* old = v1->getEdge(v2);
	delete old;
	Edge* e = new Edge(v1,v2,tran);
	v1->addEdge(e);
}
int Graph::vertexExist(geo::city* id) {
	if (_vertices.count(id) != 0) {
		return 1;
	}
	return 0;
}
void Graph::printGraph(std::string file) {
	std::ofstream fd;
	fd.open (file.c_str());
	fd << "Printing graph:" << std::endl;
	for (std::tr1::unordered_map<geo::city*,Vertex*>::iterator it = _vertices.begin();it!=_vertices.end();it++) {
		it->second->printVertex(fd);
	}
	fd << "end Graph" << std::endl;
	fd.close();
}
Vertex* Graph::getVertex( geo::city* id ) {
	if (_vertices.count(id) != 0) {
		return _vertices[id];
	}
	return 0;
}
tran::transport* Graph::getTran( geo::city* from, geo::city* to) {
	Vertex* v1;
	if (_vertices.count(from) != 0) {
		v1 = _vertices[from];
	} else {
		return 0;
	}
	Vertex* v2;
	if (_vertices.count(to) != 0) {
		v2 = _vertices[to];
	} else {
		return 0;
	}
	Edge* e = v1->getEdge(v2);
	if (e != 0) {
		return e->getTran();
	}
	return 0;
}

Vertex* Graph::CreateVertex(geo::city* id) {
	if (_vertices.count(id) == 1){
		return _vertices[id];
	}
	Vertex* v = new Vertex(id);
	_vertices[id] = v;
	return v;
}

}
