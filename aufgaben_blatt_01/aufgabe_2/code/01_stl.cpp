


#include "Point3D.hpp"
#include "LineStrip3D.hpp"

#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <algorithm>

int main()
{

    ///////
    // TODO
    // Create a container for linestrips
    
    //std::vector<LineStrip3D> is ideal because it dynamically resizes to hold any number of line strips. It also allows fast sequential access and sorting, and we don’t need deletions.
    std::vector<LineStrip3D> lines;

    ///////
    // TODO
    // Add three linestrips to the container and add a couple of points to each linestrip
    LineStrip3D line1;
    line1.addPoint(Point3D(0,0,0));
    line1.addPoint(Point3D(0,3,0));
  
    LineStrip3D line2;
    line2.addPoint(Point3D(0,0,0));
    line2.addPoint(Point3D(1,0,0));
    line2.addPoint(Point3D(1,1,0));


    LineStrip3D line3;
    line3.addPoint(Point3D(0,0,0));
    line3.addPoint(Point3D(1,1,1));
    line3.addPoint(Point3D(2,2,2));

    lines.push_back(line1);
    lines.push_back(line2);
    lines.push_back(line3);


    std::cout << "==================================" << std::endl;
    std::cout << "Length of all linestrips:" << std::endl;

    ///////
    // TODO
    // Print the length of all line strips on the command line
    
    std::cout << "Lengths before sorting:\n";
    for (const auto& line : lines)
        std::cout << line.computeLength() << "\n";


    std::cout << "==================================" << std::endl;
    std::cout << "Length of all linestrips (sorted):" << std::endl;

    ///////
    // TODO
    // Sort the line strips in the container based on their length.
    std::sort(lines.begin(), lines.end());
    // For validation, print the lengths of all linestrips on the command line one more time.
    
    std::cout << "Lengths after sorting:\n";
    for (const auto& line : lines)
        std::cout << line.computeLength() << "\n";

    return 0;

    return EXIT_SUCCESS;


}
