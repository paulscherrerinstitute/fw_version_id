/*############################################################################
#  Copyright (c) 2021 by Paul Scherrer Institute, Switzerland
#  All rights reserved.
############################################################################*/

#include "fw_version_id.h"

// -------------------------------------------------
uint32_t get_offset(versionid_t sw_id) {
  switch (sw_id) {
    case FW:
      return 0x020;
      break;
    case SW0:
      return 0x080;
      break;
    case SW1:
      return 0x0B0;
      break;
    case SW2:
      return 0x0E0;
      break;
    default:
      return 0;
  }
}

// -------------------------------------------------
void set_version_git(const uint32_t base_addr, versionid_t id, char * version) {
  uint32_t offset = get_offset(id);

  if (offset != 0) {
     // Write Git Describe version as 32 byte string to EpicsParamRam:
    uint32_t version_part;
    for(int i=0;i<8;i++) {
      // store as little endian:
       version_part = (version[(i*4)+3]<<24) | (version[(i*4)+2]<<16) | (version[(i*4)+1]<<8) | version[(i*4)];
       Xil_Out32(base_addr + offset + (i*4), version_part);
    }
  }
}

// -------------------------------------------------
void set_version_build(const uint32_t base_addr, versionid_t id, const uint32_t build_date, const uint32_t build_time) {
  uint32_t offset = get_offset(id);

  if (offset != 0) {
    Xil_Out32(base_addr + offset + 0x20, build_date);
    Xil_Out32(base_addr + offset + 0x24, build_time);
  }
}

// -------------------------------------------------
void get_version_build(const uint32_t base_addr, versionid_t id, char* build_datetime, const size_t size) {
  uint32_t offset = get_offset(id);
  uint8_t i=0, c=0;

  uint32_t build_date = Xil_In32(base_addr + offset + 0x20);
  uint32_t build_time = Xil_In32(base_addr + offset + 0x24);

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

