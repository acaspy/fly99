/*
 * Csv.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: tsnappir
 */

#include "Csv.h"

namespace parser {


Csv::~Csv() {
}

void Csv::parse(dataStracture::Graph* g, std::tr1::unordered_map<std::string,geo::city*>& places) {
	//std::tr1::unordered_map<std::string,geo::city*> places;
	int line_length = 8;
	std::ifstream input( _file.c_str() );
	std::vector<std::string> arr_string(line_length);
	std::string from;
	std::string to;
	geo::city* city_from;
	geo::city* city_to;
	tran::transport* t;
	for( std::string line; getline( input, line ); ) {
		std::istringstream ss(line);
		std::string token;
		for (int i=0;i<line_length;i++) {
			std::getline(ss, token, ',');
			arr_string[i] = token;
			//std::cout << token << " ";
		}
		from = arr_string[0] + "_" + arr_string[2];
		to = arr_string[1] + "_" + arr_string[2];
		double cost = atof( arr_string[5].c_str());
		int date = atoi( arr_string[2].c_str());
		if (places.count(from) != 1) {
			city_from = new geo::cityday(arr_string[0],date);
			places[from] = city_from;
			g->addVertex(city_from);
		} else {
			city_from = places[from];
		}
		if (places.count(to) != 1) {
			city_to = new geo::cityday(arr_string[1],date);
			places[to] = city_to;
			g->addVertex(city_to);
		} else {
			city_to = places[to];
		}

		t = g->getTran(city_from,city_to);
		if (t != 0) {
			if (cost < t->getCost()) {
				t = new tran::transport(city_from,city_to,cost);
				g->updateEdge(city_from,city_to,t);
			}
		} else {
			t = new tran::transport(city_from,city_to,cost);
			// if exist - take the cheapest flight
			g->addEdge(city_from,city_to,t);
		}
	}
}


} /* namespace parser */
