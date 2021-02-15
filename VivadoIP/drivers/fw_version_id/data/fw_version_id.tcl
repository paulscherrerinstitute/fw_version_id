

proc generate {drv_handle} {
	xdefine_include_file $drv_handle "xparameters.h" fw_version_id "NUM_INSTANCES" "DEVICE_ID"  "C_BASEADDR" "C_HIGHADDR"
}
