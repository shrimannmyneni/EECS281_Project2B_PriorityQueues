// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr },
                parent {nullptr}
            {}

            // Description: Allows access to the element at that Node's
            // position.  There are two versions, getElt() and a dereference
            // operator, use whichever one seems more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *parent;
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp },  nodes_count{0}, root{nullptr}{
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, nodes_count{0}, root{nullptr} {
        for (auto i = start; i != end; ++i){push(*i);}
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare }, nodes_count{0}, root {nullptr} {
                std::deque<Node*> h;
                h.push_back(other.root);
                while (!h.empty()){
                    Node *c = h.front();
                    h.pop_front();
                    if (c->sibling){h.push_back(c->sibling);}
                    if (c->child){h.push_back(c->child);}
                    push(c->elt);
                }
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
                    PairingPQ t(rhs);
                    std::swap(root, t.root);
                    std::swap(nodes_count, t.nodes_count);
                    return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
               if (empty()){return;}
        if (size() == 1){delete root; return;}
        
        std::deque<Node*> h;
        h.push_back(root);

        while (!h.empty()){
            Node *c = h.front();
            h.pop_front();
            if (c->sibling){h.push_back(c->sibling);}
            if (c->child){h.push_back(c->child);}
            delete c;
        }

    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant.  You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
            std::deque<Node*> ph; // ph = pairing heap
            ph.push_back(root);
            Node* h = nullptr;

            while (!ph.empty()){
                Node* c = ph.front();/*c = current*/ 
                ph.pop_front();

                if (c->sibling){ph.push_back(c->sibling);}
                if (c->child){ph.push_back(c->child);}

                c->sibling = nullptr;
                c->child = nullptr;
                c->parent = nullptr;
                h = meld(c, h);
            }
            root = h;
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely
    //              in the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the pairing heap is empty. Though you are welcome to
    // if you are familiar with them, you do not need to use exceptions in
    // this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // if (size() == 1){--nodes_count; delete root; root = nullptr; return;}
        Node *t = root->child; std::deque<Node*> h; delete root;

        for (Node* n = t; n; n = t){ n->parent = nullptr; t = n->sibling; n->sibling = nullptr; h.push_back(n);}

        while (h.size() > 1){Node* ca = h.front(); h.pop_front(); Node* cb = h.front(); h.pop_front(); Node* nr = meld(ca, cb); h.push_back(nr);}
        --nodes_count;
        if (h.empty()){ root = nullptr; } else {root = h.front();}
    // while (t){
    //     h.push_back(t);
    //     p = t;
    //     t = t->sibling;
    //     p->sibling = nullptr;
    // }
    // while (h.size() > 1){
    //     Node *f = h.front();
    //     h.pop_front();
    //     Node *s = h.front();
    //     h.pop_front();
    //     h.push_back(meld(f,s));
    // }
    // nodes_count--;
    // root = h.front();
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        return root->elt;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
        return nodes_count;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return (root == nullptr);
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value.  Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //              extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        node->elt = new_value;
        if (node == root){return;}
        if(this->compare(new_value, node->parent->elt)){ node->elt = new_value; return;}
        if (node->parent->child == node){ node->parent->child = node->sibling;} 
        else { Node* ls = node->parent->child; 
        while (ls && ls->sibling != node){ ls = ls->sibling;}
        if(ls){ls->sibling = node->sibling;}} node->sibling = nullptr; node->parent = nullptr; root = meld(node, root);
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // Runtime: O(1)
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    Node* addNode(const TYPE &val) {
        // base case
        if (empty()){
            ++nodes_count;
            root = new Node (val);
            return root;
        }
        //else if not empty
        ++nodes_count;
        Node *m = new Node(val);
        root = meld(root, m);
        return m;
    } // addNode()


private:
    Node* meld(Node *first, Node* second){
        if (!first){ return second; }
        if (!second){ return first; }
        if (this->compare(first->elt, second->elt)){
            //if PRIb > PRIa
            first->sibling = second->child;
            first->parent = second;
            second->child = first;

            return second;
        } else{
            //if PRIa > PRIb
            second->sibling = first->child;
            second->parent = first;
            first->child = second;

            return first;
        }
    }
    size_t nodes_count;
    Node *root;

};


#endif // PAIRINGPQ_H
