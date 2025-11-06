#ifndef LineStrip3D_hpp
#define LineStrip3D_hpp

#include <array>
#include <list>
#include <vector>
#include <iostream>

#include "Point3D.hpp"

class LineStrip3D
{
public:
    /** Comparison operator. */
    bool operator<(LineStrip3D const& rhs) const;

    /** Adds a point to the end of the line strip. */
    void addPoint(Point3D p);

    /** Removes the point from the line strip with the given index. */
    void removePoint(size_t idx);

    /** Returns the number of points that make up the line strip. */
    size_t getPointCount() const;

    /** Returns the length of the line strip, that is, the sum of the lengths of all segements.*/
    float computeLength() const;

private:
    ///////
    // TODO
    // Add a container for storing the line strip's points
    //The line strip can have any number of points, so we need a dynamically resizable container.
    //std::vector<Point3D> is the best choice because it can grow dynamically as more points are added.

    //For a LineStrip3D, you almost always traverse sequentially to compute length, so vector is faster and simpler than a list, even tough in list you can delete easier(i.e from the middle)
    std::vector <Point3D> point;

};

#endif // !LineStrip3D_hpp
