#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog2_ex1.h"


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
    
}lineDetails;


void configure_io_from_args(int argc, char *argv[] ,FILE **in ,FILE **out);
CommandType identify_command(char *tokens[], int count);
lineDetails *add_line(char *tokens[], int count, lineDetails *allLines);
void remove_line(char *tokens[], int count, lineDetails *allLines);
void add_station_to_line(char *tokens[], int count, lineDetails *allLines);




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

void remove_line(char *tokens[], int count, lineDetails *allLines)
{
    
}


void add_station_to_line(char *tokens[], int count, lineDetails *allLines)

{
    
}