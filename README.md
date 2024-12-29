# eZ80 Studio [![Discord Chat Link](https://img.shields.io/discord/1012426214226530424?logo=discord)](https://discord.gg/RDTtu258fW) [![Release](https://img.shields.io/github/v/release/EzCE/ez80-studio?include_prereleases)](https://github.com/EzCE/ez80-studio/releases/latest)

eZ80 Studio is an on-calc eZ80 assembly IDE for the TI-84 Plus CE and TI-83 Premium CE calculators. It includes an editor, assembler, and include file support.

## Screenshots

![File editing and assembling](screenshots/ez80-studio.gif "File editing and assembling")    ![Settings](screenshots/settings.gif "Settings")
![Other menus](screenshots/other-menus.gif "Other menus")      ![About](screenshots/about.png "About")

## Features

* Editor with word wrap and up to 14 lines and 38 columns on screen at once.
* Toggleable syntax highlighting.
* Light and dark themes.
* Special characters.
* Quick jump to lines.
* Built-in eZ80 assembler, with support for data and reserve macros.
* Support for `$` symbol to represent the current address when assembling.

## Installation

1. Download the latest version of eZ80 Studio from [the GitHub releases page](https://github.com/EzCE/ez80-studio/releases/latest).
2. Send **EZSTUDIO.8xp** along with any include files (Found in **includes/\*.8xv**) to your calculator using TI-Connect CE or TiLP. If you don't have the [CE C libraries](https://tiny.cc/clibs), you'll need to download and send those as well.
3. Run **prgmEZSTUDIO** from the programs menu (You will need to use the [arTIfiCE jailbreak](https://yvantt.github.io/arTIfiCE) if you are on an OS version 5.5 and above).

## Navigation

Below is a table with keys and their various usage in eZ80 Studio:

| Key                                                    | Action performed                                              |
|--------------------------------------------------------|---------------------------------------------------------------|
| <kbd>2nd</kbd> / <kbd>enter</kbd>                      | Select options from menus or insert a newline.                |
| <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd> | Scroll through menus or move the cursor in the editor.        |
| <kbd>y=</kbd>                                          | Open/exit files menu.                                         |
| <kbd>window</kbd>                                      | Assemble the currently opened file.                           |
| <kbd>zoom</kbd>                                        | Open/exit goto line menu.                                     |
| <kbd>trace</kbd>                                       | Open/exit special characters menu.                            |
| <kbd>graph</kbd>                                       | Open/exit settings menu.                                      |
| <kbd>del</kbd>                                         | Delete the character in front of the cursor.                  |
| <kbd>mode</kbd>                                        | Backspace.                                                    |
| <kbd>alpha</kbd>                                       | Switch between uppercase, lowercase, and numeric input modes. |
| <kbd>clear</kbd>                                       | Exit the program or close the current menu or window.         |

## Include files

Five include files are provided with eZ80 Studio, though you can also [convert your own](#converting-files). These include files are based on **[ti84pceg.inc](https://github.com/CE-Programming/asm-docs/blob/master/programs/include/ti84pceg.inc)** and the include files provided with **[BASM-3](https://github.com/beckadamtheinventor/BASM-3/tree/master/data)**. **TIOSRTNS.8xv** contains system routines, **TIOSRAMA.8xv** contains RAM areas, **TIOSFLAG.8xv** contains system flags, **TIOSKBEQ.8xv** contains keyboard and context equates, and **TI84PCEG_smaller.8xv** is a slightly downsized version of the full **ti84pceg.inc** (which is too large to fit on the calculator in one file). **TI84PCEG_smaller.8xv** contains the majority of the other four include files, so it unlikely you would need both the four smaller includes as well.

## Converting files

Converting include or source files from the computer to a file compatible with eZ80 Studio can be done quickly using the provided conversion scripts.
 
To convert source files, use **convert.sh**. You will also need [convbin](https://github.com/mateoconlechuga/convbin) if it is not already installed. The syntax for **convert.sh** is `convert.sh <input name> <output name> <mode>`, where `<input name>` is the name of the file to convert, `<output name>` is the name of the output file to generate when converting, and `<mode>` is either `var` to convert an eZ80 Studio AppVar to an assembly source file or `asm` to convert an assembly source file to an eZ80 Studio AppVar editable on the calculator.
 
To convert include files, use **includes/conv-inc.py**. You will also need [fasmg](https://flatassembler.net/download.php) if it is not already installed. Running the python program will prompt for the name of the file to convert and should output the converted file to **includes/bin**.

## Bugs

If you encounter a bug while using eZ80 Studio, don't hesitate to [make an issue](https://github.com/EzCE/ez80-studio/issues) or report it on the [Discord server](https://discord.gg/RDTtu258fW). Feel free to request features or ask for help on the discord or in the [Cemetech topic](https://ceme.tech/t19925) as well!

## Credits

Thanks to [beckadamtheinventor](https://github.com/beckadamtheinventor/) for help with the assembler portion of the program and to [Cemetech](https://cemetech.net) members for feedback!

© 2022 - 2024 RoccoLox Programs and TIny_Hacker
