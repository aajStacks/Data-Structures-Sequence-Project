#include <iostream>
#include <cassert>
//#include <cstdlib>
#include "sequence2.h"
#include <algorithm>


using namespace main_savitch_4;



typedef double value_type;

typedef std::size_t size_type;




// CONSTRUCTOR for the sequence class:

//   sequence(size_type initial_capacity = DEFAULT_CAPACITY)
//     Postcondition: The sequence has been initialized as an empty sequence.
//     The insert/attach functions will work efficiently (without allocating
//     new memory) until this capacity is reached.
//
//     sequence(const sequence& source)
//	Precondition:
//	Post Condition:

sequence::sequence(size_type initial_capacity){
    data=new value_type[initial_capacity];
    current_index=initial_capacity + 1;
    capacity=initial_capacity;
	used=0;
}



sequence::sequence(const sequence& source){
    capacity=source.size();
    used=capacity;
    current_index = capacity+1;
    data=new value_type[capacity];
    for (int i=0; i<used;i++)
        data[i]=source.data[i];
}

sequence::~sequence(){
    delete [] data;
}


//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void resize(size_type new_capacity)
//     Postcondition: The sequence's current capacity is changed to the
//     new_capacity (but not less that the number of items already on the
//     sequence). The insert/attach functions will work efficiently (without
//     allocating new memory) until this new capacity is reached.
//

void sequence::resize(size_type new_capacity){
    if (new_capacity>used){
        value_type *temp = new value_type[new_capacity];
        for(int i=0; i<used;i++)
            temp[i]=data[i];
        value_type *destroy = data;
        data=temp;
        delete [ ] destroy;
        capacity=new_capacity;
    }
}


//   void start( )
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//

void sequence::start( ){
    current_index = 0;
}


//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item on the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
void sequence::advance( ){
    current_index++;
}

//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence before
//     the current item. If there was no current item, then the new entry has
//     been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//

void sequence::insert(const value_type& entry){
    if (used+1>capacity){
        resize(capacity+5);
    }
    value_type *temp = new value_type[capacity];
    int i=0;
    if (is_item()){
		for(i=i; i<current_index;i++)
            temp[i]=data[i];
        temp[i]=entry;
        current_index = i;
        i++;
        for(i=i;i<used;i++)
                temp[i]=data[i];

        value_type *destroyme = data;
        data=temp;
        delete [ ] destroyme;

    }
    else{
        for(int i=used;i>0;i--)
            data[i]=data[i-1];
        data[0]=entry;
        current_index = 0;
    }


    used++;
}

//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//

void sequence::attach(const value_type& entry){
    if (used+1>capacity){
        resize(capacity+5);
    }
    value_type *temp = new value_type[capacity];
    if (is_item()){
        int i=0;
		for(i; i<=current_index+1; i++)
            temp[i]=data[i];
        temp[i]=entry;
        current_index = i;
        for(i;i<=used;i++)
            temp[i]=data[i];
        value_type *destroy=data;
        data=temp;
        delete [ ] destroy;
    }
    else{
        data[used]=entry;
        current_index = used;
    }

    used++;;

}


//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.
//

void sequence::remove_current(){
	for(int i=current_index;i<used;i++)
        data[i]=data[i+1];
    used--;
}



// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items on the sequence.
//


size_type sequence::size() const{
    return used;
}

//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//

bool sequence::is_item() const{
	if (current_index<used)
        return true;
    else
        return false;
}

//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item on the sequence.
//
value_type sequence::current() const{
	return data[current_index];
}


// VALUE SEMANTICS for the sequence class:
//   Assignments and the copy constructor may be used with sequence objects.
//
// DYNAMIC MEMORY USAGE by the sequence
//   If there is insufficient dynamic memory, then the following functions

void sequence::operator=(const sequence& source){
    capacity=source.size();
    used=capacity;
    current_index = capacity+1;
    data=new value_type[capacity];
    for(int i=0;i<used;i++)
        data[i]=source.data[i];
}
