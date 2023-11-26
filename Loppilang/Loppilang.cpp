#pragma once

#include "AVLTree.h"
#include <iostream>
using std::cout;

int main()
{
	AVLTree tree;

	tree.insert("a", 1);
	tree.insert("aa", 2);
	tree.insert("ab", 1);
	tree.insert("aaaaa", 3);

	cout << tree.count("a") << "\n";
	cout << tree.count("aba") << "\n";
	cout << tree.count("ab") << "\n";
	cout << "\n";
	
	tree.bfs_out();

	cout << "\n";
	cout << tree.get_type("aaaaa") << "\n";
	cout << tree.get_type("abcd") << "\n";
}