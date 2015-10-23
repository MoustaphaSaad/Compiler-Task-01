#pragma once
#include "Globals.hpp"

#include <map>
#include <set>
#include <vector>

namespace CTools{
	class API State{
	protected:
		std::multimap<char, State*> m_transition;
		
		s32 m_id;
		std::set<State*> m_NFAStates;
		bool m_accept;
		
	public:
		State();
		State(s32 id);
		State(s32 id, bool accept);
		State(std::set<State*> NFAState, s32 nID);
		
		virtual ~State();
		
		void addTransition(char input, State* state);
		
		void removeTransition(State* state);
		
		void getTransition(char input, std::vector<State*> &states);

		State* Consume(char c);
		
		s32 getId();

		void setId(s32 val);
		
		bool isDeadEnd();

		s32 getTransitionCount(){return m_transition.size();}
		
		bool isAcceptState();

		void setAccept(bool val){m_accept = val;}

		std::set<State*>& getNFAState(){return m_NFAStates;}
	};
}