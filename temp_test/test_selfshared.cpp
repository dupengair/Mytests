#include "test_selfshared.h"

main() 
{
    std::shared_ptr<selfshared> sptr = std::make_shared<selfshared>(1);
    sptr->counter();

    std::shared_ptr<selfshared> sptr2 = CreateObj(2);
    sptr2->counter();

    std::shared_ptr<selfshared2> s2ptr = std::make_shared<selfshared2>(1);
    s2ptr->counter();
}
    
