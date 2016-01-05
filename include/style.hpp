#ifndef __UX_STYLE_
#define __UX_STYLE_

#include <string>
#include <limits>
#include "typedefs.hpp"

namespace ux {

    constexpr int ZTOP = std::numeric_limits<int>::max() - 1;
    constexpr int ZBOTTOM = std::numeric_limits<int>::min() + 1;

    enum Shapes {
        NONE,
        RECTANGLE,
        CIRCLE,
        SECTOR,
        ROUNDED_RECTANGLE,
        TRIANGLE,
        POLYGON,
        ELLIPSE
    };

    enum Positioning {
        RELATIVE,
        ABSOLUTE,
        FIXED
    };
    
    enum Filter {
        BW,
        EDGE,
        SHARPEN,
        BRIGHTEN,
        LIGHTEN,
        DARKEN,
        BLUR,
        SEPIA,
        CONTRAST,
        GLASS
    };

	enum Alignment {
	    LEFT = 0u,
	    RIGHT = 1 << 1,
	    CENTER = 1 << 2,
	    TOP = 1 << 3,
	    BOTTOM = 1 << 4,
	    JUSTIFY = 1 << 5
    };

    enum FontType {
        NORMAL,
        BOLD,
        ITALIC,
        BOLD_ITALIC
    };

    enum Cursor {
        WAIT,
        POINTER,
        DEFAULT,
        CROSSHAIR,
        INDETERMINATE,
        HEXPAND,
        VEXPAND,
        RLEXPAND,
        LREXPAND,
        MOVE
    };

	enum Property {
        ELEMENT_POSITION,
        SHAPE_POSITION,
        CONTENT_POSITION,
        FONT_SIZE,
        SHAPE_HEIGHT,
        SHAPE_WIDTH,
        SHAPE_DIM,
        RADIUS,
        RADIUS_MAJOR,
        RADIUS_MINOR,
        RADIUS_TOPLEFT,
        RADIUS_TOPRIGHT,
        RADIUS_BOTTOMLEFT,
        RADIUS_BOTTOMRIGHT,
        SHAPE_SCALE,
        ELEMENT_SCALE,
        PADDING_WIDTH,
        PADDING_TOP,
        PADDING_BOTTOM,
        PADDING_LEFT,
        PADDING_RIGHT,
        BORDER_WIDTH,
        BORDER_TOP,
        BORDER_BOTTOM,
        BORDER_LEFT,
        BORDER_RIGHT,
        MARGIN_WIDTH,
        MARGIN_TOP,
        MARGIN_BOTTOM,
        MARGIN_LEFT,
        MARGIN_RIGHT,
        SHAPE_COLOR,
        SHADOW_COLOR,
        TEXT_COLOR,
        BORDER_COLOR,
        BORDER_TOP_COLOR,
        BORDER_BOTTOM_COLOR,
        BORDER_RIGHT_COLOR,
        BORDER_LEFT_COLOR,
        SHAPE_TEXTURE,
        SHADOW_TEXTURE,
        BORDER_TEXTURE,
        SHADOW_SPREAD,
        SHADOW_ANGLE
    };

    enum Colors {
        ALICEBLUE = 0,
        ANTIQUEWHITE,
        AQUA,
        AQUAMARINE,
        AZURE,
        BEIGE,
        BISQUE,
        BLACK,
        BLANCHEDALMOND,
        BLUE,
        BLUEVIOLET,
        BROWN,
        BURLYWOOD,
        CADETBLUE,
        CHARTTRUESE,
        CHOCOLATE,
        CORAL,
        CORNFLOWERBLUE,
        CORNSILK,
        CRIMSON,
        CYAN,
        DARKBLUE,
        DARKCYAN,
        DARKGOLDENROD,
        DARKGRAY,
        DARKGREEN,
        DARKKHAKI,
        DARKMAGENTA,
        DARKOLIVEGREEN,
        DARKORANGE,
        DARKORCHID,
        DARKRED,
        DARKSLAMON,
        DARKSEAGREEN,
        DARKSLATEBLUE,
        DARKSLATEGRAY,
        DARKTURQUOISE,
        DARKVIOLET,
        DEEPPINK,
        DEEPSKYBLUE,
        DIMGRAY,
        DODGERBLUE,
        FIREBRICK,
        FLORALWHITE,
        FORESTGREEN,
        FUCHSIA,
        GAINSBORO,
        GHOSTWHITE,
        GOID,
        GOLDENROD,
        GRAY,
        GREEN,
        GREENYELLOW,
        HONEYDEW,
        HOTPINK,
        INDIANRED,
        INDIGO,
        IVORY,
        KHAKI,
        LAVENDER,
        LAVENDERBLUSH,
        LAWNGREEN,
        LEMONCHIFFON,
        LIGHTBLUE,
        LIGHTCORAL,
        LIGHTCYAN,
        LIGHTGOLDENRODYELLOW,
        LIGHTGREEN,
        LIGHTGREY,
        LIGHTPINK,
        LIGHTSALMON,
        LIGHTSEAGREEN,
        LIGHTSKYBLUE,
        LIGHTSLATEGRAY,
        LIGHTSTEELBLUE,
        LIGHTYELLOW,
        LIME,
        LIMEGREEN,
        LINEN,
        MAGENTA,
        MAROON,
        MEDIUMAQUAMARINE,
        MEDIUMBLUE,
        MEDIUMORCHID,
        MEDIUMPURPLE,
        MEDIUMSEAGREEN,
        MEDIUMSLATEBLUE,
        MEDIUMSPRINGGREEN,
        MEDIUMTURQUOISE,
        MEDIUMVIOLETRED,
        MIDNIGHTBLUE,
        MINTCREAM,
        MISTYROSE,
        MOCCASIN,
        NAVAJOWHITE,
        NAVY,
        NAVYBLUE,
        OLDLACE,
        OLIVE,
        OLIVEDRAB,
        ORANGE,
        ORANGERED,
        ORCHID,
        PALEGOLDENROD,
        PALEGREEN,
        PALETURQUOISE,
        PALEVIOLETRED,
        PAPAYAWHIP,
        PEACHPUFF,
        PERU,
        PINK,
        PLUM,
        POWDERBLUE,
        PURPLE,
        RED,
        ROSYBROWN,
        ROYALBLUE,
        SADDLEBROWN,
        SALMON,
        SANDYBROWN,
        SEAGREEN,
        SEASHELL,
        SIENNA,
        SILVER,
        SKYBLUE,
        SLATEBLUE,
        SLATEGRAY,
        SNOW,
        SPRINGGREEN,
        STEELBLUE,
        TAN,
        TEAL,
        THISTLE,
        TOMATO,
        TURQUOISE,
        VIOLET,
        WHEAT,
        WHITE,
        WHITESMOKE,
        YELLOW,
        YELLOWGREEN
    };

    const Color RGB[Colors::YELLOWGREEN + 1] = {
        Color{ 240, 248, 255 },
        Color{ 250, 235, 215 },
        Color{ 0, 255, 255 },
        Color{ 127, 255, 212 },
        Color{ 240, 255, 255 },
        Color{ 245, 245, 220 },
        Color{ 255, 228, 196 },
        Color{ 0, 0, 0 },
        Color{ 255, 235, 205 },
        Color{ 0, 0, 255 },
        Color{ 138, 43, 226 },
        Color{ 165, 42, 42 },
        Color{ 222, 184, 135 },
        Color{ 95, 158, 160 },
        Color{ 95, 168, 160 },
        Color{ 210, 105, 30 },
        Color{ 255, 127, 80 },
        Color{ 100, 149, 237 },
        Color{ 255, 248, 220 },
        Color{ 220, 20, 60 },
        Color{ 0, 255, 255 },
        Color{ 0, 0, 139 },
        Color{ 0, 139, 139 },
        Color{ 184, 134, 11 },
        Color{ 169, 169, 169 },
        Color{ 0, 100, 0 },
        Color{ 189, 183, 107 },
        Color{ 139, 0, 139 },
        Color{ 85, 107, 47 },
        Color{ 255, 140, 0 },
        Color{ 153, 50, 204 },
        Color{ 139, 0, 0 },
        Color{ 233, 150, 122 },
        Color{ 143, 188, 143 },
        Color{ 72, 61, 139 },
        Color{ 47, 79, 79 },
        Color{ 0, 206, 209 },
        Color{ 148, 0, 211 },
        Color{ 255, 20, 147 },
        Color{ 0, 191, 255 },
        Color{ 105, 105, 105 },
        Color{ 30, 144, 255 },
        Color{ 178, 34, 34 },
        Color{ 255, 250, 240 },
        Color{ 34, 139, 34 },
        Color{ 255, 0, 255 },
        Color{ 220, 220, 220 },
        Color{ 248, 248, 255 },
        Color{ 255, 215, 0 },
        Color{ 218, 165, 32 },
        Color{ 127, 127, 127 },
        Color{ 0, 128, 0 },
        Color{ 173, 255, 47 },
        Color{ 240, 255, 240 },
        Color{ 255, 105, 180 },
        Color{ 205, 92, 92 },
        Color{ 75, 0, 130 },
        Color{ 255, 255, 240 },
        Color{ 240, 230, 140 },
        Color{ 230, 230, 215 },
        Color{ 255, 240, 245 },
        Color{ 124, 252, 0 },
        Color{ 255, 250, 205 },
        Color{ 173, 216, 230 },
        Color{ 240, 128, 128 },
        Color{ 224, 255, 255 },
        Color{ 250, 250, 210 },
        Color{ 144, 238, 144 },
        Color{ 211, 211, 211 },
        Color{ 255, 182, 193 },
        Color{ 255, 160, 122 },
        Color{ 32, 178, 170 },
        Color{ 135, 206, 250 },
        Color{ 119, 136, 153 },
        Color{ 176, 196, 222 },
        Color{ 255, 255, 224 },
        Color{ 0, 255, 0 },
        Color{ 50, 205, 50 },
        Color{ 250, 240, 230 },
        Color{ 255, 0, 255 },
        Color{ 128, 0, 0 },
        Color{ 102, 105, 170 },
        Color{ 0, 0, 205 },
        Color{ 186, 85, 211 },
        Color{ 147, 112, 219 },
        Color{ 60, 179, 113 },
        Color{ 123, 104, 238 },
        Color{ 0, 250, 154 },
        Color{ 72, 209, 204 },
        Color{ 199, 21, 133 },
        Color{ 25, 25, 112 },
        Color{ 245, 255, 250 },
        Color{ 255, 228, 225 },
        Color{ 255, 228, 181 },
        Color{ 255, 222, 173 },
        Color{ 0, 0, 128 },
        Color{ 159, 175, 223 },
        Color{ 253, 245, 230 },
        Color{ 128, 128, 0 },
        Color{ 107, 142, 35 },
        Color{ 255, 165, 0 },
        Color{ 255, 69, 0 },
        Color{ 218, 112, 214 },
        Color{ 238, 232, 170 },
        Color{ 152, 251, 152 },
        Color{ 175, 238, 238 },
        Color{ 219, 112, 147 },
        Color{ 255, 239, 213 },
        Color{ 255, 218, 185 },
        Color{ 205, 133, 63 },
        Color{ 255, 192, 203 },
        Color{ 221, 160, 221 },
        Color{ 176, 224, 230 },
        Color{ 128, 0, 128 },
        Color{ 255, 0, 0 },
        Color{ 188, 143, 143 },
        Color{ 65, 105, 225 },
        Color{ 139, 69, 19 },
        Color{ 250, 128, 114 },
        Color{ 244, 164, 96 },
        Color{ 46, 139, 87 },
        Color{ 255, 245, 238 },
        Color{ 160, 82, 45 },
        Color{ 192, 192, 192 },
        Color{ 135, 206, 235 },
        Color{ 106, 90, 205 },
        Color{ 112, 128, 144 },
        Color{ 255, 250, 250 },
        Color{ 0, 255, 127 },
        Color{ 70, 130, 180 },
        Color{ 210, 180, 140 },
        Color{ 0, 128, 128 },
        Color{ 216, 191, 216 },
        Color{ 255, 99, 71 },
        Color{ 64, 224, 208 },
        Color{ 238, 130, 238 },
        Color{ 245, 222, 179 },
        Color{ 255, 255, 255 },
        Color{ 245, 245, 245 },
        Color{ 255, 255, 0 },
        Color{ 139, 205, 50 }
    };
    
    struct Sides
    {
         float m_left, m_right, m_top, m_bottom ;
    };

    inline bool operator==(const Sides& lhs, const Sides& rhs)
    {
        return lhs.m_left == rhs.m_left && lhs.m_right == rhs.m_right &&
               lhs.m_bottom == rhs.m_bottom && lhs.m_top == rhs.m_top ;
    }

    inline bool operator!=(const Sides& lhs, const Sides& rhs)
    {
        return !(lhs == rhs);
    }
    
    struct Border
    {
        float  m_thickness ;
        Color  m_color ;
    }

    namespace shape
    {
      
        struct Rect
        {
            float m_height, m_width ;
            
        };

        struct Circle
        {
            float  m_radius ;
        } ;

        struct Ellipse
        {
            float m_major, m_minor ;
        };

        struct RoundedRect
        {
            float m_height, m_width ;
            float m_topleft, m_bottomleft, m_topright, m_bottomright ;
        };

        inline bool operator==(const Rect& lhs, const Rect& rhs)
        {
            return lhs.m_height == rhs.m_height && lhs.m_width == rhs.m_width ;
        }

        inline bool operator!=(const Rect& lhs, const Rect& rhs)
        {
            return !(lhs == rhs);
        }

        inline bool operator==(const Circle& lhs, const Circle& rhs)
        {
            return lhs.m_radius == rhs.m_radius ;
        }

        inline bool operator!=(const Circle& lhs, const Circle& rhs)
        {
            return !(lhs == rhs);
        }

        inline bool operator==(const Ellipse& lhs, const Ellipse& rhs)
        {
            return lhs.m_major == rhs.m_major && lhs.m_minor == rhs.m_minor ;
        }

        inline bool operator==(const RoundedRect& lhs, const RoundedRect& rhs)
        {
            return lhs.m_height == rhs.m_height && lhs.m_width == rhs.m_width &&
                   lhs.m_bottomleft  == rhs.m_bottomleft &&
                   lhs.m_bottomright == rhs.m_bottomright &&
                   lhs.m_topleft == rhs.m_topleft && lhs.m_topright == rhs.m_topright ;
        }
    }

    struct ElementShape
    {
        union
        {
            shape::Rect        m_rect ;
            shape::Circle      m_circle ;
            shape::RoundedRect m_rounded_rect ;
            shape::Ellipse     m_ellipse ;
        };
        
        union
        {
            struct {
                Border m_border_left, m_border_right, m_border_top, m_border_bottom;
            }
            Border m_border;
        };
        
        Shapes m_type ;
        Color  m_color ;
        Vec2f  m_position ;
    } ;

    bool operator==(const ElementShape& lhs, const ElementShape& rhs);

    struct Content
    {
        Color       m_color ;
        std::string m_text ;
        int         m_font_type ;
        std::string m_font ;
        float       m_font_size ;
        bool        m_auto_size ;
        Alignment   m_alignment ;
        Vec2f       m_position ;
        Sides       m_bounding_box ;
        float       m_line_height ;
        float       m_letter_spacing ;

        Content(const std::string& str, const Color& color) :
            m_text{str}, m_color{color}, m_auto_size{false}
        {}

        Content() : m_auto_size{false}, m_color{RGB[BLACK]} {}
    } ;
    
    bool operator==(const Content&, const Content&);

    struct Shadow
    {
        float m_spread ;
        Color m_color ;
        bool  m_smooth ;
    };
    
    bool operator==(const Shadow&, const Shadow&);

    struct Graphics
    {
        uint64_t m_texture;
        int      m_z;
        bool     m_smooth;
        bool     m_repeat;
    };
    
    bool operator==(const Graphics&, const Graphics&);

    struct StyleData
    {
        Vec2f        m_position ;
        bool         m_visible ;
        ElementShape m_shape ;
        Positioning  m_positioning ;
        Content      m_content ;
        Shadow       m_shadow ;
        Sides        m_padding ;
        Sides        m_margin ;
        Graphics     m_graphics ;
        Filter       m_filter ;

        StyleData() ;
        StyleData(const StyleData&) = default ;
        StyleData(StyleData&&) = default ;
        StyleData& operator=(const StyleData&) = default ;
        
        bool operator==(const StyleData&) const;
        bool operator!=(const StyleData&) const;

        StyleData& operator()(Property, const Vec2f&);
        StyleData& operator()(Property, const Color&);
        StyleData& operator()(Property, float);
        StyleData& operator()(Property, const Sides&);
        StyleData& operator()(Property, const std::string& s) { m_content.m_text = s; }

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

	std::ostream& operator<<(std::ostream& stream, const Sides&);
	std::ostream& operator<<(std::ostream& stream, const Border&);
	std::ostream& operator<<(std::ostream& stream, const Content&);
	std::ostream& operator<<(std::ostream& stream, const ElementShape&);

}

#endif
