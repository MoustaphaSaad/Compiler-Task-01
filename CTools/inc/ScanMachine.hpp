#pragma once

#include "Globals.hpp"
#include "RegEx.hpp"
#include <set>

namespace CTools
{
	enum class ScanState:u8
	{
		NONE=0, CONVERGED=1, AMBIGUIOUS=2, STABLE=3, START = 4
	};

	class API Token
	{
	public:
		bool valid;
		std::string tag;
		std::string lexeme;
		Position position;

		static Token INVALID()
		{
			Token t;
			t.valid = false;
			return t;
		}
	};

	class API IScanner
	{
	public:
		virtual ~IScanner(){}
		virtual ScanState consume(char c)=0;
		virtual void reset() =0;
		virtual ScanState cut()=0;
		virtual ScanState recover()=0;
		virtual Token getToken()=0;
		virtual ScanState getCurrentState()=0;
		virtual std::string getCurrentString()=0;
	};

	struct API Layer
	{
		std::vector<State*> activeStates;
		std::vector<s32> activeMIX;
		std::string lexeme;
		ScanState state;
	};

	class API ScanMachine: public IScanner
	{
	private:
		std::vector<RegEx*> m_littleMachines;

		std::vector<std::string> m_tags;

		std::vector<State*> m_activeStates;

		std::vector<s32> m_activeMIX;

		std::stack<Layer> m_StateStack;

		std::string m_word;

		ScanState m_state;

		void insertLayer();
	public:

		~ScanMachine();

		void addSubMachine(RegEx* machine, std::string tag);

		ScanState consume(char c) override;

		void reset() override;

		ScanState cut() override;

		ScanState recover() override;

		Token getToken() override;

		ScanState getCurrentState()override ;

		std::string getCurrentString() override;
	};

}