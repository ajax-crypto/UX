#ifndef __UX__INTERPOLATE__
#define __UX__INTERPOLATE__

#include "typedefs.hpp"

namespace ux
{
    template <typename T>
	class LinearInterpolate
	{
	    T m_max, m_min ;
	    unsigned int m_steps, m_progress;
	    bool m_dir ;
	    float m_ratio ;

    public:
        LinearInterpolate(T mx, T mn, unsigned int s, bool d = true)
            : m_max{mx}, m_min{mn}, m_steps{s}, m_dir{d}, m_progress{0u}
        {
            m_ratio = (static_cast<float>(m_max) - static_cast<float>(m_min))/static_cast<float>(m_steps);
        }
        LinearInterpolate() = default ;

        T forward() ;
        T backward() ;
        bool isFinished() const { return m_progress > m_steps ; }
        void reset() { m_progress = 0u; }

        friend class ColorInterpolate ;
	};

	template <typename T> T
	LinearInterpolate<T>::forward()
	{
	    if(m_progress < m_steps)
        {
            T val = static_cast<T>(m_min + (static_cast<float>(m_progress) * m_ratio));
            ++m_progress ;
            return val ;
        }
        ++m_progress ;
        return m_max ;
	}

	template <typename T> T
	LinearInterpolate<T>::backward()
	{
	    if(m_progress < m_steps)
        {
            T val = m_max - static_cast<T>(static_cast<float>(m_progress) * m_ratio);
            ++m_progress ;
            return val ;
        }
        return m_min ;
	}

	class ColorInterpolate
	{
	    Color m_max, m_min ;
	    bool m_dir ;
	    LinearInterpolate<int16_t> m_lr, m_lg, m_lb ;

    public:
        ColorInterpolate(const Color&, const Color&, unsigned int, bool = true);
        ColorInterpolate() = default ;

        Color forward();
        Color backward();

        Color operator()();
        bool  isFinished() const { return m_lr.isFinished(); }
        void reset() { m_lr.reset(); m_lg.reset(); m_lb.reset(); }
	};

	class Vec2Interpolate
	{
	    Vec2f m_max, m_min ;
	    bool m_dir ;
	    LinearInterpolate<float> m_a, m_b ;

    public:
        Vec2Interpolate(const Vec2f&, const Vec2f&, unsigned int, bool = true);
        Vec2Interpolate() = default ;

        Vec2f forward();
        Vec2f backward();

        Vec2f operator()();
        bool  isFinished() const { return m_a.isFinished(); }
        void reset() { m_a.reset(); m_b.reset(); }
	};
}

#endif // __UX__INTERPOLATE__
