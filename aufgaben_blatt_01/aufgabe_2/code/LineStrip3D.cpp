#include "LineStrip3D.hpp"
#include <cmath>

bool LineStrip3D::operator<(LineStrip3D const& rhs) const
{
    ///////
    // TODO
    // Implement comparison based on length.
    return this->computeLength() < rhs.computeLength();

}

void LineStrip3D::addPoint(Point3D p)
{
    ///////
    // TODO
    // Implement adding a given point to the line strip.
    
    point.push_back(p);

}

void LineStrip3D::removePoint(size_t idx)
{
    ///////
    // TODO
    // Implement the removal of the point with the given index.
    
    if (idx >= point.size())
        {
            std::cerr << "Index out of range!\n";
            return;
        }

    point.erase(point.begin() + idx);

}

size_t LineStrip3D::getPointCount() const
{
    ///////
    // TODO
    // Return the number of points of the line strip.
    return point.size();

}

float LineStrip3D::computeLength() const
{
    ///////
    // TODO
    // Implement computation of the line strip's length,
    // that is, the sum of the lengths of all segements.
    double length = 0.0;
    for (size_t i = 1; i < point.size(); ++i)
    {
        double dx = point[i].x() - point[i-1].x();
        double dy = point[i].y() - point[i-1].y();
        double dz = point[i].z() - point[i-1].z();
        length += std::sqrt(dx*dx + dy*dy + dz*dz);
    }
    return length;

}
