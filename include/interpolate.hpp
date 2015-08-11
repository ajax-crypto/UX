#ifndef __UX__INTERPOLATE__
#define __UX__INTERPOLATE__

#include "typedefs.hpp"

namespace ux
{
    template <typename T>
	class LinearInterpolate
	{
	    T max, min ;
	    unsigned int steps, progress;
	    bool dir ;
	    float ratio ;

    public:
        LinearInterpolate(T mx, T mn, unsigned int s, bool d = true)
            : max{mx}, min{mn}, steps{s}, dir{d}, progress{0u}
        {
            ratio = (static_cast<float>(max) - static_cast<float>(min))/static_cast<float>(steps);
        }
        LinearInterpolate() = default ;

        T forward() ;
        T backward() ;
        bool isFinished() const { return progress > steps ; }
        void reset() { progress = 0u; }

        friend class ColorInterpolate ;
	};

	template <typename T> T
	LinearInterpolate<T>::forward()
	{
	    if(progress < steps)
        {
            T val = static_cast<T>(min + (static_cast<float>(progress) * ratio));
            ++progress ;
            return val ;
        }
        ++progress ;
        return max ;
	}

	template <typename T> T
	LinearInterpolate<T>::backward()
	{
	    if(progress < steps)
        {
            T val = max - static_cast<T>(static_cast<float>(progress) * ratio);
            ++progress ;
            return val ;
        }
        return min ;
	}

	class ColorInterpolate
	{
	    Color max, min ;
	    bool dir ;
	    LinearInterpolate<int16_t> lr, lg, lb ;

    public:
        ColorInterpolate(const Color&, const Color&, unsigned int, bool = true);
        ColorInterpolate() = default ;

        Color forward();
        Color backward();

        Color operator()();
        bool  isFinished() const { return lr.isFinished(); }
        void reset() { lr.reset(); lg.reset(); lb.reset(); }
	};

	class Vec2Interpolate
	{
	    Vec2f max, min ;
	    bool dir ;
	    LinearInterpolate<float> a, b ;

    public:
        Vec2Interpolate(const Vec2f&, const Vec2f&, unsigned int, bool = true);
        Vec2Interpolate() = default ;

        Vec2f forward();
        Vec2f backward();

        Vec2f operator()();
        bool  isFinished() const { return a.isFinished(); }
        void reset() { a.reset(); b.reset(); }
	};
}

#endif // __UX__INTERPOLATE__
