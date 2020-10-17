#pragma once
#include <string>
class Feed_info
{
public:
    Feed_info();
    ~Feed_info();

private:
    /* Full name of the organization that publishes the dataset. This might be the same as one of the
     * agency.agency_name values. */
    std::string feed_publisher_name; // Required

    /* URL of the dataset publishing organization's website. This may be the same as one of the agency.agency_url
     * values. */
    std::string feed_publisher_url; // Required

    /* Default language for the text in this dataset. This setting helps GTFS consumers choose capitalization rules
    and other language-specific settings for the dataset.

    To define another language, use the language field in translations.txt.

    Multilingual datasets might be the default language with the original text in multiple languages. In such cases, use the ISO 639-2 language code mul in the feed_lang field. Provide a translation for each of the languages used in the dataset in translations.txt. If all of the original text in the dataset is in the same language, don't use mul.

    For example, a dataset in Switzerland might set the original stops.stop_name field populated with stop names in different languages. Each stop name is written in accordance with the dominant language in that stop’s geographic location. Stop names include Genève for the French-speaking city of Geneva, Zürich for the German-speaking city of Zurich, and Biel/Bienne for the bilingual city of Biel/Bienne. Set feed_lang=mul and provide the following translations in translations.txt:German: ""Genf,"" ""Zürich,"" and ""Biel""
    French: ""Genève,"" ""Zurich,"" and ""Bienne""
    Italian: ""Ginevra,"" ""Zurigo,"" and ""Bienna""
    English: ""Geneva,"" ""Zurich,"" and ""Biel/Bienne""*/
    std::string feed_lang; // Required

    /* Defines the language used when the data consumer doesn’t know the language of the rider. It's often defined as
     * en, English. */
    std::string default_lang; // Optional

    /* The dataset provides complete and reliable schedule information for service in the period from the beginning of
     * the feed_start_date day to the end of the feed_end_date day. Both days can be left empty if unavailable. The
     * feed_end_date date must not precede the feed_start_date date if both are given. Dataset providers are encouraged
     * to give schedule data outside this period to advise of likely future service, but dataset consumers should treat
     * it mindful of its non-authoritative status. If feed_start_date or feed_end_date extend beyond the active calendar
     * dates defined in calendar.txt and calendar_dates.txt, the dataset is making an explicit assertion that there is
     * no service for dates within the feed_start_date to feed_end_date range but not included in the active calendar
     * dates. */
    /* Date */ int feed_start_date; // Optional

    /* Refer to the feed_start_date row in this table. */
    /* Date */ int feed_end_date; // Optional

    /* String that indicates the current version of their GTFS dataset. GTFS-consuming applications can display this
     * value to help dataset publishers determine whether the latest dataset has been incorporated. */
    std::string feed_version; // Optional

    /* Email address for communication regarding the GTFS dataset and data publishing practices. feed_contact_email is
     * a technical contact for GTFS-consuming applications. Provide customer service contact information through
     * agency.txt. */
    std::string feed_contact_email; // Optional

    /* URL for contact information, a web-form, support desk, or other tools for communication regarding the GTFS
     * dataset and data publishing practices. feed_contact_url is a technical contact for GTFS-consuming applications.
     * Provide customer service contact information through agency.txt. */
    std::string feed_contact_url; // Optional
};
