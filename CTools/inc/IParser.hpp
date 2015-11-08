#pragma once
#include "Globals.hpp"
#include "ScanMachine.hpp"
#include <deque>
#include "PNode.hpp"

namespace CTools
{
	typedef std::deque<Token> TokenStream;

	class API IParser
	{
	public:
		virtual ~IParser(){}

		virtual PNode* Parse(TokenStream& stream)=0;
	};
}
