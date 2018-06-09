#ifndef RANGE_H
#define RANGE_H

namespace GPS
{
	template<typename T, T min, T max>
	class Range
	{
	private:
		using value_type = T;

		value_type value_;

	public:
		Range(const value_type value): value_{ value } {};

		operator value_type()
		{
			return value_;
		}
	};
}
#endif