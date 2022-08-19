/*******************************************************************************
* BinMan Implimentation. See BinMan.h or README.md for more useage info
*
* ADBeta
* 19 Aug 2022
*******************************************************************************/

#include "BinMan.h"

#include <limits>     //allows max stream size value
#include <iomanip>    //For printing hex values with leading 0
#include <iostream>
#include <fstream>

/** Constructor and configuration *********************************************/
BinMan::BinMan(const char* inputfn) {
	this->m_filename = inputfn;
}

BinMan::~BinMan() {
	std::cout << "deconstruct begin" << std::endl;
	//Clear the byte array. flush should always be run, this is a safety backup
	if(m_fBuffer != NULL) {
		delete [] m_fBuffer;
		m_fBuffer = NULL;	
	}
	//Clear the selBuffer
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
	
	//Set the buffer size variable
	m_fBufSize = inBytes;
	
	//If verbose, print the size and status
	if(Verbose) {
		infoMsg("BinMan: Read " + (std::string)m_filename + " Success.\t",
		        std::to_string(inBytes) + " Bytes.");
	}
	
	//Close the file
	this->close();
}

void BinMan::printChunk(const std::streamsize startByte,
                        const std::streamsize endByte) {	
	//If end is higher than the bytes in file, warn then exit function.
	if(endByte > m_fBufSize) {
		warnMsg("printChunk: end byte is larger than the size of the file");
		return;
	}
		
	int col = 0; //Current byte position across the 'screen'
	
	//Start index at -start- and go to -end-
	std::streamsize index = startByte;
	while(index < endByte) { 
		//If 20 bytes have been printed, move to next line
		if(col == 20) {
			std::cout << std::endl; 
			col = 0;
		}
		
		//TODO Add byte offset to beginning of line?
		//Print each byte as a hex value, followed by a space
		pHex(m_fBuffer[index]);
		std::cout << " ";
		
		//Next position on screen
		++col;
		//Next byte index
		++index;	
	}
	
	//Newline for clean-ness - Use std::dec to revert back from hex mode
	std::cout << std::dec << std::endl;
}

void BinMan::printAll() {
	printChunk(0x00, m_fBufSize);
}

//TODO combine both printChunk and printAll functionality into one block


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
	if(m_fBuffer != NULL) {
		delete [] m_fBuffer;
		m_fBuffer = NULL;	
	}
}

int BinMan::overwrite() {
	//Open file as output, truncate
	m_file.open(m_filename, std::ios::out | std::ios::trunc | std::ios::binary);
	
	//Make sure file is open and exists
	if(m_file.is_open() == 0) { 
		warnMsg("overwrite: Could not create file", (std::string)m_filename);
		return EXIT_FAILURE;
	}
	
	//Write RAM to file
	std::streamsize outByte = 0;
	while(outByte < m_fBufSize) {
		//Put the byte into the stream file
		m_file.put(m_fBuffer[outByte]);
	
		++outByte;
	}
	
	//Close file and clear flags
	close();
	
	//If verbosity is enabled, print a nice message
	if(Verbose == true) {
		infoMsg("BinMan: Succcessfully wrote " + std::to_string(outByte),
		        " bytes to " + (std::string)m_filename);
	}
	
	return EXIT_SUCCESS;
}

int BinMan::writeTo(BinMan &target) {
	//Open file as output, truncate
	target.m_file.open(target.m_filename, std::ios::out | std::ios::trunc |
	                                      std::ios::binary);
	
	//Make sure file is open and exists
	if(target.m_file.is_open() == 0) { 
		warnMsg("writeTo: Could not create file ", target.m_filename);
		
		return EXIT_FAILURE;
	}
	
	//Write parent object RAM to target file
	std::streamsize outByte = 0;
	while(outByte < this->m_fBufSize) {
		//Put the byte into the stream file
		target.m_file.put(this->m_fBuffer[outByte]);
	
		++outByte;
	}
	
	//Close file and clear flags
	target.close();
	
	//If verbosity is enabled, print a nice message
	if(Verbose == true) {
		infoMsg("BinMan: Succcessfully wrote " + std::to_string(outByte),
		        " bytes to " + (std::string)target.m_filename);
	}
	
	return EXIT_SUCCESS;
}

/** Helper Functions **********************************************************/
//Inlining this didn't help speed. oh well
void BinMan::pHex(const unsigned char byte) {
	std::cout << std::uppercase << std::setfill('0') << std::setw(2) 
		      << std::hex << (int)byte;
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
