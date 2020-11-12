#pragma once

class FareRule
{
public:
    FareRule();
    ~FareRule();

private:
    /* Identifies a fare class. */
    /* ID referencing fare_attributes.fare_id */ int fare_id; // Required

    /* Identifies a route associated with the fare class. If several routes with the same fare attributes exist,
    create a record in fare_rules.txt for each route.Example: If fare class ""b"" is valid on route ""TSW"" and ""TSE"",
    the fare_rules.txt file would contain these records for the fare class:
     fare_id,route_id
    b,TSW
     b,TSE*/
    /* ID referencing routes.route_id */ int route_id; // Optional

    /* Identifies an origin zone. If a fare class has multiple origin zones, create a record in fare_rules.txt for
     each origin_id.Example: If fare class ""b"" is valid for all travel originating from either zone ""2"" or zone
     ""8"", the fare_rules.txt file would contain these records for the fare class:
     fare_id,...,origin_id
     b,...,2
     b,...,8*/
    /* ID referencing stops.zone_id */ int origin_id; // Optional

    /* Identifies a destination zone. If a fare class has multiple destination zones, create a record in
    fare_rules.txt for each destination_id.Example: The origin_id and destination_id fields could be used together to
    specify that fare class ""b"" is valid for travel between zones 3 and 4, and for travel between zones 3 and 5, the
    fare_rules.txt file would contain these records for the fare class:
    fare_id,...,origin_id,destination_id
    b,...,3,4
     b,...,3,5*/
    /* ID referencing stops.zone_id */ int destination_id; // Optional

    /* Identifies the zones that a rider will enter while using a given fare class. Used in some systems to calculate
    correct fare class. Example: If fare class ""c"" is associated with all travel on the GRT route that passes through
    zones 5, 6, and 7 the fare_rules.txt would contain these records:
     fare_id,route_id,...,contains_id
     c,GRT,...,5
    c,GRT,...,6
    c,GRT,...,7
     Because all contains_id zones must be matched for the fare to apply, an itinerary that passes through
        zones 5 and 6 but not zone 7 would not have fare class ""c"". For more detail, 
        see https://code.google.com/p/googletransitdatafeed/wiki/FareExamples in the GoogleTransitDataFeed 
        project wiki.*/
    /* ID referencing stops.zone_id */ int contains_id; // Optional
};
