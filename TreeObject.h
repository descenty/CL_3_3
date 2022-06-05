#ifndef __TREEOBJECT_H__
#define __TREEOBJECT_H__

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include "StringExtensions.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class TreeObject;

typedef void (TreeObject::* TYPE_SIGNAL)(string&);
typedef void (TreeObject::* TYPE_HANDLER)(string);

#define SIGNAL_D(signal_f) (TYPE_SIGNAL) (&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER) (&handler_f)
struct Connection
{
	TYPE_SIGNAL signal;
	TreeObject* object;
	TYPE_HANDLER handler;
};

class TreeObject
{
private:
	string name = "";
	TreeObject* parent = nullptr;
	vector<TreeObject*> children;
	vector<Connection> connections;
public:
	int state = 0;
	int classNum = 0;
	TreeObject(TreeObject* parent, string name);
	TreeObject(TreeObject* parent = nullptr);

	string GetName();
	void SetName(string newName);
	void SetParent(TreeObject* newParent);

	TreeObject* GetRoot();
	TreeObject* GetObjectByName(string name, bool withNested);
	TreeObject* GetObjectByNameInChildren1(string name);
	TreeObject* GetObjectByPath(string path);
	string GetAbsolutePath();

	void PrintTree(string);
	void PrintTreeWithStates(string);
	void SetState(int);
	bool IsReady();
	bool BranchReady();

	void SetConnection(TYPE_SIGNAL signal, TreeObject* object, TYPE_HANDLER handler);
	void DeleteConnection(TYPE_SIGNAL signal, TreeObject* object, TYPE_HANDLER handler);
	void EmitSignal(TYPE_SIGNAL signal, string& message);
};

#endif