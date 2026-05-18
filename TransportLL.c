#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TransportLL.h"



TransportDB *TransportCreate(void)
{
TransportDB *tdb = (TransportDB*)malloc(sizeof(TransportDB));

    if(tdb==NULL)
        return NULL;
    
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
}


TransportResult is_price_valid(allLines *new_line, float price)
{
    if(price<=0)
    {
        free(new_line);
        return TRANSPORT_INVALID_PRICE;
    }
    new_line->price=price;
}


TransportResult TransportAddLine(TransportDB* tdb, const char *type, int line_id, float price)
{
    if(tdb == NULL)
        return TRANSPORT_NULL_ARGUMENTS;
    
    allLines *new_line=(allLines *)malloc(sizeof(allLines));
    if(new_line==NULL)
        return TRANSPORT_OUT_OF_MEMORY;

    if(is_type_valid(new_line, type)==TRANSPORT_INVALID_LINE_TYPE)
        return TRANSPORT_INVALID_LINE_TYPE;

    allLines *current_line = tdb->Lines;
    if(is_id_valid(current_line, new_line, line_id)!=TRANSPORT_ALREADY_EXISTS)
        return  TRANSPORT_ALREADY_EXISTS;
    if(is_id_valid(current_line, new_line, line_id)!=TRANSPORT_INVALID_LINE_NUMBER)
        return  TRANSPORT_INVALID_LINE_NUMBER;
     new_line->line_id=line_id;

    if(is_price_valid(new_line, price)==TRANSPORT_INVALID_PRICE)
        return TRANSPORT_INVALID_PRICE;

    new_line->nextLine = tdb->Lines;
    tdb->Lines= new_line;

    return TRANSPORT_SUCCESS;
}


TransportResult TransportRemoveLine(TransportDB* tdb, int line_id)
{
    
}


