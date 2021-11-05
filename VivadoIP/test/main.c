#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fw_version_id.h"

#define OFFSET(base, addr) (uint32_t)((uint64_t)&(addr) - base)
 
int main() {
  volatile structIdVersion_t *version;

  printf("\n\n**** fw_version_id Test **** \n\n");
  printf("__DATE__ =  '%s'\n", __DATE__);
  printf("__TIME__ =  '%s'\n\n", __TIME__);

  // allocate memory for version structure:
  structId_t* mem = (structId_t*)malloc(sizeof(structId_t));
  uint64_t baseaddr = (uint64_t)mem;

  set_version_project(baseaddr, "SwissFEL", "Athos DBPM3");
  set_version_hwrev(baseaddr, "F");
  set_version_id(baseaddr, ID_0, "PL", VERSION_GIT_REPO);
  set_version_id(baseaddr, ID_1, "RPU0", VERSION_GIT_REPO);
  set_version_id(baseaddr, ID_2, "RPU1", VERSION_GIT_REPO);
  // if you want to define the DATE/TIME from another place, this function can be called:
  set_version_datetime(baseaddr, ID_0, __DATE__, __TIME__);
  set_version_datetime(baseaddr, ID_1, "May 21 2019", __TIME__);
  set_version_datetime(baseaddr, ID_2, __DATE__, __TIME__);


  volatile structId_t *idAll = get_version_all(baseaddr);

  //printf("Build Date: %s\n", get_version_id(baseaddr, 1)->datetime);
  printf("===========================\n");
  baseaddr = (uint64_t)&(idAll->facility);
  printf(" %03X : Facility    =  %s\n", OFFSET(baseaddr, idAll->facility), idAll->facility);
  printf(" %03X : Project     =  %s\n", OFFSET(baseaddr, idAll->project), idAll->project);
  printf(" %03X : HW Revision =  %s\n", OFFSET(baseaddr, idAll->hardwareRev), idAll->hardwareRev);

  for (int i=0;i<MAX_VERSIONS;i++) {
    version = get_version_id(baseaddr, (enumIdIndex_t)i);
    printf("\n");
    printf(" %03X : (ID%i) Descriptor =  %s\n", OFFSET(baseaddr, version->descriptor), i, version->descriptor);
    printf(" %03X : (ID%i) Version    =  %s\n", OFFSET(baseaddr, version->version), i, version->version);
    printf(" %03X : (ID%i) Build Date =  %s\n", OFFSET(baseaddr, version->datetime), i, version->datetime);
  }
  printf("===========================\n");

  free(mem);
  return 0;
}

