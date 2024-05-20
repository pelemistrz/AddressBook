#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;

struct Contact
{
    string name= "", surname = "", email = "", address = "", phone = "";
    int id = 0;
};

struct User
{
    int id;
    string login;
    string password;
};


int loadAddressBookFromFile(vector<Contact> &contacts);
int newContact(vector<Contact> &contacts,int numberOfContacts);
void searchByName(vector<Contact> &contacts,int numberOfContacts);
void searchBySurname(vector<Contact> &contacts, int numberOfContacts);
void showAllContacts(vector<Contact> &contacts, int numberOfContacts);
int deleteContact(vector<Contact> &contacts, int numberOfContacts);
void editContact(vector<Contact> &contacts, int numberOfContacts);

int loadUsers(vector<User> &users);
int registration(vector<User> &users, int numberOfUsers);
int logIn(vector<User> &users, int numberOfUsers);

void showContact(vector<Contact> &contacts, int whichContact);


//Ksiazka addressowa - funkcje
int newContact(vector<Contact> &contacts,int numberOfContacts)
{
    int lastId = 0;
    int contactId = 0;
    string name, surname, email, address, phone;

    cout << "Please provide name " << endl;
    cin >> name;
    cout << "Please provide surname: " << endl;
    cin >> surname;
    cout << "Please provide email: " << endl;
    cin >> email;
    cout << "Please provide address: " << endl;
    cin.sync();
    getline(cin, address);
    cout << "Please provide phone number: " << endl;
    cin.sync();
    getline(cin, phone);

    if (contacts.size()==0)
    {
        contactId = 1;
    }
    else
    {
        lastId = contacts[contacts.size()-1].id;
        contactId = lastId + 1;
    }

    Contact newContact;

    newContact.id = contactId;
    newContact.name = name;
    newContact.surname = surname;
    newContact.email = email;
    newContact.address = address;
    newContact.phone = phone;

    contacts.push_back(newContact);

    ofstream file;
    file.open("AddressBook.txt",ios::out | ios::app);
    if (file.good())
    {
        file<<contactId<<"|";
        file<<name<<"|";
        file<<surname<<"|";
        file<<phone<<"|";
        file<<email<<"|";
        file<<address<<endl;

        file.close();
        cout<<endl;
    }

    numberOfContacts++;
    cout<<"Contact has been added"<<endl;
    system("pause");
    system("cls");
    return numberOfContacts;
}

int loadAddressBookFromFile(vector<Contact> &contacts)
{
    ifstream file;
    file.open("AddressBook.txt",ios::in);
    int counter = 0;
    string line;

    Contact contact;

    if (file.good())
    {
        while (getline(file,line,'|'))
        {
            contact.id = atoi(line.c_str());

            getline(file,line,'|');
            contact.name = line;

            getline(file,line,'|');
            contact.surname = line;

            getline(file,line,'|');
            contact.phone = line;

            getline(file,line,'|');
            contact.email = line;

            getline(file,line);
            contact.address = line;

            contacts.push_back(contact);

            counter++;
        }
    }

    return counter;
}

void searchByName(vector<Contact> &contacts, int numberOfContacts)
{
    string name;
    bool isFound = false;
    cout <<"Please enter name: "<<endl;
    cin.sync();
    cin >> name;
    cout<<endl;

    for(int i=0; i<numberOfContacts; i++)
    {
        if (name == contacts[i].name)
        {
            showContact(contacts,i);
            isFound = true;
        }
    }
    if(!isFound)
    {
        cout << "\n"
             << "There is no contact with this name"
             << "\n"
             << "\n";
    }
}

void searchBySurname(vector<Contact> &contacts, int numberOfContacts)
{
    string surname;
    bool isFound = false;
    cout <<"Please enter surname: "<<endl;
    cin.sync();
    cin >> surname;
    cout<<endl;

    for(int i=0; i<numberOfContacts; i++)
    {
        if (surname == contacts[i].surname)
        {
            showContact(contacts,i);
            isFound = true;
        }
    }
    if(!isFound)
    {
        cout << "\n"
             << "There is no contact with this surname"
             << "\n"
             << "\n";
    }

}

void showAllContacts(vector<Contact> &contacts, int numberOfContacts)
{
    if (numberOfContacts == 0)
    {
        cout << "There is no contacts" << endl;
    }
    cout << endl;
    for (int i = 0; i < numberOfContacts; i++)
    {
        showContact(contacts,i);
    }
}

int deleteContact(vector<Contact> &contacts, int numberOfContacts)
{
    int contactToDelete;
    cout << "Please provide contact id to remove." << endl;
    cin >> contactToDelete;
    int i = 0;
    bool isFound = false;

    while (i < numberOfContacts)
    {
        if (contactToDelete == contacts[i].id)
        {
            isFound = true;
            break;
        }
        i++;
    }
    if (!isFound)
    {
        cout << "There is no contact with this id." << endl;
        return numberOfContacts;
    }
    else
    {
        cout << "Are you sure you want remove this contact? Enter \'y\' for yes on \'n\' for no" << endl;
        char yesOrNo;
        cin.sync();
        cin >> yesOrNo;

        if (yesOrNo == 'y')
        {
            vector<Contact>::iterator itr;
            itr = contacts.begin();

            contacts.erase(itr + i);

            int sizeOfVectorAterRemovingContact = contacts.size();

            fstream file;
            file.open("AddressBook.txt", ios::out);
            file.clear();
            for (int i = 0; i < sizeOfVectorAterRemovingContact; i++)
            {
                file << contacts[i].id << "|";
                file << contacts[i].name << "|";
                file << contacts[i].surname << "|";
                file << contacts[i].phone << "|";
                file << contacts[i].email << "|";
                file << contacts[i].address << endl;
            }
            file.close();
            cout << "Contact has been deleted." << endl;
            return --numberOfContacts;
        }
        else
        {
            return numberOfContacts;
        }
    }
}

void editContact(vector<Contact> &contacts, int numberOfContacts)
{
    int contactIdForEdit;
    cout << "Please provide contact id for editing: " << endl;
    cin >> contactIdForEdit;
    int i = 0;
    bool isFound = false;

    while (i < numberOfContacts)
    {
        if (contactIdForEdit == contacts[i].id)
        {
            isFound = true;
            break;
        }
        i++;
    }
    if (!isFound)
    {
        cout << "There is no id" << endl;
        return;
    }
    else
    {
        cout << "Which field do you want edit  " << endl;
        char choice;

        cout << "1. Change name. " << endl;
        cout << "2. Change surname. " << endl;
        cout << "3. Change email. " << endl;
        cout << "4. Change address. " << endl;
        cout << "5. Change phone number." << endl;
        cout << "6. Main menu." << endl;
        cin >> choice;
        cin.sync();

        string line;
        switch (choice)
        {
        case '1':
            cout << "Please provide name." << endl;
            getline(cin, line);
            contacts[i].name = line;
            break;
        case '2':
            cout << "Please provide surname." << endl;
            getline(cin, line);
            contacts[i].surname = line;
            break;
        case '3':
            cout << "Please provide email." << endl;
            getline(cin, line);
            contacts[i].email = line;
            break;
        case '4':
            cout << "Please provide address." << endl;
            getline(cin, line);
            contacts[i].address = line;
            break;
        case '5':
            cout << "Please provide phone." << endl;
            getline(cin, line);
            contacts[i].phone = line;
            break;
        case '6':
            return;
            break;
        default:
            break;
        }
        fstream file;
        file.open("AddressBook.txt", ios::out);
        file.clear();
        for (int i = 0; i < numberOfContacts; i++)
        {
            file << contacts[i].id << "|";
            file << contacts[i].name << "|";
            file << contacts[i].surname << "|";
            file << contacts[i].phone << "|";
            file << contacts[i].email << "|";
            file << contacts[i].address << endl;
        }
        file.close();
    }
}


//users funkcje

int loadUsers(vector<User> &users)
{
    ifstream file;
    file.open("Users.txt", ios::in);
    int counter = 0;
    string line;

    User user;

    if(file.good())
    {
        while(getline(file,line,'|'))
        {
            user.id = atoi(line.c_str());

            getline(file,line,'|');
            user.login = line;

            getline(file,line);
            user.password = line;

            users.push_back(user);
            counter++;
        }
    }
    return counter;
}

int registration(vector<User> &users, int numberOfUsers)
{
    int lastId = 0;
    int contactId = 0;
    string login, password;
    cout << endl;
    cout << "Please provide login." << endl;
    cin >> login;

    int i = 0;
    while (i < numberOfUsers)
    {
        if (users[i].login == login)
        {
            cout << "This login exists. Please provide different." << endl;
            cin >> login;
            i = 0;
        }
        else
        {
            i++;
        }
    }

    cout << "Please provide your password." << endl;
    cin >> password;

    User newUser;
    int userId = numberOfUsers + 1;
    newUser.id = userId;
    newUser.login = login;
    newUser.password = password;

    users.push_back(newUser);
    cout << "Your account has been created." << endl;

    ofstream file;
    file.open("Users.txt", ios::out | ios::app);
    if (file.good())
    {
        file << userId << "|";
        file << login << "|";
        file << password << endl;

        file.close();
        cout << endl;
    }

    return numberOfUsers + 1;

}

int logIn(vector<User> &users, int numberOfUsers)
{
    string login, password;
    cout << "Please provide your login" << endl;
    cin >> login;

    int i = 0;
    while (i < numberOfUsers)
    {
        if (users[i].login == login)
        {
            for (int attempt = 0; attempt < 3; attempt++)
            {
                cout << "Please enter your password. You have "  << 3 - attempt << " attempts:" << endl;
                cin >> password;
                if (users[i].password == password)
                {
                    cout << "You log in." << endl;
                    return users[i].id;
                }
            }

            cout << " You entered 3 times wrong passwod. Try again for 3 secunds." << endl;
            Sleep(3000);
            return 0;
        }

        i++;
    }
    cout << "There is no user with this login." << endl;
    return 0;



}

//funkcje pomocnicze
void showContact(vector<Contact> &contacts,int whichContact)
{


    cout << "ID: " << contacts[whichContact].id << endl;
    cout << "Imie: " << contacts[whichContact].name << endl;
    cout << "Nazwisko: " << contacts[whichContact].surname << endl;
    cout << "Telefon: " << contacts[whichContact].phone << endl;
    cout << "Email: " << contacts[whichContact].email << endl;
    cout << "Adres: " << contacts[whichContact].address << endl;
    cout << "\n";
}


int main()
{
    vector<Contact> contacts;
    vector<User> users;

    int numberOfUsers = loadUsers(users);
    int idLoggedUser = 0;

    int numberOfContacts = loadAddressBookFromFile(contacts);


    char choice;

    while(1)
    {
        if(idLoggedUser==0)
        {
            cout << endl;
            cout << "1. Sign in." << endl;
            cout << "2. Log in." << endl;
            cout << "9. Exit." << endl;
            cin >> choice;
            if (choice == '1')
            {
                numberOfUsers = registration(users, numberOfUsers);
            }
            if (choice == '2')
            {
                idLoggedUser = logIn(users, numberOfUsers);
            }
            if (choice == '9')
            {
                exit(0);
            }
        }


        if(idLoggedUser !=0)
        {
            cout<<endl;
            cout<<"Welcome in Address Book. Please choose one option: " <<endl<<endl;
            cout<<"1. Add new contact."<<endl;
            cout<<"2. Search by name."<<endl;
            cout<<"3. Search by surname."<<endl;
            cout<<"4. Show all contacts."<<endl;
            cout<<"5. Delete contact."<<endl;
            cout<<"6. Edit contact."<<endl;
            cout<<"7. Log out."<<endl;
            cout<<"9. Exit."<<endl;
            cin>>choice;
            if (choice == '1')
            {
                numberOfContacts = newContact(contacts,numberOfContacts);
            }
            else if (choice == '2')
            {
                searchByName(contacts,numberOfContacts);
                system("pause");
                system("cls");
            }
            else if (choice == '3')
            {
                searchBySurname(contacts,numberOfContacts);
                system("pause");
                system("cls");

            }
            else if (choice == '4')
            {
                showAllContacts(contacts,numberOfContacts);
                system("pause");
                system("cls");

            }
            else if (choice == '5')
            {
                numberOfContacts = deleteContact(contacts,numberOfContacts);
                system("pause");
                system("cls");

            }
            else if (choice == '6')
            {
                editContact(contacts,numberOfContacts);
                system("pause");
                system("cls");

            } else if (choice == '7'){
                idLoggedUser=0;
            } else if (choice == '9')
            {
                exit(0);
            }
        }



    }
}

