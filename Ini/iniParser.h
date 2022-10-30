#pragma once
#include<iostream>
#include<map>
#include<string>
#include<sstream>

namespace Sakura
{
namespace iniParser
{
class Value
{
public:
    /*构造函数以及构造函数的重载*/
    Value();
    Value(bool value);
    Value(int value);
    Value(double value);
    Value(const char* value);
    Value(const std::string &value);

    /*运算符重载:实现等号赋值*/
    Value & operator = (bool value);
    Value & operator = (int value);
    Value & operator = (double value);
    Value & operator = (const char* value);
    Value & operator = (std::string &value);

    /*运算符重载实现类型赋值*/
    operator bool();
    operator int();
    operator double();
    operator std::string();

    //析构函数
    ~Value();

private:
    std::string m_value;
};

typedef std::map<std::string,Value>Section;

class IniFile
{
public:
    IniFile();
    /**
     * @brief:加载ini文件
     * @param:文件路径
     * @return:若加载ini文件成功则返回true,否则false
     * @author:SY
    */
    bool loadIniFile(const std::string &fileName);

    /**
     * @brief:去除字符串前后空格、回车符、换行符
     * @param:传入的字符串
     * @return:返回去除格式后的字符串
     * @author:SY
    */
    std::string trimmed(std::string s);

    /**
     * @brief:获取某个section中的key
     * @param:section和key
     * @return:返回Value对象
     * @author:SY
    */
    Value & get(const std::string &section,const std::string &key);

    /*中括号重载*/
    Section & operator [] (const std::string section)
    {
        return m_sections[section];
    }

    
    /**
     * @brief:向section的key设置不同种类的value
     * @param:section、key、value
     * @return:无
     * @author:SY
    */
    template<class T>
    void set(const std::string &section,const std::string &key,T value);

    /**
     * @brief:判断ini文件中是否包含该section和key
     * @param:section、key
     * @return:若包含则返回true，否则返回false
     * @author:SY
    */
    bool has(const std::string &section,const std::string &key);
    /**
     * @brief:判断ini文件中是否包含该section
     * @param:section
     * @return:若包含则返回true,否则返回false
     * @author:SY
    */
    bool has(const std::string &section);

    /*删除ini文件中的section对应的key或者section*/
    void remove(const std::string &section,const std::string &key);
    void remove(const std::string &section);
    //清空m_section
    void clear();

    //打印ini文件中的section、key、value
    void print();

    //获取ini文件的所有字符串
    std::string str();

    //另存ini文件
    void save(const std::string &fileName);
    
    ~IniFile();

private:
    std::string m_fileName;
    std::map<std::string,Section>m_sections;
};

}
}