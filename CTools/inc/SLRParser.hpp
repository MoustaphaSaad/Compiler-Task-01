#pragma once
#include "IParser.hpp"
#include "ParseTable.hpp"

namespace CTools
{
	struct API stackElement
	{
		std::string str;
		int num;
		Cell cell;
		PNode* node;
		Token token;
	};

	class API SLRParser: public IParser
	{
		TokenStream::iterator m_begin, m_end, m_cursor;
		ParseTable m_table;
		stackElement m_state;

		stackElement move(stackElement element,std::string str);

		PNode* reduce(std::stack<stackElement>& parsing_stack, std::string id);
		PNode* reduceReadstmt(std::stack<stackElement>& parsing_stack);
		PNode* reduceID(std::stack<stackElement>& parsing_stack);
		PNode* reduceMatch(std::stack<stackElement>& parsing_stack);
		PNode* reduceStatement(std::stack<stackElement>& parsing_stack);
		PNode* reduceStSeq(std::stack<stackElement>& parsing_stack);
		PNode* reduceFactor(std::stack<stackElement>& parsing_stack);
		PNode* reduceMulop(std::stack<stackElement>& parsing_stack);
		PNode* reduceTerm(std::stack<stackElement>& parsing_stack);
		PNode* reduceAddop(std::stack<stackElement>& parsing_stack);
		PNode* reduceComparison(std::stack<stackElement>& parsing_stack);
		PNode* reduceSimpleExp(std::stack<stackElement>& parsing_stack);
		PNode* reduceExp(std::stack<stackElement>& parsing_stack);
		PNode* reduceAssignstmt(std::stack<stackElement>& parsing_stack);
		PNode* reduceWritestmt(std::stack<stackElement>& parsing_stack);
		PNode* reduceRepeatstmt(std::stack<stackElement>& parsing_stack);
		PNode* reduceIFstmt(std::stack<stackElement>& parsing_stack);
		PNode* reduceProgram(std::stack<stackElement>& parsing_stack);
	public:
		SLRParser(ParseTable table);
		PNode* Parse(TokenStream& stream) override;

		PNode* ParseProgram();

		~SLRParser(void); 
	};
}

