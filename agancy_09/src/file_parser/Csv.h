/*
 * Csv.h
 *
 *  Created on: Jan 24, 2017
 *      Author: tsnappir
 */

#ifndef FILE_PARSER_CSV_H_
#define FILE_PARSER_CSV_H_

#include "parser.h"
#include <tr1/unordered_map>
#include <sstream>
#include <vector>
#include <stdlib.h>

namespace parser {

class Csv: public parser {
public:
	Csv(std::string file) : parser(file) {}
	virtual ~Csv();
	virtual void parse (dataStracture::Graph* g, std::tr1::unordered_map<std::string,geo::city*>& places);
};

} /* namespace parser */

#endif /* FILE_PARSER_CSV_H_ */
