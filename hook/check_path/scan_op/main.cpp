#include "scan_op.h"

//#include <ex
#include <regex>
#include <iostream>
using namespace std;

int main()
{
    cout << "== begin ==" << endl;



//    std::cmatch m;
//    auto ret = std::regex_search("123<xml>value</xml>456", m, reg);
//    if (ret)
//    {
//        for (auto& elem : m)
//            std::cout << elem << std::endl;
//    }


//    std::string qq = "12356789A";
//    std::regex qq_reg("[1-9]\\d{4,11}");
//    bool ret = std::regex_match(qq, qq_reg);
//    std::cout << (ret ? "valid" : "invalid") << std::endl;

//    try {

//        std::string str = "2023-06-07 10:18:54    /media/28FCEEE6FCEEAD6E/.Trash-1000/files/    123123 (第8个复件).4.txt.swp123";
//        std::regex reg("(.*.swp)");
//        std::cmatch m;
//        auto ret1 = std::regex_search(str.c_str(), m ,reg);
//        cout<<ret1<<endl;
//        if (ret1)
//        {
//            for (auto& elem : m)
//                std::cout << elem << std::endl;
//        }


//    } catch (...) {
//        cout << "== catch ==" << endl;
//    }

//    {
//        std::regex reg("<(.*)>(.*)</(\\1)>");
//        std::cmatch m;
//        auto ret = std::regex_search("123<xml>value</xml>456", m, reg);
//        if (ret)
//        {
//            for (auto& elem : m)
//                std::cout << elem << std::endl;
//        }

//    }



    scan_op op;
    op.open_scan();

    cout << "== end ==" << endl;
    return 0;
}
