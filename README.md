# Contact-Management-System

## Introduction

An application to store your personal contacts. The application stores the contact’s attributes, such as first name, last name, phone number, email address, city, country, and a flag showing whether a contact is among favorite contacts or not. The application will be able to import/ export the contacts into a comma separated (CSV) file. The user interface should allow a user to navigate and perform the tasks/features listed in the following section.

It is a program utilizing the object-oriented programming (OOP) principles and appropriate data structures. You are required to use Binary search trees (BSTs) as the primary data structure to implement the application. You should implement all the data structures manually, STL based containers are not allowed to be used here.
           
## Implementation

### CSV File Format:
The details of each contact in order are:
First name, last name, email address, phone, city, country, isFavorite
Ex.: Amal, Obeid, amal.obeid@gmail.com, +971506177234, Al Ain, UAE, 1 

Storing the contact details will generate a file similar to the following:
contacts.csv

Meghan, Malcom, meghan.malcom@live.com, +865505565, Tianmen, China, 0 
Shante, Julian, julian.s@yahoo.com, +521369398, Tijuana, Mexico, 0
Suk, Cornelius, cornelius@gmail.com, +918078552, Bangalore, India, 0 
Desire, Carlo, carlo.desire@airtel.com, +913951978, Ghaziabad, India, 1 
Tamica, Jeremiah, tamica@gmail.com, +814017766, Sapporo, Japan, 1
Nellie, Spencer, n.spencer@nyu.edu, +867652089, Zhanjiang, China, 0 
Deloise, Evan, del.e@nyu.edu, +869645954, Kunming, China, 0 
Wendolyn, Drew, drew@gmail.com, +553847549, Curitiba, Brazil, 1 
Freeman, Odis, freeman@yahoo.com, +844280166, Hanoi, Vietnam, 1 
Teena, Emerson, teena@gmail.com, +919636770, Agra, India, 1 
Nancie, Milan, milan.nancie@gmail.com, +860105217, Taipei, China, 0

### Constraints:
- First name + last name (separated by a space) will serve as a key. For instance, the first name, “John” and the last name “Smith”, form the key “John Smith”.
- Every BST node stores a vector of contact objects. This will allow to have multiple contacts with the same first and last name (i.e., the same key).

### User Interface:
The application will interact with the user using a command line (terminal based) interface as shown below:
The application, after performing the user’s desired operation, presents the menu again for the next operation to be performed.

### Features to Implement:

When your program starts, the user is presented with the list of possible commands. The user is able to interact with the system using the commands until an exit command is issued.

The following features are required to be implemented in the contact management application.
 
1. import [path]
    - Imports a CSV file
    - It will invoke a method with the following header:
        int importCSV(Node* ptr, string path)
    - This method takes pointer to the root node and path as arguments and loads all the contacts from the CSV file at path to the binary search tree. The method either returns the number of contacts read from the file as integer or returns -1 if a bad path is provided

2. export [path]
    - Exports a CSV file
    - It will invoke a method with the following header:
       int exportCSV(Node* ptr, string path)
    - This method takes pointer to the root node and path as arguments and writes all the contacts from the binary search tree to a CSV file in an ascending order. The method either returns the number of contacts written to the file as integer or returns -1 if file cannot be created
 
3. add
    - Adds a new contact.
    - It will invoke a method with the following header:
      Node* add(Node* ptr, string key, Contact *data)
      - It takes pointer to the root node, the key, and the pointer to a Contact object as arguments and returns a pointer to the inserted node/contact (a Node object)
      - The key is of string data type and essentially is firstName + ‘ ‘ + lastName
    
4. edit [key]
    - Updates a contact’s details
    - It will invoke a method with the following header:
       Node* update(Node* ptr, string key)
       - This method takes pointer to the root node and the key as arguments and returns a pointer to the node/contact (the key is immutable (cannot be edited))

5. del [key]
    - Deletes a contact
    - It will invoke a method with the following header:
      Node* delete(Node* ptr, string key)
      - This method takes pointer to the root node and the key as arguments and returns a pointer to the deleted node/contact (a Node object) or a null pointer

6. searchFor [key]
    - Searches for a contact
    - It will invoke a method with the following header:
       Node* search(Node* ptr, string key)
      - This method takes pointer to the root node and the key as arguments and returns a pointer to the found node/contact (a Node object) or a null pointer if the search fails to find any contact with the given key.

7. markfv [key]
    - Marks acontact as favorite
    - It will invoke a method with the following header:
      bool markFav(Node* ptr, string key)
      - This method takes pointer to the root node and the key as arguments and returns a Boolean flag showing if the operation was successful
 
8. umarkfv [key]
    - Unmarks a contact as favorite
    - It will invoke a method with the following header:
      bool unmarkFav(Node* ptr, string key)
      - This method takes pointer to the root node and the key as arguments and returns a Boolean flag showing if the operation was successful
      
9. printASC
    - Displays all contacts in an ascending order
    - It will invoke a method with the following header:
      void printASC(Node* ptr)
       - This method takes pointer to the root node as arguments and prints the data at each node until the entire tree has been traversed
       
10. printDES
     - Displays all contacts in a descending order
     - It will invoke a method with the following header:
       void printDES(Node* ptr)
       - This method takes pointer to the root node as arguments and prints the data at each node until the entire tree has been traversed
  
11. printfv
    - Displays all favorite contacts in an ascending order 
    - It will invoke a method with the following header:
      void printFav(Node* ptr)
      - This method takes pointer to the root node as arguments and prints the data at each node (only if it is marked as favorite) until the entire tree is traversed
      
12. help
    - Displays the available commands and their descriptions

13. exit
    - Exits the program
