| l.p | Data structure name         | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      | Lang | Paradigm                                                                                                                                        |
|-----|-----------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| 1   | Dynamic array               | 1. Implementation of an array of pointers to objects.<br>(Employee** arrOfEmployees = new Employee* [numberOfEmployees];).<br><br>2. Array is being bubble-sorted (optimized version)<br><br>3. FisherYates shuffling is used for Employee->uniqueValue generation.                                                                                                                                                                                                                                                                                                                                                                                                                                                                              | C++  | structural                                                                                                                                      |
| 2   | SkipList                    | Implementation of a SkipList.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    | C++  | object oriented but classes are in single cpp file                                                                                              |
| 3   | Binary Search Tree with DSW | Binary Search Tree with possibility to make a right or left backbone and balancing the backbone algorithm (Day-Stout-Warren algorithm)..                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         | C++  | object oriented but classes are in single cpp file                                                                                              |
| 4   | HashTable & List            | Generic HashTable<TKey, TNode, THashFunc> partial implementation with tree strategies resolving collisions (scenario where same index value is generated by hashTable):<br>a) Chaining, where it assumes that on collision  a LinkedList is being created for all collisions nodes.<br><br>b) Linear probing, where it assumes that on collision we try to find a place as close as possible to the given node<br><br>c) DoubleHashing, where it assumes that if first hash function resulted in collision, the second is used<br><br>I also accidentally implemented simple  List (LinkedList) because I thought it would be useful for linear probing strategy, but I've just expanded TblNode with *TblNode _next field and was not needed :) | C++  | object oriented with classes organized in several(.h and .cpp) files instead of<br>having all in single main.cpp. c++ templates were also used  |
