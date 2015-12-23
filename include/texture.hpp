#ifndef __UX_TEXTURE_
#define __UX_TEXTURE_

#include "log.hpp"
#include "typedefs.hpp"

#include <map>

namespace ux
{
    class TextureSilo
    {
        static std::map<Color, RenderTexture> color_textures;
        static std::map<std::string, RenderTexture> file_textures;
        static unsigned int seed;

        TextureSilo() {};

    public:
        static void AddTexture(const Vec2f&, const Color&);
        static void AddTexture(const Vec2f&, const std::string&);
        static RenderTexture& Get(const Color&);
        static RenderTexture& Get(const std::string&);
    };
}

#endif // __UX_TEXTURE_
