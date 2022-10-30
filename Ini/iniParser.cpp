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
    // //������ת��Ϊ�ַ���
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
    //��c���Ե��ַ���ת��Ϊ����
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
 * @brief:ȥ���ַ���ǰ��ո񡢻س��������з�
 * @param:��
 * @return:����ȥ����ʽ����ַ���
 * @author:SY
*/
std::string IniFile::trimmed(std::string s)
{
    if(s.empty())
    {
        return s;
    }
    //ɾ��ǰ��ո񡢻س��������з�
    s.erase(0,s.find_first_not_of(" \n\r"));
    s.erase(s.find_last_not_of(" \n\r")+1);
    return s;
}

/**
 * @brief:����ini�ļ�
 * @param:�ļ�·��
 * @return:������ini�ļ��ɹ��򷵻�true,����false
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
    //��ȡÿ������
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
            //��¼�����ŵ�����λ��
            int pos=line.find_first_of("]");
            //��ȡ���section�ַ���
            section=line.substr(1,pos-1);
            //��ŵ�m_sections��
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
 * @brief:��ȡĳ��section�е�key
 * @param:section��key
 * @return:����Value����
 * @author:SY
*/
Value & IniFile::get(const std::string &section,const std::string &key)
{
    return m_sections[section][key];
}

/**
 * @brief:��section��key���ò�ͬ�����value
 * @param:section��key��value
 * @return:��
 * @author:SY
*/
template<class T>
void IniFile::set(const std::string &section,const std::string &key,T value)
{
    m_sections[section][key]=value;
}
/**
 * @brief:�ж�ini�ļ����Ƿ������section��key
 * @param:section��key
 * @return:�������򷵻�true�����򷵻�false
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
 * @brief:�ж�ini�ļ����Ƿ������section
 * @param:section
 * @return:�������򷵻�true,���򷵻�false
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

