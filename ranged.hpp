#ifndef __UX_RANGED_
#define __UX_RANGED_

namespace ux
{
	template <typename T> class Ranged
	{
		T val ;
		T high, low ;

	public:
		Ranged() {}
		Ranged(T a, T b) : high{a}, low{b}, val{b} {}
		Ranged(T a, T b, T c) : high{a}, low{b}, val{c} {}

		void setHigh(T a) { high = a; }
		T getRange() const { return high - low; }

		Ranged operator++()
		{
			++val ;
			if(val > high)
				val = high ;
			return Ranged(high, low, val);
		}

		Ranged operator--()
		{
			--val ;
			if(val < low)
				val = low ;
			return Ranged(high, low, val);
		}

		Ranged operator+=(T v)
		{
		    low += v ;
		    if(val > high)
                val = high ;
            else if(val < low)
                val = low ;
            return Ranged(high, low, val);
		}

		operator T() const { return val; }
	};
}

#endif
