#include "source1.hpp"
#include "source2.hpp"

//Defining a non-inline function (sum) in a header file causes multiple definition errors at link time, because every .cpp file that includes the header will generate its own copy of sum.

//we can fix it by making it inline


int main() {
    a();
    b();
}
