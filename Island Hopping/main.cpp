#include "stdafx.h"

#include <string>
#include <array>
#include <forward_list>
#include <map>
#include <vector>
#include <ctime>

#include  "gsl.h"

#include "GPS.h"
#include "Compare.h"
#include "Distance.h"

int main() noexcept
{
	using namespace std::string_literals;

	static std::array<GPS::Location, 12> const islands
	{
		GPS::Location{ "Faichuk Islands"s,	GPS::Latitude{ GPS::Latitude::Cardinal::N,  7, 21,  8 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 151, 36, 30 } },
		GPS::Location{ "Hawaii"s,			GPS::Latitude{ GPS::Latitude::Cardinal::N, 21, 18, 41 },	GPS::Longitude{ GPS::Longitude::Cardinal::W, 157, 47, 47 } },
		GPS::Location{ "Marina Islands"s,	GPS::Latitude{ GPS::Latitude::Cardinal::N, 17,  0,  0 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 146,  0,  0 } },
		GPS::Location{ "Johnston Atoll"s,	GPS::Latitude{ GPS::Latitude::Cardinal::N, 16, 44, 13 },	GPS::Longitude{ GPS::Longitude::Cardinal::W, 169, 31, 26 } },
		GPS::Location{ "Kosrae"s,			GPS::Latitude{ GPS::Latitude::Cardinal::N,  5, 19,  0 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 162, 59,  0 } },
		GPS::Location{ "Falalop"s,			GPS::Latitude{ GPS::Latitude::Cardinal::N, 10,  1, 14 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 139, 47, 23 } },
		GPS::Location{ "Guam"s,				GPS::Latitude{ GPS::Latitude::Cardinal::N, 13, 30,  0 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 144, 48,  0 } },
		GPS::Location{ "Pohnpei"s,			GPS::Latitude{ GPS::Latitude::Cardinal::N,  6, 51,  0 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 158, 13,  0 } },
		GPS::Location{ "Marshall Islands"s, GPS::Latitude{ GPS::Latitude::Cardinal::N,  7,  7,  0 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 171,  4,  0 } },
		GPS::Location{ "Yap"s,				GPS::Latitude{ GPS::Latitude::Cardinal::N,  9, 32,  0 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 138,  7,  0 } },
		GPS::Location{ "Wake Island"s,		GPS::Latitude{ GPS::Latitude::Cardinal::N, 19, 17, 43 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 166, 37, 52 } },
		GPS::Location{ "New Zealand"s,		GPS::Latitude{ GPS::Latitude::Cardinal::S, 41, 17,  0 },	GPS::Longitude{ GPS::Longitude::Cardinal::E, 174, 27,  0 } }
	};

	//clock_t tI = clock(); //Time in ms

	std::vector<double> distance; //To calculate all list distances

	// VECTOR BEGIN //

	std::vector<std::reference_wrapper<const GPS::Location>> islandsRef(islands.begin(), islands.end()); //initialize with microdegrees. See CST136SRS04 Notes. create function, makeMicrodegress()

	sort(islandsRef.begin(), islandsRef.end(), CMP::cmpLat()); //sorts sn

	for(auto i = 0; i < 11; i++)
	{
		MF::Distance vDist(islandsRef.at(i), islandsRef.at(i + 1));
		distance.push_back(vDist.haversine());
	}

	auto nsVRSum = std::accumulate(distance.begin(), distance.end(), 0.0); //distance km
	distance.clear(); //clear out the distance vector for reuse

	sort(islandsRef.begin(), islandsRef.end(), CMP::cmpLng()); //sorts ew

	for (auto i = 0; i < 11; i++)
	{
		MF::Distance vDist(islandsRef.at(i), islandsRef.at(i + 1));
		distance.push_back(vDist.haversine());
	}

	auto ewVRSum = std::accumulate(distance.begin(), distance.end(), 0.0);
	distance.clear();

	// VECTOR END // 

	//auto tV = clock() - tI;

	// FORWARD_LIST BEGIN //

	std::forward_list<GPS::Location> islandsFL(islands.begin(), islands.end()); //Create forward_list of islands array

	islandsFL.sort(CMP::cmpLat()); //sorts sn

	auto next{islandsFL.begin()};
	++next;
	for(auto curr = islandsFL.begin(); next != islandsFL.end(); ++curr, ++next)
	{
		MF::Distance flDist(*curr, *next);

		distance.push_back(flDist.haversine());
	}

	auto snFLSum = std::accumulate(distance.begin(), distance.end(), 0.0);
	distance.clear();

	islandsFL.sort(CMP::cmpLng()); //sorts ew

	next = islandsFL.begin();
	++next;
	for (auto curr = islandsFL.begin(); next != islandsFL.end(); ++curr, ++next)
	{
		MF::Distance flDist(*curr, *next);

		distance.push_back(flDist.haversine());
	}

	auto ewFLSum = std::accumulate(distance.begin(), distance.end(), 0.0);
	distance.clear();

	// FORWARD_LIST END //

	//auto tF = clock() - tV;

	// MAP BEGIN //

	std::map<int, GPS::Location> islandsMap; //maps are already sorted. make longitudes compare by comparing angles, write a function in Angle to do so (longitude inherits from angle)

	sort(islandsRef.begin(), islandsRef.end(), CMP::cmpLat());

	for (int i = 0; i < islandsRef.size(); i++)
	{
		islandsMap.insert(std::pair<int, GPS::Location>(i, islandsRef.at(i)));
	}
	for (int i = 0; i < 11; i++)
	{
		MF::Distance mapDist(islandsMap.at(i), islandsMap.at(i + 1));

		distance.push_back(mapDist.haversine());
	}

	auto snMSum = std::accumulate(distance.begin(), distance.end(), 0.0);
	distance.clear();
	islandsMap.clear();
	
	sort(islandsRef.begin(), islandsRef.end(), CMP::cmpLng());

	for (int i = 0; i < islandsRef.size(); i++)
	{
		islandsMap.insert(std::pair<int, GPS::Location>(i, islandsRef.at(i)));
	}
	for (int i = 0; i < 11; i++)
	{
		MF::Distance mapDist(islandsMap.at(i), islandsMap.at(i + 1));

		distance.push_back(mapDist.haversine());
	}

	auto ewMSum = std::accumulate(distance.begin(), distance.end(), 0.0);
	distance.clear();

	// MAP END //

	//auto tM = clock() - tF;

	return 0;
}
