

#ifndef MGE_MAPITERATOR_H
#define MGE_MAPITERATOR_H

#include <map>

namespace mge
{

/**
 * This class acts as wrapper to a map::iterator. It just changes the
 * opearator* behaviour, which now returns a pointer to the contained value
 * hidding the user the value key.
 */
template <typename Key, typename Data>
class MapIterator : public std::map<Key, Data>::iterator
{
public:
    /** Constructor. */
    MapIterator()
	{}

    /** Constructor from a map::iterator. */
    MapIterator (const typename std::map<Key, Data>::iterator& i) :
	std::map<Key, Data>::iterator(i) {}

    /** Copy constructor. */
    MapIterator (const MapIterator<Key, Data>& i) :
	std::map<Key, Data>::iterator(static_cast<const typename std::map<Key, Data>::iterator>(i))
	{}

    /**
     * Indirection operator, returns a reference to the referred value.
     */
    Data& operator*() {
	return std::map<Key, Data>::iterator::operator*().second;
    }

    /**
     * Indirection operator, returns a pointer to the referred value.
     */
    Data* operator->() {
	return &std::map<Key, Data>::iterator::operator*().second;
    }

    /**
     * Const indirection operator, returns a constant reference to the
     * referred value.
     */
    const Data& operator*() const {
	return std::map<Key, Data>::iterator::operator*().second;
    }

    /**
     * Indirection operator, returns a pointer to the referred value const value.
     */
    const Data* operator->() const {
	return &std::map<Key, Data>::iterator::operator*().second;
    }

    /**
     * Preincrement operator.
     */
    MapIterator<Key, Data> operator++() {
	return std::map<Key, Data>::iterator::operator++();
    }

    /**
     * Postincrement operator.
     */
    MapIterator<Key, Data> operator++(int) {
	return std::map<Key, Data>::iterator::operator++(0);
    }
};

/**
 * This class acts as wrapper to a @c map::const_iterator. It just changes the
 * opearator* behaviour, which now returns a pointer to the contained value
 * hidding the user the value key. Just a @c const version of @c MapIterator
 * to hold constant data.
 *
 * @todo Implement -> operator.
 */
template <typename Key, typename Data>
class MapConstIterator : public std::map<Key, Data>::const_iterator
{
public:
    /** Constructor from a @c map::const_iterator */
    MapConstIterator (const typename std::map<Key, Data>::const_iterator& i) :
	std::map<Key, Data>::const_iterator(i) {}

    /** Copy constructor. */
    MapConstIterator (const MapConstIterator<Key, Data>& i) :
	std::map<Key, Data>::const_iterator(static_cast<const typename std::map<Key, Data>::const_iterator>(i))
	{}

    /**
     * Indirection operator, returns a reference to the referred value.
     */
    const Data& operator*() {
	return std::map<Key, Data>::const_iterator::operator*().second;
    }

    /**
     * Const indirection operator, returns a constant reference to the
     * referred value.
     */
    const Data& operator*() const {
	return std::map<Key, Data>::const_iterator::operator*().second;
    }
};

} /* namespace mge */

#endif /* MGE_MAPITERATOR_H */
