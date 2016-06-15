#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

//------------------------------------------------------------------------------
/***< Debug Code */
//------------------------------------------------------------------------------
#ifdef DEBUG
	#define STD_LOG(x) std::clog << x << std::endl;
#else
	#define STD_LOG(x)
#endif /* DEBUG */

void forceStop(std::string fileName, unsigned lineNo); // assert function declaration

#ifdef DEBUG
	#define ASSERT(x) \
		if (x) \
			{} \
		else \
			forceStop(__FILE__,__LINE__)
#else
	#define ASSERT(x)
	// If DEBUG is not defined, the assertions will be "switched off".
#endif /* DEBUG */

#endif /* DEBUG_H */
