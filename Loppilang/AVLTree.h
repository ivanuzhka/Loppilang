#pragma once

#include <queue>
#include <iostream>
#include <string>

using std::string;

class NodeAVL
{
public:
	NodeAVL* _left = nullptr, * _right = nullptr;
	NodeAVL() : _key(0) {}
	NodeAVL(string x) : _key(x) {}
	string _key;
};

class AVLTree
{
private:

	int height(const NodeAVL*) const;

	void small_left_rotate(NodeAVL*&);
	void small_right_rotate(NodeAVL*&);
	void big_left_rotate(NodeAVL*&);
	void big_right_rotate(NodeAVL*&);

	void balance(NodeAVL*&);

	void insert(NodeAVL*&, string);

	void erase(NodeAVL*&, string);

	void bfs_out(NodeAVL*) const;

	int count(NodeAVL*, string) const;

	NodeAVL* _tree;

public:
	AVLTree() : _tree(nullptr) {}
	AVLTree(NodeAVL* other) : _tree(other) {}

	void insert(string);
	void erase(string);
	int count(string) const;

	void bfs_out() const;
};
