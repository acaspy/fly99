/*
 * parser.h
 *
 *  Created on: Jan 19, 2017
 *      Author: tsnappir
 */

#include<string>
#include <tr1/unordered_map>
#include <fstream>
#include <iostream>
#include "../algo/salesMan.h"

#ifndef FILE_PARSER_PARSER_H_
#define FILE_PARSER_PARSER_H_

namespace parser {

class parser {
public:
	parser(std::string file) : _file (file) {}
	virtual void parse (dataStracture::Graph* g, std::tr1::unordered_map<std::string,geo::city*>& places) = 0;
	virtual ~parser();
protected:
	std::string _file;
};

} /* namespace parser */

#endif /* FILE_PARSER_PARSER_H_ */
