#ifndef COMPARE_H
#define COMPARE_H

#include "Location.h"

namespace CMP
{
	struct cmpLat
	{
		bool operator()(const GPS::Location& lhs, const GPS::Location& rhs) const
		{
			return lhs.getLat().makeMicrodegrees() < rhs.getLat().makeMicrodegrees();
		}
	};

	struct cmpLng
	{
		bool operator()(const GPS::Location& lhs, const GPS::Location& rhs) const
		{
			return lhs.getLng().makeMicrodegrees() < rhs.getLng().makeMicrodegrees();
		}
	};
}
#endif