#include <stdio.h>
#include "prog2_ex2.h"
#include "TransportLL.h"

#define MAGENTA "\033[35m"
#define RESET "\033[0m"

#ifdef DEBUG
#define PRINT_DBG(command) \
    do { \
        printf(MAGENTA "[DEBUG] %s:%d - %s\n" RESET, __func__, __LINE__, #command); \
    } while(0)
#else
#define PRINT_DBG(command)
#endif

#define CHECK_RESULT(command) \
    do { \
        PRINT_DBG(command); \
        TransportResult result = command; \
        if (result != TRANSPORT_SUCCESS) { \
            prog2_report_error_message(result); \
        } \
    } while(0)

int test1(void)
{
    TransportDB* db = TransportCreate();
    if (db == NULL) {
        return 0;
    }

    CHECK_RESULT(TransportAddLine(db, "BUS", 1, 5.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 2, 5.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 300, 5.5));
    CHECK_RESULT(TransportAddLine(db, "BUS", 4, 6.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 5, 4.5));
    CHECK_RESULT(TransportAddLine(db, "BUS", 6, 5.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 7, 5.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 8, 7.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 9, 5.5));
    CHECK_RESULT(TransportAddLine(db, "BUS", 10, 6.0));
    
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 101, 20.0));
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 102, 22.5));
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 103, 25.0));
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 104, 30.0));
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 105, 15.0));
    
    CHECK_RESULT(TransportAddLine(db, "METRO", 201, 10.0));
    CHECK_RESULT(TransportAddLine(db, "METRO", 202, 10.0));
    CHECK_RESULT(TransportAddLine(db, "METRO", 203, 12.0));
    CHECK_RESULT(TransportAddLine(db, "METRO", 204, 10.0));
    CHECK_RESULT(TransportAddLine(db, "METRO", 205, 15.0));


    CHECK_RESULT(TransportAddStation(db, 1, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 1, "Ramat Gan"));
    CHECK_RESULT(TransportAddStation(db, 1, "Bnei Brak"));
    CHECK_RESULT(TransportAddStation(db, 1, "Petah Tikva"));

    CHECK_RESULT(TransportAddStation(db, 2, "Haifa"));
    CHECK_RESULT(TransportAddStation(db, 2, "Krayot"));
    CHECK_RESULT(TransportAddStation(db, 2, "Acre"));

    CHECK_RESULT(TransportAddStation(db, 300, "Jerusalem"));
    CHECK_RESULT(TransportAddStation(db, 300, "Mevaseret Zion"));
    CHECK_RESULT(TransportAddStation(db, 300, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 4, "Ashdod"));
    CHECK_RESULT(TransportAddStation(db, 4, "Ashkelon"));
    CHECK_RESULT(TransportAddStation(db, 4, "Sderot"));

    CHECK_RESULT(TransportAddStation(db, 5, "Eilat"));
    CHECK_RESULT(TransportAddStation(db, 5, "Mitzpe Ramon"));
    CHECK_RESULT(TransportAddStation(db, 5, "Beer Sheva"));

    CHECK_RESULT(TransportAddStation(db, 6, "Netanya"));
    CHECK_RESULT(TransportAddStation(db, 6, "Herzliya"));
    CHECK_RESULT(TransportAddStation(db, 6, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 7, "Bat Yam"));
    CHECK_RESULT(TransportAddStation(db, 7, "Holon"));
    CHECK_RESULT(TransportAddStation(db, 7, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 8, "Rishon LeZion"));
    CHECK_RESULT(TransportAddStation(db, 8, "Ness Ziona"));
    CHECK_RESULT(TransportAddStation(db, 8, "Rehovot"));

    CHECK_RESULT(TransportAddStation(db, 9, "Afula"));
    CHECK_RESULT(TransportAddStation(db, 9, "Tiberias"));
    CHECK_RESULT(TransportAddStation(db, 9, "Safed"));

    CHECK_RESULT(TransportAddStation(db, 10, "Karmiel"));
    CHECK_RESULT(TransportAddStation(db, 10, "Nahariya"));
    CHECK_RESULT(TransportAddStation(db, 10, "Haifa"));

    CHECK_RESULT(TransportAddStation(db, 101, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 101, "Haifa"));
    CHECK_RESULT(TransportAddStation(db, 101, "Nahariya"));

    CHECK_RESULT(TransportAddStation(db, 102, "Jerusalem"));
    CHECK_RESULT(TransportAddStation(db, 102, "Ben Gurion Airport"));
    CHECK_RESULT(TransportAddStation(db, 102, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 102, "Herzliya"));

    CHECK_RESULT(TransportAddStation(db, 103, "Beer Sheva"));
    CHECK_RESULT(TransportAddStation(db, 103, "Kiryat Gat"));
    CHECK_RESULT(TransportAddStation(db, 103, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 201, "Petah Tikva"));
    CHECK_RESULT(TransportAddStation(db, 201, "Bnei Brak"));
    CHECK_RESULT(TransportAddStation(db, 201, "Ramat Gan"));
    CHECK_RESULT(TransportAddStation(db, 201, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 201, "Bat Yam"));

    CHECK_RESULT(TransportAddStation(db, 202, "Herzliya"));
    CHECK_RESULT(TransportAddStation(db, 202, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 202, "Holon"));
    CHECK_RESULT(TransportAddStation(db, 202, "Rishon LeZion"));

    CHECK_RESULT(TransportRemoveStation(db, 202, 2)); // Removing "Tel Aviv" from line 202
    CHECK_RESULT(TransportRemoveStation(db, 202, 0)); // Removing "Herzliya" from line 202

    CHECK_RESULT(TransportAddStation(db, 203, "Kfar Saba"));
    CHECK_RESULT(TransportAddStation(db, 203, "Hod Hasharon"));
    CHECK_RESULT(TransportAddStation(db, 203, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 203, "Ra'anana"));
    CHECK_RESULT(TransportAddStation(db, 203, "Herzliya"));

    CHECK_RESULT(TransportReportLines(db, "BUS"));
    CHECK_RESULT(TransportReportLines(db, "METRO"));
    
    CHECK_RESULT(TransportReportStations(db, 1));
    CHECK_RESULT(TransportReportStations(db, 101));
    CHECK_RESULT(TransportReportStations(db, 201));
    CHECK_RESULT(TransportReportStations(db, 300));
    CHECK_RESULT(TransportReportStations(db, 102));

    CHECK_RESULT(TransportReportDirections(db, "Tel Aviv", "Haifa"));
    CHECK_RESULT(TransportReportDirections(db, "Jerusalem", "Tel Aviv"));
    CHECK_RESULT(TransportReportDirections(db, "Petah Tikva", "Tel Aviv"));
    CHECK_RESULT(TransportReportDirections(db, "Beer Sheva", "Tel Aviv"));
    
    CHECK_RESULT(TransportRemoveLine(db, 1));
    CHECK_RESULT(TransportRemoveLine(db, 101));
    CHECK_RESULT(TransportRemoveLine(db, 201));
  
    CHECK_RESULT(TransportReportLines(db, "ALL"));
    
    TransportDestroy(db);

    return 0;
}


int test2(void)
{
    TransportDB* db = TransportCreate();
    if (db == NULL) {
        return 1;
    }

    CHECK_RESULT(TransportAddLine(db, "BUS", 601, 9.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 605, 9.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 29, 5.5));
    CHECK_RESULT(TransportAddLine(db, "BUS", 15, 6.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 8, 4.5));
    CHECK_RESULT(TransportAddLine(db, "BUS", 149, 8.0));
    CHECK_RESULT(TransportAddLine(db, "BUS", 947, 24.5));
    
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 50, 18.0));
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 51, 35.5));
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 52, 40.0));
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 53, 20.0));
    
    CHECK_RESULT(TransportAddLine(db, "METRO", 1, 12.0));
    CHECK_RESULT(TransportAddLine(db, "METRO", 2, 12.0));
    CHECK_RESULT(TransportAddLine(db, "METRO", 3, 12.0));
    CHECK_RESULT(TransportAddLine(db, "METRO", 4, 15.0));

    CHECK_RESULT(TransportAddLine(db, "AIRPLANE", 777, 200.0)); // TRANSPORT_INVALID_LINE_TYPE
    CHECK_RESULT(TransportAddLine(db, "BUS", -10, 5.0));        // TRANSPORT_INVALID_LINE_NUMBER
    CHECK_RESULT(TransportAddLine(db, "TRAIN", 50, 20.0));      // TRANSPORT_ALREADY_EXISTS
    CHECK_RESULT(TransportAddLine(db, "METRO", 100, -5.0));     // TRANSPORT_INVALID_PRICE
    CHECK_RESULT(TransportRemoveLine(db, 888));                 // TRANSPORT_DOESNT_EXIST
    CHECK_RESULT(TransportAddStation(db, 888, "Nowhere"));      // TRANSPORT_DOESNT_EXIST
    CHECK_RESULT(TransportAddStation(db, -5, "Invalid"));       // TRANSPORT_INVALID_LINE_NUMBER
    CHECK_RESULT(TransportReportStations(db, 777));             // TRANSPORT_DOESNT_EXIST
    CHECK_RESULT(TransportReportStations(db, -1));              // TRANSPORT_INVALID_LINE_NUMBER

    CHECK_RESULT(TransportAddStation(db, 601, "Netanya"));
    CHECK_RESULT(TransportAddStation(db, 601, "Herzliya"));
    CHECK_RESULT(TransportAddStation(db, 601, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 605, "Netanya"));
    CHECK_RESULT(TransportAddStation(db, 605, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 29, "Netanya"));
    CHECK_RESULT(TransportAddStation(db, 29, "Ra'anana"));
    CHECK_RESULT(TransportAddStation(db, 29, "Kfar Saba"));
    CHECK_RESULT(TransportAddStation(db, 29, "Herzliya"));

    CHECK_RESULT(TransportAddStation(db, 15, "Netanya"));
    CHECK_RESULT(TransportAddStation(db, 15, "Hadera"));

    CHECK_RESULT(TransportAddStation(db, 8, "Netanya North"));
    CHECK_RESULT(TransportAddStation(db, 8, "Netanya Center"));
    CHECK_RESULT(TransportAddStation(db, 8, "Netanya South"));

    CHECK_RESULT(TransportAddStation(db, 149, "Kfar Saba"));
    CHECK_RESULT(TransportAddStation(db, 149, "Ra'anana"));
    CHECK_RESULT(TransportAddStation(db, 149, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 947, "Haifa"));
    CHECK_RESULT(TransportAddStation(db, 947, "Netanya"));
    CHECK_RESULT(TransportAddStation(db, 947, "Ra'anana"));
    CHECK_RESULT(TransportAddStation(db, 947, "Jerusalem"));

    CHECK_RESULT(TransportAddStation(db, 50, "Binyamina"));
    CHECK_RESULT(TransportAddStation(db, 50, "Hadera"));
    CHECK_RESULT(TransportAddStation(db, 50, "Netanya"));
    CHECK_RESULT(TransportAddStation(db, 50, "Herzliya"));
    CHECK_RESULT(TransportAddStation(db, 50, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 51, "Nahariya"));
    CHECK_RESULT(TransportAddStation(db, 51, "Acre"));
    CHECK_RESULT(TransportAddStation(db, 51, "Haifa"));
    CHECK_RESULT(TransportAddStation(db, 51, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 51, "Modi'in"));

    CHECK_RESULT(TransportAddStation(db, 52, "Carmiel"));
    CHECK_RESULT(TransportAddStation(db, 52, "Haifa"));
    CHECK_RESULT(TransportAddStation(db, 52, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 52, "Beer Sheva"));

    CHECK_RESULT(TransportAddStation(db, 1, "Petah Tikva"));
    CHECK_RESULT(TransportAddStation(db, 1, "Bnei Brak"));
    CHECK_RESULT(TransportAddStation(db, 1, "Ramat Gan"));
    CHECK_RESULT(TransportAddStation(db, 1, "Tel Aviv"));

    CHECK_RESULT(TransportAddStation(db, 2, "Holon"));
    CHECK_RESULT(TransportAddStation(db, 2, "Tel Aviv"));
    CHECK_RESULT(TransportAddStation(db, 2, "Herzliya"));

    CHECK_RESULT(TransportAddStation(db, 3, "Rishon LeZion"));
    CHECK_RESULT(TransportAddStation(db, 3, "Bat Yam"));
    CHECK_RESULT(TransportAddStation(db, 3, "Tel Aviv"));

    CHECK_RESULT(TransportReportLines(db, "ALL"));
    CHECK_RESULT(TransportReportLines(db, "BUS"));
    CHECK_RESULT(TransportReportLines(db, "TRAIN"));
    CHECK_RESULT(TransportReportLines(db, "METRO"));
    
    CHECK_RESULT(TransportReportStations(db, 601));
    CHECK_RESULT(TransportReportStations(db, 29));
    CHECK_RESULT(TransportReportStations(db, 947));
    CHECK_RESULT(TransportReportStations(db, 50));
    CHECK_RESULT(TransportReportStations(db, 51));
    CHECK_RESULT(TransportReportStations(db, 1));
    CHECK_RESULT(TransportReportStations(db, 2));

    CHECK_RESULT(TransportReportDirections(db, "Netanya", "Tel Aviv"));
    CHECK_RESULT(TransportReportDirections(db, "Haifa", "Tel Aviv"));
    CHECK_RESULT(TransportReportDirections(db, "Petah Tikva", "Tel Aviv"));
    CHECK_RESULT(TransportReportDirections(db, "Netanya", "Jerusalem"));
    CHECK_RESULT(TransportReportDirections(db, "Binyamina", "Herzliya"));
    
    CHECK_RESULT(TransportReportDirections(db, "Jerusalem", "Nahariya")); 
    CHECK_RESULT(TransportReportDirections(db, "Eilat", "Tiberias"));

    CHECK_RESULT(TransportRemoveLine(db, 601));
    CHECK_RESULT(TransportRemoveLine(db, 605));
    CHECK_RESULT(TransportRemoveLine(db, 50));
    CHECK_RESULT(TransportRemoveLine(db, 1));
    
    CHECK_RESULT(TransportReportLines(db, "ALL"));
    CHECK_RESULT(TransportReportDirections(db, "Netanya", "Tel Aviv"));
    
    CHECK_RESULT(TransportRemoveLine(db, 601));
    CHECK_RESULT(TransportRemoveLine(db, 50));

    TransportDestroy(db);

    return 0;
}



int main(void)
{
#ifdef TEST1
    return test1();
#endif
#ifdef TEST2
    return test2();
#endif

return 0;
}
