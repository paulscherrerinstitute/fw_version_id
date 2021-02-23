#include "fw_version_id.h"

main() {
#
  char version_str[VERSION_STRING_SIZE] = VERSION_GIT_REPO;

  set_version_git(XPAR_FW_VERSION_ID_0_BASEADDR, SW0, version_str);
  set_version_build(XPAR_FW_VERSION_ID_0_BASEADDR, SW0, SW_BUILD_DATE, SW_BUILD_TIME); 

}
