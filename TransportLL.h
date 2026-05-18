#ifndef __TransportLL__
#define __TransportLL__
#include "prog2_ex2.h"

typedef struct StationsList_t
{
    char *stationsName;
    struct StationsList_t *nextStation;
}StationsList;


typedef struct allLines_t
{
    int line_id;
    float price;
    TransportType type;
    StationsList *stations;
    struct allLines_t *nextLine;
}allLines;


typedef struct TransportDB_t
{
    allLines *Lines;
}TransportDB;


TransportDB *TransportCreate(void);
void TransportDestroy(TransportDB *tdb);
TransportResult is_type_valid(allLines *new_line, const char *type);
TransportResult is_id_valid(allLines *current_line ,allLines *new_line, int line_id);
TransportResult is_price_valid(allLines *new_line, float price);
TransportResult TransportAddLine(TransportDB* tdb, const char *type, int line_id, float price);
TransportResult TransportRemoveLine(TransportDB* tdb, int line_id);


#endif