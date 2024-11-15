DSA HACKATHON 

TEAM NUMBER: 1 

TEAM MEMBERS:  

SS Neranjana – PES2UG23CS606 

Suchitra Shankar - PES2UG23CS608 

Tejas R - PES2UG23CS648 

T Sai Rishil - PES2UG23CS655 


Recommender System 

Modules used: 

#include <stdio.h>:  includes the standard input-output header file (stdio. h), which contains essential functions like printf() , scanf() , and many other. 

#include <string.h>: it is a standard header file in the C language that contains functions for manipulating strings. 

User Defined Modules (product.c, users.c, rengine.c[Recommendation engine]) 

Data Structure used: Hashing (Linear Probing), Splay Tree. 

Justification:  

The system involves adding, searching, updating, and displaying users. Linear probing provides a straightforward mechanism to handle these operations efficiently. 

The logic for linear probing is straightforward: simply move to the next slot until an empty slot is found. 

Given the size of the hash table (1000 slots) and typical user management requirements, linear probing should work well. 

Splay tree gives most recently accessed node on the root, this makes accessing history much easier since we can directly access the most recent changes.  

The logic for splay tree is to rotate the tree and bring the most recent addition to the top, this series of rotations is called splaying. 

The recommendation system involves the implementation of a collaborative filtering mechanism, where users with similar taste in products get each others interests as recommendations. A graph has been used to facilitate this  



OUTPUT: 

![image](https://github.com/user-attachments/assets/a32590e5-83bf-49e8-b80e-2058b5e94619)

![image](https://github.com/user-attachments/assets/9ed49c37-3c8c-45ff-90c4-2e2c9afa976f)

![image](https://github.com/user-attachments/assets/b8e29b61-0f4e-46f2-a1c5-bef07c1f893c)

![image](https://github.com/user-attachments/assets/142d3838-696b-4462-af00-79da09fc8a77)

![image](https://github.com/user-attachments/assets/50ea6fec-32a5-4f6a-b20b-21a9eb2e1d86)





