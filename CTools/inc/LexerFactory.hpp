#pragma once

#include "Globals.hpp"
#include "ScanMachine.hpp"
#include <string>
#include <vector>
#include <utility>
namespace CTools{
	typedef std::vector<std::pair<std::string,std::string> > Tokens_Table;
	class API ScannerFactory{
	private:
		static Tokens_Table parseTokens(const std::string& content); 	
	public:
		static ScanMachine* createFromString(const std::string& content);
		
		static ScanMachine* createFromFile(std::string path);
	};
}