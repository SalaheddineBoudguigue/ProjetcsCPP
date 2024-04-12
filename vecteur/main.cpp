#include "vecteur.h"
#include <iostream>
#include <cassert>


/** \brief Programme principal */

int main()
{
  /** Insérez votre code ici... */

  Vecteur* v1 = lireVecteur();
  std::cout << *v1 << std::endl;
  
  Vecteur* v2(lireVecteur()); 
  std::cout << *v2 << std::endl;

  // initialiser v3 avec 0 et affecter la somme de v1 et v2 à v3
  Vecteur v3 = *v1 + *v2;
  afficherVecteur(&v3);

  // test de la surcharge de l'opérateur *
  float prdScalaire_v1_v2 = *v1 * *v2;
  std::cout << "Produit scalaire de v1 et v2 : " << prdScalaire_v1_v2 << std::endl;

  // test de la surcharge de l'opérateur +
  v3 = v3 + v3 + v3;
  std::cout << v3 << std::endl;

  // test de la surcharge de l'opérateur [] en lecture
  Vecteur v4;
  std::cin >> v4;
  for (int i = 0; i < v4.dimensions(); i++) {
    std::cout << v4[i] << " ";
  }
  std::cout << std::endl;

  // test de la surcharge de l'opérateur [] en écriture
  v4[0] = 1000;
  for (int i = 0; i < v4.dimensions(); i++) {
    std::cout << v4[i] << " ";
  }
  std::cout << std::endl;
  

  // libérer la mémoire
  delete v1;
  delete v2;


  return 0 ;
}


/*
REMARK :
 Vecteur v3(add(v1, v2); is same as Vecteur v3 = add(v1, v2); without implementing the = operator
*/

/* Q3 . Lorsqu'on fournit une coordonnée supérieure dans une dimension supérieure à celle
  du vecteur, le programme s'arrête de s'exécuter. Cela est dû à l'assertion qui vérifie que 
  l'indice est inférieur à la dimension du vecteur. (assert (i >= 0 && i < N);)
*/

/* Q4. 
  Lorsqu'on décommente la ligne  v3 = add(v1, v2);, le programme ne compile pas. 
  Cela est dû au fait que l'opérateur = n'est pas défini pour la classe Vecteur.
  Pour résoudre ce problème, on peut définir l'opérateur = pour la classe Vecteur.
*/

/*
Q6.

When compiled with -fno-elide-constructors, the output is:
Vecteur de dimension 3 initialisé avec la valeur 1
Vecteur de dimension 3 : ( 0 0 0 )
Vecteur de dimension 3 : ( 1 1 1 ) 
        --- MEMORY MANAGER: tableaux --- Allocation @ 0x55a3a2e85a10 / 12 octets
Vecteur de dimension 3 initialisé avec la valeur 0
        --- MEMORY MANAGER: tableaux --- Liberation @ 0x55a3a2e85a10 / 12 octets
Vecteur de dimension 3 : ( -nan -nan -nan )
        --- MEMORY MANAGER: tableaux --- Liberation @ 0x55a3a2e85960 / 12 octets
        --- MEMORY MANAGER: objects  --- Liberation @ 0x55a3a2e85940 / 16 octets
        --- MEMORY MANAGER: tableaux --- Liberation @ 0x55a3a2e859f0 / 12 octets
        --- MEMORY MANAGER: objects  --- Liberation @ 0x55a3a2e859d0 / 16 octets
        --- MEMORY MANAGER: tableaux ---  ERREUR ! @ 0x5653cbe6fa10 non allouée !

And this is due to the fact that the temporary object (created inside add function) is not elided, and the destructor is called on it. 
This is why the memory manager is called twice for the temporary object, and once for the two arrays.

Implemeting the destructor won't solve the problem.
The solution is to use the optimization provided by the compiler so we don't call the copy constructor and the destructor when we don't need to.
Or we implement the copy constructor (deep copy) and the = assignment operator
ourselves rather than relying on the default ones.


*/


/*
Q7.  

Here writing *v1 = *v2; wihtout implementing the =operator (using the default one provided by the compiler) 
leads to a memory leak because the data pointer of v1 will be lost and the memory will not be freed  
*/

/*
Q8.
  
I thought about using a reference, but I used the add function to implement the addition of two vectors. 
However, the add function returns a Vector object and not a reference.

We should not use a reference to implement the addition of two vectors because we cannot return a reference to a local object. 
This is because the local object will be destroyed at the end of the function, making the reference invalid.

We also cannot use a pointer to return the object because we would have to manage memory manually. 
This resulted in a memory leak in the case of adding two vectors because I wasn't able to free the allocated memory for the result vector (somme). 
Even though I freed the memory allocated for vectors v1, v2, and somme (v3). 
This is due the fact that the pointer to the result vector is lost after the function returns.
*/