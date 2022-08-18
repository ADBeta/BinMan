/*******************************************************************************
* BinMan Implimentation. See BinMan.h or README.md for more useage info
*
* ADBeta
* 18 Aug 2022
*******************************************************************************/

#include "BinMan.h"

#include <iostream>
#include <fstream>

/** Constructor and configuration *********************************************/
BinMan::BinMan(const char* inputfn) {
	this->m_filename = inputfn;
}

int BinMan::getBytes() {

file.ignore( std::numeric_limits<std::streamsize>::max() );
std::streamsize length = file.gcount();
file.clear();   //  Since ignore will have set eof.
file.seekg( 0, std::ios_base::beg );

}

int BinMan::read() {
	//Open file as read
	this->m_file.open(this->m_filename, std::ios::in | std::ios::binary);
	
	//Check that the file opened and/or exists
	if(m_file.is_open() == 0) {
		std::cout << "FIle doesn't exist" << std::endl;
		//errorMsg("read", "File does not exist");
		return EXIT_FAILURE;
	}
	
	
	//Close the file
	this->close();
	
	return 0;
}

void BinMan::close() {
	//Only perform action if the file is open
	if(this->m_file.is_open()) {
	//Clear the ios flags, EOF specifically
	this->m_file.clear();
	//Seek to beginning of the file
	this->m_file.seekg(0, std::ios::beg);
	//Close the stream
	this->m_file.close();
	}
}
