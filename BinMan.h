/*******************************************************************************
* Binary Manager
* Open, Modify, Read, Manipulate and Write binary files.
* 
* Usage:
*
*
*
*
* ADBeta
* 18 Aug 2022
* Version 0.0.5
*******************************************************************************/

#ifndef BINMAN_H
#define BINMAN_H

#include <fstream>

class BinMan {
	public:
	/** Constructor and configuration *****************************************/	
	//Constructor passes filename to BinMan
	BinMan(const char*);

	//Flags
	//Verbosity flag. true allows output of information, warnings and more
	bool Verbose = false;

	/** File managment ********************************************************/
	//Gets the amount of bytes in the file and returns value
	//!!Warning!! This resets the current position in file
	int getBytes();
	
	//Read the file into a RAM buffer, then close the file - for next operation
	int read();

	
	//Close a file if it is open. can be called at any point
	void close();
	
	//private:
	const char* m_filename; //Filename as char array
	std::fstream m_file; //fsteam object of file

}; //class BinMan

#endif
