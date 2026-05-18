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

typedef struct TransportDB_t
{
    Line *head;
} TransportDB;

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


typedef struct lineDetails_t
{
    int line_id;
    float price;
    transport_type type;
    int num_of_stations;
    char *stations_list;
    struct lineDetails_t *next;
    
} LineDetails;


void configure_io_from_args(int argc, char *argv[] ,FILE **in ,FILE **out);
CommandType identify_command(char *tokens[], int count);
lineDetails *add_line(char *tokens[], int count, lineDetails *allLines);
void remove_line(char *tokens[], int count, lineDetails *allLines);
void add_station_to_line(char *tokens[], int count, lineDetails *allLines);
TransportResult TransportAddStation(TransportDB* tdb, int line_id, const char *station);
TransportResult TransportRemoveStation(TransportDB* tdb, int line_id, unsigned int index);
TransportResult TransportReportLines(TransportDB* tdb, const char *station);
TransportResult TransportReportStations(TransportDB* tdb, int line_id);
TransportResult TransportReportDirections(TransportDB* tdb, const char *from, const char *to);
Line *find_line(TransportDB* tdb, int line_id);


int main(int argc, char *argv[])
{
    FILE *in = stdin;
    FILE *out = stdout;
    configure_io_from_args(argc, argv , &in , &out);
    
    lineDetails *allLines = NULL;

    char line[256];
    while (fgets(line, sizeof(line), in) != NULL)
    {
        char *tokens[10];
        int count = 0;
        char *token = strtok(line, " \n");
        
        while (token != NULL && count < 6)
        {
            tokens[count++] = token;
            token = strtok(NULL, " \n");
        }

        CommandType cmd = identify_command(tokens, count);
        switch (cmd)
        {
            case CMD_ADD_LINE:
                allLines=add_line(tokens, count, allLines);
            break;
            case CMD_ADD_STATION_TO_LINE:
                add_station_to_line(tokens, count, allLines);
            break;
            case CMD_REMOVE_LINE:
                remove_line(tokens, count, allLines);
            break;
            // case CMD_COMMENT:
            //     add_line(tokens, count);
            // break;
            // case CMD_UNKNOWN:
            //     add_line(tokens, count);
            // break;
        }
    }

    while (allLines->next!=NULL)
    {   if(allLines->type==1)
            printf("BUS ");
        if(allLines->type==4)
            printf("METRO ");
        if(allLines->type==2)
            printf("TRAIN ");
        printf("%d %d %.2f\n",allLines->line_id , allLines->num_of_stations , allLines->price);
        allLines = allLines->next;
    }
    
    if(in!=stdin)
        fclose(in);

    if(out!=stdout)
        fclose(out);

    return 0;
}



void configure_io_from_args(int argc, char* argv[] ,FILE **in ,FILE **out)
{
    if (argc >= 3 && strcmp(argv[1], "-i") == 0)
    {    
        *in = fopen(argv[2], "r");
        if (*in == NULL)
        {   perror(argv[2]);
            prog2_report_error_message(TRANSPORT_CANNOT_OPEN_FILE);
            return;
        }
    }
    else if (argc == 3 && strcmp(argv[1], "-o") == 0)
    {   
        *out = fopen(argv[2], "w");
        if (*out == NULL)
        {
            prog2_report_error_message(TRANSPORT_CANNOT_OPEN_FILE);
            return;
        }
    }

    if (argc == 5 && strcmp(argv[3], "-o") == 0)
    {   
        *out = fopen(argv[4], "w");
        if (*out == NULL)
        {
            prog2_report_error_message(TRANSPORT_CANNOT_OPEN_FILE);
            if (*in != stdin)
                fclose(*in);
            return;
        }
    }    
    
}


CommandType identify_command(char *tokens[], int count)
{
    if (count == 6 &&
        strcmp(tokens[0], "Add") == 0 &&
        strcmp(tokens[1], "Line") == 0)
    {
        return CMD_ADD_LINE;
    }
    if (count == 3 &&
        strcmp(tokens[0], "Remove") == 0 &&
        strcmp(tokens[1], "Line") == 0)
    {
        return CMD_REMOVE_LINE;
    }
    
    if (count == 6 &&
        strcmp(tokens[0], "Add") == 0 &&
        strcmp(tokens[1], "Station") == 0 &&
        strcmp(tokens[2], "To") == 0 &&
        strcmp(tokens[3], "Line") == 0)
    {
        return CMD_ADD_STATION_TO_LINE;
    }
    
    if (count == 3 &&
        strcmp(tokens[0], "Report") == 0 &&
        strcmp(tokens[1], "Lines") == 0)
    {
        return CMD_REPORT_LINES;
    }
    
    if (count == 3 &&
        strcmp(tokens[0], "Report") == 0 &&
        strcmp(tokens[1], "Stations") == 0)
    {
        return CMD_REPORT_STATIONS;
    }

    if (count == 4 &&
        strcmp(tokens[0], "Report") == 0 &&
        strcmp(tokens[1], "Directions") == 0)
    {
        return CMD_REPORT_DIRECTIONS;
    }

    if (count >= 1 &&
        strcmp(tokens[0], "#") == 0)
    {
        return CMD_COMMENT;
    }

    return CMD_UNKNOWN;
}



    lineDetails *add_line(char *tokens[], int count, lineDetails *allLines)
{
    lineDetails *newNode = malloc(sizeof(lineDetails));

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

void remove_line(char *tokens[], int count, lineDetails *allLines)ד
{
    
}


void add_station_to_line(char *tokens[], int count, lineDetails *allLines)

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

