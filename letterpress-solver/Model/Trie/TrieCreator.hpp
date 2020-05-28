//
//  TrieCreator.hpp
//  letterpress-solver
//
//  Copyright © 2020 Kevin Broom. All rights reserved.
//

#ifndef TrieCreator_hpp
#define TrieCreator_hpp

#include <fstream>
#include <string>

#include "TrieNode.hpp"

class TrieCreator {
public:
    static TrieNode* MakeTrie(std::string file_name) {
        // make trie from provided dictionary
        TrieNode* root = new TrieNode();
        std::ifstream word_file(file_name);
        std::string current_line;
        while (word_file >> current_line) {
            // convert to lowercase
            std::transform(current_line.begin(), current_line.end(), current_line.begin(), [](unsigned char c){ return std::tolower(c); });

            TrieNode* current_node = root;
            for (char c : current_line) {
                if (current_node->children[c - 'a'] == nullptr) {
                    current_node->children[c - 'a'] = new TrieNode(c);
                }
                current_node->children[c - 'a']->prefix = current_node->prefix + c;
                current_node = current_node->children[c - 'a'];
            }
            current_node->prefix = current_line;
            current_node->is_word = true;
        }
        return root;
    }
};

#endif /* TrieCreator_hpp */
