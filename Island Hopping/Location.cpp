#include "stdafx.h"

#include "Location.h"

namespace GPS
{
	Location::Location(const std::string name, const Latitude latitude, const Longitude longitude) : 
		name_{ name }, latitude_{ latitude }, longitude_{ longitude } {}
}