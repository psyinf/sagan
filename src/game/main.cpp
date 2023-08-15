#include <stdio.h>
#include <exception>

int main(int argc, char** argv)
try
{
    puts("Hello, World!");
    return 0;
}
catch (const std::exception& e) 
{
    //TODO: Log exception
}
catch (...)
{
    //TODO: Log unknown exception
}
