#include "../include/interpolate.hpp"

namespace ux
{
    ColorInterpolate::ColorInterpolate(const Color& mx, const Color& mn, unsigned int steps, bool d)
    : max{mx}, min{mn}, dir{d}
    {
        lr = LinearInterpolate<int16_t>{ max.r, min.r, steps, dir };
        lg = LinearInterpolate<int16_t>{ max.g, min.g, steps, dir };
        lb = LinearInterpolate<int16_t>{ max.b, min.b, steps, dir };
    }

    Color ColorInterpolate::forward()
    {
        int16_t r = lr.forward();
        int16_t g = lg.forward();
        int16_t b = lb.forward();
        typedef sf::Uint8 u8 ;
        return Color{ (u8)r, (u8)g, (u8)b };
    }

    Color ColorInterpolate::backward()
    {
        int16_t r = lr.backward();
        int16_t g = lg.backward();
        int16_t b = lb.backward();
        typedef sf::Uint8 u8 ;
        return Color{ (u8)r, (u8)g, (u8)b };
    }

    Vec2Interpolate::Vec2Interpolate(const Vec2f& mx, const Vec2f& mn, unsigned int steps, bool d)
    : max{mx}, min{mn}, dir{d}
    {
        a = LinearInterpolate<float>{ max.x, min.x, steps, dir };
        b = LinearInterpolate<float>{ max.y, min.y, steps, dir };
    }

    Vec2f Vec2Interpolate::forward()
    {
        float x = a.forward();
        float y = b.forward();
        return Vec2f{ x, y };
    }

    Vec2f Vec2Interpolate::backward()
    {
        float x = a.backward();
        float y = b.backward();
        return Vec2f{ x, y };
    }
}
