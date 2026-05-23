#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TransportLL.h"



TransportDB *TransportCreate(void)
{
TransportDB *tdb = (TransportDB*)malloc(sizeof(TransportDB));
    if(tdb==NULL)
        return NULL;
    tdb->Lines = NULL;
    return tdb;
}


void TransportDestroy(TransportDB *tdb)
{
    if(tdb!=NULL)
    {
        
        while(tdb->Lines!=NULL)
        {
            allLines *next_line = tdb->Lines->nextLine;

            StationsList *station = tdb->Lines->stations;

            while (station!= NULL)
            {
                StationsList *next_station = station->nextStation;
                free(station->stationsName);
                free(station);
                station = next_station;
            }
            free(tdb->Lines);
            tdb->Lines = next_line;
            
        }
        free(tdb);
    }
    return;
    
}


void clear_stations(allLines *curr)
{
     while (curr->stations!= NULL)
            {
                StationsList *next_station = curr->stations->nextStation;
                free(curr->stations->stationsName);
                free(curr->stations);
                curr->stations = next_station;
            } 

}


TransportResult is_type_valid(allLines *new_line, const char *type)
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


TransportResult is_id_valid(allLines *current_line ,allLines *new_line, int line_id)
{
    while(current_line != NULL)
    {
        if(current_line->line_id==line_id)
        {
            free(new_line);
            return TRANSPORT_ALREADY_EXISTS;
        }
        current_line=current_line->nextLine;
    }
    if(line_id<=0)
        {
            free(new_line);
            return TRANSPORT_INVALID_LINE_NUMBER;
        }
    
    return TRANSPORT_SUCCESS;
}


TransportResult is_price_valid(allLines *new_line, float price)
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
    if(tdb == NULL)
        return TRANSPORT_NULL_ARGUMENTS;
    
    allLines *new_line=(allLines *)malloc(sizeof(allLines));
    if(new_line==NULL)
        return TRANSPORT_OUT_OF_MEMORY;
    
    new_line->stations = NULL;

    TransportResult res = is_type_valid(new_line, type);
    if(res==TRANSPORT_INVALID_LINE_TYPE)
        return TRANSPORT_INVALID_LINE_TYPE;

    allLines *current_line = tdb->Lines;


    res = is_id_valid(current_line, new_line, line_id);
    if (res != TRANSPORT_SUCCESS)
        return res;

     new_line->line_id=line_id;

    res = is_price_valid(new_line, price);
    if(res==TRANSPORT_INVALID_PRICE)
        return TRANSPORT_INVALID_PRICE;

    new_line->nextLine = tdb->Lines;
    tdb->Lines= new_line;

    return TRANSPORT_SUCCESS;
}


TransportResult TransportRemoveLine(TransportDB* tdb, int line_id)
{
    if(tdb ==NULL || tdb->Lines == NULL)
        return TRANSPORT_EMPTY;

    allLines *curr = tdb->Lines->nextLine;
    allLines *prev = tdb->Lines;
    if (prev->line_id == line_id)
    {
        clear_stations(prev);
        tdb->Lines = tdb->Lines->nextLine;
        free(prev);
        return TRANSPORT_SUCCESS;
    }

    while (curr!=NULL)
    {
        if(curr->line_id==line_id)
        {
            clear_stations(curr);
            prev->nextLine = curr->nextLine;
            free(curr);
            return TRANSPORT_SUCCESS;
        }

        prev = curr;
        curr = curr->nextLine;
    }
    return TRANSPORT_DOESNT_EXIST;
    
}


allLines *find_line(TransportDB* tdb, int line_id)
{
    if (tdb == NULL) 
    {
        return NULL;
    }

    allLines *curr = tdb->Lines;

    if(curr != NULL)
    {
        if (curr->line_id == line_id)
        {
            return curr; 
        } 
    }

    while (curr != NULL) 
    {
        if (curr->nextLine->line_id == line_id)
        {
            return curr; 
        } 
        curr = curr->nextLine;
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

    allLines *request_line = find_line(tdb, line_id);

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

    new_station->stationsName = (char*)malloc(sizeof(char) * (strlen(new_station_name) + 1));
    if (new_station->stationsName  == NULL)
    {
        free(new_station);
        return TRANSPORT_OUT_OF_MEMORY;
    }

    StationsList *curr_sta = request_line->stations;

    strcpy(new_station->stationsName, new_station_name);
    new_station->nextStation = NULL;

    if (request_line->stations == NULL) 
    {
        request_line->stations = new_station;

        return TRANSPORT_SUCCESS;
    }

    while (curr_sta != NULL)
    {
        if (curr_sta->nextStation == NULL)
        {
            curr_sta->nextStation = new_station;
            
            return TRANSPORT_SUCCESS;
        }
        
        curr_sta = curr_sta->nextStation;
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