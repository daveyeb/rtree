#ifndef __RT__SCANNER_H__
#define __RT__SCANNER_H__

namespace RTToken
{

    template <typename T>
    class Scanner
    {
    public:
        virtual T current() const = 0;
        virtual T next() = 0;

    protected:
        unsigned int _current;
    };

}

#endif
