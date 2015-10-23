#pragma once
#include "Globals.hpp"
#include <map>
#include <assert.h>
namespace CTools{
	class API Memory{
	protected:
		byte* m_buffer;
		u32 m_size;
		u32 m_cursor;
		std::map<byte*, u32> m_allocTable;
		std::map<byte*, u32> m_freeTable;
		
		void merge();
	public:
		Memory(u32 size);
		virtual ~Memory();
		
		byte* c_alloc(u32 size);

		template<class T>
		T* alloc()
		{
			u32 size = sizeof(T);
			assert(size+m_cursor<m_size);
			byte* location = nullptr;
			for(auto block:m_freeTable){
				if(block.second >= size){
					m_freeTable[block.first+size] = block.second-size;
					m_freeTable.erase(m_freeTable.find(block.first));
					location = block.first;
					m_allocTable[location] = size;
					m_cursor += size;
					break;
				}
			}
			assert(location != nullptr);
			new (location) T();
			return (T*)location;
		}

		template<class T, class A>
		T* alloc(A arg0)
		{
			u32 size = sizeof(T);
			assert(size+m_cursor<m_size);
			byte* location = nullptr;
			for(auto block:m_freeTable){
				if(block.second >= size){
					m_freeTable[block.first+size] = block.second-size;
					m_freeTable.erase(m_freeTable.find(block.first));
					location = block.first;
					m_allocTable[location] = size;
					m_cursor += size;
					break;
				}
			}
			assert(location != nullptr);
			new (location) T(arg0);
			return (T*)location;
		}

		template<class T, class A, class B>
		T* alloc(A arg0,B arg1)
		{
			u32 size = sizeof(T);
			assert(size+m_cursor<m_size);
			byte* location = nullptr;
			for(auto block:m_freeTable){
				if(block.second >= size){
					m_freeTable[block.first+size] = block.second-size;
					m_freeTable.erase(m_freeTable.find(block.first));
					location = block.first;
					m_allocTable[location] = size;
					m_cursor += size;
					break;
				}
			}
			assert(location != nullptr);
			new (location) T(arg0,arg1);
			return (T*)location;
		}

		template<class T, class A, class B, class C>
		T* alloc(A arg0, B arg1, C arg2)
		{
			u32 size = sizeof(T);
			assert(size+m_cursor<m_size);
			byte* location = nullptr;
			for(auto block:m_freeTable){
				if(block.second >= size){
					m_freeTable[block.first+size] = block.second-size;
					m_freeTable.erase(m_freeTable.find(block.first));
					location = block.first;
					m_allocTable[location] = size;
					m_cursor += size;
					break;
				}
			}
			assert(location != nullptr);
			new (location) T(arg0,arg1,arg2);
			return (T*)location;
		}
		
		template<class T>
		void free(T* ptr)
		{
			ptr->~T();
			auto it = m_allocTable.find((byte*)ptr);
			assert(it != m_allocTable.end());
			memset(ptr,0, it->second);
			m_cursor -= it->second;
			m_freeTable[(byte*)ptr] = it->second;
			m_allocTable.erase(it);
			merge();
			return;
		}
		
		void terminate();
	};
}