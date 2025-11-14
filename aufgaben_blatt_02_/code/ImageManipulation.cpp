#include "ImageManipulation.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

cg::image<cg::color_space_t::HSV> cg::image_manipulation::modify_in_hsv(const image<color_space_t::HSV>& original)
{
    // Convert RGB to HSV
    cg::image<cg::color_space_t::HSV> modified(original.get_width(), original.get_height());

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            const float h = original(i, j)[0];
            const float s = original(i, j)[1];
            const float v = original(i, j)[2];

            float hNew = h, sNew = s, vNew = v;

            ////////
            // TODO:
            // Create a Color-Key-Effect image by
            // 1. Rotating the hue by 30 degrees
            
            hNew = h + 30.0f;
            if (hNew >= 360.0f)
                hNew -= 360.0f;
            
            // 2. Setting the saturation to 90 % of its previous value
            //    for all pixels whose shifted and normalized hue lies
            //    between [50,100] degree.
            // 3. Setting the lightness value to 70 % of its previous value
            //    for all pixels whose shifted and normalized hue lies
            //    between [50,100] degree.
            // 4. Setting the saturation to zero for all other pixels.
            // 5. Setting the lightness value to 80 % of its previous value
            //    for all other pixels.
            // ...
            
            bool inRange = (hNew >= 50.0f && hNew <= 100.0f);
            
            
            if (inRange)
           {
               // 2. Saturation *= 0.9
               sNew = s * 0.9f;

               // 3. Value (lightness) *= 0.7
               vNew = v * 0.7f;
           }
           else
           {
               // 4. Saturation = 0
               sNew = 0.0f;

               // 5. Value *= 0.8
               vNew = v * 0.8f;
           }

            // ...

            modified(i, j)[0] = hNew;
            modified(i, j)[1] = sNew;
            modified(i, j)[2] = vNew;
        }
    }

    return modified;
}

