//
// unionFindSetImpl.h
// CS 106B Assignment 7 Pathfinder
//
// Created by Zhiming Wang on 12/04/12.
//
// Implements the <code>UnionFindSet</code> class.
//

//#include "unionFindSet.h"

template <typename Key>
UnionFindSet<Key>::UnionFindSet() {
    // Do nothing. <code>std::map</code> is automatically initialized.
}

template <typename Key>
template <typename InputIt>
UnionFindSet<Key>::UnionFindSet(InputIt begin, InputIt end) {
    for (InputIt i = begin; i != end; ++i) {
        insert(*i);
    }
}

template <typename Key>
UnionFindSet<Key>::~UnionFindSet() {
    // Do nothing. <code>std::map</code> destructs automatically.
}

template <typename Key>
void UnionFindSet<Key>::insert(const Key& key) {
    parentMap[key] = key;
    rankMap[key]   = 0;
}

template <typename Key>
typename UnionFindSet<Key>::Rep UnionFindSet<Key>::findRep(const Key& key) {
    if (parentMap[key] == key) {
        return key;
    }
    Rep rep = static_cast<Rep>(findRep(parentMap[key]));
    parentMap[key] = rep;
    return rep;
}

template <typename Key>
void UnionFindSet<Key>::unionSetsByReps(const Rep& rep1, const Rep& rep2) {
    // rep1 and rep2 are implicitly casted to <code>Key</code> objects.
    if (rankMap[rep1] > rankMap[rep2]) {
        parentMap[rep2] = rep1;
    } else if (rankMap[rep1] < rankMap[rep2]) {
        parentMap[rep1] = rep2;
    } else {
        parentMap[rep2] = rep1;
        ++rankMap[rep1];
    }
}

template <typename Key>
bool UnionFindSet<Key>::tryToUnionSetsByKeys(const Key& key1, const Key& key2) {
    Rep rep1 = findRep(key1);
    Rep rep2 = findRep(key2);
    if (rep1 == rep2) {
        return false;
    }
    unionSetsByReps(rep1, rep2);
    return true;
}