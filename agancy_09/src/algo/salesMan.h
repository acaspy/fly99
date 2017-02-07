/*
 * salesMan.h
 *
 *  Created on: Dec 14, 2016
 *      Author: tsnappir
 */

#ifndef ALGORITHM_SALESMAN_H_
#define ALGORITHM_SALESMAN_H_


#include <vector>
#include <map>
#include <tr1/unordered_map>
#include <string>
#include <iostream>

#include "../data_structure/graph.h"
#include "../geo/cityday.h"

namespace Graph_Algorithm {


struct sm_pair {
public:
	sm_pair() : cost(), _vertices() {}
	sm_pair(double c, dataStracture::Vertex* v) : cost(c), _vertices(1,v) {}
	sm_pair(sm_pair* orig) : cost(orig->cost), _vertices(orig->_vertices) {}

	void print () {
		std::cout << "Print sm_pair. cost : " << cost << std::endl;
		for (unsigned int i=0;i<_vertices.size()-1;i++) {
			dataStracture::Vertex* v = _vertices[i];
			std::cout << v->getId()->getName() << " , " << v->getEdge(_vertices[i+1])->getTran()->getCost() << " , ";
		}
		std::cout << "Done"  << std::endl;
	}
	double cost;
	std::vector<dataStracture::Vertex*> _vertices;
} ;


struct smvector {
	smvector( sm_pair* smp) : vec(1,smp) {	}
	void addSmPair(sm_pair* smp) {vec.push_back(smp);}
	void print() {
		for (unsigned int i=0;i<vec.size();i++) {
			vec[i]->print();
		}
	}
	std::vector<sm_pair*> vec;
} ;

class salesMan {
public:
	salesMan(dataStracture::Graph* g) : _g(g) {}
	~salesMan();
	std::vector<std::string> calc (int num, geo::city* start, geo::city* end);
	int ElemExist(sm_pair* smp, std::string elem);
private:
	dataStracture::Graph* _g;
};

}

#endif /* ALGORITHM_SALESMAN_H_ */
