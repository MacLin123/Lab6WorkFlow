#pragma once
#include <iostream>
class TDatValue
{
    public:
    virtual TDatValue* GetCopy() = 0; //create copy
    ~TDatValue() {}
};
typedef TDatValue* PTDatValue;