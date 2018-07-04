#include <string>
#include <stdexcept> 
#include <sstream>
#include <memory>

template<typename T>
Buffer2D<T>::Buffer2D(int width, int height) : width{width}, height{height}
{
    if(width <=0 || height <=0)
    {
        std::stringstream ss;
        ss << "Can't initliazer buffer of size (" << width << "," << height << ")";
        throw std::invalid_argument(ss.str());
    }
    data = std::make_unique<T[]>(width*height);
}

template<typename T>
size_t Buffer2D<T>::getByteSize()
{
    return width * height * sizeof(T);
}

template<typename T>
void Buffer2D<T>::boundsAssert(int x, int y)
{
    if(!isInBounds(x, y))
    {
        std::stringstream ss;
        ss << "Attempt to access location (" << x << "," << y
           << ") in buffer of size (" << width << "," << height << ")";
        throw std::out_of_range(ss.str());
    }

}
template<typename T>
T Buffer2D<T>::get(int x, int y)
{
    boundsAssert(x,y);
    return data[(y*width) + x];
}

template<typename T>
void Buffer2D<T>::set(int x, int y, T value)
{
    boundsAssert(x,y);
    data[(y*width) + x] = value;
}

template<typename T>
void Buffer2D<T>::clear(T value)
{
    for(int i = 0; i < width*height; i++)
    {
        data[i] = value;
    }
}