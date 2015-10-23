#pragma once

#include "Globals.hpp"
#include "ScanMachine.hpp"
#include <map>
#include <sstream>

namespace CTools
{
	class Position;
	class API ITokenProcessor
	{
	public:
		virtual ~ITokenProcessor(){}
		virtual void Process(Token& tkn, std::istream& file, errorCallback error)=0;
	};
}
