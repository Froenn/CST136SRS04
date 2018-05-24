#include "stdafx.h"

#include "GPS.h"

int main()
{
	std::array<GPS::Location, 12> island
	{
		GPS::Location{ "Faichuk Islands"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 7, 21, 8 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 151, 36, 30 } }
		/// ...
	};

    return 0;
}

