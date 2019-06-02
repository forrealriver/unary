#pragma once

class Filter
{
public:
    Filter(void);
    ~Filter(void);
    int Filter::filter(CStringArray &fileNames, CStringArray &filterNames);
};
