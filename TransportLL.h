#ifndef __MOOVITLIST__
#define __MOOVITLIST__
#include "prog2_ex2.h"

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

#endif