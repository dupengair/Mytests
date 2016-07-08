#ifndef _MYCOUT_H
#define _MYCOUT_H



namespace MYCOUT
{    
    std::ostream& operator << (std::ostream &os, char *str)
        {
        //os << "This is mycout : " << str;

        return os;
        }

    std::ostream& operator << (std::ostream &os, const char *str)
        {
        //os << "This is mycout : " << str;

        return os;
        }

}


#endif
