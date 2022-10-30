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
    /*���캯���Լ����캯��������*/
    Value();
    Value(bool value);
    Value(int value);
    Value(double value);
    Value(const char* value);
    Value(const std::string &value);

    /*���������:ʵ�ֵȺŸ�ֵ*/
    Value & operator = (bool value);
    Value & operator = (int value);
    Value & operator = (double value);
    Value & operator = (const char* value);
    Value & operator = (std::string &value);

    /*���������ʵ�����͸�ֵ*/
    operator bool();
    operator int();
    operator double();
    operator std::string();

    //��������
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
     * @brief:����ini�ļ�
     * @param:�ļ�·��
     * @return:������ini�ļ��ɹ��򷵻�true,����false
     * @author:SY
    */
    bool loadIniFile(const std::string &fileName);

    /**
     * @brief:ȥ���ַ���ǰ��ո񡢻س��������з�
     * @param:������ַ���
     * @return:����ȥ����ʽ����ַ���
     * @author:SY
    */
    std::string trimmed(std::string s);

    /**
     * @brief:��ȡĳ��section�е�key
     * @param:section��key
     * @return:����Value����
     * @author:SY
    */
    Value & get(const std::string &section,const std::string &key);

    /*����������*/
    Section & operator [] (const std::string section)
    {
        return m_sections[section];
    }

    
    /**
     * @brief:��section��key���ò�ͬ�����value
     * @param:section��key��value
     * @return:��
     * @author:SY
    */
    template<class T>
    void set(const std::string &section,const std::string &key,T value);

    /**
     * @brief:�ж�ini�ļ����Ƿ������section��key
     * @param:section��key
     * @return:�������򷵻�true�����򷵻�false
     * @author:SY
    */
    bool has(const std::string &section,const std::string &key);
    /**
     * @brief:�ж�ini�ļ����Ƿ������section
     * @param:section
     * @return:�������򷵻�true,���򷵻�false
     * @author:SY
    */
    bool has(const std::string &section);

    /*ɾ��ini�ļ��е�section��Ӧ��key����section*/
    void remove(const std::string &section,const std::string &key);
    void remove(const std::string &section);
    //���m_section
    void clear();

    //��ӡini�ļ��е�section��key��value
    void print();

    //��ȡini�ļ��������ַ���
    std::string str();

    //���ini�ļ�
    void save(const std::string &fileName);
    
    ~IniFile();

private:
    std::string m_fileName;
    std::map<std::string,Section>m_sections;
};

}
}