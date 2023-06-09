/*****************************************************************************
*  Copyright (c) 2021 by Paul Scherrer Institute, Switzerland
*  All rights reserved.
*****************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//*********************************************
// Includes
//*********************************************
#include <stddef.h>
#include <string.h>
#include <stdint.h>

//*********************************************
//* Defines
//*********************************************
#define VERSION_STRING_SIZE 32
#define BUILDDATE_STRING_SIZE 20

#define MAX_VERSIONS 5

//*********************************************
// Types
//*********************************************

// Index Enumeration:
typedef enum {
  ID_0 = 0,
  ID_1 = 1,
  ID_2 = 2,
  ID_3 = 3,
  ID_4 = 4,
} enumIdIndex_t;

// Version structure:
typedef struct __attribute__ ((packed)) {
  char descriptor[8];
  char version[VERSION_STRING_SIZE];
  char datetime[BUILDDATE_STRING_SIZE];
  char reserved1[4];
} structIdVersion_t;

// Main memory structure:
typedef struct __attribute__ ((packed)) {
  char facility[16];
  char project[16];
  char hardwareRev[4];
  char reserved1[12];
  char reserved2[16];
  structIdVersion_t version[MAX_VERSIONS];
} structId_t;


//*******************************************************************************
// Functions
//*******************************************************************************
void set_version_id(const uint64_t base_addr, enumIdIndex_t idx, const char* descriptor, const char* version);
void set_version_datetime(const uint64_t base_addr, enumIdIndex_t idx, const char * date, const char * time);
void set_version_hwrev(const uint64_t base_addr, const char* hardwareRev);
void set_version_project(const uint64_t base_addr, const char* facility, const char* project);
volatile structIdVersion_t* get_version_id(const uint64_t base_addr, enumIdIndex_t idx);
volatile structId_t* get_version_all(const uint64_t base_addr);

#ifdef __cplusplus
}
#endif

