
#ifndef LISTE_H
#define LISTE_H

#include "cyclicNode.h"
#include <cassert>
#include <iostream>

template <class T>
class Liste{

  private:

    typedef DataStructure::cyclicNode<T> Chainon;

    // Attributs
    Chainon * m_liste;
    unsigned int m_size;


  public:
    // Default constructor
    Liste():m_liste(new Chainon()), m_size(0) {}


    // Destructeur, must remove all blocs
    ~Liste(){
      // remove all nodes from list
      unsigned int size = m_size;
      for (unsigned int i=0; i < size; i++){
        this->pop_front();
      }
      // remove m_liste since it was initialzed with a new in constructor
      delete m_liste;
    }

    // Check if list is empty
    bool empty() const{
      return m_size == 0;
    }

    // Access first block, (read and write)
    T& front() {
      assert(!empty());
      return m_liste->next()->data(); 
    }

    // Access last block, (read and write)
    T& back() {
      assert(!empty());
      return m_liste->previous()->data(); 
    }

    // Access first block, (read)
    const T& front() const{
      assert(!empty());
      return m_liste->next()->data(); 
    }

    // Access last block, (read)
    const T& back() const{
      assert(!empty());
      return m_liste->previous()->data(); 
    }

    // add a block in the front
    void push_front(const T& bloc) {
      Chainon* newNode = new Chainon(bloc);
      m_liste->insertAfter(newNode);
      m_size++;
    }

    // add a block in the end
    void push_back(const T bloc){
      Chainon* newNode = new Chainon(bloc);
      m_liste->insertBefore(newNode);
      m_size++;
    }

    // remove from front
    void pop_front(){
      assert(!empty());
      Chainon* tmp = m_liste->next(); // tmp stands for temporary, since it is a temporary node used so we don't loose the address of the front node when we detach it 
      m_liste->next()->detach(); // detach handles the re linking of the node with the next and previous nodes (see cyclicNode.h)
      delete tmp; // delete the node
      m_size--;
    }

    // remove from end
    void pop_back(){
      assert(!empty());
      Chainon* tmp = m_liste->previous(); // same idea as in pop_front()
      m_liste->previous()->detach();
      delete tmp;
      m_size--;
    }

    unsigned int size() const{
      return m_size;
    }

    public:
      
      // const iterator
      class const_iterator {

        private:
          // sentinel referes to the end of the list and current refers to the current node (will be used to iterate through the list)
          
          Chainon* m_sentinel;
          Chainon* m_current;

          friend class Liste<T>;
          const_iterator(Chainon* sentinel, Chainon* current):m_sentinel(sentinel), m_current(current){} // Liste<int>::const_iterator it = Liste::const_iterator(m_liste, m_liste->next());

        public:

          const T& operator*() const{ // *it to access the data of the current node (read only)
            assert(m_current != m_sentinel); 
            return m_current->data();
          }

          const_iterator& operator++(){ // ++it to move to the next node
            assert(m_current != m_sentinel); // make sure we don't go past the end of the list
            m_current = m_current->next();
            return *this;
          }

          const_iterator& operator--(){ // --it to move to the previous node
            assert(m_current != m_sentinel->next()); // make sure we don't go past the beginning of the list (sentinel->next() is the first node of the list
            m_current = m_current->previous();
            return *this;
          }

          bool operator==(const const_iterator& other) const{ // it1 == it2 to compare equality of two iterators
            return m_current == other.m_current && m_sentinel == other.m_sentinel;
          }

          bool operator!=(const const_iterator& other) const{ // it1 != it2 to compare difference of two iterators
            return m_current != other.m_current || m_sentinel != other.m_sentinel;
          }

          // -> operator to address the data of the current node (read only)
          const T* operator->() const{
            assert(m_current != m_sentinel);
            return &m_current->data();
          }
      };

      //  iterator (Can be used to modify the data of the current node)
      class iterator{

        private:
          friend class Liste<T>;

          Chainon* m_sentinel;
          Chainon* m_current;
          

          // constructor is private so that it can be accessed from a return of a function
          iterator(Chainon* sentinel ,Chainon* current):m_sentinel(sentinel), m_current(current){} // Liste<int>::const_iterator it = Liste::const_iterator(m_liste, m_liste->next());


        public:

          T& operator*(){ // *it to access the data of the current node (read and write only)
            assert(m_current != m_sentinel);
            return m_current->data();
          }

          iterator& operator++(){ // ++it to move to the next node
            assert(m_current != m_sentinel); // make sure we don't go past the end of the list
            m_current = m_current->next();
            return *this;
          }


          iterator& operator--(){ // --it to move to the previous node
            assert(m_current != m_sentinel->next()); // make sure we don't go past the beginning of the list sentinel->next() is the first node of the list
            m_current = m_current->previous();
            return *this;
          }


          bool operator==(const iterator& other) const{ // it1 == it2 to compare equality of two iterators
            return m_current == other.m_current && m_sentinel == other.m_sentinel;
          }

          bool operator!=(const iterator& other) const{ // it1 != it2 to compare difference of two iterators
            return m_current != other.m_current || m_sentinel != other.m_sentinel;
          }

          // -> operator to address the data of the current node (read only)
          T* operator->(){
            assert(m_current != m_sentinel);
            return &m_current->data();
          }
      };

    public:
      
      // const iterator to the first element (read only)
      const_iterator begin() const{
        return const_iterator(m_liste, m_liste->next());
      }

      // const iterator to the last element (read only)
      const_iterator end() const{
        return const_iterator(m_liste, m_liste);
      }

      // iterator to the first element (read and write)
      iterator begin(){
        return iterator(m_liste, m_liste->next());
      }

      // iterator to the last element (read and write)
      iterator end(){
        return iterator(m_liste, m_liste);
      }
      /**
       * Insère un élément dans la position donnée.
       * @param position : itérateur pointant vers la position d'insertion
       * @param x : valeur à insérer
       * @return itérateur vers l'élément inséré
       */
      iterator insert(iterator position, const T& x){
        assert(position.m_sentinel == m_liste); // this line made me change the whole implementation of the class iterator, since the only attrubte
                                                // I was using is m_current, so the test ASSERT_DEATH(liste1.insert(liste2.begin(), 3.14159), "Assertion.*failed"); 
                                                // was failing, so I had to add a new attribute m_sentinel to the iterator class to be able to test that the 
                                                // iterator is from the same list as the one we are trying to insert into

        Chainon* newNode = new Chainon(x); // node to be inserted
        position.m_current->insertBefore(newNode); // insert the node before the current node
        m_size++;
        --position;
        return position; // return iterator to the new node
      }

      iterator erase(iterator position){
        // We suppose position exists in the list
        assert(position.m_sentinel == m_liste); // same idea as in insert() to verify the iterator passed is from the same list
        assert(!empty());
        assert(position != this->end());
        Chainon* tmp = position.m_current; // node to be deleted
        ++position; // move iterator to the next node
        tmp->detach(); // detach the node from list
        delete tmp;
        m_size--;
        return position; // return iterator to the next node
      }

      

};


  /**
 * Recherche un élément dans la séquence [premier, dernier[
 * @param premier : début de la séquence
 * @param dernier : fin de séquence
 * @param x : valeur recherchée
 * @return itérateur qui désigne x s'il est trouvé ;
 *         cet itérateur est égal à dernier si x est absent
 */
template <class InputIterator, class T>
InputIterator find(InputIterator premier, InputIterator dernier, const T& x){
  while (premier != dernier && *premier != x){
  ++premier;
  }
  return premier;
}


#endif // LISTE_H
