# cachedMap
c++

Implementation of a system for managing main memory and cache by implementing smart pointers.

The system creates a template class which contains 2 maps:

A. A map containing all the members, whose value (V) is a common smart pointer (ptr_shared) to V.

B. A map containing cache of the recently accessed organs, where the value (V) is a weak smart pointer (weak_ptr) to V.


Implementation of methods that allow:

- Given a key, the method searches the map for an organ that has that key.

- Given a key and value, the method adds this element to the map.

- Given a key, the method first searches the cache for a value for that key. If so, the method distinguishes between two cases - 

(1) the value that is in the correct cache - in this case, the method returns a common pointer (ptr_shared) to this object. 

(2) The value in the cache is invalid - in this case, the method deletes the member from the cache.
If the organ is not in the cache, the method searches for the organ on the map. If found, first add it to the cache and then return a common pointer (ptr_shared) to this object. If not found, the method returns nullptr.
