/*****************************************************************************
*  Copyright (c) 2021 by Paul Scherrer Institute, Switzerland
*  All rights reserved.
*****************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


//*******************************************************************************
// Includes
//*******************************************************************************
#include <stddef.h>
#include <stdint.h>

/*****************************************************************************
 * Build Date/Time 
****************************************************************************/

/* Data declaration */
/* Output of __DATE__ : */
/* Jan  1 2015 */
/* Feb  1 2015 */
/* Mar  1 2015 */
/* Apr  1 2015 */
/* May  1 2015 */
/* Jun  1 2015 */
/* Jul  1 2015 */
/* Aug  1 2015 */
/* Sep  1 2015 */
/* Oct  1 2015 */
/* Nov  1 2015 */
/* Dec  1 2015 */
/* 0123456789A */
#define DATE_YEAR (((__DATE__[ 7] - '0') * 1000) + ((__DATE__[ 8] - '0') * 100) + ((__DATE__[ 9] - '0') * 10) + (__DATE__[10] - '0'))

#define DATE_MONTH (__DATE__[ 0] == 'J' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'n' ?  1 :\
                    __DATE__[ 0] == 'F' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'b' ?  2 :\
                    __DATE__[ 0] == 'M' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'r' ?  3 :\
                    __DATE__[ 0] == 'A' && __DATE__[ 1] == 'p' && __DATE__[ 2] == 'r' ?  4 :\
                    __DATE__[ 0] == 'M' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'y' ?  5 :\
                    __DATE__[ 0] == 'J' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'n' ?  6 :\
                    __DATE__[ 0] == 'J' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'l' ?  7 :\
                    __DATE__[ 0] == 'A' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'g' ?  8 :\
                    __DATE__[ 0] == 'S' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'p' ?  9 :\
                    __DATE__[ 0] == 'O' && __DATE__[ 1] == 'c' && __DATE__[ 2] == 't' ? 10 :\
                    __DATE__[ 0] == 'N' && __DATE__[ 1] == 'o' && __DATE__[ 2] == 'v' ? 11 :\
                    __DATE__[ 0] == 'D' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'c' ? 12 :\
                    0)
#define DATE_DAY   (__DATE__[ 4] == ' ' ? (__DATE__[ 5] - '0') : (((__DATE__[ 4] - '0') * 10) + (__DATE__[ 5] - '0')))

/* Output of __TIME__ : */
/* 14:30:30 */
/* 01234567 */
#define TIME_HOUR   (__TIME__[0] == ' ' ? (__TIME__[1] - '0') : (((__TIME__[0] - '0') * 10) + (__TIME__[1] - '0')))
#define TIME_MINUTE (__TIME__[3] == ' ' ? (__TIME__[4] - '0') : (((__TIME__[3] - '0') * 10) + (__TIME__[4] - '0')))


//*******************************************************************************
// User Macros
//*******************************************************************************
// Version Macros to be used in application:
#define SW_BUILD_DATE   ((DATE_YEAR<<16) + (DATE_MONTH<<8) + DATE_DAY)
#define SW_BUILD_TIME    ((TIME_HOUR<<8) + TIME_MINUTE)

#define VERSION_STRING_SIZE 32
#define BUILDDATE_STRING_SIZE 16

#define MAX_VERSIONS 5

//*******************************************************************************
// Types
//*******************************************************************************
typedef struct __attribute__ ((packed)) {
} structIdBuildDate_t;

typedef struct __attribute__ ((packed)) {
} structIdBuildTime_t;

// Version structure:
typedef struct __attribute__ ((packed)) {
  uint8_t descriptor[8];
  char version[VERSION_STRING_SIZE];
  char datetime[BUILDDATE_STRING_SIZE];
} structIdVersion_t;

// Main memory structure:
typedef struct __attribute__ ((packed)) {
  uint8_t facility[16];
  uint8_t project[16];
  uint8_t hardwareRev[4];
  structIdVersion_t version[MAX_VERSIONS];
} structId_t;


//*******************************************************************************
// Functions
//*******************************************************************************
void set_version_id(const uint32_t base_addr, uint8_t idx, char* version);
void set_version_build(const uint32_t base_addr, uint8_t idx);
void get_version_id(const uint32_t base_addr, uint8_t idx, structIdVersion_t* dataset);
void get_version_all(const uint32_t base_addr, uint8_t idx, structId_t* dataset);
void get_version_build(const uint32_t base_addr, uint8_t idx, char* build_datetime, const size_t size);


#ifdef __cplusplus
}
#endif

