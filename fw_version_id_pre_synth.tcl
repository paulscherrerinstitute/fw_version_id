# ----------------------------------------------------
# Pre Synthesis Tcl Script
#
# Set Git Version and Build Date in fw_version_id IP
#
# https://git.psi.ch/GFA/Libraries/Firmware/VHDL/fw_version_id
# ----------------------------------------------------

# change byte order of string within 32 bit words:
proc string_to_hex {str} {
  set str_reverse [string reverse $str]
  binary scan $str_reverse H* hexdata
  return $hexdata
}

# Function to set top level generics
proc set_top_generics {} {

   puts "fw_version_id_pre_synth.tcl script"

    # CD to project root directory for propper GIT Repo identification:
    set curr_dir [pwd]
    set proj_dir [get_property DIRECTORY [current_project]]
    cd $proj_dir

    # Update the generics
    set datetime_str [clock format [clock seconds] -format {%Y-%m-%d %H:%M:%S}]

    set current_generics ""

    set current_generics [get_property generic [current_fileset]]

    puts " version_id Date/Time:  $datetime_str"
    set datetime_hex [string_to_hex $datetime_str]

    # Get GIT repo version description and convert to hex numbers:
    set git_version [exec git describe --abbrev=6 --dirty --always --tags]
    puts " git version: $git_version"
    set git_hex [string_to_hex $git_version]
    #set git_hex [string_to_hex ABCDEF]

    set_property generic "G_FW_BUILD_DATE_TIME=160'h$datetime_hex G_FW_GIT_VERSION=256'h$git_hex" [current_fileset]

    set current_generics [get_property generic [current_fileset]]
    puts "top level generics: $current_generics"

    cd $curr_dir
  }

set_top_generics


