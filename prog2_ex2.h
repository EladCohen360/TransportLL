#ifndef __PROG2_EX2__
#define __PROG2_EX2__

/*
 * prog2_ex2.h
 * This file contains the definitions of the functions that you need to implement in prog2_ex2.c.
 * !! You should not modify this file !!
 * Author: David Avdat
 */

#include <stdio.h>

typedef int line_id;

/*
 * Transport type enumeration
 */
typedef enum {
    BUS = 1,
    TRAIN = 2,
    METRO = 4,
    ALL = 7,
} TransportType;

/*
 * Transport error enumeration
*/
typedef enum 
{
    TRANSPORT_SUCCESS,
    TRANSPORT_NULL_ARGUMENTS,
    TRANSPORT_OUT_OF_MEMORY,
    TRANSPORT_INVALID_LINE_TYPE,
    TRANSPORT_INVALID_LINE_NUMBER,
    TRANSPORT_INVALID_PRICE,
    TRANSPORT_ALREADY_EXISTS,
    TRANSPORT_DOESNT_EXIST,
    TRANSPORT_EMPTY

} TransportResult;

/*
 * Function prototypes
 */

/*
function: prog2_report_error_message
 * Description: Reports an error message based on the provided transport error code
 * Parameters: error - the transport error code
 */
void prog2_report_error_message(TransportResult error);

/*
function: prog2_report_line
 * Description: Reports information about a transport line
 * Parameters: 
 *             number - the line number
 *             type - the transport type (BUS, TRAIN, METRO)
 *             num_stations - the actual number of stations that were added to the line
 *             price - the price of the line
 */
void prog2_report_line(line_id number, TransportType type, int num_stations, double price);

/*
function: prog2_report_station
 * Description: Reports information about a transport station
 * Parameters:
 *             name - the name of the station
 */
void prog2_report_station(const char *name);

#endif
