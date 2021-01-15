#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <string>

class StringHelper
{
private:

std::string result;
std::string input;
public:
    StringHelper();
    StringHelper( std::string const&  text);
    size_t GetIndex(size_t  elementCount,const std::string str,std::string val);
    std::string GetConnectionString(std::string serverName, std::string dbName);

};

#endif // STRINGHELPER_H
