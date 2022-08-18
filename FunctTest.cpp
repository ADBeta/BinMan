/*******************************************************************************
* Function test and development file for BinMan Library. For actual usecase help
* see BinMan.h or README.md
* -- For staging and testing, see Staging.cpp --
*
* g++ ./FunctTest.cpp ./BinMan.cpp -o BinMan
*
* ADBeta
* 18 Aug 2022
*******************************************************************************/

#include "BinMan.h"

BinMan binFile("TestFiles/Example.jpg");


int main() {

	
	binFile.Verbose = true;
	binFile.read();
	return 0;
}
