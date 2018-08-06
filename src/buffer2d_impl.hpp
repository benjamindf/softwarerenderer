#ifndef BUFFER_2D_IMPL_H
#define BUFFER_2D_IMPL_H
#include "buffer2d_def.hpp"

template<typename T>
Buffer2D<T>::Buffer2D(int width, int height) : _width{width} , _height{height}
{
    if(_width <=0 || _height <=0)
    {
        std::stringstream ss;
        ss << "Can't initliazer buffer of size (" << width << "," << height << ")";
        throw std::invalid_argument(ss.str());
    }
    data = std::make_unique<T[]>(width*height);
}


template<typename T>
T Buffer2D<T>::get(int x, int y) const
{
    if(isInBounds(x,y))
    {
        return data[(y*_width) + x];
    }
    else 
    {
        throw buffer2d_out_of_range(x,y, _width,_height);
    }
}

template<typename T>
void Buffer2D<T>::set(int x, int y, T value)
{
    if(isInBounds(x,y))
    {
        data[(y*_width)+x] = value;
    } 
    else 
    {
        throw buffer2d_out_of_range(x,y,_width,_height);
    }
}

template<typename T>
void Buffer2D<T>::clear(T value)
{
    for(int i = 0; i < _width*_height; i++)
    {
        data[i] = value;
    }
}


#endif