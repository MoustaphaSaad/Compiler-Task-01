#pragma once
#include "Globals.hpp"
#include "Memory.hpp"

namespace CTools{
	class API Services{
	public:
		static Memory* memory;
		
		static void init();	
		static void terminate();
	};
}
