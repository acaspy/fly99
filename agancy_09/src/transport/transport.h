/*
 * transport.h
 *
 *  Created on: Jan 27, 2017
 *      Author: tsnappir
 */

#ifndef TRANSPORT_TRANSPORT_H_
#define TRANSPORT_TRANSPORT_H_

#include "../geo/city.h"
#include <iostream>

namespace tran {

class transport {
public:
	transport(geo::city* from, geo::city* to, double cost) : _from(from) , _to(to), _cost (cost) {}
	virtual ~transport();
	void setCost(double cost) { _cost = cost;}
	double getCost () {return _cost;}
	void print (std::ostream& fd = std::cout);

private:
	geo::city* _from;
	geo::city* _to;
	double _cost;
};

} /* namespace tran */

#endif /* TRANSPORT_TRANSPORT_H_ */
