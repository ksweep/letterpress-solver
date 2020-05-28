//
//  BoardLetter.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef BoardLetter_hpp
#define BoardLetter_hpp

#include <assert.h>

class BoardLetter {
public:
    char character;
    int index;
    int color;

    BoardLetter(char ch, int in, int co) : character(ch), index(in), color(co) {
        assert(character >= 'a' && character <= 'z');
        assert(index >= 0 && index <= 24);
        assert(color >= 0 && color <= 2);
    };
private:
};

#endif /* BoardLetter_hpp */
