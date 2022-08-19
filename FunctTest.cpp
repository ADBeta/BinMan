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

#include <iostream>

BinMan binFile("TestFiles/Example.jpg");


int main() {
	
	binFile.Verbose = true;
	
	binFile.read();
	
	
	for(int x = 0; x < 20; x++) {
		std::cout << std::hex << (int)binFile.m_fBuffer[x] << "  ";
	
	}
	std::cout << std::endl;
	
	//Must always flush before exit to clear RAM
	binFile.flush();
	return 0;
}
