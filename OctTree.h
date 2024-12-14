#ifndef _OCTTREE_DEFINED
#define _OCTTREE_DEFINED

#include <vector>
#include "Node.h"

constexpr double THETA = 0.9;

class OctTree {
private:
    Root *root;
    bool parallel;

public:
    OctTree(std::vector<Leaf *> &particles, vector_3d lowerBound, vector_3d upperBound);
    ~OctTree();
    void insert(Leaf *particle);
    void insertParticle(Root *root, Leaf *particle, const int octet);
    void insertParticles(std::vector<Leaf *> &particles);
    int findOctet(const vector_3d &rootPos, const vector_3d &bodyPos);
    void remove(Leaf *particle);
    void maybeReplaceRoot(Root *root);
    void setCenterOfMass();
    void centerOfMass(Root *root);
    vector_3d treeForce(Leaf *particle);
    vector_3d partialTreeForce(Leaf *particle, Node *node);
    bool checkParticleBounds(Leaf *particle);
    void print();
    void printRecurse(Root *root);
};

#endif // _OCTTREE_DEFINED