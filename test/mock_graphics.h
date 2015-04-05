#ifndef MOCK_GRAPHICS_H
#define MOCK_GRAPHICS_H

#include "../graphics.h"

class MockGraphics : public gbemu::IGraphics {
    MOCK_METHOD1(step, void(int));
    MOCK_METHOD1(get, unsigned char&(unsigned int));
    MOCK_CONST_METHOD1(get, const unsigned char&(unsigned int));

    virtual unsigned char& operator[](unsigned int i) { return get(i); }
    virtual const unsigned char& operator[](unsigned int i) const { return get(i); }

};

#endif
