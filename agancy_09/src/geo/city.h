/*
 * city.h
 *
 *  Created on: Dec 28, 2016
 *      Author: tsnappir
 */

#ifndef GEO_CITY_H_
#define GEO_CITY_H_

#include<string>

namespace geo {

class city {
public:
	city(std::string id) : _id(id) {}
	city(const city& obj) : _id (obj._id) {}
	const std::string getName() const {return _id;}
	virtual int getDate() = 0;
	virtual ~city();

protected:
	std::string _id;
};

 /* namespace geo */


/*
	std::string ttt =
	return lhs.getName() == rhs.getName();
}
*/

}

#endif /* GEO_CITY_H_ */
