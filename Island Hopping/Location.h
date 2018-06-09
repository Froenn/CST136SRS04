#ifndef LOCATION_H
#define LOCATION_H

#include <string>

#include "Latitude.h"
#include "Longitude.h"

namespace GPS
{
	class Location
	{
	private:
		const std::string name_;
		const Latitude latitude_;
		const Longitude longitude_;

	public:
		auto getLat() const { return latitude_; };
		auto getLng() const { return longitude_; };

		auto getLatWhole() const { return latitude_.getWholeDegrees(); };
		auto getLngWhole() const { return longitude_.getWholeDegrees(); };

	public:
		Location(const std::string name, const Latitude latitude, const Longitude longitude);
	};
}
#endif