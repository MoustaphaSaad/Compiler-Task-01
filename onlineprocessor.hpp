#ifndef ONLINEPROCESSOR_HPP
#define ONLINEPROCESSOR_HPP

#include <CTools.hpp>

class OnlineProcessor:public CTools::ITokenProcessor
{
public:
    OnlineProcessor(){}
    ~OnlineProcessor(){}

    void Process(CTools::Token& tkn, std::istream& file, CTools::errorCallback error) override
    {

        int n = 0;
        if(tkn.tag == "COMMENT")
        {
            int n = 1;
            char c;
            file.get();
            while(file.get(c))
            {
                if(c == '{')
                {
                    n++;
                }else if(c=='}')
                {
                    n--;
                }

                tkn.lexeme.push_back(c);

                if(n==0)
                {
                    break;
                }
            }
            if(n!=0)
            {
                error("comment didn't end correctly",tkn.position);
            }
        }
    }
};
#endif // ONLINEPROCESSOR_HPP

