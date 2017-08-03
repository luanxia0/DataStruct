//
// Created by magicsun on 16-2-10.
//

#ifndef DATASTRUCTS_BITMAP_H
#define DATASTRUCTS_BITMAP_H

#include <string>

class Bitmap
{
private:
    char *_bitData;
    int _size;

protected:
    void init(int n);
    void expand(int k);

public:

    Bitmap(int n = 8){ init(n); }
    Bitmap(const char *file, int n = 8);
    ~Bitmap(){delete _bitData; _bitData = nullptr;}

    void set(int k)
    {
        expand(k);
        _bitData[k >> 3] |= (0x80 >> (k & 0x07));
    }
    void clear(int k)
    {
        expand(k);
        _bitData[k >> 3] &= ~(0x80 >> (k & 0x07));
    }
    bool test(int k)
    {
        expand(k);
        return _bitData[k >> 3] & (0x80 >> (k & 0x07));
    }

    void dump(const char *file);

    std::string bits2string(int n);

};


#endif //DATASTRUCTS_BITMAP_H
