#include"iniParser.h"
#include<fstream>
#include<stdlib.h>
using namespace Sakura::iniParser;

Value::Value()
{

}
Value::Value(bool value)
{
    // m_ini=value ? "true" : "false";
    *this=value;
}
Value::Value(int value)
{
    // std::stringstream ss;
    // ss<<value;
    // //将整形转化为字符串
    // m_ini=ss.str();
    *this=value;
}
Value::Value(double value)
{
    // std::stringstream ss;
    // ss<<value;
    // m_ini=ss.str();
    *this=value;
}
Value::Value(const char* value)
{
    *this=value;
}
Value::Value(const std::string &value) 
{
    *this=value;
}
Value::~Value()
{

}

Value & Value::operator = (bool value)
{
    m_value=value ? "true" : "false";
    return *this;
}
Value & Value::operator = (int value)
{
    std::stringstream ss;
    ss<<value;
    m_value=ss.str();
    return *this;
}
Value & Value::operator = (double value)
{
    std::stringstream ss;
    ss<<value;
    m_value=ss.str();
    return *this;
}
Value & Value::operator = (const char* value)
{
    m_value=value;
    return *this;
}
Value & Value::operator = (std::string &value)
{
    m_value=value;
    return *this;
}

Value::operator bool()
{
    if(m_value=="true")
    {
        return true;
    }
    return false;
}
Value::operator int()
{
    //将c语言的字符串转化为整形
    return (std::atoi(m_value.c_str()));
}
Value::operator double()
{
    return (std::atof(m_value.c_str()));
}
Value::operator std::string()
{
    return m_value;
}

IniFile::IniFile()
{

}
IniFile::~IniFile()
{

}

/**
 * @brief:去除字符串前后空格、回车符、换行符
 * @param:无
 * @return:返回去除格式后的字符串
 * @author:SY
*/
std::string IniFile::trimmed(std::string s)
{
    if(s.empty())
    {
        return s;
    }
    //删除前后空格、回车符、换行符
    s.erase(0,s.find_first_not_of(" \n\r"));
    s.erase(s.find_last_not_of(" \n\r")+1);
    return s;
}

/**
 * @brief:加载ini文件
 * @param:文件路径
 * @return:若加载ini文件成功则返回true,否则false
 * @author:SY
*/
bool IniFile::loadIniFile(const std::string &fileName)
{
    m_fileName=fileName;
    std::ifstream fin(fileName);
    if(fin.fail())
    {
        return false;
    }
    //读取每行数据
    std::string line;
    std::string section;
    while(std::getline(fin,line))
    {
        line=trimmed(line);
        if(line=="")
        {
            continue;
        }
        if(line[0]=='[')
        {
            //记录右括号的索引位置
            int pos=line.find_first_of("]");
            //截取获得section字符串
            section=line.substr(1,pos-1);
            //存放到m_sections中
            section=trimmed(section);
            m_sections[section]=Section();
        }
        else
        {
            int pos=line.find_first_of("=");
            std::string key=line.substr(0,pos);
            key=trimmed(key);
            std::string value=line.substr(pos+1,line.length()-pos);
            value=trimmed(value);
            m_sections[section][key]=value;
        }
        //std::cout<<line<<std::endl;
    }
    fin.close();
    return true;
}

/**
 * @brief:获取某个section中的key
 * @param:section和key
 * @return:返回Value对象
 * @author:SY
*/
Value & IniFile::get(const std::string &section,const std::string &key)
{
    return m_sections[section][key];
}

/**
 * @brief:向section的key设置不同种类的value
 * @param:section、key、value
 * @return:无
 * @author:SY
*/
template<class T>
void IniFile::set(const std::string &section,const std::string &key,T value)
{
    m_sections[section][key]=value;
}
/**
 * @brief:判断ini文件中是否包含该section和key
 * @param:section、key
 * @return:若包含则返回true，否则返回false
 * @author:SY
*/
bool IniFile::has(const std::string &section,const std::string &key)
{
    auto it=m_sections.find(section);
    if(it!=m_sections.end())
    {
        return (it->second.find(key)!=it->second.end());
    }
    return false;
}
/**
 * @brief:判断ini文件中是否包含该section
 * @param:section
 * @return:若包含则返回true,否则返回false
 * @author:SY
*/
bool IniFile::has(const std::string &section)
{
    return (m_sections.find(section) != m_sections.end());
}

void IniFile::remove(const std::string &section,const std::string &key)
{
    auto it=m_sections.find(section);
    if(it!=m_sections.end())
    {
        it->second.erase(key);
    }
}
void IniFile::remove(const std::string &section)
{
    m_sections.erase(section);
}
void IniFile::clear()
{
    m_sections.clear();
}

std::string IniFile::str()
{
    std::stringstream ss;
    for(auto it=m_sections.begin();it!=m_sections.end();it++)
    {
        ss<<"[" <<it->first<< "]"<<std::endl;
        for(auto iter=it->second.begin();iter!=it->second.end();iter++)
        {
            ss<<iter->first<< "=" <<std::string(iter->second)<<std::endl;
        }
        ss<<std::endl;
    }
    return ss.str();
}

void IniFile::print()
{
    std::cout<<str();
}

void IniFile::save(const std::string &fileName)
{
    std::ofstream fout(fileName);
    if(fout.fail())
    {
        return;
    }
    fout<<str();
    fout.close();
}

