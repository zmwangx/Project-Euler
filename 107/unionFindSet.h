//
// unionFindSet.h
// CS 106B Assignment 7 Pathfinder
//
// Created by Zhiming Wang on 12/04/12.
//
// Defines the interface of <code>UnionFindSet</code> class.
//

#ifndef __pathfinder__unionFindSet__
#define __pathfinder__unionFindSet__

#include <map>

/**
 * A disjoint-set data structure that exports the functionalities of union-find
 * algorithm. For concepts of the data structure and algorithm, refer to 
 * <a href ="http://en.wikipedia.org/wiki/Union-find">Wikipedia</a>.
 * <p>
 * Note that in a typical disjoint-set, keys are sequential numbers (subscripts) 
 * of actual nodes, so locating a node by key takes constant time. However, in 
 * <code>UnionFindSet</code>, keys may not sequential, and the actual locating 
 * time depends on the STL infrastruture (typically logarithmic in the size 
 * (number of keys), but not gauranteed).
 * <p>
 * Since this class is infrastructure-dependent, the complexities provided are 
 * based on the the assumption that locating node by key takes constant time.
 *
 * @type        Key     Assignment operator; equality, inequality, and 
 *                      comparison operators must be be overloaded for the 
 *                      <code>Key</code> class. Copy constructor must be 
 *                      defined.
 */
template <typename Key>
class UnionFindSet {
    
    /**
     * Representive of a set in the disjoint-set data structure. Must be a valid 
     * return value by the <code>findRep</code> method. Otherwise logically 
     * meaningless, and calling methods with meaningless <code>Rep<code> is 
     * undefined.
     */
    typedef Key Rep;
    
public:
    
    /**
     * Constructs an empty union-find set, or takes in keys in the range [first, 
     * last) and creates an initialized union-find set with every key in a 
     * distinct set.
     *
     * @param       begin   iterator to first key in the range, e.g., c.begin()
     *                      of an STL container c
     * @param       end     iterator to the location immediately past the last
     *                      key in the range, e.g., c.end() of an STL container 
     *                      c
     * @type        InputIt <a href=http://en.cppreference.com/w/cpp/concept/
     *                      Iterator>Iterators</a> pointing to a <code>Key</
     *                      code> objectthat support at least equality/ 
     *                      inequality comparison. <a href=http://en.
     *                      cppreference.com/w/cpp/concept/InputIterator>
     *                      InputIterators</a> are recommended.
     * @complexity  (1) constant
     *              (2) linear in size of range
     * @see         insert
     */
    UnionFindSet();
    template <typename InputIt>
    UnionFindSet(InputIt begin, InputIt end);
    
    /**
     * Destructs the union-find set and used storage is deallocated. Note that 
     * if the keys are pointers, the pointed-to objects are not destroyed.
     */
    ~UnionFindSet();
    
    /**
     * Inserts a new key into the union-find set, which resides in a distinct 
     * set created for it. Note that the new key must be different from all 
     * existing keys. Otherwise the result is undefined.
     * <p>
     * Previously assigned <code>Rep</code> objects are not affected by 
     * <code>insert</code>.
     *
     * @param       key     a new key to be inserted
     * @complexity  constant
     * @see         (constructor)
     */
    void insert(const Key& key);
    
    /**
     * Finds the set in which <code>key</code> resides and returns an 
     * representitive to that set.
     * <p>
     * <code>findRep</code> is the only way to obtain a valid <code>Rep</code> 
     * object.
     * <p>
     * Previously assigned <code>Rep</code> objects are not affected by 
     * <code>findRep</code>.
     *
     * @param       key     the key whose residing set is to be looked up
     * @complexity  almost constant, at worst circumstance logarithmic to size
     * @see         unionSetsByReps
     * @see         tryToUnionSetsByKeys
     */
    Rep findRep(const Key& key);
    
    /**
     * Unions two sets represently by <code>rep1</code> and <code>rep2</code> 
     * respectively. <code>rep1</code> and <code>rep2</code> must be valid 
     * <code>Rep</code> objects returned by <code>findRep</code>. Calling with 
     * random <code>Key</code> objects or invalidated <code>Rep</code> objects
     * results in undefined behavior. Also note that <code>rep1</code> and 
     * <code>rep2</code> should be different. Otherwise the performance may be 
     * affected.
     * <p>
     * All previously assigned <code>Rep</code> objects are after calling 
     * <code>unionSetsByReps</code>.
     *
     * @param       rep1, rep2  representatives to the two sets to be merged
     * @complexity  constant
     * @see         findRep
     * @see         tryToUnionSetsByKeys
     */
    void unionSetsByReps(const Rep& rep1, const Rep& rep2);
    
    /**
     * Unions two sets containing <code>key1</code> and <code>key2</code>, 
     * respectively (and if they are in the same set, does nothing). Returns if 
     * the keys are in different sets (whether a union is actually performed). 
     * This method essentially performs:
     * (1) finding representatives of key1 and key2, respectively;
     * (2) if the reps are the same, returning false without any action; 
     * otherwise, calling <code>unionSetsByReps</code> on the two reps, and 
     * returning true.
     *
     * @param       key1, key2  keys in the two sets to be merged
     * @return      true if a union is actually performed, false otherwise
     * @complexity  almost constant, at worst circumstance logarithmic to size
     * @see         findRep
     * @see         unionSetsByReps
     */
    bool tryToUnionSetsByKeys(const Key& key1, const Key& key2);
    
private:
    
    std::map<Key, Key> parentMap;
    
    std::map<Key, int> rankMap;
    
};

#include "unionFindSetImpl.h"

#endif /* defined(__pathfinder__unionFindSet__) */
