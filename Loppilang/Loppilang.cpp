#pragma once

#include <iostream>

#include "AVLTree.h"
#include "TIDTree.h"
#include "TypeOpStack.h"

using std::cout;
using std::cin;

void print_type(const NodeType& type)
{
	if (type == NodeType::ROOT)
		std::cout << "ROOT";
	else if (type == NodeType::SCOPE)
		std::cout << "SCOPE";
	else if (type == NodeType::FUNC)
		std::cout << "FUNC";
	else if (type == NodeType::TYPE)
		std::cout << "TYPE";
	else
		std::cout << "BODY";
}

void print_current_tid(TIDTree& tid_tree) {
	Node* current_node = tid_tree.get_current_node();

	cout << "\n\n";
	print_type(current_node->_type);
	cout << " Name: " << current_node->_name << "\n";

	cout << "\n\nVars: " << current_node->_tid.get_vars().get_vars().size() << "\n";
	for (auto& scope : current_node->_tid.get_vars().get_vars())
	{
		cout << "name: " << scope.first << " type: " << scope.second << "\n";
	}

	cout << "\n\nFuncs: " << current_node->_tid.get_funcs().get_funcs().size() << "\n";
	for (auto& func : current_node->_tid.get_funcs().get_funcs())
	{
		cout << "name: " << func.first << " return_type: " << func.second.first << "\n";
		for (auto& [par, type] : func.second.second)
		{
			cout << "\tname: " << par << " type: " << type << "\n";
		}
	}

	cout << "\n\nTypes: " << current_node->_tid.get_types().get_types().size() << "\n";
	for (auto& type : current_node->_tid.get_types().get_types())
	{
		cout << "name: " << type.first << "\n";
		for (auto& [var, var_type] : type.second)
		{
			cout << "\tname: " << var << " type: " << var_type << "\n";
		}
	}

	cout << "\n\nChildren: " << current_node->_children.size() << "\n";
	for (auto& child : current_node->_children)
	{
		cout << "\t";
		print_type(child.second->_type);
		cout << " name: " << child.first << "\n";
	}
}

void process() {
	TIDTree tid_tree;

	print_current_tid(tid_tree);
	while (true) {
		std::string command;
		std::cout << ">>> ";
		std::cin >> command;
		if (command == "create_body")
		{
			tid_tree.create_tid(NodeType::BODY);
		}
		else if (command == "create_scope")
		{
			std::string name;
			std::cin >> name;
			tid_tree.create_tid(NodeType::SCOPE, name);
		}
		else if (command == "create_func")
		{
			std::string name;
			std::cin >> name;
			tid_tree.create_tid(NodeType::FUNC, name);
		}
		else if (command == "create_type")
		{
			std::string name;
			std::cin >> name;
			tid_tree.create_tid(NodeType::TYPE, name);
		}
		else if (command == "leave_tid")
		{
			tid_tree.leave_tid();
		}
		else if (command == "push_var")
		{
			std::string name, type;
			std::cin >> name >> type;
			tid_tree.push_var(name, type);
		}
		else if (command == "push_func")
		{
			std::string name, return_type;
			std::cin >> name >> return_type;
			int param_size;
			std::cin >> param_size;
			func_parameters params(param_size);
			for (auto& el : params)
			{
				std::cin >> el.first >> el.second;
			}

			tid_tree.push_func(name, return_type, params);
		}
		else if (command == "push_type")
		{
			std::string name;
			std::cin >> name;
			int fields_size;
			std::cin >> fields_size;
			std::map<std::string, std::string> fields;
			for (int i = 0; i < fields_size; ++i)
			{
				std::string f, s;
				std::cin >> f >> s;
				fields[f] = s;
			}
			tid_tree.push_type(name, fields);
		}
		else if (command == "delete_var")
		{
			std::string name;
			std::cin >> name;
			tid_tree.delete_var(name);
		}
		else if (command == "push_jump")
		{
			std::string s;
			cin >> s;
			tid_tree.push_jump(s);
		}
		else if (command == "check_jumps")
		{
			tid_tree.check_jumps();
		}
		else
		{
			continue;
		}
		print_current_tid(tid_tree);
	}
}

void print_stack(const TypeOpStack& st)
{
	cout << "\n" << st.size() << "\n";
	for (auto& el : st.get_stack())
	{
		cout << el << " ";
	}
	cout << "\n\n";
}

void process_stack() {
	TypeOpStack st;

	while (true) {
		cout << ">>> ";
		std::string s;
		cin >> s;
		if (s == "push")
		{
			std::string lex;
			cin >> lex;
			st.push(lex);
		}
		else if (s == "check_bin")
		{
			cout << st.check_bin() << "\n";
		}
		else if (s == "check_uno")
		{
			cout << st.check_uno() << "\n";
		}
		else if (s == "checl_assignment")
		{
			cout << st.check_assignment() << "\n";
		}
		else if (s == "eq_bool")
		{
			cout << st.eq_bool() << "\n";
		}
		else if (s == "clear")
		{
			st.clear();
		}
		else {
			continue;
		}
		print_stack(st);
	}
}

int main()
{
	try
	{
		process_stack();
	}
	catch (std::invalid_argument error)
	{
		std::cerr << "Invalid argument: " << error.what() << "\n";
	}
	catch (std::logic_error error)
	{
		std::cerr << "Logic error: " << error.what() << "\n";
	}
}