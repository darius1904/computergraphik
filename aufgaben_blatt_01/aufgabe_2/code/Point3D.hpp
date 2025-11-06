#ifndef Point3D_hpp
#define Point3D_hpp

#include <array>
#include <list>
#include <vector>


struct Point3D
{
    ///////
    //
    // TODO
    // Implement the constructor

    
    
    Point3D(float x = 0.0, float y = 0.0, float z = 0.0) {
        
        coord[0] = x;
        coord[1] = y;
        coord[2] = z;
    }

    ///////
    // TODO
    // Implement access to the three coordinate values.
    float x() const { return coord[0]; }
    float y() const { return coord[1]; }
    float z() const { return coord[2]; }

   
    inline void setX(float x) { coord[0] = x; }
    inline void setY(float y) { coord[1] = y; }
    inline void setZ(float  z) { coord[2] = z; }

private:
    ///////
    // TODO
    // Use a suitable STL container to store the three values of a point in 3d space.
    //I chose std::array because a 3D point always has exactly three coordinates, so a fixed-size container is ideal. It provides fast, contiguous access and is simpler and more memory-efficient than vector or list.
    
    std::array <float,3> coord;

};

#endif // !Point3D_hpp
