#ifndef __UX_STYLE_
#define __UX_STYLE_

#include <string>
#include "typedefs.hpp"

namespace ux {

    enum Shapes { RECTANGLE = 1u, CIRCLE, SECTOR, ROUNDED_RECTANGLE, TRIANGLE, POLYGON, ELLIPSE };

	enum Alignment { LEFT, RIGHT, CENTER, TOP, BOTTOM, JUSTIFY };

	enum Property {
        ELEMENT_POSITION,
        SHAPE_POSITION,
        CONTENT_POSITION,
        FONT_SIZE,
        SHAPE_HEIGHT,
        SHAPE_WIDTH,
        SHAPE_DIM,
        SHAPE_RADIUS,
        SHAPE_SCALE,
        ELEMENT_SCALE,
        PADDING_WIDTH,
        PADDING_TOP,
        PADDING_BOTTOM,
        PADDING_LEFT,
        PADDING_RIGHT,
        OUTLINE_WIDTH,
        BORDER_WIDTH,
        BORDER_TOP,
        BORDER_BOTTOM,
        BORDER_LEFT,
        BORDER_RIGHT,
        SHAPE_COLOR,
        SHADOW_COLOR,
        TEXT_COLOR,
        OUTLINE_COLOR,
        SHADOW_SPREAD,
        SHADOW_ANGLE
    };

    struct StyleData
    {
        Vec2f position ;
        bool visible ;

        struct {
            union {
                struct {
                    float height, width ;
                } rect ;

                struct {
                    float radius ;
                } circle ;

                struct {
                    float major, minor ;
                } ellipse;

                struct {
                    float height, width ;
                    union {
                        struct {
                            float top, bottom, left, right ;
                        } corner ;
                        float radius ;
                    };
                } rounded_rect;

                struct {
                    float radius ;
                    float angle ;
                } sector;
            };
            Shapes type ;
            Color color ;
            Texture texture ;
            Vec2f position ;
        } shape ;

        struct {
            Color color ;
            std::string text ;
            int  font_type ;
            std::string font ;
            float font_size ;
            bool auto_size ;
            Alignment alignment ;
            Vec2f position ;
        } content ;

        struct {
            float width ;
            Color color ;
            Texture texture ;
        } outline;

        struct {
            union {
                struct {
                    float left, right, top, bottom ;
                };
                float width ;
            };
            Color color ;
            Texture texture ;
         } border;

        struct {
            float spread ;
            bool  smooth ;
            Color color ;
            Texture texture ;
        } shadow ;

        struct {
            union {
                struct {
                    float top, bottom, left, right ;
                };
                float width ;
            };
        } padding ;

        struct {
            union {
                struct {
                    float top, bottom, left, right ;
                };
                float width ;
            };
        } margin ;

        StyleData() ;
        StyleData(const StyleData&) = default ;
        StyleData(StyleData&&) = default ;
        StyleData& operator=(const StyleData&) = default ;

        StyleData& operator()(Property, const Vec2f&);
        StyleData& operator()(Property, const Color&);
        StyleData& operator()(Property, float);
        StyleData& operator()(Property, const std::string& s) { content.text = s; }

        void extract(Property, Vec2f&);
        void extract(Property, Color&);
        void extract(Property, float&);
    };

    struct GlobalDrawingStates
	{
		static bool Redraw ;
		static bool IsWithin(const StyleData&, float, float);
		static bool IsRectWithin(float, float, float, float, float, float);
		static bool IsCircleWithin(float, float, float, float, float);
	};
}

#endif
