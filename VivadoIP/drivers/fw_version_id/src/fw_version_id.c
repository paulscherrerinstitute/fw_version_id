/*############################################################################
#  Copyright (c) 2019 by Paul Scherrer Institute, Switzerland
#  All rights reserved.
############################################################################*/

#include "fw_version_id.h"

void set_version_git(id_t sw_id, char* version) {

   // Write Git Describe version as 32 byte string to EpicsParamRam:
  uint32_t version_part;
  for(int i=0;i<8;i++) {
    // store as little endian:
     version_part = (C_VERSION[(i*4)+3]<<24) | (C_VERSION[(i*4)+2]<<16) | (C_VERSION[(i*4)+1]<<8) | C_VERSION[(i*4)];
     Xil_Out32(base_addr + sw_base + (i*4), version_part);
  }

   return;
}


