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
void sort_list(TransportDB* tdb);

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


TransportResult TransportRemoveStation(TransportDB* tdb, int line_id, unsigned int index)
{
    int counter = 0;

    if (tdb == NULL) 
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

    if (request_line->stations == NULL) 
    {
        return TRANSPORT_DOESNT_EXIST;
    } 

    StationsList *prev_sta = NULL;
    StationsList *curr_sta = request_line->stations;

    if (curr_sta->next == NULL) 
    {
        if (index == counter)
        {  
            request_line->stations = NULL;

            free(curr_sta->station_name);
            free(curr_sta);
            
            return TRANSPORT_SUCCESS;
        }
        else 
        {
            return TRANSPORT_DOESNT_EXIST;
        }
    }

    while (curr_sta != NULL) 
    {
        if (index == counter)
        {  
            if (prev_sta == NULL)
            {
                request_line->stations = curr_sta->next;
                free(curr_sta->station_name);
                free(curr_sta);

                return TRANSPORT_SUCCESS;
            }
            else 
            {
                prev_sta->next = curr_sta->next;
                free(curr_sta->station_name);
                free(curr_sta);
            
                return TRANSPORT_SUCCESS;
            }
        }

        prev_sta = curr_sta;
        curr_sta = curr_sta->next;
    
        counter++;
    }
    return TRANSPORT_DOESNT_EXIST;
}


void sort_list(TransportDB* tdb) 
{
    if (tdb == NULL || tdb->head == NULL) 
    {
        return;
    }

    Line *curr_line = tdb->head;
    Line *cmp_line = tdb->head->next;
    Line temp_line;

    while (curr_line != NULL)
    {
        cmp_line = curr_line->next;
        
        while (cmp_line != NULL)
        {
            if (cmp_line->line_id < curr_line->line_id)
            {
                temp_line.line_id = curr_line->line_id;
                curr_line->line_id = cmp_line->line_id;
                cmp_line->line_id = temp_line.line_id;

                temp_line.price = curr_line->price;
                curr_line->price = cmp_line->price;
                cmp_line->price = temp_line.price;

                temp_line.type = curr_line->type;
                curr_line->type = cmp_line->type;
                cmp_line->type = temp_line.type;

                temp_line.stations = curr_line->stations;
                curr_line->stations = cmp_line->stations;
                cmp_line->stations = temp_line.stations;

            }

            cmp_line = cmp_line->next;
        }
        curr_line = curr_line->next;
    }

    return;
}

TransportResult TransportReportLines(TransportDB* tdb, const char *type) 
{
    if (tdb == NULL || type == NULL)
    {
        return TRANSPORT_NULL_ARGUMENTS;
    }

    TransportType requested_type;

    if (strcmp(type, "BUS") == 0) {
        requested_type = BUS;
    } 
    else if (strcmp(type, "METRO") == 0) {
        requested_type = METRO;
    } 
    else if (strcmp(type, "TRAIN") == 0) {
        requested_type = TRAIN;
    } 
    else if (strcmp(type, "ALL") == 0) {
        requested_type = ALL;
    } 
    else {
        return TRANSPORT_INVALID_LINE_TYPE;
    }

    if (tdb->head == NULL) 
    {
        return TRANSPORT_EMPTY;
    }
    
    sort_list(tdb);
    
    Line *curr_line = tdb->head;
    StationsList *curr_station = curr_line->stations;

    int num_stations = 0;
    int found = 0;

    if (requested_type == ALL) 
    {
        while (curr_line != NULL)
        {
            curr_station = curr_line->stations;

            while (curr_station != NULL)
            {
                curr_station = curr_station->next;
                num_stations++;
            }
        
            prog2_report_line(curr_line->line_id, curr_line->type, num_stations, curr_line->price);
            curr_line = curr_line->next;
            num_stations = 0;
        }

        return TRANSPORT_SUCCESS;
    }
            
    else 
    {
        while (curr_line != NULL)
        {
            curr_station = curr_line->stations;

            if (requested_type == curr_line->type)
            {
                while (curr_station != NULL)
                {
                    curr_station = curr_station->next;
                    num_stations++;
                }   
                prog2_report_line(curr_line->line_id, curr_line->type, num_stations, curr_line->price);
                found++;
                num_stations = 0;
            }   
            curr_line = curr_line->next;
        }

        if (found == 0)
        {
            return TRANSPORT_EMPTY;
        }
        return TRANSPORT_SUCCESS;        
    }
}


TransportResult TransportReportStations(TransportDB* tdb, int line_id) 
{


}


TransportResult TransportReportDirections(TransportDB* tdb, const char *from, const char *to) 
{


}

