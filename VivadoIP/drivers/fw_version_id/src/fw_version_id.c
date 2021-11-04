/*############################################################################
#  Copyright (c) 2021 by Paul Scherrer Institute, Switzerland
#  All rights reserved.
############################################################################*/

#include "fw_version_id.h"

// -------------------------------------------------
// Private Functions
// -------------------------------------------------

// Volatile memory copy:
void v_memcpy(volatile void *dest, const volatile void *src, size_t size) { 

  const volatile uint8_t *src_c = src;
  volatile uint8_t *dest_c  = dest;

  while (size > 0) {
      size--;
      dest_c[size] = src_c[size];
  }
}

// -------------------------------------------------
// Public Functions
// -------------------------------------------------
void set_version_id(const uint64_t base_addr, enumIdIndex_t idx, char* descriptor, char* version) {
   // Write Git Describe version as 32 byte string:
  volatile structId_t *fwId = (structId_t *)base_addr;

  v_memcpy(fwId->version[idx].descriptor, descriptor, sizeof(fwId->version[idx].descriptor));
  v_memcpy(fwId->version[idx].version, version, sizeof(fwId->version[idx].version));

  set_version_datetime(base_addr, idx, __DATE__, __TIME__);
}

// -------------------------------------------------
void set_version_datetime(const uint64_t base_addr, enumIdIndex_t idx, char* date, char* time) {
  volatile structId_t *fwId = (structId_t *)base_addr;
  volatile structIdVersion_t *ver = &(fwId->version[idx]);

if (!memcmp(date, "Jan", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '1';}
if (!memcmp(date, "Feb", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '2';}
if (!memcmp(date, "Mar", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '3';}
if (!memcmp(date, "Apr", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '4';}
if (!memcmp(date, "May", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '5';}
if (!memcmp(date, "Jun", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '6';}
if (!memcmp(date, "Jul", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '7';}
if (!memcmp(date, "Aug", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '8';}
if (!memcmp(date, "Sep", 3)) {ver->datetime[5] = '0'; ver->datetime[6] = '9';}
if (!memcmp(date, "Oct", 3)) {ver->datetime[5] = '1'; ver->datetime[6] = '0';}
if (!memcmp(date, "Nov", 3)) {ver->datetime[5] = '1'; ver->datetime[6] = '1';}
if (!memcmp(date, "Dec", 3)) {ver->datetime[5] = '1'; ver->datetime[6] = '2';}

  ver->datetime[0] = date[7];
  ver->datetime[1] = date[8];
  ver->datetime[2] = date[9];
  ver->datetime[3] = date[10];
  ver->datetime[4] = '-';
  //ver->datetime[5]
  //ver->datetime[6]
  ver->datetime[7] = '-';
  ver->datetime[8] = date[4] == ' ' ? '0' : date[4];
  ver->datetime[9] = date[5];
  ver->datetime[10] = ' ';
  ver->datetime[11] = time[0];
  ver->datetime[12] = time[1];
  ver->datetime[13] = ':';
  ver->datetime[14] = time[3];
  ver->datetime[15] = time[4];
  ver->datetime[16] = ':';
  ver->datetime[17] = time[6];
  ver->datetime[18] = time[7];
  ver->datetime[19] = 0;
  ver->datetime[20] = 0;
}

// -------------------------------------------------
void set_version_hw(const uint64_t base_addr, char* facility, char* project, char* hardwareRev) {
  structId_t *fwId = (structId_t *)base_addr;
  v_memcpy(fwId->facility, facility, 16);
  v_memcpy(fwId->project, project, 16);
  v_memcpy(fwId->hardwareRev, hardwareRev, 4);
}

// -------------------------------------------------
volatile structIdVersion_t* get_version_id(const uint64_t base_addr, enumIdIndex_t idx) {
  structId_t *fwId = (structId_t *)base_addr;
  return &(fwId->version[idx]);
}

// -------------------------------------------------
volatile structId_t* get_version_all(const uint64_t base_addr) {
  volatile structId_t *fwId = (structId_t *)base_addr;
  return fwId;
}

