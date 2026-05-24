#ifndef __MOOVITLIST__
#define __MOOVITLIST__

#include "prog2_ex2.h"

typedef struct TransportDB_t TransportDB;

TransportDB *TransportCreate(void);
void TransportDestroy(TransportDB *tdb);

TransportResult TransportAddLine(TransportDB* tdb, const char *type, int line_id, float price);
TransportResult TransportRemoveLine(TransportDB* tdb, int line_id);
TransportResult TransportAddStation(TransportDB* tdb, int line_id, const char *station);
TransportResult TransportRemoveStation(TransportDB* tdb, int line_id, unsigned int index);
TransportResult TransportReportLines(TransportDB* tdb, const char *type);
TransportResult TransportReportStations(TransportDB* tdb, int line_id);
TransportResult TransportReportDirections(TransportDB* tdb, const char *from, const char *to);

#endif