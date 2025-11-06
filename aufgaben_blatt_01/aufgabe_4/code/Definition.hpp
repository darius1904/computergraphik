// header file
#ifndef DEFINITION_H
#define DEFINITION_H

//we can fix it by making the function inline
//inline tells the compiler: “It’s okay if multiple translation units define this function; merge them at link time.”

inline int sum(int f, int g)
{
    return f + g;
}
#endif
