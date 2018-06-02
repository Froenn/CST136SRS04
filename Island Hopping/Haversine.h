#ifndef HAVERSINE_H
#define HAVERSINE_H

#define _USE_MATH_DEFINES

#include <cmath>

namespace formulas
{
	template<T lat1, T lng1 , T lat2, T lng2>
	class Haversine
	{
	private: //km - note: a better value for this calculation would be 6371km, but just following spec
		static constexpr auto radiusEarth = 6378;

	private: //converts coord degrees to radians for proper use in haversine equation
		const auto phi1_{ lat1 * M_PI / 180 }; 
		const auto phi2_{ lat2 * M_PI / 180 };
		const auto lambda1_{ lng1 * M_PI / 180 };
		const auto lambda2_{ lng2 * M_PI / 180 };
		
	public: //haversine equation - distance km
		static constexpr auto distance_{ 2 * radiusEarth * asin(sqrt(pow(sin((phi2_ - phi1_) / 2), 2) + cos(phi1_) * cos(phi2_) * pow(sin((lambda2_ - lambda1_) / 2), 2))) };
	};
}
#endif