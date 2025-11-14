#include "ImageConverter.hpp"

#include <cmath>

cg::image<cg::color_space_t::HSV> cg::image_converter::rgb_to_hsv(const image<color_space_t::RGB>& original)
{
    // Convert RGB to HSV
    cg::image<cg::color_space_t::HSV> converted(original.get_width(), original.get_height());

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            const float r = original(i, j)[0];
            const float g = original(i, j)[1];
            const float b = original(i, j)[2];

            const float c_max = std::max(std::max(r, g), b);
            const float c_min = std::min(std::min(r, g), b);
            const float delta = c_max - c_min;

            float h = 0.f, s = 0.f, v = 0.f;

            ////////
            // TODO:
            // Implement the conversion from RGB to HSV as described in
            // https://de.wikipedia.org/wiki/HSV-Farbraum#Umrechnung_RGB_in_HSV/HSL

            // ...
            
            v = c_max;
            
            // Saturation
            if (c_max != 0.f)
                s = delta / c_max;
            else
                s = 0.f; // if c_max is 0, saturation is 0

            // Hue
            if (delta == 0.f)
            {
                h = 0.f; // undefined, can set to 0
            }
            else if (c_max == r)
            {
                h = 60.f * fmod(((g - b) / delta), 6.f);
            }
            else if (c_max == g)
            {
                h = 60.f * (((b - r) / delta) + 2.f);
            }
            else // c_max == b
            {
                h = 60.f * (((r - g) / delta) + 4.f);
            }

            // Ensure hue is positive
            if (h < 0.f)
                h += 360.f;

            converted(i, j)[0] = h;
            converted(i, j)[1] = s;
            converted(i, j)[2] = v;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::RGB> cg::image_converter::hsv_to_rgb(const image<color_space_t::HSV>& original)
{
    // Convert HSV to RGB
    image<color_space_t::RGB> converted(original.get_width(), original.get_height());

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            const float h = original(i, j)[0];
            const float s = original(i, j)[1];
            const float v = original(i, j)[2];

            float r = 0.f, g = 0.f, b = 0.f;

            ////////
            // TODO:
            // Implement the conversion from HSV to RGB as described in
            // https://de.wikipedia.org/wiki/HSV-Farbraum#Umrechnung_HSV_in_RGB

            // ...
            
            float C = v * s;                                     // chroma
            float X = C * (1.0f - std::fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
            float m = v - C;

            float r1 = 0.f, g1 = 0.f, b1 = 0.f;

            if (h >= 0 && h < 60)        { r1 = C; g1 = X; b1 = 0; }
            else if (h >= 60 && h < 120) { r1 = X; g1 = C; b1 = 0; }
            else if (h >= 120 && h < 180){ r1 = 0; g1 = C; b1 = X; }
            else if (h >= 180 && h < 240){ r1 = 0; g1 = X; b1 = C; }
            else if (h >= 240 && h < 300){ r1 = X; g1 = 0; b1 = C; }
            else                          { r1 = C; g1 = 0; b1 = X; }

            r = r1 + m;
            g = g1 + m;
            b = b1 + m;

            converted(i, j)[0] = r;
            converted(i, j)[1] = g;
            converted(i, j)[2] = b;

       
        }
        
    }

    return converted;
}

cg::image<cg::color_space_t::Gray> cg::image_converter::rgb_to_gray(const image<color_space_t::RGB>& original)
{
    // Convert RGB to grayscale
    image<color_space_t::Gray> converted(original.get_width(), original.get_height());

    ////////
    // TODO:
    // Implement the conversion from RGB to grayscale using the luminance
    // approximation formula presented in the lecture.

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            float R = original(i, j)[0]; // Red channel
            float G = original(i, j)[1]; // Green channel
            float B = original(i, j)[2]; // Blue channel

            // Luminance formula
            float gray = 0.299f * R + 0.587f * G + 0.114f * B;

            converted(i, j)[0] = gray;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::BW> cg::image_converter::gray_to_bw(const image<color_space_t::Gray>& original)
{
    // Convert grayscale to black and white
    image<color_space_t::BW> converted(original.get_width(), original.get_height());

    ////////
    // TODO:
    // Implement the conversion from grayscale to black and white such that
    // luminance values < 0.5 are mapped to black (0.0) and values >= 0.5
    // are mapped to white (1.0).

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            
            
            float gs=original(i,j)[0];
            float bw;

            if ((gs - static_cast<int>(gs)) < 0.5f)
                bw = 0.0f;
            else
                bw = 1.0f;
            
            converted(i,j)[0]=bw;
            // converted(i, j)[0] = ...

        }
    }

    return converted;
}
