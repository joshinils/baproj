#include "GTFS.h"
#include "TimePoint.h"
#include "stopwatch.h"

int main(int argc, char* argv[])
try
{
    Stopwatch sw(__PRETTY_FUNCTION__);
    /*
    /// test timepoint
    std::string s("12:34:56");
    TimePoint tp(s);
    std::cout << tp << '\n';

    std::string s2("456789");
    TimePoint tp2(s2);
    std::cout << tp2 << '\n';
    return 0;
    */


    //for(size_t i = 0; i < argc; i++) { std::cout << argv[i] << '\n'; }

    //CSVReader csv(argv[1]);
    GTFS data("BVG_VBB_bereichsscharf");

    sw.printTime("after creating GTFS obj");

    auto G = data.makeGraph();

    std::cout << G.anzKnoten() << '\n';

    sw.printTime("after creating generated Graph");

    ///    std::cout << G << std::endl;
    G.saveToFile("test.gra");

    //std::cout << "foo" << std::endl;
    return 0;
}
/// catch(const std::exception& e)
/// {
///     std::cerr << e.what() << '\n';
/// }
catch(const std::string& e)
{
    std::cerr << "aborting! std::string thrown:\n";
    std::cerr << e << '\n';
}
