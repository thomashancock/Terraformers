#include "Debug.hpp"

void forceStop(std::string fileName, unsigned lineNo) {
  fflush(NULL);
	std::cerr << "\nAssertion failed: Line: " << lineNo << ", File: " << fileName << std::endl;
	exit(0);
}
