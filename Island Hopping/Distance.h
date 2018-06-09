#ifndef DISTANCE_H
#define DISTANCE_H

#include <corecrt_math_defines.h>

#include "Location.h"

namespace MF
{
	class Distance
	{
	private:
		const GPS::Location& l1_;
		const GPS::Location& l2_;

	public:
		double haversine() const
		{
			static constexpr auto radiusEarth = 6378;

			const auto phi1{ l1_.getLatWhole() * M_PI / 180 };
			const auto phi2{ l2_.getLatWhole() * M_PI / 180 };
			const auto lambda1{ l1_.getLngWhole() * M_PI / 180 };
			const auto lambda2{ l2_.getLngWhole() * M_PI / 180 };

			return (2 * radiusEarth * asin(sqrt(pow(sin((phi2 - phi1) / 2), 2) + cos(phi1) * cos(phi2) * pow(sin((lambda2 - lambda1) / 2), 2))));;
		}

	public:
		Distance(const GPS::Location& pointA, const GPS::Location& pointB): l1_(pointA), l2_(pointB) {}
	};
}
#endif