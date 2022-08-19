/*******************************************************************************
* BinMan Implimentation. See BinMan.h or README.md for more useage info
*
* ADBeta
* 18 Aug 2022
*******************************************************************************/

#include "BinMan.h"

#include <limits>
#include <iostream>
#include <fstream>

/** Constructor and configuration *********************************************/
BinMan::BinMan(const char* inputfn) {
	this->m_filename = inputfn;
}

void BinMan::read() {
	//Open file as read
	m_file.open(m_filename, std::ios::in | std::ios::binary);
	
	//Check that the file opened and/or exists
	if(m_file.is_open() == 0) {
		errMsg("read", "File " + (std::string)m_filename, "does not exist.");
	}
	
	////    Get the size of the file    ////
	//Read the file until EOF delim is encountered
	m_file.ignore(std::numeric_limits<std::streamsize>::max());
	//Get the size of the input file
	std::streamsize inBytes = m_file.gcount();
		
	//If the file is too large, error and exit
	if(inBytes > _maxInputBytes) {
		errMsg("read", "File " + (std::string)m_filename, "is too large.");
	}
	
	//Clear the EOF flag and return to first byte for buffer fill
	m_file.clear();
	m_file.seekg(0, std::ios_base::beg);
	
	//Malloc with safeties and warnings
	try {
		m_fBuffer = new unsigned char[inBytes]; 
	}
	catch(std::bad_alloc&) {
		errMsg("read", "could not allocate the file buffer");
	}
	
	//Copy the file data to the array
	std::streamsize index = 0;
	while(index < inBytes) {
		m_fBuffer[index] = (unsigned char)m_file.get();
	
		++index;
	}
	
	//If verbose, print the size and status
	if(Verbose) {
		infoMsg("BinMan: Read " + (std::string)m_filename + " Success.\t",
		        std::to_string(inBytes) + " Bytes.");
	}
	
	//Close the file
	this->close();
}

void BinMan::close() {
	//Only perform action if the file is open
	if(m_file.is_open()) {
		//Clear the ios flags, EOF specifically
		m_file.clear();
		//Seek to beginning of the file
		m_file.seekg(0, std::ios::beg);
		//Close the stream
		m_file.close();
	}
}

void BinMan::flush() {
	//Clear the byte array
	delete [] m_fBuffer;
}

void BinMan::cleanExit(int exitcode) {
	//Must clear the malloc'd array, close the file, and exit

	this->close();
	exit(exitcode);
}

/** Message ouput functions ***************************************************/
void BinMan::infoMsg(const std::string &msg1, const std::string &msg2) {
	//Output first string
	std::cout << msg1;
	
	//Output second messgae if availible
	if(msg2.empty()) {
		std::cout << std::endl;
		return;
	}
	
	std::cout << " " << msg2 << std::endl;
}

void BinMan::warnMsg(const std::string &msg1, const std::string &msg2) {
	//Output first string
	std::cerr << "Warning: BinMan:\t" << msg1;
	
	//Output second messgae if availible
	if(msg2.empty()) {
		std::cerr << std::endl;
		return;
	}
	
	std::cerr << " " << msg2 << std::endl;
}

void BinMan::errMsg(const std::string &func, const std::string &msg1, 
                    const std::string &msg2) {
	//Output function name and the first string
	std::cerr << "Error: BinMan: In Function " << func << ":\t" << msg1;
	
	//Output second messgae if availible
	if(msg2.empty()) {
		std::cerr << std::endl;
	} else {	
		std::cerr << " " << msg2 << std::endl;
	}
	
	//Exit the program
	cleanExit(EXIT_FAILURE);	
}
