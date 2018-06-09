#ifndef LATITUDE_H
#define LATITUDE_H

#include "Angle.h"

namespace GPS
{
	class Latitude : public Angle<-89, 90>
	{
	public:
		enum class Cardinal { S = -1, N = +1 };

	private:
		const Cardinal cardinal_;

	private:
		long normalDegree() const override
		{
			degree_type degree { degree_ };
			Cardinal const cardinal{ cardinal_ };

			if (cardinal == Cardinal::S)
				return (0 - degree);
			return degree;
		}

	public:
		auto getCardinalSign() const
		{
			if(cardinal_ == Cardinal::S)
				return -1;
			return 1;
		}

	public:
		Latitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second);

		virtual ~Latitude() = default;
	};
}
#endif
