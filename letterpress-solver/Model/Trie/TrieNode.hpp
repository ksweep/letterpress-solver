//
//  TrieNode.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef TrieNode_hpp
#define TrieNode_hpp

#include <vector>
#include <string>

class TrieNode {
public:
    TrieNode() {
        children = std::vector<TrieNode*>(26, nullptr);
        prefix = "";
        is_word = false;
    }

    TrieNode(char c) {
        children = std::vector<TrieNode*>(26, nullptr);
        prefix = "";
        is_word = false;
    }

    std::vector<TrieNode*> children;
    std::string prefix; // not necessary -- this just helps with debugging
    bool is_word;
};

#endif /* TrieNode_hpp */
