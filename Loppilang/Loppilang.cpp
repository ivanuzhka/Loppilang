#pragma once

#include "AVLTree.h"
#include <iostream>
using std::cout;

int main()
{
	AVLTree tree;

	tree.insert("a");
	tree.insert("aa");
	tree.insert("ab");
	tree.insert("aaaaa");

	cout << tree.count("a") << "\n";
	cout << tree.count("aba") << "\n";
	cout << tree.count("ab") << "\n";
}