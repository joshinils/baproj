#include "GTFS.h"


int main(int argc, char* argv[])
try
{
    //for(size_t i = 0; i < argc; i++) { std::cout << argv[i] << '\n'; }

    //CSVReader csv(argv[1]);
    GTFS data("BVG_VBB_bereichsscharf");

    //std::cout << "foo" << std::endl;
    return 0;
}
// catch(const std::exception& e)
// {
//     std::cerr << e.what() << '\n';
// }
catch(const std::string& e)
{
    std::cerr << "aborting! std::string thrown:\n";
    std::cerr << e << '\n';
}
