#include<iostream>
#include"ini/iniParser.h"
#include"ini/iniParser.cpp"
using namespace Sakura::iniParser;

int main()
{
    //std::cout<<"hello Sakura"<<std::endl;
    /*构造函数测试*/
    // Value v1(true);
    // Value v2(123);
    // Value v3(1.23);
    // Value v4("hello world");

    /*运算符重载测试*/
    // Value v1;
    // v1=true;
    // Value v2;
    // v2=123;
    // Value v3;
    // v3=1.23;
    // Value v4;
    // v4="hello world";

    // Value v1(true);
    // bool b=v1;
    // Value v2(123);
    // int i=v2;
    // Value v3(1.23);
    // double d=v3;
    // Value v4("hello world");
    // const std::string &s=v4;

    /*测试读取ini文件中的key和section*/
    IniFile ini;
    ini.loadIniFile("./main.ini");

    const std::string &ip=ini["server"]["ip"];
    int port=ini.get("server","port");

    ini.set("server","timeout",1000);
    ini.set("server","flag",true);

    bool ret=ini.has("server22");

    ini.remove("server","flag");

    ini.print();

    ini.save("./temp.ini");

    return 0;
}