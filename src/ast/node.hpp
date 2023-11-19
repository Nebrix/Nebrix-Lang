#pragma once

enum NodeType {
    None
};

class Node {
    public:
        NodeType Type() {
            return NodeType::None;
        }
};

class Stmt : Node {

};