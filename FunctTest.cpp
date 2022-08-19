/*******************************************************************************
* Function test and development file for BinMan Library. For actual usecase help
* see BinMan.h or README.md
* -- For staging and testing, see Staging.cpp --
*
* g++ ./FunctTest.cpp ./BinMan.cpp -o BinMan
*
* ADBeta
* 19 Aug 2022
*******************************************************************************/

#include "BinMan.h"

#include <iostream>

BinMan binFile("TestFiles/Example.jpg");
BinMan outFile("TestFiles/writeout.jpg");

int main() {
	
	binFile.Verbose = true;
	
	binFile.read();
	
	//binFile.printAll();
	binFile.printChunk(0x00, 0xF0);

	//binFile.overwrite();
	binFile.writeTo(outFile);

	//Must always flush before exit to clear RAM
	binFile.flush();
	return 0;
}
