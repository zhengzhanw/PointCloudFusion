#ifndef READFILE_H
#define READFILE_H

#include "export.h"
#include <iostream>
#include <fstream>

class POINTCLOUDFUSIONAPP_EXPORT ReadFile
{
public:

    enum iof_type{
        IOS_IN=std::ios::in,
        IOS_OUT=std::ios::out,
        IOS_ATE=std::ios::ate,
        IOS_APP=std::ios::app,
        IOS_TRUNC=std::ios::trunc,
        IOS_BINARY=std::ios::binary
    };

public:
    ReadFile();
    bool open(const std::string,iof_type);
    bool read(char *,int);
    bool write(char *);
    bool close();



private:
    std::fstream m_iostream;

};

#endif // READFILE_H
