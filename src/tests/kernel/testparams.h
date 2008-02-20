/*                                                                              
 * PDFedit - free program for PDF document manipulation.                        
 * Copyright (C) 2006, 2007  PDFedit team:      Michal Hocko, 
 *                                              Miroslav Jahoda,       
 *                                              Jozef Misutka, 
 *                                              Martin Petricek                                             
 *
 * Project is hosted on http://sourceforge.net/projects/pdfedit                                                                      
 */ 
// vim:tabstop=4:shiftwidth=4:noexpandtab:textwidth=80

#ifndef _TESTPARAMS_H_
#define _TESTPARAMS_H_

/**
 * Parameter class.
 *	-all - prints all output
 *	-dir dirname - input directory
 *	-debug_level level - level of verbosity 0 - minimum; 5 - maximum
 *	all other parameters are treated as file (if they stand for regular file)
 *	or test name otherwise
 */
class TestParams : public libs::Singleton<TestParams>
{
	friend class libs::Singleton<TestParams>;

public:
	typedef std::vector<std::string> FileList;

	// Default test pdf file
	static const char* DEFAULT_PDF;
	static const char* DEFAULT_DIR;
	static const unsigned int DEFAULT_DEBUG_LEVEL;
	
	//
	// Params
	//
	FileList files;		// input pdf files
	
	std::string input_dir; // directory for special input files, configuration, multiversion
	static const std::string INPUT_DIR;
	
	bool all_output;	// output everything
	static const std::string ALL_OUTPUT;

	FileList tests;	// selected lists
	static const std::string TESTS;

	static const std::string DEBUG_LEVEL;
	unsigned int debugLevel;
	//
	// Methods
	//

	// parse parameters and fill in test_params
	static bool init (int argc, char* argv[]);

	// add path to filename
	static std::string add_path (const char* filename) {
		return instance().input_dir + "/" + std::string (filename);
	}

}; // class TestParams




#endif // _TESTPARAMS_H_
