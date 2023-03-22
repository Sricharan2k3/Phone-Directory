#include<iostream>
#include<string>
#include<cmath>
#include <fstream>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
using namespace std;

class node {
public:
    long long int data;
    string nam;
    node *right;
    node *left;
};

float scanNum(char ch) {
    int value;
    value = ch;
    return float(value - '0');
}

node *insertion(node *root, string name, long long int number) {
    int i = 0;
    if (root) {
        while (scanNum(root->nam[i]) == scanNum(name[i])) {
            i++;
        }
    }

    if (!root) {
        root = new node;
        root->nam = name;
        root->data = number;
        root->left = nullptr;
        root->right = nullptr;
    } else if (scanNum(root->nam[i]) > scanNum(name[i])) {

        root->left = insertion(root->left, name, number);
    } else {
        root->right = insertion(root->right, name, number);
    }
    return root;
}

void inorder(node *root) {
    if (root) {
        inorder(root->left);
        cout << "\nName : " << root->nam << "\n" << "Contact Number : +91 " << root->data << endl;
        inorder(root->right);
    }

}

node *minValueNode(node *root) {
    node *current = root;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

node *deleteNode(node *root, string key) {
    int i = 0;

    if (root->nam != key) {
        while (scanNum(root->nam[i]) == scanNum(key[i])) {
            i++;
        }
    }

    if (key[i] < root->nam[i])
        root->left = deleteNode(root->left, key);

    else if (key[i] > root->nam[i])
        root->right = deleteNode(root->right, key);

    else {
        if (root->left == nullptr) {
            node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == nullptr) {
            node *temp = root->left;
            free(root);
            return temp;
        }
        node *temp = minValueNode(root->right);
        root->nam = temp->nam;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->nam);
    }

    return root;
}

long long int search(node *root, string sname) {
    if (root) {
        while (root != nullptr) {
            if (sname > root->nam)
                root = root->right;
            else if (sname < root->nam)
                root = root->left;
            else
                return root->data;
        }
        return 0;
    }
}


void merge(node *root, string mname, long long int number) {
    if (root) {
        while (root != nullptr) {
            if (mname > root->nam)
                root = root->right;
            else if (mname < root->nam)
                root = root->left;
            else {
                root->data = number;
                break;
            }
        }
    }
}


bool ifNodeExists(node *root, long long int key) {
    if (root == nullptr)
        return false;

    if (root->data == key)
        return true;

    bool res1 = ifNodeExists(root->left, key);
    if (res1) return true;

    bool res2 = ifNodeExists(root->right, key);
    return res2;
}

int main() {
    int choice;
    long long int number;

    string name;
    string del;
    string sname;
    char ans;
    int size;
    int pos;
    long long int num;
    long long int r, p;
    node *root = nullptr;
    fstream fin;
    fin.open("data.csv");
    string line;
    while(!fin.eof()){

        fin>>line;
        cout<<line<<" ";
    }


        cout
                << "\n\n********************************************* PHONE DIRECTORY **************************************************\n";
        while (true) {
            cout
                    << "\nEnter the choice\n\n 1) New Contact\n 2) Delete Existing Contact\n 3) Display Directory\n 4) Search Contact\n 5) Exit\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter contact name : " << endl;
                    cin >> name;
                    cout << "Enter contact number : " << endl;
                    cin >> number;
                    size = trunc(log10(number)) + 1;
                    if (size != 10) {
                        cout << "Enter valid contact number" << endl;
                        break;
                    }


                    if (ifNodeExists(root, number)) {
                        cout << "Duplicate contact found. Re-enter details." << endl;
                        break;
                    }


                    if (search(root, name)) {
                        cout << "Duplicate contact found. Do you want to merge and update contact? (y/n)" << endl;
                        cin >> ans;
                        if (ans == 'y') {
                            merge(root, name, number);
                            break;
                        } else
                            break;
                    } else {
                        root = insertion(root, name, number);
                        break;
                    }


                case 2:
                    cout << "Enter name of the contact to delete : " << endl;
                    cin >> del;
                    p = search(root, del);
                    if (p) {
                        deleteNode(root, del);
                        cout << "You have successfully deleted the contact" << endl;
                        cout << "Name : " << del << endl;
                        cout << "Contact Number : +91 " << p << endl;

                    } else
                        cout << "No contact found";
                    break;

                case 3:
                    if (root) {
                        inorder(root);
                    } else
                        cout << "Phone Directory is empty.";
                    break;

                case 4:
                    cout << "Enter name of contact to search in directory : " << endl;
                    cin >> sname;
                    r = search(root, sname);
                    if (r) {
                        cout << "Contact Found" << endl;
                        cout << "Name : " << sname << endl;
                        cout << "Contact Number : +91 " << r << endl;
                    } else {
                        cout << "Contact Not Found !!" << endl;
                    }
                    break;

                case 5:
                    exit(0);
            }
        }
    }
