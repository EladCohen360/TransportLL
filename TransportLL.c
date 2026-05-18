#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TransportLL.h"



TransportDB *TransportCreate(void)
{
   TransportDB *tdb = (TransportDB*)malloc(sizeof(TransportDB));
   if(tdb==NULL)
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
//     lineDetails *newNode = malloc(sizeof(lineDetails));
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


TransportResult TransportRemoveLine(TransportDB* tdb, int line_id)
{
    
}


