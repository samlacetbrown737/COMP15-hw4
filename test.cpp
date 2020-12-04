/*
 * test.cpp
 *
 *  Created on: Nov 11th, 2020
 *      Author: Sam Lacet-Brown
 * Driver for testing the BinarySearchTree class
 */
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

void copyTest() {
    BinarySearchTree bst;
    cout << "Inserting 4x 108, 0, and -8" << endl;
    bst.insert(108);
    bst.insert(-8);
    bst.insert(108);
    bst.insert(108);
    bst.insert(0);
    bst.insert(108);
    bst.print_tree();
    cout << "Made a copy of the BST" << endl;
    BinarySearchTree bst_copy_constructor = bst;
    bst_copy_constructor.print_tree();
    cout << "Assigned BST to a new BST" << endl;
    BinarySearchTree bst_copy_1;
    bst_copy_1 = bst;
    bst_copy_1.print_tree();
    cout << "contains -8? " << bst.contains(-8) << endl;
    cout << "contains 18? " << bst.contains(18) << endl;
    bst.remove(-8);
    cout << "Removing -8" << endl;
    cout << "contains -8? " << bst.contains(-8) << endl;
    bst.insert(-8);
    cout << "Inserting -8" << endl;
    cout << "contains -8? " << bst.contains(-8) << endl;
    bst.insert(-8);
    bst.insert(-8);
    cout << "Inserting 2x -8" << endl;
    cout << "contains -8? " << bst.contains(-8) << endl;
}

void removalTest() {
    cout << "Making new BST" << endl;
    BinarySearchTree bst2;
        int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
        int numValues = sizeof(values) / sizeof(int);

        for (int i = 0; i < numValues; i++) {
            bst2.insert(values[i]);
            cout << "Inserted  " << values[i] << endl;
        }
        bst2.print_tree();
        bst2.remove(-6);
        cout << "remove -6" << endl;
        bst2.print_tree();
        bst2.remove(9);
        cout << "remove 9" << endl;
        bst2.print_tree();
        bst2.remove(11);
        cout << "remove 11" << endl;
        bst2.print_tree();
        bst2.remove(3);
        cout << "remove 3" << endl;
        bst2.print_tree();
        bst2.remove(4);
        cout << "remove 4" << endl;
        bst2.print_tree();
}

int main()
{
    copyTest();
    removalTest();
}