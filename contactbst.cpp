#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include<exception>
#include<stdexcept>
#include<random>
#include<fstream>

#include "contactbst.h"

using namespace std;

Node::Node(string key, MyVector<Contact>* contactVector) // Constructor For Node
{
    this->key = key;
    this->contactVector = contactVector;
    this->left = nullptr;
    this->right = nullptr;
}

Node::~Node() // Destructor For Node
{
    cout<<"deleted.."<<this->key<<endl;
}

ContactBST::ContactBST() // Constructor For ContactBST
{
	this->root = nullptr;
};

ContactBST::~ContactBST() // Destructor For ContactBST
{
	// Keep removing the root of the tree untill it becomes empty
	while(root)
		root = destruct(root, root->key);
};

Node* ContactBST::getRoot()
{
	return root;
};

Node* ContactBST::destruct(Node* ptr, string key)        //Delete all Nodes (For Destructor)
{

    //return null if no node exists
    if (ptr == nullptr)
    {
        return nullptr;
    }
    // Recursively go to left or right until the key is found
    else if (key<ptr->key)
    {
        return destruct(ptr->left, key);
    }
    else if (key>ptr->key)
    {
        return destruct(ptr->right, key);
    }
    // Delete every contact
    else
    {

        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            ptr->getData()->erase(i);
        }

    }

    return nullptr; // return null when every node is deleted

}

int ContactBST::importCSV(Node* ptr, string path) //Load all the contacts from the CSV file to the BST
{
    int count = 0;
    ifstream CSVfile(path);

    if (CSVfile.is_open())
    {

        string line;

        while (getline(CSVfile, line))
        {
            string firstName, lastName, email, phone, city, country, isFavorite;
            bool bool_isFavorite = true;
            string temp_key;

            int commas = 0;

            // Iterate over the entire line, split it according to the number of commas, add the words into a list
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ',')
                {
                    commas++;
                }
                else
                {
                    if (commas == 0 && line[i] != ' ') firstName += line[i];
                    else if (commas == 1 && line[i] != ' ') lastName += line[i];
                    else if (commas == 2 && line[i] != ' ') email += line[i];
                    else if (commas == 3 && line[i] != ' ') phone += line[i];
                    else if (commas == 4 && line[i] != ' ') city += line[i];
                    else if (commas == 5 && line[i] != ' ') country += line[i];
                    else if (commas == 6 && line[i] != ' ') isFavorite += line[i];
                }
            }

            // Set boolean isFavorite variable corresponding the 0 or 1 in the file
            if (isFavorite == "0") bool_isFavorite = false;

            temp_key = firstName + " " + lastName; // Making the key for the contact

            count++; // Increment number of contacts added

            //use the loaded data to create a contact
            Contact* newContact = new Contact(firstName, lastName, email, phone, city, country, bool_isFavorite);

            insert_helper(temp_key, newContact); // Insert contact into the BST
        }

    }
    else
    {
        // Error Message in case file cannot open
        cerr << "Error! File could not be opened." << endl;
        return -1;
    }

    return count; // Return the number of contacts added
}

void ContactBST::sortedContacts(Node* ptr, MyVector<Contact>& tempContacts) // Sorts contacts and adds them into a vector (used by ExportCSV)
{
    if (ptr != nullptr)
    {
        // Move to left of BST until it is null
        if (ptr->left != nullptr) sortedContacts(ptr->left, tempContacts);

        //Adding to vector
        for (int i = 0; i < ptr->getData()->size(); i++)
        {
            tempContacts.push_back(ptr->getData()->at(i));
        }

        // Then move to right of BST until it is null so it adds to vector in ascending order
        if (ptr->right != nullptr) sortedContacts(ptr->right, tempContacts);
    }
}

int ContactBST::exportCSV(Node* ptr, string path) //Export all the contacts from the BST to a CSV file in an ascending order
{
	ofstream contacts(path); 

    int count = 0;

    if (contacts.fail())
    {
        cerr << "Error! File could not be opened." << endl;
        exit(1);
    }

    string line = "";

    // Creating a temporary vector and sorting it in ascending order
    MyVector<Contact> tempContacts;
    sortedContacts(ptr, tempContacts);

    string ifFav; // Used in converting from boolean to string

    for (int i = 0; i < tempContacts.size(); i++)
    {
        // converting from boolean to string
        if (tempContacts.at(i).getisFav() == true)
        {
            ifFav = "1";
        }
        else
        {
            ifFav = "0";
        }

        // One contact's information in a single line
        line = tempContacts.at(i).getfname() + ", " + tempContacts.at(i).getlname() + ", " + tempContacts.at(i).getemail() + ", " + tempContacts.at(i).getprimaryPhone() + ", " + tempContacts.at(i).getcity() + ", " + tempContacts.at(i).getcountry() + ", " + ifFav;
        contacts << line << endl; //printing the line into the file
        count++; // Increment number of contacts printed in the file
    }

    return count; // Return Number of contacts printed in file

}

Node* ContactBST::add(Node* ptr, string key, Contact* data)     //add key into tree/subtree with root ptr
{
    MyVector<Contact>* newContactVector =  new MyVector<Contact>; // Pointer to a vector to add in a node

    // If key already exists, add the contact in the existing vector
    if (search(root, key) != nullptr) 
    {
        ptr->contactVector->push_back(*data);
        return ptr;
    }

    // If key does not exist, use the new vector, add contact in the vector, then add the vector to the node
    else if (ptr == nullptr)
    {
        newContactVector->push_back(*data);
        Node* newNode = new Node(key, newContactVector);
        return newNode;
    }
    else if (key<ptr->key)
    {
        ptr->left = add(ptr->left, key, data);
    }
    else if (key>ptr->key)
    {
        ptr->right = add(ptr->right, key, data);
    }

    return ptr;
}

Node* ContactBST::update(Node* ptr, string key) //Edit the node with key
{
    int index;
    int choice;
    string again;

    // If the key does not exist, return null
    if (ptr == nullptr)
    {
        return nullptr;
    }
    // Recursively go to left or right until the key is found
    else if (key<ptr->key) 
    {
        return update(ptr->left, key);
    }
    else if (key>ptr->key)
    {
        return update(ptr->right, key);
    }
    // Asking user input to update a specific contact
    else
    {
        cout<<ptr->getData()->size()<<" records found:"<<endl;

        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            cout<<i<<". "<<ptr->getData()->at(i).getfname()<<" "<<ptr->getData()->at(i).getlname()<<", "<<ptr->getData()->at(i).getemail()<<", "<<ptr->getData()->at(i).getprimaryPhone()<<", "<<ptr->getData()->at(i).getcity()<<", "<<ptr->getData()->at(i).getcountry()<<endl;
        }

        do
        {
            cout<<"Please select the record you want to edit: ";
            cin>>index;

            cout<<"Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, 6) Country: ";
            cin>>choice;

            if (choice == 1)
            {
                string firstName;

                cout<<"Write the updated First Name: ";
                cin>>firstName;

                ptr->getData()->at(index).setfname(firstName);
            }
            else if (choice == 2)
            {
                string lastName;

                cout<<"Write the updated Last Name: ";
                cin>>lastName;

                ptr->getData()->at(index).setlname(lastName);
            }
            else if (choice == 3)
            {
                string email;

                cout<<"Write the updated Email: ";
                cin>>email;

                ptr->getData()->at(index).setemail(email);
            }
            else if (choice == 4)
            {
                string phone;

                cout<<"Write the updated Phone#: ";
                cin>>phone;

                ptr->getData()->at(index).setprimaryPhone(phone);
            }
            else if (choice == 5)
            {
                string city;

                cout<<"Write the updated City: ";
                cin>>city;

                ptr->getData()->at(index).setcity(city);
            }
            else if (choice == 6)
            {
                string country;

                cout<<"Write the updated Country: ";
                cin>>country;

                ptr->getData()->at(index).setcountry(country);
            }

            cout<<"Do you want to edit another field (y/n)? ";
            cin>>again;

        } while (again == "y");

        return ptr;
    }

}

Node* ContactBST::del(Node* ptr, string key)        //Delete a node with key from the tree/subtree with root
{
    int index;

    //converting from boolean to string
    if (ptr == nullptr)
    {
        return nullptr;
    }
    // Recursively go to left or right until the key is found
    else if (key<ptr->key)
    {
        return del(ptr->left, key);
    }
    else if (key>ptr->key)
    {
        return del(ptr->right, key);
    }
    // Asking user input to delete a specific contact
    else
    {
        cout<<ptr->getData()->size()<<" records found:"<<endl;

        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            cout<<i<<". "<<ptr->getData()->at(i).getfname()<<" "<<ptr->getData()->at(i).getlname()<<", "<<ptr->getData()->at(i).getemail()<<", "<<ptr->getData()->at(i).getprimaryPhone()<<", "<<ptr->getData()->at(i).getcity()<<", "<<ptr->getData()->at(i).getcountry()<<endl;
        }

        cout<<"Please select the record you want to delete: ";
        cin>>index;

        ptr->getData()->erase(index);

        cout<<"The contact record has succesfully been deleted!"<<endl;

        return ptr;
    }

}

Node* ContactBST::search(Node* ptr,string key) //Find and returns the node with key
{
    // If the key does not exist, return null
    if (ptr == nullptr)
    {
        return nullptr;
    }
    // Return the founbd pointer
    else if (ptr->key == key)
    {
        return ptr;
    }
    // Recursively go to left or right until the key is found
    else if (key<ptr->key)
    {
        return search(ptr->left, key);
    }
    else if (key>ptr->key)
    {
        return search(ptr->right, key);
    }

    return ptr;

}

bool ContactBST::markFav(Node* ptr, string key)  //Mark a contact as favorite
{
    int index;

    // If the key does not exist, return null
    if (ptr == nullptr)
    {
        return false;
    }
    // Recursively go to left or right until the key is found
    else if (key<ptr->key) 
    {
        return markFav(ptr->left, key);
    }
    else if (key>ptr->key)
    {
        return markFav(ptr->right, key);
    }
    // Asking user input to Mark Favorite a specific contact
    else
    {
        cout<<ptr->getData()->size()<<" records found:"<<endl;

        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            cout<<i<<". "<<ptr->getData()->at(i).getfname()<<" "<<ptr->getData()->at(i).getlname()<<", "<<ptr->getData()->at(i).getemail()<<", "<<ptr->getData()->at(i).getprimaryPhone()<<", "<<ptr->getData()->at(i).getcity()<<", "<<ptr->getData()->at(i).getcountry()<<endl;
        }

        cout<<"Please select the record you want to mark as favorite: ";
        cin>>index;

        // If it is already marked as favorite, give user the message
        if (ptr->getData()->at(index).getisFav() == true)
        {
            cout<<"It is already as the favorite"<<endl;
            return ptr;
        }

        ptr->getData()->at(index).setisFav(true);

        cout<<ptr->getData()->at(index).getfname()<<" "<<ptr->getData()->at(index).getlname()<<" ("<<ptr->getData()->at(index).getemail()<<") has succesfully been marked as favorite."<<endl;

        return true;
    }
}

bool ContactBST::unmarkFav(Node* ptr, string key)  //Unmark a contact as favorite
{
    int index;

    // If the key does not exist, return null
    if (ptr == nullptr)
    {
        return nullptr;
    }
    // Recursively go to left or right until the key is found
    else if (key<ptr->key) 
    {
        return unmarkFav(ptr->left, key);
    }
    else if (key>ptr->key)
    {
        return unmarkFav(ptr->right, key);
    }
    // Asking user input to Unmark Favorite a specific contact
    else
    {
        cout<<ptr->getData()->size()<<" records found:"<<endl;

        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            cout<<i<<". "<<ptr->getData()->at(i).getfname()<<" "<<ptr->getData()->at(i).getlname()<<", "<<ptr->getData()->at(i).getemail()<<", "<<ptr->getData()->at(i).getprimaryPhone()<<", "<<ptr->getData()->at(i).getcity()<<", "<<ptr->getData()->at(i).getcountry()<<endl;
        }

        cout<<"Please select the record you want to unmark as favorite: ";
        cin>>index;

        // If it is already unmarked as favorite, give user the message
        if (ptr->getData()->at(index).getisFav() == false)
        {
            cout<<"It is already not the favorite"<<endl;
            return ptr;
        }

        ptr->getData()->at(index).setisFav(false);

        cout<<ptr->getData()->at(index).getfname()<<" "<<ptr->getData()->at(index).getlname()<<" ("<<ptr->getData()->at(index).getemail()<<") has succesfully been unmarked as favorite."<<endl;

        return ptr;
    }
}

void ContactBST::printASC(Node* ptr)           //Print the data at nodes in an ascending order
{
    if (ptr != nullptr)
    {
        // First move to left of BST until it is null
        printASC(ptr->left);

        // Print the Contact Information
        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            cout<<ptr->getData()->at(i).getfname() <<" "<<ptr->getData()->at(i).getlname()<<", "<<ptr->getData()->at(i).getemail()<<", "<<ptr->getData()->at(i).getprimaryPhone()<<", "<<ptr->getData()->at(i).getcity()<<", "<<ptr->getData()->at(i).getcountry()<<", "<<ptr->getData()->at(i).getisFav()<<endl;
        }
        // Then move to left of BST until it is null, so as to traverse tree in ascending order
        printASC(ptr->right);
    }

}

void ContactBST::printDES(Node* ptr)           //Print the data at nodes in a descending order
{
    if (ptr != nullptr)
    {
        // First move to right of BST until it is null
        printDES(ptr->right);

        // Print the Contact Information
        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            cout<<ptr->getData()->at(i).getfname() <<" "<<ptr->getData()->at(i).getlname()<<", "<<ptr->getData()->at(i).getemail()<<", "<<ptr->getData()->at(i).getprimaryPhone()<<", "<<ptr->getData()->at(i).getcity()<<", "<<ptr->getData()->at(i).getcountry()<<", "<<ptr->getData()->at(i).getisFav()<<endl;
        }
        // Then move to left of BST until it is null, so as to traverse tree in desecending order
        printDES(ptr->left);
    }
}

void ContactBST::printFav(Node* ptr)           //Print the favorite data at nodes in an ascending order
{
    if (ptr != nullptr)
    {
        // First move to left of BST until it is null
        printFav(ptr->left);

        // Check if it's favorite and then Print the Contact Information
        for (int i = 0; i < ptr->getData()->size(); ++i)
        {
            if (ptr->getData()->at(i).getisFav() == true)
            {
                cout<<ptr->getData()->at(i).getfname()<<" "<<ptr->getData()->at(i).getlname()<<", "<<ptr->getData()->at(i).getemail()<<", "<<ptr->getData()->at(i).getprimaryPhone()<<", "<<ptr->getData()->at(i).getcity()<<", "<<ptr->getData()->at(i).getcountry()<<", "<<ptr->getData()->at(i).getisFav()<<endl;
            }
        }

        // Then move to left of BST until it is null, so as to traverse tree in ascending order
        printFav(ptr->right);
    }
}

//Helper method for insert method
void ContactBST::insert_helper(string key, Contact* data)
{   
    root = add(root, key, data);
}
//=================================================
//Helper method for remove 
void ContactBST::remove_helper(string key)
{
    root = del(root, key);
}
//==================================================================
