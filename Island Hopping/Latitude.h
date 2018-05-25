#ifndef LATITUDE_H
#define LATITUDE_H

#include "Angle.h"

namespace GPS
{
	class Latitude : public Angle<-89, 90>
	{
	public:
		enum class Cardinal { S = -1, N = +1 };

		Latitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second);
	};
}
#endif
