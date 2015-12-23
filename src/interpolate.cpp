#include "../include/interpolate.hpp"

namespace ux
{
    ColorInterpolate::ColorInterpolate(const Color& mx, const Color& mn, unsigned int steps, bool d)
    : m_max{mx}, m_min{mn}, m_dir{d}
    {
        m_lr = LinearInterpolate<int16_t>{ m_max.r, m_min.r, steps, m_dir };
        m_lg = LinearInterpolate<int16_t>{ m_max.g, m_min.g, steps, m_dir };
        m_lb = LinearInterpolate<int16_t>{ m_max.b, m_min.b, steps, m_dir };
    }

    Color ColorInterpolate::forward()
    {
        int16_t r = m_lr.forward();
        int16_t g = m_lg.forward();
        int16_t b = m_lb.forward();
        typedef sf::Uint8 u8 ;
        return Color{ (u8)r, (u8)g, (u8)b };
    }

    Color ColorInterpolate::backward()
    {
        int16_t r = m_lr.backward();
        int16_t g = m_lg.backward();
        int16_t b = m_lb.backward();
        typedef sf::Uint8 u8 ;
        return Color{ (u8)r, (u8)g, (u8)b };
    }

    Vec2Interpolate::Vec2Interpolate(const Vec2f& mx, const Vec2f& mn, unsigned int steps, bool d)
    : m_max{mx}, m_min{mn}, m_dir{d}
    {
        m_a = LinearInterpolate<float>{ m_max.x, m_min.x, steps, m_dir };
        m_b = LinearInterpolate<float>{ m_max.y, m_min.y, steps, m_dir };
    }

    Vec2f Vec2Interpolate::forward()
    {
        float x = m_a.forward();
        float y = m_b.forward();
        return Vec2f{ x, y };
    }

    Vec2f Vec2Interpolate::backward()
    {
        float x = m_a.backward();
        float y = m_b.backward();
        return Vec2f{ x, y };
    }
}
