/*
 * salesMan.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: tsnappir
 */

#include "salesMan.h"




int Graph_Algorithm::salesMan::ElemExist(sm_pair* smp,  std::string elem) {
	for (unsigned int i=0;i<smp->_vertices.size()-1;i++) {
		if (smp->_vertices[i]->getId()->getName() == elem) {
			return 1;
		}
	}
	return 0;
}

std::vector<std::string> Graph_Algorithm::salesMan::calc (int num, geo::city* start, geo::city* end) {
	if ( ! (_g->vertexExist(start)) ||  (! _g->vertexExist(end))) {
		std::cout << "starting poing " << start->getName() << " or ending point " << " doesn't exist" << std::endl;
		std::vector<std::string> tmp;
		return tmp;
	}
	std::tr1::unordered_map< dataStracture::Vertex*,smvector*> current, next;
	dataStracture::Vertex* cur = _g->getVertex(start);
	sm_pair* smp = new sm_pair(0,cur);
	smvector* smv = new smvector(smp);
	 dataStracture::Vertex* ne;
	current[cur] =  smv;
	sm_pair* smp_new;

	std::tr1::unordered_map<dataStracture::Vertex*,smvector*>::iterator map_it;
	std::vector<sm_pair*> smp_vec;
	std::vector<std::string> stringv;
	dataStracture::Edge* e;
	std::vector< dataStracture::Edge*> ve;
	std::vector< dataStracture::Edge*>::iterator ve_it;
	std::vector<sm_pair*>::iterator smpv_it;
	bool dummy = 0;
	for (;num>0; num--) {

		for(map_it = current.begin(); map_it != current.end(); ++map_it) {
			cur = map_it->first;
			smv = map_it->second;
			smp_vec = smv->vec;
			ve = cur->getEdges();
			//std::cout <<  "TTTT num = " << num << " " << cur->getId()->getName() << std::endl ;
			//vv = _g->getVertexes(_g->getVertex(cur));
			for (ve_it = ve.begin(); ve_it != ve.end() ; ve_it++) {
				e = *ve_it;
				if (!dummy && e->getTran()->getCost()==-1) {
					continue;
				}
				if (dummy && e->getTran()->getCost()!=-1) {
					continue;
				}
				ne = e->getDestination();
				for (smpv_it = smp_vec.begin(); smpv_it != smp_vec.end() ; smpv_it++) {
					smp = *smpv_it;
					if (ElemExist(smp,ne->getId()->getName()) && num>1) {
						continue;
					}
					//smp_new = smp->CreateNewVectorWithAdditionalElem(e->getCost(),ne);
					smp_new = new sm_pair(smp);
					smp_new->_vertices.push_back(ne);
					smp_new->cost+= e->getTran()->getCost();
					if (next.count(ne) != 1){
						next[ne] = new smvector(smp_new);
					} else {
						next[ne]->addSmPair(smp_new);
					}
				}
			}
		}
		current.clear();
		current = next;
		next.clear();
		dummy = !dummy;
	}


	cur = _g->getVertex(end);
	smv = current[cur];
	smv->print();

	std::vector<std::string> tmp;
	return tmp;
}
