//
// Created by magicsun on 16-2-10.
//

#include <string.h>
#include <stdio.h>
#include "Bitmap.h"

void Bitmap::init(int n)
{
    _size = (n + 7) / 8;//向上取整
    _bitData = new char[_size];
    memset(_bitData, 0, _size);
}

Bitmap::Bitmap(const char *file, int n)
{
    init(n);
	FILE *fp = nullptr;

	//fopen_s(&fp, file, "r");
    fread(_bitData, sizeof(char), _size, fp);
    fclose(fp);
}

void Bitmap::dump(const char *file)
{
	FILE *fp = nullptr;
	//fopen_s(&fp, file, "w");
    fwrite(_bitData, sizeof(char), _size, fp);
    fclose(fp);
}

std::string Bitmap::bits2string(int n)
{
    expand(n - 1);
    std::string str(n, '\0');
    for(int i = 0; i < n; ++i)
    {
        str[i] = (test(i)? '1' : '0');
    }
    return str;
}

void Bitmap::expand(int k)
{
    if(k < _size * 8)
    {
        return;
    }

    int oldSize = _size;
    const char *oldBitData = _bitData;
    init(k * 2);

    memcpy(_bitData, oldBitData, _size);

    delete oldBitData;
}
