# BinMan

BinMan is a Binary File Manager, for reading, writing and modifying binary files

## Description

This library is intended to be used to assist tasks like header maniuplation,
data skimming and repair, pattern detection, etc. Similar in nature to a 
previous library I have written - [TeFiEd](https://github.com/ADBeta/TeFiEd)

## How To Use

Simply copy BinMan.cpp and BinMan.h into your project, alternatively create a 
.a file and include that. - No non-standard C++ libraries are needed.

See BinMan.h for a list of funcitons and usages.

## TO-DO 

Currently the library supports reading binary files into RAM, printing chunks
or the whole binary to the console, and some other simple functions

I plan to add:
* byte-for-byte insertion 
* Shrink or grow of RAM block, more full-featured editing
* Ability to write the RAM to another file
* Ability to overwrite the input file
* Built-in pattern searching tools
* Better output to console (including byte offsets)

Written by ADBeta 

##Licence

BinMan is under the GPL (GPL3.0), please see LICENCE for information
