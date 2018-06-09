#include "stdafx.h"

#include "Longitude.h"

namespace GPS
{
	Longitude::Longitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second) :
		Angle<-180, 180>(degree, minute, second), cardinal_{ cardinal } {}
}