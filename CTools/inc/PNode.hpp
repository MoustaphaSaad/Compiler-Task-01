#pragma once

#include "Globals.hpp"
#include <vector>

namespace CTools{
    class API PNode{
        std::vector<PNode*> m_childrens;
        PNode* m_parent;
    public:
        std::string Tag;
        std::string Value;

        PNode();
        virtual ~PNode();

        void addChild(PNode* child);
        PNode* getParent();
        void setParent(PNode* parent);
        PNode* operator[](u32 ix);
        u32 size();
    };
}
