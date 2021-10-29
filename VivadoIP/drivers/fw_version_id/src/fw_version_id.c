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
volatile structIdVersion_t* get_version_id(const uint64_t base_addr, enumIdIndex_t idx) {
  structId_t *fwId = (structId_t *)base_addr;
  return &(fwId->version[idx]);
}

// -------------------------------------------------
volatile structId_t* get_version_all(const uint64_t base_addr) {
  volatile structId_t *fwId = (structId_t *)base_addr;
  return fwId;
}

// -------------------------------------------------
void set_version_datetime(const uint64_t base_addr, enumIdIndex_t idx, char* date, char* time) {
  volatile structId_t *fwId = (structId_t *)base_addr;
  volatile structIdVersion_t *ver = &(fwId->version[idx]);

// convert the month names into a number:
uint8_t month =    (date[ 0] == 'J' && date[ 1] == 'a' && date[ 2] == 'n' ?  1 :
                    date[ 0] == 'F' && date[ 1] == 'e' && date[ 2] == 'b' ?  2 :
                    date[ 0] == 'M' && date[ 1] == 'a' && date[ 2] == 'r' ?  3 :
                    date[ 0] == 'A' && date[ 1] == 'p' && date[ 2] == 'r' ?  4 :
                    date[ 0] == 'M' && date[ 1] == 'a' && date[ 2] == 'y' ?  5 :
                    date[ 0] == 'J' && date[ 1] == 'u' && date[ 2] == 'n' ?  6 :
                    date[ 0] == 'J' && date[ 1] == 'u' && date[ 2] == 'l' ?  7 :
                    date[ 0] == 'A' && date[ 1] == 'u' && date[ 2] == 'g' ?  8 :
                    date[ 0] == 'S' && date[ 1] == 'e' && date[ 2] == 'p' ?  9 :
                    date[ 0] == 'O' && date[ 1] == 'c' && date[ 2] == 't' ? 10 :
                    date[ 0] == 'N' && date[ 1] == 'o' && date[ 2] == 'v' ? 11 :
                    date[ 0] == 'D' && date[ 1] == 'e' && date[ 2] == 'c' ? 12 :
                    0);

  ver->datetime[0] = date[7];
  ver->datetime[1] = date[8];
  ver->datetime[2] = date[9];
  ver->datetime[3] = date[10];
  ver->datetime[4] = '-';
  ver->datetime[5] = (month / 10) + '0';
  ver->datetime[6] = (month / 10 * 10 - month) + '0';
  ver->datetime[7] = '-';
  ver->datetime[8] = date[4];
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
