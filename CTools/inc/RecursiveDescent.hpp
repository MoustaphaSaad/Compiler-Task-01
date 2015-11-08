#pragma once

#include "Globals.hpp"
#include "IParser.hpp"
#include <vector>

namespace CTools
{
	class API RecursiveDescent: public IParser
	{
		//iterator for begining of stream
		TokenStream::iterator m_begin;
		TokenStream::iterator m_end;
		TokenStream::iterator m_cursor;

		std::vector<std::string> m_errors;

		PNode* match(std::string tag);

		void rassert(bool exp,std::string msg);
	protected:
		void error(std::string msg);
	public:
		RecursiveDescent();
		~RecursiveDescent();

		PNode* Parse(TokenStream& stream) override;

		PNode* program();

		PNode* stmt_sequence();

		PNode* statement();

		PNode* read_stmt();

		PNode* assign_stmt();

		PNode* exp();

		PNode* comparison_op();

		PNode* add_op();

		PNode* mul_op();

		PNode* factor();

		PNode* term();

		PNode* simple_exp();

		PNode* write_stmt();

		PNode* repeat_stmt();

		PNode* if_stmt();

		std::vector<std::string> getErrors();
	};
}
