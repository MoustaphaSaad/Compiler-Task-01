#pragma once

#include "Globals.hpp"
#include "FSM.hpp"
#include <deque>
#include <string>
#include <stack>

namespace CTools{
	typedef std::deque<State*> FSA_TABLE;
	class API RegEx{
		u32 m_nNextStateID;
		FSA_TABLE m_NFATable, m_DFATable;

		std::stack<FSA_TABLE> m_OperandStack;
		std::stack<char> m_OperatorStack;
		std::set<char> m_InputSet;
	public:

		RegEx(){m_nNextStateID=0;}
		~RegEx(){}
		void push(char c);
		
		bool pop(FSA_TABLE& table);
		
		bool isOperator(char c);
		
		bool presedence(char left, char right);
		
		bool isInput(char c);
		
		bool concat();
		
		bool star();
		
		bool Union();

		void Combine(RegEx& reg);
		
		std::string concatExpand(std::string reg);
		
		std::string rangeExpand(std::string red);

		std::string plusExpand(std::string reg);

		std::string operatorExpand(std::string reg);
				
		bool createNFA(std::string reg);

		FSA_TABLE& getNFA(){return m_NFATable;}

		State* getDFAStart(){if(m_DFATable.size()==0)return nullptr; return m_DFATable[0];}

		State* getDFAState(s32 id)
		{
			FSA_TABLE::iterator it;
			for(it=m_DFATable.begin();it!=m_DFATable.end();it++)
			{
				if((*it)->getId() == id)
					return *it;
			}
			return nullptr;
		}

		bool Eval();

		void EpsilonClosure(std::set<State*> input, std::set<State*> &output);

		void Move(char c, std::set<State*> input, std::set<State*> &output);
		
		void ConvertToDFA();

		void OptimizeDFA();
	};
}