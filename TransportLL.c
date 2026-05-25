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
Line *add_line(char *tokens[], int count, Line *Line);
void remove_line(char *tokens[], int count, Line *Line);
void add_station_to_line(char *tokens[], int count, Line *Line);

Line *find_line(TransportDB* tdb, int line_id);
void sort_by_id(TransportDB* tdb);
void sort_by_price(TransportDB* tdb);


TransportDB *TransportCreate(void)
{
TransportDB *tdb = (TransportDB*)malloc(sizeof(TransportDB));
    if(tdb == NULL)
        return NULL;
    tdb->head = NULL;
    return tdb;
}


void TransportDestroy(TransportDB *tdb)
{
    if(tdb != NULL)
    {
        
        while(tdb->head != NULL)
        {
            Line *next_line = tdb->head->next;

            StationsList *station = tdb->head->stations;

            while (station!= NULL)
            {
                StationsList *next_station = station->next;
                free(station->station_name);
                free(station);
                station = next_station;
            }
            free(tdb->head);
            tdb->head = next_line;
            
        }
        free(tdb);
    }
    return;   
}


void clear_stations(Line *curr)
{
     while (curr->stations!= NULL)
    {
        StationsList *next_station = curr->stations->next;
        free(curr->stations->station_name);
        free(curr->stations);
        curr->stations = next_station;
    } 
}


TransportResult is_type_valid(Line *new_line, const char *type)
{
    if(strcmp(type ,"BUS")==0)
    {
        new_line->type = BUS;
    }
    else if(strcmp(type ,"METRO")==0)
    {
        new_line->type = METRO;
    }
    else if(strcmp(type ,"TRAIN")==0)
    {
        new_line->type = TRAIN;
    }
    else
    {   
        free(new_line);
        return TRANSPORT_INVALID_LINE_TYPE;
    }
    return TRANSPORT_SUCCESS;
}


TransportResult is_id_valid(Line *current_line ,Line *new_line, int line_id)
{
    while(current_line != NULL)
    {
        if(current_line->line_id==line_id)
        {
            free(new_line);
            return TRANSPORT_ALREADY_EXISTS;
        }
        current_line=current_line->next;
    }
    if(line_id<=0)
        {
            free(new_line);
            return TRANSPORT_INVALID_LINE_NUMBER;
        }
    
    return TRANSPORT_SUCCESS;
}


TransportResult is_price_valid(Line *new_line, float price)
{
    if(price<=0)
    {
        free(new_line);
        return TRANSPORT_INVALID_PRICE;
    }
    new_line->price=price;
    return TRANSPORT_SUCCESS;
}


TransportResult TransportAddLine(TransportDB* tdb, const char *type, int line_id, float price)
{
    if(tdb == NULL || type == NULL)
    {
        return TRANSPORT_NULL_ARGUMENTS;
    }
    
    Line *new_line=(Line *)malloc(sizeof(Line));
    if(new_line==NULL)
        return TRANSPORT_OUT_OF_MEMORY;
    
    new_line->stations = NULL;

    TransportResult res = is_type_valid(new_line, type);
    if(res==TRANSPORT_INVALID_LINE_TYPE)
        return TRANSPORT_INVALID_LINE_TYPE;

    Line *current_line = tdb->head;


    res = is_id_valid(current_line, new_line, line_id);
    if (res != TRANSPORT_SUCCESS)
        return res;

     new_line->line_id=line_id;

    res = is_price_valid(new_line, price);
    if(res==TRANSPORT_INVALID_PRICE)
        return TRANSPORT_INVALID_PRICE;

    new_line->next = tdb->head;
    tdb->head= new_line;

    return TRANSPORT_SUCCESS;
}


TransportResult TransportRemoveLine(TransportDB* tdb, int line_id)
{
    if (tdb == NULL)
    {
        return TRANSPORT_NULL_ARGUMENTS;
    }

    if (line_id <= 0)
    {
        return TRANSPORT_INVALID_LINE_NUMBER;
    }

    if (tdb->head == NULL)
        return TRANSPORT_DOESNT_EXIST;


    Line *curr = tdb->head->next;
    Line *prev = tdb->head;
    if (prev->line_id == line_id)
    {
        clear_stations(prev);
        tdb->head = tdb->head->next;
        free(prev);
        return TRANSPORT_SUCCESS;
    }

    while (curr != NULL)
    {
        if (curr->line_id == line_id)
        {
            clear_stations(curr);
            prev->next = curr->next;
            free(curr);
            return TRANSPORT_SUCCESS;
        }

        prev = curr;
        curr = curr->next;
    }
    return TRANSPORT_DOESNT_EXIST;
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


void sort_by_id(TransportDB* tdb) 
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
    
    sort_by_id(tdb);
    
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
    if (tdb == NULL)
    {
        return TRANSPORT_NULL_ARGUMENTS;
    }

    if (line_id <= 0)
    {
        return TRANSPORT_INVALID_LINE_NUMBER;
    }

    if (tdb->head == NULL) 
    {
        return TRANSPORT_DOESNT_EXIST;
    }

    Line *curr_line = tdb->head;
    StationsList *curr_sta;
    int num_stations = 0;
    
    while (curr_line != NULL)
    {
        if (curr_line->line_id == line_id)
        {
            curr_sta = curr_line->stations;

            if (curr_sta == NULL)
            {
                return TRANSPORT_EMPTY;
            }

            while (curr_sta != NULL)
            {
                num_stations++;
                curr_sta = curr_sta->next;
            }
            
            curr_sta = curr_line->stations;

            prog2_report_line(curr_line->line_id, curr_line->type, num_stations, curr_line->price);

            while (curr_sta != NULL)
            {
                prog2_report_station(curr_sta->station_name);
                curr_sta = curr_sta->next;
            }

            return TRANSPORT_SUCCESS;
        }

        curr_line = curr_line->next;
    }
    return TRANSPORT_DOESNT_EXIST;
}


void sort_by_price(TransportDB* tdb) 
{
    if (tdb == NULL || tdb->head == NULL) 
    {
        return;
    }

    Line *curr_line = tdb->head;
    Line *cmp_line;
    Line temp_line;

    while (curr_line != NULL)
    {
        cmp_line = curr_line->next;
        
        while (cmp_line != NULL)
        {
            if (cmp_line->price <= curr_line->price)
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


TransportResult TransportReportDirections(TransportDB* tdb, const char *from, const char *to) 
{
    if (tdb == NULL || from == NULL || to == NULL)
    {
        return TRANSPORT_NULL_ARGUMENTS;
    }

    if (tdb->head == NULL)
    {
        return TRANSPORT_EMPTY;
    }

    sort_by_price(tdb);

    Line *curr_line = tdb->head;
    StationsList *curr_sta;
    StationsList *after_from_sta;
    StationsList *count_sta;
    StationsList *last_sta = NULL;
    int num_stations = 0;
    int count = 0;
    int found_this_line = 0;

    while (curr_line != NULL)
    {
        found_this_line = 0;
        curr_sta = curr_line->stations;
        if (curr_sta == NULL)
        {
            curr_line = curr_line->next;
            continue;
        }

        while (curr_sta != NULL && found_this_line == 0)
        {
            if (strcmp(curr_sta->station_name, from) == 0)
            {
                after_from_sta = curr_sta;

                while (after_from_sta != NULL && found_this_line == 0)
                {
                    if (strcmp(after_from_sta->station_name, to) == 0)
                    {
                        count_sta = curr_line->stations;
                        num_stations = 0;

                        while (count_sta != NULL)
                        {
                            last_sta = count_sta;
                            num_stations++;
                            count_sta = count_sta->next;
                        }                  

                        prog2_report_line(curr_line->line_id, curr_line->type, num_stations, curr_line->price);
                        prog2_report_station(curr_line->stations->station_name);
                        prog2_report_station(last_sta->station_name);

                        count++;
                        found_this_line = 1;
                    }
                    after_from_sta = after_from_sta->next;
                }
            }
            curr_sta = curr_sta->next;
        }
        curr_line = curr_line->next;
    }

    if (count > 0)
    {
        return TRANSPORT_SUCCESS;
    }
    return TRANSPORT_DOESNT_EXIST;
}

