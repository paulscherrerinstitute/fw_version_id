#include "fw_version_id.h"

main() {

  char version_str[VERSION_STRING_SIZE] = VERSION_GIT_REPO;

  set_version_id(XPAR_FW_VERSION_ID_0_BASEADDR, ID_1, "A_RPU1", version_str);
  set_version_datetime(XPAR_FW_VERSION_ID_0_BASEADDR, ID_1, __DATE__, __TIME__);

  set_version_hwrev(XPAR_FW_VERSION_ID_0_BASEADDR, "B");
}
