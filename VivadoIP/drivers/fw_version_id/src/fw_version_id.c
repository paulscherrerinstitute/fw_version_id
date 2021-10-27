/*############################################################################
#  Copyright (c) 2021 by Paul Scherrer Institute, Switzerland
#  All rights reserved.
############################################################################*/

#include "fw_version_id.h"

// -------------------------------------------------
void set_version_id(const uint32_t base_addr, uint8_t idx, char* version) {
   // Write Git Describe version as 32 byte string:
  volatile structId_t *fwId = (structId_t *)base_addr;

  fwId->version[idx].version[VERSION_STRING_SIZE-1] = 0;

  for(int i=0;i<8;i++) {
    // store as little endian:
     fwId->version[idx].version[(i*4)+3] = version[(i*4)+0];
     fwId->version[idx].version[(i*4)+2] = version[(i*4)+1];
     fwId->version[idx].version[(i*4)+1] = version[(i*4)+2];
     fwId->version[idx].version[(i*4)+0] = version[(i*4)+3];
   }
}

// -------------------------------------------------
void get_version_id(const uint32_t base_addr, uint8_t id, structIdVersion_t* dataset) {
   // Write Git Describe version as 32 byte string:
  volatile structId_t *fwId = (structId_t *)base_addr;
  //dataset = fwId->version[idx];
}

// -------------------------------------------------
void get_version_all(const uint32_t base_addr, uint8_t idx, structId_t* dataset) {
   // Write Git Describe version as 32 byte string:
  volatile structId_t *fwId = (structId_t *)base_addr;
  dataset = fwId;
}


// -------------------------------------------------
void set_version_datetime(const uint32_t base_addr, uint8_t idx) {
  volatile structId_t *fwId = (structId_t *)base_addr;
  volatile structIdVersion_t *ver = (structIdVersion_t *)&fwId[idx];

  ver->datetime[0] = __DATE__[7];
  ver->datetime[1] = __DATE__[8];
  ver->datetime[2] = __DATE__[9];
  ver->datetime[3] = __DATE__[10];
  ver->datetime[4] = '-';
  ver->datetime[5] = (DATE_MONTH / 10) + '0';
  ver->datetime[6] = (DATE_MONTH / 10 * 10 - DATE_MONTH) + '0';
  ver->datetime[7] = '-';
  ver->datetime[8] = __DATE__[4];
  ver->datetime[9] = __DATE__[5];
  ver->datetime[10] = ' ';
  ver->datetime[11] = __TIME__[0];
  ver->datetime[12] = __TIME__[1];
  ver->datetime[13] = ':';
  ver->datetime[14] = __TIME__[3];
  ver->datetime[15] = __TIME__[4];
  ver->datetime[16] = 0;
}

// -------------------------------------------------
void get_version_build(const uint32_t base_addr, uint8_t id, char* build_datetime, const size_t size) {
  uint32_t offset = 2;
  uint8_t i=0, c=0;

  //uint32_t build_date = Xil_In32(base_addr + offset + 0x20);
 uint32_t build_date;
 uint32_t build_time;
  //uint32_t build_time = Xil_In32(base_addr + offset + 0x24);

  // build date string: YYYY-MM-DD
  for (i=0;i<8;i++) {
    build_datetime[c] = 48 + (build_date>>(28-i*4)&0xF);
    switch (i) {
      case 3:
        build_datetime[4] = '-';
        c+=2;
        break;
      case 5:
        build_datetime[7] = '-';
        c+=2;
        break;
      default:
        c++;
    }
  }

  // build time string: hh:mm
  c=0;
  for (i=0;i<4;i++) {
    build_datetime[c] = 48 + (build_time>>(12-i*4)&0xF);
    switch (i) {
      case 1:
        build_datetime[2] = ':';
        c+=2;
        break;
      default:
        c++;
    }
  }

  build_datetime[c] = 0;
}

