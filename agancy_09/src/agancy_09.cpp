//============================================================================
// Name        : agancy_01.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "algo/salesMan.h"
#include "geo/city.h"
#include "file_parser/Csv.h"
#include <time.h>
#include <ctime>
#include <stdlib.h>


using namespace std;


vector<int> spanDates (std::string start_s, std::string end_s, int flights) {
	int start = atoi(start_s.c_str());
	int end = atoi(end_s.c_str());

	//20170406
	int s_days = start % 100;
	int e_days = end % 100;
	start /= 100;
	end /= 100;
	int s_mons = start % 100;
	int e_mons = end % 100;
	start /= 100;
	end /= 100;

    struct std::tm s_date = {0,0,0,s_days,s_mons,start-1900};
    struct std::tm e_date = {0,0,0,e_days,e_mons,end-1900};

    std::time_t x = std::mktime(&s_date);
    std::time_t y = std::mktime(&e_date);



    double difference;
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) ) {
        difference = std::difftime(y,x) / (60 * 60 * 24);
    } else {
    	vector<int> res;
    	return res;
    }
    double days4flight = difference / (flights-1);
    //std::cout << "TTTT difference = " << difference << " , flights = " << flights << " , days4flight = " << days4flight << std::endl;

    vector<int> res(flights);
    int buf = 0;;
    for (int i=0; i<flights-1; i++) {
    	s_date.tm_mday += days4flight*i-buf;
    	buf = days4flight*i;
    	res[i] = s_date.tm_mday + s_date.tm_mon*100 + (1900+s_date.tm_year)*10000;
    	//s_date.tm_mday += days4flight;
    }
    res[flights-1] = e_date.tm_mday + e_date.tm_mon*100 + (1900+e_date.tm_year)*10000;
	return res;
}


int main(int argc, char** argv) {
	//args needed (csv file of flights, start date, start city, end city, flights
	/*
	 if (argc != 6) {
	 	 std::cout << "5 arguments are needed! exit..." << std::endl;
	 }
	std::string fn = argv[0];
	int start_date = atoi(argv[1]);
	std::string start_city = argv[2];
	int end_date = atoi(argv[3]);
	std::string end_city = argv[4];
	int flights = atoi(argv[5]);

	 */

	std::string fn = "C:\\Users\\tsnappir\\new_eclipse\\flights.csv";
	std::string start_date = "20170401";
	std::string start_city = "WAW";
	std::string end_date = "20170420";
	std::string end_city = "WAW";
	std::string flights_s = "4";


	int flights = atoi(flights_s.c_str());
	std::string start_algo = start_city + "_" + start_date;
	std::string end_algo = end_city + "_" + end_date;

	std::vector<int> dates = spanDates(start_date,end_date,flights);

	for (unsigned int i=0; i<4; i++) {
		std::cout << "flight on " << dates[i] << std::endl;
	}

	dataStracture::Graph* g = new dataStracture::Graph();
	std::tr1::unordered_map<std::string,geo::city*> places;

	parser::Csv* p = new parser::Csv(fn);
	std::cout << "Starting to parse " << fn << std::endl;
	p->parse(g,places);
	std::cout << "Done parsing" << std::endl;

	std::cout << "Print g" << std::endl;

	dataStracture::Graph* g3 = new dataStracture::Graph();
	g3->CloneFilteredGraph(g,dates,1,1);
	std::cout << "Print g3" << std::endl;
	//g3->printGraph("C:\\Users\\tsnappir\\new_eclipse\\g3.csv");

	//std::cout << "Start to run algorithm" << std::endl;
	  clock_t begin = clock();

	Graph_Algorithm::salesMan* sm = new Graph_Algorithm::salesMan(g3);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC/1000);
	sm->calc(flights*2-1,places[start_algo],places[end_algo]);
	std::cout << "time meas: " << elapsed_secs ;
	return 0;
}
