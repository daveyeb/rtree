#ifndef __RT__SCANNER_H__
#define __RT__SCANNER_H__

template <typename T>
class Scanner
{
protected:
    unsigned int current;

public:
    Scanner() {}
    ~Scanner() {}

    virtual T getCurrent() = 0;
    virtual T next() = 0;
};

#endif
