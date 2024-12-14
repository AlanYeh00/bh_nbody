#ifndef _NODE_DEFINED
#define _NODE_DEFINED

#include "Body.h"

constexpr int OCT_REGIONS = 8;

inline vector_3d average(const vector_3d &lowerBound, const vector_3d &upperBound) {
    double xPos = (std::get<X>(lowerBound) + std::get<X>(upperBound)) / 2;
    double yPos = (std::get<Y>(lowerBound) + std::get<Y>(upperBound)) / 2;
    double zPos = (std::get<Z>(lowerBound) + std::get<Z>(upperBound)) / 2;
    return (vector_3d)std::make_tuple(xPos, yPos, zPos);
}

class Node {
public:
    Node *parent;
    int octet;
    Node(Node *parent);
    virtual ~Node() {};
    virtual bool isLeaf() = 0;
};

class Root : public Node {
public:
    vector_3d pos;
    vector_3d lowerBound;
    vector_3d upperBound;
    double size;
    double mass;
    vector_3d centerOfMass;
    int numChildren;
    Node **children;
    
    Root(Node *parent, vector_3d lowerBound, vector_3d upperBound);
    ~Root();
    friend std::ostream& operator<<(std::ostream& out, const Root& r);
    bool isLeaf() { return false; }
};

class Leaf : public Node {
public:
    Body body;
    Leaf(Node *parent, Body &&body);
    friend std::ostream& operator<<(std::ostream& out, const Leaf& l);
    bool isLeaf() { return true; }
    double leafDistance(Leaf *leaf);
    double rootDistance(Root *root);
    vector_3d rootForce(Root *root, double dist);
};

#endif // _NODE_DEFINED