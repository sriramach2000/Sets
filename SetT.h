#pragma once
#include<string>
#include<iostream>
#include<forward_list>
#include<unordered_map>
#include <fstream>

using namespace std;

const int DEFAULT_BUCKETS = 5;

template<class T>
class SetT
{
public:
	SetT();
	SetT(int numBucks);
	~SetT();

	void Add(T elem);
	void Remove(T elem);
	bool Contains(T elem);
	int Size() { return numElems; };
	double LoadFactor();
	// void ReHash(int numBucks);  // Extra credit

	void operator+(T elem);				// Add
	void operator-(T elem);				// Remove
	SetT operator+(const SetT& other);  // Union
	SetT operator*(const SetT& other);  // Intersection
	SetT operator-(const SetT& other);  // Difference
	SetT operator=(const SetT& other);

	void ResetIterator();	// Reset iterator
	bool HasNext();
	T GetNextItem();
	void print_bucket();
	void print_bucket(ostream& out);

private:
	forward_list<T>** buckets;	// An array of forward_list's 
								// (ie, each index is a forward_list pointer)
	int numBuckets;
	int getHashIndex(const T& elem);
	int numElems;

	// Iterator variables
	int currBucket;											// what bucket is the iterator on?
	mutable typename forward_list<T>::iterator bucketIter;	// the iterator of the current bucket
	mutable typename forward_list<T>::iterator otherIter;
	
};

template<class T>
int SetT<T>::getHashIndex(const T& key)
{
	// hash function that uses an unordered map
	unordered_map<int, T> mapper;
	typename unordered_map<int, T>::hasher hashFunction = mapper.hash_function();
	return static_cast<int>(hashFunction(key) % numBuckets);
}



template<class T>
SetT<T>::SetT()
{

	// Create an array of forward_lists and initially set to an empty forward_list
	buckets = new forward_list<T> * [DEFAULT_BUCKETS];
	for (int i = 0; i < DEFAULT_BUCKETS; i++) {
		buckets[i] = new forward_list<T>;
	}
	numBuckets = DEFAULT_BUCKETS;
}

template<class T>
SetT<T>::SetT(int numBucks)
{
	// Does the same thing as default constructor except for a custom number of
	// buckets
	buckets = new forward_list<T> * [numBucks];
	for (int i = 0; i < numBucks; i++) {
		buckets[i] = new forward_list<T>;
	}
	numBuckets = numBucks;
}

template<class T>
SetT<T>::~SetT()
{
	// Loop over buckets and delete each bucket
	// optional deconstructor def
	/*
	for (int i = 0; i < numBuckets; i++) {
		delete buckets[i];
	}
	*/
}

template<class T>
void SetT<T>::Add(T elem)
{

	// Add elem to the set if it doesn't already contain it
	// Get the bucket index and check to see if the bucket
	// contains elements. If the bucket has never had elements,
	// then initialize the forward_list of that bucket.  Add the
	// element to the bucket.

	int index = SetT::getHashIndex(elem);
	if (!Contains(elem)) {

			
		buckets[index]->push_front(elem);
		numElems++;		
	}


}

template<class T>
void SetT<T>::Remove(T elem)
{
	// Remove elem from the set if elem in the set.
	
	int index = SetT::getHashIndex(elem);
	SetT<T> result;
	if (Contains(elem)) {

		buckets[index]->remove(elem);
		numElems--;
			
	}
}

template<class T>
bool SetT<T>::Contains(T elem)
{
	// Use hash function to find the bucket, then check
	// to see if elem is in the bucket.
	int hash_index = getHashIndex(elem);

	for (auto bucketIter = buckets[hash_index]->begin(); bucketIter != buckets[hash_index]->end(); ++bucketIter) {
		if (*bucketIter == elem) {
			//cout << "item exists" << endl;
			return true;
		}
	}

	return false;

}
//optional function for rehashing
template<class T>
double SetT<T>::LoadFactor()
{

}


template<class T>
void SetT<T>::operator+(T elem)
{
	this->Add(elem);
}

template<class T>
SetT<T> SetT<T>::operator+(const SetT& other)
{
	SetT<T> result;
	
	
	// This function should return the union of "this" and otherSet.

	result.ResetIterator();

	for (int i = 0; i < other.numBuckets; ++i) {
		for (auto bucketIter = other.buckets[i]->begin(); bucketIter != other.buckets[i]->end(); ++bucketIter) {
			result.Add(*bucketIter);

		}
	}
	// for when the current bucket is larger than the other bucket
	for (int i = 0; i < numBuckets; ++i) {
		for (auto bucketIter = buckets[i]->begin(); bucketIter != buckets[i]->end(); ++bucketIter) {

			result.Add(*bucketIter);			
		}
	}


	return result;
}

template<class T>
SetT<T> SetT<T>::operator*(const SetT& other)
{
	SetT<T> result;
	// This function should return the Intersection between "this" and otherSet.

	if (other.numElems <= numElems) {

		for (int i = 0; i < other.numBuckets; ++i) {
			for (auto bucketIter = other.buckets[i]->begin(); bucketIter != other.buckets[i]->end(); ++bucketIter) {

				// use contains funtion
				if (Contains(*bucketIter)) {
					result.Add(*bucketIter);

				}

			}
		}


		if (other.numElems >= numElems) {
			for (int i = 0; i < other.numBuckets; ++i) {
				for (auto bucketIter = other.buckets[i]->begin(); bucketIter != other.buckets[i]->end(); ++bucketIter) {

					if (Contains(*bucketIter)) { //use contains 

						result.Add(*bucketIter);

					}

				}
			}

			result.print_bucket();
		}

		return result;
	}
}

	template<class T>
	void SetT<T>::operator-(T elem)
	{
		// Your code here
		this->Remove(elem);
	}

	template<class T>
	SetT<T> SetT<T>::operator-(const SetT & other)
	{
		SetT<T> result;

	
		// This function should return the Difference between "this" and otherSet.
		// It should NOT change "this" or otherSet
		result.ResetIterator();

		if (other.numElems < numElems) {
			//set B iteration
			for (int i = 0; i < other.numBuckets; ++i) {
				for (auto otherIter = other.buckets[i]->begin(); otherIter != other.buckets[i]->end(); ++otherIter) {
					result.Add(*otherIter);

				}
			}


			//set A iteration
			for (int i = 0; i < numBuckets; ++i) {
				for (auto bucketIter = buckets[i]->begin(); bucketIter != buckets[i]->end(); ++bucketIter) {
					result.Add(*bucketIter);
					if (result.Contains(*bucketIter)) { // use contains funtion
						result.Remove(*bucketIter);
						//this->Remove(*bucketIter);
					}
					else {
						break;
					}
				}
			}

		}

		if (other.numElems > numElems) {
			// set B iteration
			for (int i = 0; i < numBuckets; ++i) {
				for (auto otherIter = buckets[i]->begin(); otherIter != buckets[i]->end(); ++otherIter) {
					result.Add(*otherIter);

				}
			}

			//set A iteration
			for (int i = 0; i < other.numBuckets; ++i) {
				for (auto bucketIter = other.buckets[i]->begin(); bucketIter != other.buckets[i]->end(); ++bucketIter) {

					if (result.Contains(*bucketIter)) { // use contains funtion

						//result.Remove(*bucketIter);
						this->Remove(*bucketIter);
					}
					else {
						break;
					}
				}
			}

		}

		return result;
	}

	// making a  deep copy
	template<class T>
	SetT<T> SetT<T>::operator=(const SetT & other)
	{


		//safety
		for (int i = 0; i < numBuckets; ++i) {
			delete buckets[i];
		}
		delete[] buckets;

		// contructor code. could put into object
		buckets = new forward_list<T> * [other.numBuckets];
		for (int i = 0; i < other.numBuckets; i++) {
			buckets[i] = new forward_list<T>;
		}

		// making copy of other variables to this->

		numBuckets = other.numBuckets;
		bucketIter = other.bucketIter;
		currBucket = other.currBucket;
		numElems = other.numElems;
		bucketIter = other.bucketIter;
		otherIter = other.otherIter;



		for (int i = 0; i < numBuckets; ++i) {

			for (bucketIter = other.buckets[i]->begin(); bucketIter != other.buckets[i]->end(); ++bucketIter) {
				//result.buckets[i];

				//cout << *bucketIter << endl;
				this->Add(*bucketIter);
			}
		}
		return other;
	}



	template<class T>
	void SetT<T>::ResetIterator()
	{
		// Reset the iterator for the set
		currBucket = 0;
		bucketIter = buckets[currBucket]->begin();

	}

	template<class T>
	bool SetT<T>::HasNext()
	{
		// This function should check if anything is
		// left in the current bucket iterator.

		// If nothing is left in the current bucket iterator,
		// move to a bucket that does have elements in the bucket.

		// If you can't find a bucket with elements, return false.

		while (true) {

			// Is bucketIter at the end of the current forward_list?
			if (bucketIter = buckets[currBucket]->end()) {
				return true;
			}
			else {
				currBucket++;

				// Your code here
				// Check if we still have buckets to look at.
				// If we still have buckets, then update bucketIter to the beginning of the next bucket.
				if (bucketIter != buckets[currBucket]->end())
					bucketIter = buckets[currBucket]->begin();

			}
		}

		return false;
	}

	template<class T>
	T SetT<T>::GetNextItem()
	{
		// Returns the next item.  You should go to each bucket and
		// iterate through each item in the bucket.  After iterating
		// through the bucket, move onto the next bucket.
		T item;

		// Your code here
		for (int i = 0; i < numBuckets; ++i) {

			for (auto it = buckets[i]->begin(); it != buckets[i]->end(); ++it) {
				item = *it;
			}

		}
		return item;
	}

	template<class T>
	void SetT<T>::print_bucket()
	{

		for (int i = 0; i < numBuckets; i++) {
			for (bucketIter = buckets[i]->begin(); bucketIter != buckets[i]->end(); ++bucketIter) {
				cout << "elem: " << *bucketIter << endl;
			}
		}
	}

	// overloaded print function for outputfile 
	template<class T>
	inline void SetT<T>::print_bucket(ostream& out)
	{
		for (int i = 0; i < numBuckets; i++) {
			for (bucketIter = buckets[i]->begin(); bucketIter != buckets[i]->end(); ++bucketIter) {
				out << "elem: " << *bucketIter << endl;
			}
		}
	}
