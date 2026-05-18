#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TransportLL.h"

typedef struct StationsList_t
{
    char *station_name;
    struct StationsList_t *next;
} StationsList;

typedef struct Line_t
{
    int line_id;
    float price;
    TransportType type;
    StationsList *stations;
    struct Line_t *next;
    
} Line;

struct TransportDB_t
{
    Line *head;
};

typedef enum {
    CMD_ADD_LINE,
    CMD_REMOVE_LINE,
    CMD_ADD_STATION_TO_LINE,
    CMD_REPORT_LINES,
    CMD_REPORT_STATIONS,
    CMD_REPORT_DIRECTIONS,
    CMD_COMMENT,
    CMD_UNKNOWN
} CommandType;

void configure_io_from_args(int argc, char *argv[] ,FILE **in ,FILE **out);
CommandType identify_command(char *tokens[], int count);
Line *add_line(char *tokens[], int count, Line *allLines);
void remove_line(char *tokens[], int count, Line *allLines);
void add_station_to_line(char *tokens[], int count, Line *allLines);

Line *find_line(TransportDB* tdb, int line_id);

TransportDB *TransportCreate(void)
{
   TransportDB *tdb = (TransportDB*)malloc(sizeof(TransportDB));
   if(tdb == NULL)
   {
    return NULL;
   }

}


void TransportDestroy(TransportDB *tdb)
{
    while(tdb->next!=NULL)
    {
        free(tdb)
    }
}


TransportResult TransportAddLine(TransportDB* tdb, const char *type, int line_id, float price)
{


}


// TransportDB *add_line(char *tokens[], int count, TransportDB *allLines)
// {
//     Line *newNode = malloc(sizeof(Line));
//     if (newNode == NULL)
//     {
//         prog2_report_error_message(TRANSPORT_OUT_OF_MEMORY);
//         return allLines;
//     }
//     newNode->stations_list = NULL;
//     if (strcmp(tokens[2], "BUS") == 0)
//         newNode->type = BUS;
//     else if (strcmp(tokens[2], "TRAIN") == 0)
//         newNode->type = TRAIN;
//     else if (strcmp(tokens[2], "METRO") == 0)
//         newNode->type = METRO;
//     else{
//         prog2_report_error_message(TRANSPORT_INVALID_ARGUMENTS);
//         free(newNode);
//         return allLines;
//     }
//     newNode->line_id = atoi(tokens[3]);
//     newNode->num_of_stations = atoi(tokens[4]);
//     newNode->price = atof(tokens[5]);
//     newNode->next = allLines;
//     return newNode;
// }



    if (newNode == NULL)
    {
        prog2_report_error_message(TRANSPORT_OUT_OF_MEMORY);
        return allLines;
    }
    newNode->stations_list = NULL;
    if (strcmp(tokens[2], "BUS") == 0)
        newNode->type = BUS;
    else if (strcmp(tokens[2], "TRAIN") == 0)
        newNode->type = TRAIN;
    else if (strcmp(tokens[2], "METRO") == 0)
        newNode->type = METRO;
    else{
        prog2_report_error_message(TRANSPORT_INVALID_ARGUMENTS);
        free(newNode);
        return allLines;
    }
    newNode->line_id = atoi(tokens[3]);
    newNode->num_of_stations = atoi(tokens[4]);
    newNode->price = atof(tokens[5]);

    newNode->next = allLines;
    return newNode;
}

void remove_line(char *tokens[], int count, Line *allLines)

TransportResult TransportRemoveLine(TransportDB* tdb, int line_id)
{
    
}


void add_station_to_line(char *tokens[], int count, Line *allLines)

{
    
}


Line *find_line(TransportDB* tdb, int line_id)
{
    if (tdb == NULL) 
    {
        return NULL;
    }

    Line *curr = tdb->head;

    while (curr != NULL) 
    {
        if (curr->line_id == line_id)
        {
            return curr; 
        } 
        curr = curr->next;
    }
    return NULL;

}


TransportResult TransportAddStation(TransportDB* tdb, int line_id, const char *new_station_name) 
{
    if (tdb == NULL || new_station_name == NULL) 
    {  
        return TRANSPORT_NULL_ARGUMENTS;
    }

    if (line_id <= 0) 
    {
        return TRANSPORT_INVALID_LINE_NUMBER;
    }

    Line *request_line = find_line(tdb, line_id);

    if (request_line == NULL) 
    {
        return TRANSPORT_DOESNT_EXIST;
    }

    StationsList *new_station;

    new_station = (StationsList*)malloc(sizeof(StationsList));
    if (new_station == NULL)
    {
        return TRANSPORT_OUT_OF_MEMORY;
    }

    new_station->station_name = (char*)malloc(sizeof(char) * (strlen(new_station_name) + 1));
    if (new_station->station_name  == NULL)
    {
        free(new_station);
        return TRANSPORT_OUT_OF_MEMORY;
    }

    StationsList *curr_sta = request_line->stations;

    strcpy(new_station->station_name, new_station_name);
    new_station->next = NULL;

    if (request_line->stations == NULL) 
    {
        request_line->stations = new_station;

        return TRANSPORT_SUCCESS;
    }

    while (curr_sta != NULL)
    {
        if (curr_sta->next == NULL)
        {
            curr_sta->next = new_station;
            
            return TRANSPORT_SUCCESS;
        }
        
        curr_sta = curr_sta->next;
    }

    return TRANSPORT_SUCCESS;
}


void TransportRemoveStation(TransportDB* tdb, int line_id, unsigned int index)
{
    
}


void TransportReportLines(TransportDB* tdb, const char *station) 
{

}


void TransportReportStations(TransportDB* tdb, int line_id) 
{


}


void TransportReportDirections(TransportDB* tdb, const char *from, const char *to) 
{


}

