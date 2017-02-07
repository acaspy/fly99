/*
 * transport.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: tsnappir
 */

#include "transport.h"

namespace tran {



transport::~transport() {
	// TODO Auto-generated destructor stub
}

void transport::print(std::ostream& fd) {
	fd << "Transport from " << _from->getName() << " to " << _to->getName() << " ; cost: " << _cost << std::endl;
}

} /* namespace tran */
