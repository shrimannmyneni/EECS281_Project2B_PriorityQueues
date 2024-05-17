// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the priority queue ADT implemented as a binary heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // data.push_back(TYPE()); // DONE
    } // BinaryPQ



    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, data{start, end} {
        // data.push_back(TYPE()); 
        updatePriorities(); // DONE
    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        for (size_t k = data.size() / 2; k > 0; --k) {
            fix_down(data.size(), k);
        } // DONE
    }


    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        data.push_back(val);
        fix_up(data.size()); //DONE
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        data[0] = data.back(); 
        data.pop_back();
        fix_down(data.size(), 1);
    }

    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        return data.front(); // DONE
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return data.size(); //DONE
    } // size()


    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return data.empty(); // DONE
    } // empty()


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    size_t parent(size_t k) const {
        return k / 2;
    }

    size_t left_child(size_t k) const {
        return 2 * k;
    }

    void fix_up(size_t k) {
        while (k > 1 && this->compare(getElement(parent(k)), getElement(k))) {
            std::swap(getElement(k), getElement(parent(k)));
            k = parent(k);
        }
    }

    void fix_down(size_t size, size_t i) {
        while (left_child(i) <= size) {
        size_t j = left_child(i);
        if (j < size && this->compare(getElement(j), getElement(j + 1))) { ++j; }
        if (!this->compare(getElement(i), getElement(j))) { break; }
        std::swap(getElement(i), getElement(j));
        i = j;
        }
    }

    TYPE &getElement(std::size_t idx){
        return data[idx-1];
    } // getElement()

    const TYPE &getElement(std::size_t idx) const{
        return data[idx-1];
    } // getElement()


    // TODO: Add any additional member functions you require here.
    //       For instance, you might add fixUp() and fixDown().
}; // BinaryPQ


#endif // BINARYPQ_H



// // Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

// #ifndef BINARYPQ_H
// #define BINARYPQ_H


// #include <algorithm>
// #include "Eecs281PQ.h"

// // A specialized version of the priority queue ADT implemented as a binary heap.
// template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
// class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
//     // This is a way to refer to the base class object.
//     using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

// public:
//     // Description: Construct an empty PQ with an optional comparison functor.
//     // Runtime: O(1)
//     explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
//         BaseClass{ comp } {

//         // //1-based indexing for the binary PQ
//         data.push_back(TYPE());
//     } // BinaryPQx


//     // Description: Construct a PQ out of an iterator range with an optional
//     //              comparison functor.
//     // Runtime: O(n) where n is number of elements in range.
//     template<typename InputIterator>
//     BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
//         BaseClass{ comp } {

//         data.push_back(TYPE());
//         data.insert(data.end(), start, end);

//         for (size_t k = size() / 2; k >= 1; --k) {
//             fix_down(k); 
//         }
//     } // BinaryPQ


//     // Description: Destructor doesn't need any code, the data vector will
//     //              be destroyed automatically.
//     virtual ~BinaryPQ() {
//     } // ~BinaryPQ()


//     // Description: Assumes that all elements inside the heap are out of order and
//     //              'rebuilds' the heap by fixing the heap invariant.
//     // Runtime: O(n)
//     virtual void updatePriorities() {
//         // TODO: Implement this function.
//            for (size_t k = size() / 2; k >= 1; --k) {
//                 fix_down(k);
//             }
//     } // updatePriorities()


//     // Description: Add a new element to the PQ.
//     // Runtime: O(log(n))
//     virtual void push(const TYPE &val) {
//         data.push_back(val); // Insert at the end (next available leaf)
//         fix_up(data.size() - 1); // Fix the heap upwards from the new leaf
//     } // push()


//     // Description: Remove the most extreme (defined by 'compare') element
//     //              from the PQ.
//     // Note: We will not run tests on your code that would require it to pop
//     // an element when the PQ is empty. Though you are welcome to if you are
//     // familiar with them, you do not need to use exceptions in this project.
//     // Runtime: O(log(n))
//     virtual void pop() {
//         if (data.size() > 2) {
//             std::swap(getElement(1), getElement(data.size() - 1));
//             data.pop_back();
//             fix_down(1);
//         } else if (data.size() == 2) {
//             data.pop_back();
//         } else {
//             throw std::logic_error("Attempting to pop element from empty heap");
//         }
//     } // pop()


//     // Description: Return the most extreme (defined by 'compare') element of
//     //              the PQ. This should be a reference for speed. It MUST
//     //              be const because we cannot allow it to be modified, as
//     //              that might make it no longer be the most extreme element.
//     // Runtime: O(1)
//     virtual const TYPE &top() const {
//         if (size() > 0) {
//             return data[getElement(1)]; // First real element (after dummy)
//         }else{
//             throw std::logic_error("Attempting to access top on empty heap");
//         }
//     } // top()


//     // Description: Get the number of elements in the PQ.
//     // Runtime: O(1)
//     virtual std::size_t size() const {
//         // TODO: Implement this function. Might be very simple,
//         // depending on your implementation.
//         return data.size() - 1; // TODO: Delete or change this line
//     } // size()


//     // Description: Return true if the PQ is empty.
//     // Runtime: O(1)
//     virtual bool empty() const {

//         return (size() == 0);
//     } // empty()


// private:
//     // Note: This vector *must* be used for your PQ implementation.
//     std::vector<TYPE> data;
//     // NOTE: You are not allowed to add any member variables. You don't need
//     //       a "heapSize", since you can call your own size() member
//     //       function, or check data.size().

//     size_t parent(size_t k) const {
//         return k / 2;
//     }

//     size_t left_child(size_t k) const {
//         return 2 * k;
//     }

//     void fix_up(size_t k)  {
//         // swap modified element with parent until root is reached or a parent
//         // with a greater than or equal priority is found
//         while (k > 1 && this->compare(getElement(data[parent(k)]), getElement(k)])){
//             std::swap(getElement(k), getElement(parent(k)));
//             k = parent(k);
//         }
//     }



// void fix_down(size_t k) {
//         size_t heapsize = data.size();
//     while (left_child(k) <= heapsize) {  // Use size() instead of data.size()
//         size_t largerChild = left_child(k);
//         if (largerChild < heapsize && this->compare(getElement(data[largerChild]), getElement(data[largerChild + 1]))) {
//             ++largerChild;
//         }
//         if (this->compare(getElement(data[largerChild]), getElement(data[largerChild-1]))) {
//             break;
//         }
//         std::swap(getElement(k-1), getElement(largerChild-1));
//         k = largerChild;
//     }
// }


//     TYPE &getElement(std::size_t i) {
//         return data[i - 1];
//     }  // getElement()

//     const TYPE &getElement(std::size_t i) const {
//         return data[i - 1];
//     }  // getElement()

//     // TODO: Add any additional member functions you require here.
//     //       For instance, you might add fixUp() and fixDown().
// }; // BinaryPQ


// #endif // BINARYPQ_H
