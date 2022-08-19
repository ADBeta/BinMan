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
* 19 Aug 2022
* Version 0.25
*******************************************************************************/

#ifndef BINMAN_H
#define BINMAN_H

#include <fstream>

using std::string;

class BinMan {
	public:
	/** Constructor and configuration *****************************************/	
	//Constructor passes filename to BinMan
	BinMan(const char*);
	~BinMan(); //Deconstructor to force clean of RAM

	//Flags
	//Verbosity flag. true allows output of information, warnings and more
	bool Verbose = false;



	/** File managment ********************************************************/
	//Read the file into a RAM buffer, then close the file - for next operation
	void read();
	//Print a selected chunk of the file, from offset 1 to offset 2
	void printChunk(const std::streamsize, const std::streamsize);
	//Print the *entire* contents of the file
	//!!This may be slow and flood the terminal
	void printAll();
	
	//Close a file if it is open. can be called at any point
	void close();
	//Flush the buffer array and close the file
	void flush();
	
	/** Helper functions ******************************************************/
	//Print a single hex char to cout, in uppercase and 2 width format
	void pHex(const unsigned char);
	
	//private:
	const char* m_filename; //Filename as char array
	std::fstream m_file; //fsteam object of file
	
	unsigned char *m_fBuffer; //File buffer array to be malloc'd
	std::streamsize m_fBufSize; //Size in bytes of the buffer
	
	unsigned char *m_selBuffer; //Selected chunk of the file to work on
	std::streamsize m_sBufSize; //Size in bytes of select buffer
	
	/** Configuration Flags and Variables *************************************/
	//file read size limit before panic exit - default 5MB
	std::streamsize _maxInputBytes = 5242880;
	//buffer max size when increasing before error and fail - default 5MB
	std::streamsize _maxBufferBytes = 5242880;

	/** Error, warning and info printing. *************************************/
	//info. two optional messages
	void infoMsg(const string &, const string & = "");
	//Warning message, two optional messages
	void warnMsg(const string &, const string & = "");
	//Error then exit program. two optional messages
	void errMsg(const string &, const string &, const string & = "");
	
	//Safe cleanup and exit function, allows exit code
	void cleanExit(int exitcode);

}; //class BinMan

#endif
