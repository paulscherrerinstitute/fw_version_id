# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Configuration [ipgui::add_page $IPINST -name "Configuration"]
  ipgui::add_param $IPINST -name "C_ID_FACILITY" -parent ${Configuration}
  ipgui::add_param $IPINST -name "C_ID_PROJECT" -parent ${Configuration}
  ipgui::add_param $IPINST -name "C_REV_PINS" -parent ${Configuration}


}

proc update_PARAM_VALUE.C_ID_FACILITY { PARAM_VALUE.C_ID_FACILITY } {
	# Procedure called to update C_ID_FACILITY when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_ID_FACILITY { PARAM_VALUE.C_ID_FACILITY } {
	# Procedure called to validate C_ID_FACILITY
	return true
}

proc update_PARAM_VALUE.C_ID_PROJECT { PARAM_VALUE.C_ID_PROJECT } {
	# Procedure called to update C_ID_PROJECT when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_ID_PROJECT { PARAM_VALUE.C_ID_PROJECT } {
	# Procedure called to validate C_ID_PROJECT
	return true
}

proc update_PARAM_VALUE.C_REV_PINS { PARAM_VALUE.C_REV_PINS } {
	# Procedure called to update C_REV_PINS when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_REV_PINS { PARAM_VALUE.C_REV_PINS } {
	# Procedure called to validate C_REV_PINS
	return true
}

proc update_PARAM_VALUE.C_S00_AXI_ID_WIDTH { PARAM_VALUE.C_S00_AXI_ID_WIDTH } {
	# Procedure called to update C_S00_AXI_ID_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S00_AXI_ID_WIDTH { PARAM_VALUE.C_S00_AXI_ID_WIDTH } {
	# Procedure called to validate C_S00_AXI_ID_WIDTH
	return true
}

proc update_PARAM_VALUE.C_S_AXI_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_ADDR_WIDTH } {
	# Procedure called to update C_S_AXI_ADDR_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_S_AXI_ADDR_WIDTH { PARAM_VALUE.C_S_AXI_ADDR_WIDTH } {
	# Procedure called to validate C_S_AXI_ADDR_WIDTH
	return true
}


proc update_MODELPARAM_VALUE.C_ID_FACILITY { MODELPARAM_VALUE.C_ID_FACILITY PARAM_VALUE.C_ID_FACILITY } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_ID_FACILITY}] ${MODELPARAM_VALUE.C_ID_FACILITY}
}

proc update_MODELPARAM_VALUE.C_ID_PROJECT { MODELPARAM_VALUE.C_ID_PROJECT PARAM_VALUE.C_ID_PROJECT } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_ID_PROJECT}] ${MODELPARAM_VALUE.C_ID_PROJECT}
}

proc update_MODELPARAM_VALUE.C_REV_PINS { MODELPARAM_VALUE.C_REV_PINS PARAM_VALUE.C_REV_PINS } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_REV_PINS}] ${MODELPARAM_VALUE.C_REV_PINS}
}

proc update_MODELPARAM_VALUE.C_S00_AXI_ID_WIDTH { MODELPARAM_VALUE.C_S00_AXI_ID_WIDTH PARAM_VALUE.C_S00_AXI_ID_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S00_AXI_ID_WIDTH}] ${MODELPARAM_VALUE.C_S00_AXI_ID_WIDTH}
}

proc update_MODELPARAM_VALUE.C_S_AXI_ADDR_WIDTH { MODELPARAM_VALUE.C_S_AXI_ADDR_WIDTH PARAM_VALUE.C_S_AXI_ADDR_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_S_AXI_ADDR_WIDTH}] ${MODELPARAM_VALUE.C_S_AXI_ADDR_WIDTH}
}

