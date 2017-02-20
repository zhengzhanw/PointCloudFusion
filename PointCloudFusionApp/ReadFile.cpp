#include "ReadFile.h"
#include <QDebug>

ReadFile::ReadFile()
{

}

bool ReadFile::open(const std::string filePath, ReadFile::iof_type type)
{
    m_iostream.open(filePath,IOS_IN|IOS_OUT|type);
    if(m_iostream.is_open())
        return true;
    return false;
}

bool ReadFile::read(char * data,int length)
{

    if(!m_iostream.eof())
    {
        m_iostream.read (data,length);
        return true;
    }
    return false;
}

bool ReadFile::write(char* data)
{
    if(m_iostream.is_open())
    {
        m_iostream << data ;
        return true;
    }
    return false;
}

bool ReadFile::close()
{
    if(m_iostream.is_open())
        m_iostream.close();
    return true;
}
