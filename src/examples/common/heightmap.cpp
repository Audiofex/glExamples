#include "heightmap.h"
#include "util.h"

HeightMap::HeightMap(float heightScale)
    : w(0), h(0), heightScale(heightScale)
{
}

HeightMap::~HeightMap()
{
}

int HeightMap::getWidth() const
{
    return w;
}

int HeightMap::getHeight() const
{
    return h;
}

const std::vector<float>& HeightMap::getData() const
{
    return data;
}

bool HeightMap::load(const char* fileName)
{
    int channels;
    unsigned char* img = SOIL_load_image(fileName, &w, &h, &channels, SOIL_LOAD_L);
    if(!img)
    {
        std::cerr << "Error loading heightmap " << fileName << ": " << SOIL_last_result() << std::endl;
        return false;
    }
    if(channels != 1)
    {
        std::cerr << "Error loading heightmap " << fileName << ": channels should be 1" << std::endl;
    }

    data.resize(w * h);

    for(int i = 0; i < w * h; ++i)
    {
        unsigned char tile = img[i];
        data[i] = tile / 255.0f * heightScale;
    }

    SOIL_free_image_data(img);

    return true;
}