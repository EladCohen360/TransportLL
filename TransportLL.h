#ifndef __MOOVITLIST__
#define __MOOVITLIST__
#include "prog2_ex2.h"


typedef struct TransportDB_t
{
    int line_id;
    float price;
    TransportType type;
    int num_of_stations;
    char *stations_list;
    struct TransportDB_t *next;
    
}TransportDB;

TransportDB *TransportCreate(void);
void TransportDestroy(TransportDB *tdb);
TransportResult TransportAddLine(TransportDB* tdb, const char *type, int line_id, float price);
TransportResult TransportRemoveLine(TransportDB* tdb, int line_id);


#endif