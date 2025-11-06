#include <iostream>
#include <cmath>
#define pi 3.14

///////
// TODO
// Write a function that computes the area of a circle given its radius as input.


float calculate_cirle_area(float r)
{
    return pi*r*r;
}


int main()
{
    float radius;

    std::cout << "Insert circle radius:" << std::endl;

    ///////
    // TODO
    // Get user input from the command line and store it in radius.
    // Check if input is valid.
    
    std::cin >> radius;
    if (std::cin.fail() || radius < 0) {
        std::cerr << "Invalid input. Please enter a non-negative number." << std::endl;
        return 1;
    }
    

    ///////
    // TODO
    // Call the function circlearea and output the computed value to the command line.
    
    float area = calculate_cirle_area(radius);
    std::cout << "Area of the circle: " << area << std::endl;

}
