#include "CSVReader.h"
#include <iostream>

int main(int argc, char* argv[])
{
    //for(size_t i = 0; i < argc; i++) { std::cout << argv[i] << '\n'; }

    CSVReader csv(argv[1]);

    for(auto row : csv) { std::cout << row.getLine() << std::endl; }

    //std::cout << "foo" << std::endl;
    return 0;
}
