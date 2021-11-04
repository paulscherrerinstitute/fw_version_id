# ----------------------------------------------------
# Pre Synthesis Tcl Script
#
#  Set Git Version and Build Date in fw_version_id IP
# ----------------------------------------------------

# change byte order of string within 32 bit words:
proc string_to_hex {str} {
  #binary scan $str i* tmp
  #puts " tmp : $tmp"
  #set swapped [binary format Ai* [string length $tmp] $tmp]
  #puts " swapped : $swapped"
  #puts " str : $str"
  set str_reverse [string reverse $str]
  #puts " str_reverse : $str_reverse"
  binary scan $str_reverse H* hexdata
  #puts " hexdata : $hexdata"
  return $hexdata
}

# Function to set top level generics
proc set_top_generics {} {

   puts "fw_version_id_pre_synth.tcl script"

    set curr_dir [pwd]
    set proj_dir [get_property DIRECTORY [current_project]]
    cd $proj_dir

    # Update the generics
    set datetime_str [clock format [clock seconds] -format {%Y-%m-%d %H:%M:%S}]

    #set datetime_arr [clock format [clock seconds] -format {%Y %y %m %d %H %M %S 00}]
    #set datecode [format "%04X%02X%02X" [scan [lindex $datetime_arr 0] %d] [scan [lindex $datetime_arr 2] %d] [scan [lindex $datetime_arr 3] %d]]
    #set datetime_str [format "%04s-%02s-%02s %2s:%2s:%2s" [scan [lindex $datetime_arr 0] %d] [scan [lindex $datetime_arr 2] %d] [scan [lindex $datetime_arr 3] %d] [scan [lindex $datetime_arr 4] %d] [scan [lindex $datetime_arr 5] %d] [scan [lindex $datetime_arr 6] %d]]
    #set timecode [format "%02X%02X" [scan [lindex $datetime_arr 4] %d] [scan [lindex $datetime_arr 5] %d]]

    set current_generics ""

    set current_generics [get_property generic [current_fileset]]
    puts "current generics:  $current_generics"

    puts " version_id Date/Time:  $datetime_str"
    set datetime_hex [string_to_hex $datetime_str]

    # Get git repo version description and convert to hex numbers:
    set git_version [exec git describe --abbrev=6 --dirty --always --tags]
    puts " git version: $git_version"
    set git_hex [string_to_hex $git_version]
    #set git_hex [string_to_hex ABCDEF]

    puts " version_id Git:  $git_hex"

    set_property generic "G_FW_BUILD_DATE_TIME=160'h$datetime_hex G_FW_GIT_VERSION=256'h$git_hex" [current_fileset]

    set current_generics [get_property generic [current_fileset]]
    puts "current generics: $current_generics"

    cd $curr_dir
  }

set_top_generics


