#include "CSVReader.h"
#include <iomanip>
#include <iostream>

void printCSV(const CSVReader& csv)
{
    int limit_out = 0;
    int max_out   = 3;

    std::cout << csv.getFilename() << " \tcontains " << csv.rowCount() << " rows:\n";

    for(size_t i = 0; i < csv.getHeader().size(); i++)
    {
        if(i + 1 < csv.getHeader().size())
            std::cout << std::left << std::setw(csv.getPrintWidth(i) + 8)
                      << "\u201C" + csv.getHeader()[i] + "\u201D" + ", ";
        else
            std::cout << std::left << std::setw(csv.getPrintWidth(i) + 6) << "\u201C" + csv.getHeader()[i] + "\u201D";
    }
    std::cout << "\n";

    for(auto row : csv)
    {
        if(limit_out++ > max_out) break;
        for(size_t i = 0; i < row.size(); i++)
        {
            if(i + 1 < row.size())
                std::cout << std::left << std::setw(csv.getPrintWidth(i) + 8) << "\u201C" + row[i] + "\u201D" + ", ";
            else
                std::cout << std::left << std::setw(csv.getPrintWidth(i) + 6) << "\u201C" + row[i] + "\u201D";
        }
        std::cout << "\n";
    }
    std::cout << '\n';
}

int main(int argc, char* argv[])
{
    //for(size_t i = 0; i < argc; i++) { std::cout << argv[i] << '\n'; }

    //CSVReader csv(argv[1]);

    CSVReader agency("BVG_VBB_bereichsscharf/agency.txt");
    printCSV(agency);

    CSVReader calendar_dates("BVG_VBB_bereichsscharf/calendar_dates.txt");
    printCSV(calendar_dates);

    CSVReader calendar("BVG_VBB_bereichsscharf/calendar.txt");
    printCSV(calendar);

    CSVReader frequencies("BVG_VBB_bereichsscharf/frequencies.txt");
    printCSV(frequencies);

    CSVReader pathways("BVG_VBB_bereichsscharf/pathways.txt");
    printCSV(pathways);

    CSVReader routes("BVG_VBB_bereichsscharf/routes.txt");
    printCSV(routes);

    CSVReader shapes("BVG_VBB_bereichsscharf/shapes.txt");
    printCSV(shapes);

    CSVReader stops("BVG_VBB_bereichsscharf/stops.txt");
    printCSV(stops);

    CSVReader stop_times("BVG_VBB_bereichsscharf/stop_times.txt");
    printCSV(stop_times);

    CSVReader transfers("BVG_VBB_bereichsscharf/transfers.txt");
    printCSV(transfers);

    CSVReader trips("BVG_VBB_bereichsscharf/trips.txt");
    printCSV(trips);


    //std::cout << "foo" << std::endl;
    return 0;
}
