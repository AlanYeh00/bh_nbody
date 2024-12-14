#include <assert.h>
#include <iostream>
#include <map>
#include <thread>
#include <vector>
#include "OctTree.h"

static std::pair<vector_3d, vector_3d> getBounds(Root *root, int octet) {
}

int OctTree::findOctet(const vector_3d &rootPos, const vector_3d &bodyPos) {
}

OctTree::OctTree(std::vector<Leaf *> &particles, vector_3d lowerBound, vector_3d upperBound) {
    this->root = new Root(nullptr, lowerBound, upperBound);
    this->parallel = NULL == std::getenv("SEQ");
    insertParticles(particles);
}

OctTree::~OctTree() {
    delete root;
}

void OctTree::insert(Leaf *particle) {
    int octet = findOctet(this->root->pos, particle->body.pos);
    insertParticle(this->root, particle, octet);
}

void OctTree::insertParticle(Root *root, Leaf *particle, const int octet) {
   
}

void OctTree::insertParticles(std::vector<Leaf *> &particles) {
   
}

void OctTree::remove(Leaf *particle) {
   
}

void OctTree::maybeReplaceRoot(Root *root) {
}

void OctTree::setCenterOfMass() {
    //#pragma omp parallel
    //{
        #pragma omp single
        centerOfMass(this->root);
    //}
}

void OctTree::centerOfMass(Root *root) {
   
}

vector_3d OctTree::treeForce(Leaf *particle) {
    return partialTreeForce(particle, (Node *)this->root);
}

vector_3d OctTree::partialTreeForce(Leaf *particle, Node *node) {
  
}

bool OctTree::checkParticleBounds(Leaf *particle) {
    Root *root = (Root *)particle->parent;
    if (std::get<X>(particle->body.pos) < std::get<X>(root->lowerBound) ||
        std::get<Y>(particle->body.pos) < std::get<Y>(root->lowerBound) ||
        std::get<Z>(particle->body.pos) < std::get<Z>(root->lowerBound) ||
        std::get<X>(particle->body.pos) > std::get<X>(root->upperBound) ||
        std::get<Y>(particle->body.pos) > std::get<Y>(root->upperBound) ||
        std::get<Z>(particle->body.pos) > std::get<Z>(root->upperBound)) {
        return true;
    }
    return particle->octet != findOctet(root->pos, particle->body.pos);
}

void OctTree::print() {
   
}

void OctTree::printRecurse(Root *root) {
   
}
