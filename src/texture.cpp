#include "../include/texture.hpp"

namespace ux
{
    static std::vector<RenderTexture> TextureSilo::textures;
    static unsigned int TextureSilo::seed = 1u;

    void TextureSilo::AddTexture(const Vec2f& dim, const Color& color)
    {
        for(auto it = color_textures.begin(); it != color_textures.end(); ++it)
            if(it->first != color)
            {
                color_textures[color] = RenderTexture{};
                color_textures[color].create(dim.x, dim.y);
                color_textures[color].clear(color);
            }
    }

    RenderTexture& TextureSilo::Get(const Color&)
    {
        return color_textures[color];
    }
}
