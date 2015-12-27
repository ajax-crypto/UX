#ifndef __UX_TEXTURE_
#define __UX_TEXTURE_

#include "log.hpp"
#include "typedefs.hpp"

#include <unordered_map>
#include <string>

namespace ux
{
    namespace hasher
    {
        struct ColorHasher
        {
            std::size_t operator()(const Color&) const;
        };
    }

    /** \brief \c TextureSilo class is responsible for caching the textures
     * and enable reuse.
     */
    class TextureSilo
    {
        static std::unordered_map<Color, RenderTexture, hasher::ColorHasher> color_textures;
        //static std::map<std::string, RenderTexture> file_textures;
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
