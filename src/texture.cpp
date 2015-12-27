#include "../include/texture.hpp"

namespace ux
{
    std::unordered_map<Color, RenderTexture, hasher::ColorHasher> TextureSilo::color_textures;
    unsigned int TextureSilo::seed = 1u;

    std::size_t hasher::ColorHasher::operator()(const Color& color) const
    {
        return std::stoul(std::to_string((unsigned int)color.r) +
                          std::to_string((unsigned int)color.g) +
                          std::to_string((unsigned int)color.b) +
                          std::to_string((unsigned int)color.a));
    }

    void TextureSilo::AddTexture(const Vec2f& dim, const Color& color)
    {
        // If the same colored texture exists then,
        // update only if new one's dimension is bigger
        if(color_textures.count(color) > 0u)
        {
            auto edim = color_textures[color].getSize();
            auto x = static_cast<float>(edim.x),
                 y = static_cast<float>(edim.y);
            if(dim.x > x || dim.y > y) {
                color_textures[color].create(
                    static_cast<unsigned int>(std::max(dim.x, x)),
                    static_cast<unsigned int>(std::max(dim.y, y)));
                color_textures[color].clear(color);
            }
        }
        else
        {
            color_textures[color].create(
                static_cast<unsigned int>(dim.x), static_cast<unsigned int>(dim.y));
            color_textures[color].clear(color);
        }
    }

    RenderTexture& TextureSilo::Get(const Color& color)
    {
        return color_textures[color];
    }
}
