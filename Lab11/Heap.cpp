
#include "Heap.h"

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap ( int maxNumber = DEFAULT_MAX_HEAP_SIZE ){
	size = 0;  //init at 0
	dataItems = new DataType[maxNumber];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap ( const Heap& other ){
	if (maxSize != other.maxSize)
		maxSize = other.maxSize;
	clear();
	size = other.size;
	for (int i = 0; i < other.size; i++)
		dataItems[i] = other.dataItems[i];
	return *this;  //return new heap
	
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>& Heap<DataType,KeyType,Comparator>::operator= ( const Heap& other ){
	if (this != &other) {   //ensure not denoting same heap
		if (!isEmpty())
			clear();  //clear current dataItems 
		maxSize = other.maxSize;
		size = other.size;
		dataItems = new DataType[maxSize];
		for (int i = 0; i < size; i++)
			dataItems[i] = other.dataItems[i];
	}
	return *this;   //return this in either case
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::~Heap (){
	delete []dataItems;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::insert ( const DataType &newDataItem )
    throw ( logic_error ){
	if (isFull())
		throw logic_error("Heap full.");
	else {
		if(size == 0)
			dataItems[0] = newDataItem;
		else {
			//insert new item at "end"
			int loc = size;  //size is item index 1 past current last item		
			int par = (loc - 1) / 2;
							 //percolate up
			Comparator compare;
				while (compare(newDataItem.getPriority(), dataItems[par].getPriority() ) && loc != 0) {
					dataItems[loc] = dataItems[par];
					loc = par;
					par = (loc - 1) / 2;
				}
				dataItems[loc] = newDataItem;  //position found, so place new item there
			}
		
		size = size + 1;
	}
}

template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType,KeyType,Comparator>::remove () throw ( logic_error ){
	if (isEmpty())
		throw logic_error("Heap is empty.");
	else {
		DataType itemToReturn = dataItems[0];
		dataItems[0] = dataItems[size - 1];
		size = size - 1;
		//percolate down
		int currLoc = 0;
		while (currLoc < size) { //until end is reached where item was moved to top
			Comparator compare;
			if (((currLoc * 2) + 2) < size) {  //if both children exist
				DataType left = dataItems[(2 * currLoc) + 1];
				DataType right = dataItems[(2 * currLoc) + 2];
				DataType grtr;   //greater value of child nodes
				int grtrLoc;

				if (compare(left.getPriority(), right.getPriority())) {
					grtrLoc = (2 * currLoc) + 1;
				}
				else {
					grtrLoc = (2 * currLoc) + 2;
				}
				if (compare(dataItems[currLoc].getPriority(), dataItems[grtrLoc].getPriority()))
					return itemToReturn;  // last item found proper location
				else {
					DataType temp = dataItems[currLoc];
					dataItems[currLoc] = dataItems[grtrLoc];
					dataItems[grtrLoc] = temp;
					currLoc = grtrLoc;
				}
			}
			else if( (((currLoc * 2) + 1) < size) && (((currLoc * 2) + 2) >= size)) { //only 1 child
				if (compare(dataItems[currLoc].getPriority(), dataItems[(2 * currLoc) + 1].getPriority()))
					return itemToReturn;
				else {
					DataType temp = dataItems[currLoc];
					dataItems[currLoc] = dataItems[(2 * currLoc) + 1];
					dataItems[(2 * currLoc) + 1] = temp;
					currLoc = ((2 * currLoc) + 1);
				}

			}
			else  //last location
				return itemToReturn;

		}
		return itemToReturn;
	}
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::clear (){
	size = 0;  //mark items to be overwritten
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isEmpty () const{
	if (size == 0)
		return true;
	else
		return false;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isFull () const{
	if (size == maxSize)
		return true;
	else
		return false;
}

#include "show11.cpp"

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::writeLevels() const {
	if (isEmpty())
		cout << "Empty heap." << endl;
	else {
		int count = 1;  //number of items to print on line
		int numPrinted = 0;
		for (int i = 0; i < size; i++) {
			cout << dataItems[i].getPriority() << "  ";
			numPrinted += 1;
			if (numPrinted == count) {
				cout << endl;  //end of level
				count = count * 2;  //count for next level
				numPrinted = 0;
			}	
		}
	}
}