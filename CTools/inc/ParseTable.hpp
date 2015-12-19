#pragma once	

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>

namespace CTools
{
	enum class Action
	{
		SHIFT, REDUCE, ACCEPT, GOTO
	};
	struct API Row
	{
		std::string id;
	};

	struct API Col
	{
		int number;
	};

	struct API Cell
	{
		Row row;
		Col col;
		Action action;
		std::string reduce_rule;
		int shift_state;
	};

	struct API ParseTable
	{
		std::vector<Cell> table;

		static ParseTable load(std::istream& file)
		{
			ParseTable res;

			std::map<std::string, Row> rows;
			std::map<int, Col> cols;
//			std::ifstream file(fileName.c_str());
			int n = 0;
			file>>n;
			std::string line;
			for(int i=0;i<n;i++)
			{
				file>>line;
				Row r;
				r.id = line;
				rows[line] = r;
			}
			file>>n;
			for(int i=0;i<=n;i++)
			{
				Col c;
				c.number = i;
				cols[i] = c;
			}
			
			while(getline(file,line))
			{
				if(line.size()>0){
					std::stringstream ss(line);
					int number;
					std::string id,action;
					ss>>number>>id>>action;
					if(action == "SHIFT")
					{
						Cell c;
						c.col.number = number;
						c.row.id = id;
						c.action = Action::SHIFT;
						ss>>c.shift_state;
						res.table.push_back(c);
					}else if(action == "GOTO")
					{
						Cell c;
						c.col.number = number;
						c.row.id = id;
						c.action = Action::GOTO;
						ss>>c.shift_state;
						res.table.push_back(c);
					}else if(action == "ACCEPT")
					{
						Cell c;
						c.col.number = number;
						c.row.id = id;
						c.action = Action::ACCEPT;
						res.table.push_back(c);
					}else if(action == "R")
					{
						Cell c;
						c.col.number = number;
						c.row.id = id;
						c.action = Action::REDUCE;
						ss>>c.reduce_rule;
						res.table.push_back(c);
					}
				}
			}

			//file.close();
			return res;
		}
	};
//	struct API TableNode;
//
//	struct API TransitionTicket
//	{
//		TableNode* value;
//		int from_col, to_col,n;
//		bool AC;
//		TableNode* reduce_val;
//	};
//
//	typedef std::multimap<int, TransitionTicket*> PARSE_TABLE;
//
//	struct API TableNode
//	{
//		std::map<std::string, TableNode*> Transitions;
//		std::map<int,TransitionTicket> Table;
//
//		std::string ID;
//
//		TableNode* Parent;
//
//		bool AC;
//
//		bool isTerminal;
//
//		TableNode(std::string id = "")
//		{
//			ID = id;
//			Parent = nullptr;
//			AC = false;
//			isTerminal = false;
//		}
//
//		~TableNode()
//		{
//			std::map<std::string, TableNode*>::iterator it;
//			for(it = Transitions.begin(); it != Transitions.end(); it++)
//			{
//				delete it->second;
//			}
//			Transitions.clear();
//			Parent = nullptr;
//		}
//
//		static PARSE_TABLE load(std::string fileName)
//		{
//			std::map<std::string, TableNode*> meta_row;
//			PARSE_TABLE table;
//
//			TableNode* startNode;
//			std::ifstream file(fileName);
//			std::string line;
//			file>>line;
//			if(line == "<TOKENS>")
//			{
//				file>>line;
//				while(line != "</TOKENS>")
//				{
//					TableNode* n = new TableNode(line);
//					n->isTerminal = true;
//					meta_row[line] = n;
//					file>>line;
//				}
//			}
//			file>>line;
//			if(line == "<Nonterminals>")
//			{
//				file>>line;
//				bool first = true;
//				while(line != "</Nonterminals>")
//				{
//					TableNode* n = new TableNode(line);
//					n->isTerminal = false;
//					meta_row[line] = n;
//					if(first)
//					{
//						startNode = n;
//						first = false;
//					}
//					file>>line;
//				}
//			}
//			file>>line;
//			if(line == "<Transations>")
//			{
//				getline(file,line);
//				while(line != "</Transations>")
//				{
//					if(line.size()>0){
//						int from,to, n;
//						std::string val, ac, REDUCE_TO_WHAT;
//						std::stringstream sstr(line);
//						sstr>>from>>val>>to>>ac>>n>>REDUCE_TO_WHAT;
//						TransitionTicket* ticket = new TransitionTicket();
//						ticket->from_col = from;
//						ticket->to_col = to;
//						ticket->value = meta_row[val];
//						ticket->AC = false;
//						ticket->n = n;
//						if(ac == "AC")
//						{
//							ticket->AC = true;
//							ticket->reduce_val = meta_row[REDUCE_TO_WHAT];
//						}
//						table.insert(std::make_pair(from,ticket));
//					}
//					getline(file,line);
//				}
//			}
//
//			file.close();
//			return table;
//		}
//	};

}
