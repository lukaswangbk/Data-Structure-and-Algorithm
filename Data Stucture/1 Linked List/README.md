# List
## Definition
A **list** of elements of type T is a finite sequence of elements of T together with the following operations:
- Create the list, and make it empty
- Determine whether the list is empty or not
- Determine whether the list is full or not
- Find the size of the list
- Retrieve any entry from the list, provided that the list is not empty
- Store a new entry replacing the entry at any position in the list provided that the list is not empty
- Insert a new entry into the list at any position, provided that the list is not full
- Delete any entry from the list, provided that the list is not empty
- Clear the list to make it empty
## Implementation
### Linked List
Array List has fixed size while Linked List can grow.\
`insert`: $\mathcal{O}(1)$\
`find`: $\mathcal{O}(n)$
### Doubly Linked List
When ask for the predecessor and check from backward.\
Storage Complexity: 3n
### Circularly Double Linked List
