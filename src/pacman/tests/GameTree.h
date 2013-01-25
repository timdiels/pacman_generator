/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../generator/GameTree.h"
#include "../model/Action.h"

#include <vector>
#include <memory>

namespace PACMAN {

    namespace GENERATOR {
        struct ChoiceNode;
    }

    namespace TEST {

        struct TreeNode {
            int score;
            int player;
            std::shared_ptr<TreeNode> parent;
            std::vector<std::shared_ptr<TreeNode>> children;
        };

        class GameTree : public GENERATOR::GameTree
        {
        public:
            GameTree(std::shared_ptr<TreeNode> root) ;

            void init(unsigned int max_rounds);
            void parent();
            void child(const std::vector<MODEL::Action>& actions);
            unsigned char get_action_count(int player) const;
            int get_score() const;
            bool is_leaf() const;
            int get_max_depth() const;

            inline int get_children_visited() {
                return children_visited;
            }

        private:
            int children_visited; // if a child is visited twice, then it is counted twice = the number of calls to next_child that return true
            std::shared_ptr<TreeNode> node;  // curent node, starts as root
            unsigned int max_depth;
        };

    }
}
