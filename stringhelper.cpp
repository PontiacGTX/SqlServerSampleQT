#include "stringhelper.h"

StringHelper::StringHelper()
{

}

StringHelper::StringHelper( std::string const&  text)
{
    this->input = text;
}



size_t StringHelper::GetIndex(size_t  elementCount,const std::string str,std::string val)
{
    size_t elementFoundAt=0;
    size_t counter = 0;
    while(counter!=elementCount)
    {
        if((elementFoundAt = str.find(val,elementFoundAt))!=0)
        {
            counter++;
        }
    }
   return elementFoundAt;

}

std::string StringHelper::GetConnectionString(std::string serverName, std::string dbName)
{
    std::string server = input.substr(0,7) + serverName + ";";
    size_t index = GetIndex(1,input,";");
    std::string Database = input.substr(index,9) + dbName;
    index = GetIndex(2,input,";");
    std::string remaining = input.substr(index,input.length() - index);
    return (result = server + Database + remaining) ;

}
