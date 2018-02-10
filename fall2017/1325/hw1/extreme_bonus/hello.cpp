#include <iostream>
#include <stdlib.h>

int main()
{
    char * name;
    
#ifdef WIN32
    name = getenv("USERNAME");
#else
    name = getenv("USER");
#endif
    std::cout << "Hello, " << name << "!" << std::endl;
    return 0;
}
