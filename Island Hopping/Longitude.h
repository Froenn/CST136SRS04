#ifndef LONGITUDE_H
#define LONGITUDE_H

#include "Angle.h"

namespace GPS
{
	class Longitude : public Angle<-180, 180>
	{
	public:
		enum class Cardinal { W = -1, E = +1 };

	private:
		const Cardinal cardinal_;

	private:
		long normalDegree() const override
		{
			auto result{ degree_ };
			const auto cardinal{ cardinal_ };

			if (cardinal == Cardinal::W)
				return 0 - result + 360;
			return result;
		}

	public:
		auto getCardinalSign() const
		{
			if (cardinal_ == Cardinal::W)
				return -1;
			return 1;
		}

	public:
		Longitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second);

		virtual ~Longitude() = default;
	};
}
#endif