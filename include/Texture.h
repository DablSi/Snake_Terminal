#ifndef TEXTURE_H
#define TEXTURE_H
#include <vector>

class Texture
{
    public:
        Texture();
        void print();
    private:
        struct TextureData{
            char symbol;
            int textColor;
            int bgColor;
        };
    public:
        int sizeY,sizeX;
        std::vector<TextureData> Field;
};

#endif // TEXTURE_H
