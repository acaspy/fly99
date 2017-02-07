/*
 * cityday.h
 *
 *  Created on: Jan 19, 2017
 *      Author: tsnappir
 */

#ifndef GEO_CITYDAY_H_
#define GEO_CITYDAY_H_

#include "city.h"

namespace geo {

class cityday: public geo::city {
public:
	cityday(std::string id, int date) : city(id), _date (date) {}
	virtual int getDate() {return _date;}
	virtual ~cityday();

private:
	int _date;
};

}
#endif /* GEO_CITYDAY_H_ */
