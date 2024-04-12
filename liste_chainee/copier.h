/**
   3.2.1 chercher une valeur dans une liste triée, nom de la fonction fonction : chercherTri
   @param premier : itérateur positionné sur le premier élément
   @param dernier : itérateur positionné après le dernier élément
   @param x : valeur à chercher
   @return position du premier élément de valeur >= x
   ou end() si un tel élément n'existe pas
 */
// TODO


/**
   3.2.2 créer une copie triée par valeurs croissantes d'une liste, nom de la fonction fonction : copierTri
   @param l : liste à copier
   @return liste triée
*/
// TODO
#ifndef COPIER_H
#define COPIER_H

#include "Liste.h"

template <typename T>
typename Liste<T>::iterator first_largest_or_equal(typename Liste<T>::iterator premier, typename Liste<T>::iterator dernier, const T& x){
  // list is supposed to be sorted
  while (premier != dernier && *premier < x){
    ++premier;
  }
  return premier;
} 

template <typename T>
Liste<T> * sortedCopy(const Liste<T>& l){
  Liste<T>* copy = new Liste<T>();
  for (auto it = l.begin(); it != l.end(); ++it){
    auto it2 = first_largest_or_equal(copy->begin(), copy->end(), *it); // find the first element in copy that is larger or equal to *it
    copy->insert(it2, *it);
  }
  return copy;
}



#endif