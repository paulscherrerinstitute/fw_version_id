# General Information

## Maintainer
Jonas Purtschert [jonas.purtschert@psi.ch]

## Authors
Jonas Purtschert [jonas.purtschert@psi.ch]

## License
This library is published under [PSI HDL Library License](License.txt), which is [LGPL](LGPL2_1.txt) plus some additional exceptions to clarify the LGPL terms in the context of firmware development.

## Detailed Documentation

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
IP for storing build date/time and version based on git repository.

## AXI Address Map

| Offset     | Register       | R/W | Length   | Description                                |
| ------     | --------       | --- | ---      | -----------                                |
| 0x000      | FW Version     | R   | 32 chars | FW Version in Git Describe format          |
| 0x020      | Facility       | R   | 16 chars | Facility e.g. SwissFEL                     |
| 0x030      | Project        | R   | 16 chars | Project e.g. DBPM3-AthosBPM                |
| 0x040      | FW Buid Date   | R   | [31:0]   | Format: YYYY-MM-DD, encoded as: 0xYYYYMMDD |
| 0x044      | FW Buid Time   | R   | [15:0]   | Format: hh:mm, encoded as: 0x0000hhmm      |
| 0x048      | GPIO           | R   | [15:0]   | GPIO, eg. Hardware Rev pins, DIP switch    |
| 0x04C..7C  |                |     |          | reserved                                   |
| 0x080      | SW1 Version    | R/W | 32 chars | Git Describe based version                 |
| 0x0A0      | SW1 Build Date | R/W | [31:0]   | Format: YYY-MM-DD                          |
| 0x0A4      | SW1 Build Time | R/W | [15:0]   | Format: hh:mm                              |
| 0x0A8..AC  |                |     |          | reserved                                   |
| 0x0B0      | SW2 Version    | R/W | 32 chars | see SW1                                    |
| 0x0D0      | SW2 Build Date | R/W | [31:0]   | see SW1                                    |
| 0x0D4      | SW2 Build Time | R/W | [15:0]   | see SW1                                    |
| 0x0D8..DC  |                |     |          | reserved                                   |
| 0x0E0      | SW3 Version    | R/W | 32 chars | see SW1                                    |
| 0x100      | SW3 Build Date | R/W | [31:0]   | see SW1                                    |
| 0x104      | SW3 Build Time | R/W | [15:0]   | see SW1                                    |
| 0x108..10C |                |     |          | reserved                                   |

 
