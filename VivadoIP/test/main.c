#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fw_version_id.h"

int main() {
  volatile structIdVersion_t *version;

  printf("\n\n**** fw_version_id Test **** \n\n");

  // allocate memory for version structure:
  structId_t* mem = (structId_t*)malloc(sizeof(structId_t));
  uint64_t baseaddr = (uint64_t)mem;

  set_version_hw(baseaddr, "SwissFEL", "Athos DBPM3", "F");
  set_version_id(baseaddr, ID_1, "RPU0", VERSION_GIT_REPO);
  set_version_id(baseaddr, ID_2, "RPU1", VERSION_GIT_REPO);
  // if you want to define the DATE/TIME from another place, this function can be called:
  set_version_datetime(baseaddr, ID_2, __DATE__, __TIME__);


  volatile structId_t *idAll = get_version_all(baseaddr);

  //printf("Build Date: %s\n", get_version_id(baseaddr, 1)->datetime);
  printf("Facility:    %s\n", idAll->facility);
  printf("Project:     %s\n", idAll->project);
  printf("HW Revision: %s\n", idAll->hardwareRev);

  for (int i=0;i<MAX_VERSIONS;i++) {
    version = get_version_id(baseaddr, i);
    printf(" [%i] Descriptor:  %s\n", i, version->descriptor);
    printf(" [%i] Version:     %s\n", i, version->version);
    printf(" [%i] Build Date:  %s\n", i, version->datetime);
  }

  free(mem);
  return 0;
}

