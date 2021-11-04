# General Information

## Maintainer
Jonas Purtschert [jonas.purtschert@psi.ch]

## Authors
Jonas Purtschert [jonas.purtschert@psi.ch]

## License
This library is published under [PSI HDL Library License](License.txt), which is [LGPL](LGPL2_1.txt) plus some additional exceptions to clarify the LGPL terms in the context of firmware development.

## Changelog
See [Changelog](Changelog.md)

## Dependencies

* TCL
  * [PsiSim](https://github.com/paulscherrerinstitute/PsiSim) (2.1.0 or higher, for development only)
  * [PsiIpPackage](https://git.psi.ch/GFA/Libraries/Firmware/TCL/PsiIpPackage) (1.6.0, for development only )
  * [PsiUtil](https://git.psi.ch/GFA/Libraries/Firmware/TCL/PsiUtil) (1.2.0, for development only )
* VHDL
  * [psi\_common](https://github.com/paulscherrerinstitute/psi_common) (2.5.0 or higher)

# Description
* IP for storing build date/time and version based on git repository.
* Constains scripts and workflow to automate FW/SW Versioning.
* See following description of the Git Repo Version format: [HowTo: Git Repo Versioning](https://git.psi.ch/GFA/Documentation/HowToWorkWithGit/blob/master/HowTo.md#git-repository-versioning)

## AXI Address Map

* Byte address offset

| Offset | Register              | R/W | Length   | Description                         | Example                |
| ------ | --------              | --- | ---      | -----------                         | -------                |
| 0x000  | Facility              | R   | 16 chars | Facility                            | SwissFEL               |
| 0x010  | Project               | R   | 16 chars | Project                             | DBPM3-AthosBPM         |
| 0x020  | HW Revision           | R   | 4 chars  | HW Revision                         | B                      |
| 0x024  |                       |     |          | reserved                            |                        |
| 0x030  | ID0 Descriptor *)     | R   | 8 chars  | Descriptor of current version block | PL                     |
| 0x038  | ID0 Version *)        | R   | 32 chars | FW Version in *Git Describe* format | 0.1.0-13-g55ecb1-dirty |
| 0x058  | ID0 Buid Date/Time *) | R   | 20 chars | Format: YYYY-MM-DD HH:MM:SS         | 2021-11-03 10:41:41    |
| 0x06C  |                       |     |          | reserved                            |                        |
| 0x070  | ID1 Descriptor        | RW  | 8 chars  |                                     | RPU0                   |
| 0x078  | ID1 Version           | RW  | 32 chars |                                     | 1.2.0                  |
| 0x098  | ID1 Buid Date/Time    | RW  | 20 chars |                                     |                        |
| 0x0AC  |                       |     |          |                                     |                        |
| 0x0B0  | ID2 Descriptor        | RW  | 8 chars  |                                     | RPU1                   |
| 0x0B8  | ID2 Version           | RW  | 32 chars |                                     | 1.2.0-3-g45abc         |
| 0x0D8  | ID2 Buid Date/Time    | RW  | 20 chars |                                     |                        |
| 0x0EC  |                       |     |          |                                     |                        |
| 0x0F0  | ID3 Descriptor        | RW  | 8 chars  |                                     |                        |
| 0x0F8  | ID3 Version           | RW  | 32 chars |                                     |                        |
| 0x118  | ID3 Buid Date/Time    | RW  | 20 chars |                                     |                        |
| 0x12C  |                       |     |          |                                     |                        |
| 0x130  | ID4 Descriptor        | RW  | 8 chars  |                                     |                        |
| 0x138  | ID4 Version           | RW  | 32 chars |                                     |                        |
| 0x158  | ID4 Buid Date/Time    | RW  | 20 chars |                                     |                        |
| 0x16C  |                       |     |          |                                     |                        |

   *) Reserved for PL and automatically set by pre-tcl script in registers.

* Register: 0x000...06C
* BRAM: 0x070..16C


# Usage

* Add `fw_version_id` as a Git Submodule to your Project's library.

## FPGA

**Integration in Vivado:**  

![VivadoIP Generics](doc/vivadoip_generics.png)

To automatically integrate the Build Date/Time and Git Repo Version, a tcl script must be added to the Build process before synthesis:

1. Add Pre-Synthesis tcl script in: *Vivado > Project Settings > Synthesis > tcl.pre*
2. Select following script from library: `/fw_version_id/fw_version_id_pre_synth.tcl`

## Software

**Integration in SDK:**  

![VivadoIP Generics](doc/sdk_software.png)

1. Copy Makefiles `/templates/makefile.defs/.targets` to SDK Project base.
2. Add Defined Symbol to SDK Project: `VERSION_GIT_REPO=\"$(VERSION_GIT_REPO)\"`:  *Properties > C/C++ Build > Symbols*
3. Adapt `makefile.targets`: Select object (e.g. main.o) which includes driver, to force compilation on a build run.
4. Call driver functions to write Git Repo Version and Build Date/Time into `fw_version_id` IP. 
   Example: [main.c](templates/main.c)

**Explanation:**  
* The Makefiles are automatically included in the SDK managed Makefile process. 
* `Makefile.defs` defines Makro with Git Repo Version (Git Describe Call)
* `Makefile.targets` is used to force a rebuild of an object on every build. Otherwise the Version/Build Date might not be updated on every compile.
* Following Macros are available: `VERSION_GIT_REPO`, `SW_BUILD_DATE` and `SW_BUILD_TIME`.
* Using Driver functions `set_version_git()` and `set_version_build()` to write Version Info into BRAM of `fw_version_id` IP in FPGA. Example [main.c](templates/main.c).

## Epics

* Example template: [version.template](templates/version.template)

**Output records to use in panels:**  

| Record                                     | Description           | Example          |
| ------                                     | ----                  | --------         |
| `$(DEV):$(SYS)-FW-FACILITY`                | FW Facility           | SwissFEL         |
| `$(DEV):$(SYS)-FW-PROJECT`                 | FW Project            | DBPM3-AthosBPM   |
| `$(DEV):$(SYS)-FW-VERSION`                 | FW Git Repo Version   | 0.3.2-13-gab3451 |
| `$(DEV):$(SYS)-FW-BUILD-DATETIME-S.SVAL`   | FW Build Date/Time    | 2021.02.17 13:40 |
| =====                                      | ====                  | ====             |
| `$(DEV):$(SYS)-RPU0-VERSION`               | SW0 Git Repo Version  | 0.3.2-13-gab3451 |
| `$(DEV):$(SYS)-RPU0-BUILD-DATETIME-S.SVAL` | SW0 Build Date/Time   | 2021.02.17 13:40 |
| =====                                      | ====                  | ====             |
| `$(DEV):$(SYS)-RPU1-VERSION`               | SW1 Git Repo Version  | 0.3.2-13-gab3451 |
| `$(DEV):$(SYS)-RPU1-BUILD-DATETIME-S.SVAL` | SW1 Build Date/Time   | 2021.02.17 13:40 |


