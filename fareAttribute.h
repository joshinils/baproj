#pragma once

class FareAttribute
{
public:
    FareAttribute();
    ~FareAttribute();

private:
    /** Identifies a fare class. */
    int fare_id; /// Required

    /** Fare price, in the unit specified by currency_type. */
    /** Non-negative float */ double price; /// Required

    /** Currency used to pay the fare. */
    /** Currency code */ int currency_type; /// Required

    /** Indicates when the fare must be paid. Valid options are:

        0 - Fare is paid on board.
        1 - Fare must be paid before boarding.*/
    enum class payment_method_enum
    {
        OnBoard        = 0, /// Fare is paid on board.
        BeforeBoarding = 1, /// Fare must be paid before boarding.
    };
    payment_method_enum payment_method; /// Required

    /** Indicates the number of transfers permitted on this fare. The fact that this field can be left empty is an
    exception to the requirement that a Required field must not be empty. Valid options are:

        0 - No transfers permitted on this fare.
        1 - Riders may transfer once.
        2 - Riders may transfer twice.
        empty - Unlimited transfers are permitted.*/
    enum class transfers_enum
    {
        None  = 0, /// No transfers permitted on this fare.
        Once  = 1, /// Riders may transfer once.
        Twice = 2, /// Riders may transfer twice.
        Infty, /// = empty - Unlimited transfers are permitted.
    };
    transfers_enum transfers; /// Required

    /** Identifies the relevant agency for a fare. This field is required for datasets with multiple agencies defined
     * in agency.txt, otherwise it is optional. */
    /** ID referencing agency.agency_id */ int agency_id; /// Conditionally Required

    /** Length of time in seconds before a transfer expires. When transfers=0 this field can be used to indicate how
     * long a ticket is valid for or it can can be left empty. */
    unsigned int transfer_duration; /// Optional
};
