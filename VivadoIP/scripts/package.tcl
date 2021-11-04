###############################################################
# Include PSI packaging commands
###############################################################
source ../../../../TCL/PsiIpPackage/PsiIpPackage.tcl
namespace import -force psi::ip_package::latest::*

###############################################################
# General Information
###############################################################
set IP_NAME fw_version_id
set IP_VERSION 1.0
set IP_REVISION "auto"
set IP_LIBRARY PSI
set IP_DESCIRPTION "FPGA Version ID (Build date and GIT version)"

init $IP_NAME $IP_VERSION $IP_REVISION $IP_LIBRARY
set_description $IP_DESCIRPTION
set_logo_relative "../doc/psi_logo_150.gif"
###############################################################
# Add Source Files
###############################################################

#Relative Source Files
add_sources_relative { \
  ../../hdl/fw_version_id_axi.vhd \
} 

#PSI Common
add_lib_relative \
  "../../../../VHDL/psi_common/hdl" \
  { \
    psi_common_array_pkg.vhd \
    psi_common_math_pkg.vhd \
    psi_common_logic_pkg.vhd \
    psi_common_pl_stage.vhd \
    psi_common_axi_slave_ipif.vhd \
    psi_common_sp_ram_be.vhd \
  }
  
###############################################################
# Driver Files
############################################################### 
add_drivers_relative ../drivers/fw_version_id { \
  src/fw_version_id.c \
  src/fw_version_id.h \
}

###############################################################
# GUI Parameters
###############################################################

#User Parameters
gui_add_page "Configuration"

gui_create_parameter "C_ID_FACILITY" "Facility (max 16 char)"
gui_add_parameter

gui_create_parameter "C_ID_PROJECT" "Project (max 16 char)"
gui_add_parameter

gui_create_parameter "C_REV_PINS" "External Rev Pins"
gui_add_parameter

gui_create_parameter "C_FREQ_HZ" "Clock frquency in Hz"
gui_add_parameter


###############################################################
# Package Core
###############################################################
set TargetDir ".."
#                     Edit  Synth 
package_ip $TargetDir false true




