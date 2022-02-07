
// https://github.com/p-ranav/argparse

#include "haversine.h"
#include "zipcodes.h"

#include <argparse/argparse.hpp>

int main(int argc, char** argv)
{
    argparse::ArgumentParser program("haversine");

    // The start zip, as an integer
    program.add_argument("-s", "--start_zip")
        .help("the starting zip code")
        .required()
        .scan<'i', int>();

    // The end zip, also as an integer
    program.add_argument("-e", "--end_zip")
        .help("the ending zip code")
        .required()
        .scan<'i', int>();

    program.add_argument("-v", "--verbose")
        .help("increase output verbosity")
        .default_value(false)
        .implicit_value(true);

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    const auto start_zip = program.get<int>("--start_zip");
    const auto end_zip = program.get<int>("--end_zip");

    auto [success, errmessage, zipcodes] = load_zip_codes("zips.csv");

    if (!success)
    {
        std::cerr << "Failure detected when attempting to load zips data\n";
        std::cerr << errmessage.c_str() << std::endl;
        std::exit(1);
    }

    // Get our Latitude and Longitude for each zip code
    const auto ll1 = zipcodes.at(start_zip);
    const auto ll2 = zipcodes.at(end_zip);

    const auto lat1 = ll1.get_latitude();
    const auto lon1 = ll1.get_longitude();
    const auto lat2 = ll2.get_latitude();
    const auto lon2 = ll2.get_longitude();

    const auto distance = calculate_distance(lat1, lon1, lat2, lon2);
    printf("Distance between zips %d and %d is %d kilometers\n", start_zip, end_zip, (int)distance);

    return 0;
}