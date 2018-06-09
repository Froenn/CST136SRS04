#ifndef ANGLE_H
#define ANGLE_H

#include "gsl.h"

#include "Range.h"

namespace GPS
{
	template<int min, int max>
	class Angle
	{
		//static_assert(min < max);

	private:
		using base_degree_type = int;
		using base_minute_type = unsigned;
		using base_second_type = unsigned;

	protected:
		using degree_type = Range<base_degree_type, min, max>;
		using minute_type = Range<base_minute_type, 0, 60>;
		using second_type = Range<base_second_type, 0, 60>;

	protected:
		const degree_type degree_;
	private:
		const minute_type minute_;
		const second_type second_;

	private:
		//this is to make longitude values properly compare since we are traveling west to east but on the globe the islands cross 0 to 180 over to -180 to 0 (east to west)
		virtual long normalDegree() const
		{
			auto result = degree_;

			return result;
		}
	public:
		//sort vector easier
		long makeMicrodegrees() const
		{
			auto degree{ degree_ };
			auto minute{ minute_ };
			auto second{ second_ };

			degree = normalDegree();

			auto result = ((degree * 1000000) + (minute * 1000000) / 60 + (second * 1000000) / 3600);

			return result;
		}
		//make angle comparisons
		friend bool operator<(const Angle& lhs, const Angle& rhs) { return lhs.makeMicrodegrees() < rhs.makeMicrodegrees(); }

	public:
		double getWholeDegrees() const
		{
			auto degree{ degree_ };
			auto minute{ minute_ };
			auto second{ second_ };

			auto result = degree + (minute / 60) + (second / 3600);
			
			return result;
		}

	public:
		Angle(const degree_type degree, const minute_type minute, const second_type second): degree_{degree}, minute_{minute}, second_{second} {}

		virtual ~Angle() = default;
	};
}
#endif