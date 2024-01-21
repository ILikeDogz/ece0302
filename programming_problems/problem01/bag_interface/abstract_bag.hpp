#ifndef _ABSTRACT_BAG_HPP_
#define _ABSTRACT_BAG_HPP_

#include <cstdlib>

/**
 * Interface made with an abstract class, called AbstractBag, for a Bag
 *
 * Defines all the virtual functions that can be used in other Bag classes
 *
 * @tparam T, type of Bag
 */
template<typename T>
class AbstractBag {
public:
    /**
     * Gets current size of bag
     * @return current size of bag
     */
    virtual std::size_t getCurrentSize() const = 0;

    /**
     * Checks if the bag is empty
     * @return returns true or false status of the bag, true if empty
     * false if not empty
     */
    virtual bool isEmpty() const = 0;

    /**
     * Allows item to be added to the bag
     *
     * @param entry the item being added to the bag
     * @return returns true if suceeded, false if failed
     */
    virtual bool add(const T& entry) = 0;

    /**
     * Remove's and item from the bag
     * @param entry the item being removed from the bag
     * @return returns true if sucessful, false if failed
     */
    virtual bool remove(const T& entry) = 0;

    /**
     * clears the bag of all items
     */
    virtual void clear() = 0;

    /**
     * Get the frequency of ann entry in the  bag
     *
     * @param entry entry being checked
     * @return returns the frequency of the entry parameter
     */
    virtual std::size_t getFrequencyOf(const T& entry) const = 0;

    /**
     * Checks if an item is contained in the bag
     * @param entry the item being checked for
     * @return returns true if the item is found in the bag 
     * false if not in the bag
     */
    virtual bool contains(const T& entry) const = 0;
};

#endif
