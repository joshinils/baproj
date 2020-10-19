#include "routes.h"


Routes::Routes(std::string route_id,
               std::optional<int> agency_id,
               std::optional<std::string> route_short_name,
               std::optional<std::string> route_long_name,
               std::optional<std::string> route_desc,
               route_type_enum route_type,
               std::optional<std::string> route_url,
               std::optional<std::string> route_color,
               std::optional<std::string> route_text_color,
               std::optional<unsigned int> route_sort_order,
               continuous_pickup_enum continuous_pickup,
               continuous_drop_off_enum continuous_drop_off)
    : route_id(route_id)
    , agency_id(agency_id)
    , route_short_name(route_short_name)
    , route_long_name(route_long_name)
    , route_desc(route_desc)
    , route_type(route_type)
    , route_url(route_url)
    , route_color(route_color)
    , route_text_color(route_text_color)
    , route_sort_order(route_sort_order)
    , continuous_pickup(continuous_pickup)
    , continuous_drop_off(continuous_drop_off)
{
    // int route_id;
    // std::optional<int> agency_id;
    // std::optional<std::string> route_short_name;
    // std::optional<std::string> route_long_name;
    // std::optional<std::string> route_desc;
    // route_type_enum route_type;
    // std::optional<std::string> route_url;
    // std::optional<std::string> route_color;
    // std::optional<std::string> route_text_color;
    // std::optional<unsigned int> route_sort_order;
    // continuous_pickup_enum continuous_pickup     = continuous_pickup_enum::Unset;
    // continuous_drop_off_enum continuous_drop_off = continuous_drop_off_enum::Unset;
}

Routes::~Routes() { }
