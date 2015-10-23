#pragma once
#include "Globals.hpp"
#include "ScanMachine.hpp"
#include "TokenProcessor.hpp"
namespace CTools
{

	typedef std::vector<std::pair<std::string, Position> > ErrorStream;
	class API IWalker
	{
	public:
		errorCallback errorFunction;

		virtual ~IWalker(){}
		virtual Token token(std::istream& stream)=0;
	};

	class API MachineWalker: public IWalker
	{
		IScanner* scanner;
		ITokenProcessor* online_processor;
		Position pos;
		void online_process(Token& t, std::istream& stream);
	public:
		MachineWalker(IScanner* lex,ITokenProcessor* p =nullptr);
		Token token(std::istream& stream) override;
		void reset();
	};
	
}