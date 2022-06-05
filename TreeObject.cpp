#include "TreeObject.h"


TreeObject::TreeObject(TreeObject* parent)
{
	SetParent(parent);
}

TreeObject::TreeObject(TreeObject* parent, string name)
{
	SetName(name);
	if (parent)
		SetParent(parent);
}

void TreeObject::SetName(string name) { this->name = name; }


string TreeObject::GetName() { return name; }

bool TreeObject::IsReady()
{
	return state != 0;
}

bool TreeObject::BranchReady()
{
	if (!parent)
		return IsReady();
	else
		return parent->IsReady();
}

void TreeObject::SetState(int state)
{
	if (parent)
	{
		if (BranchReady())
		{
			this->state = state;
			if (!IsReady())
				for (size_t i = 0; i < children.size(); i++)
					children[i]->SetState(0);
		}
		else
		{
			this->state = 0;
			for (size_t i = 0; i < children.size(); i++)
				children[i]->SetState(0);
		}
	}
	else
	{
		this->state = state;
		if (!IsReady())
			for (size_t i = 0; i < children.size(); i++)
				children[i]->SetState(0);
	}
}

void TreeObject::SetParent(TreeObject* newParent)
{
	/*
	if (parent)
		for (size_t i = 0; i < parent->children.size(); i++)
			if (parent->children[i] == this)
			{
				parent->children.erase(parent->children.begin() + i);
				break;
			}
	*/
	parent = newParent;
	if (parent)
		parent->children.push_back(this);
	SetState(state);
}

TreeObject* TreeObject::GetObjectByName(string name, bool withNested)
{
	if (this->name == name)
		return this;
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->GetName() == name)
			return children[i];
		if (withNested && children[i]->GetObjectByName(name, true))
			return children[i]->GetObjectByName(name, true);
	}
	return nullptr;
}

TreeObject* TreeObject::GetRoot()
{
	if (!parent)
		return this;
	else
		return parent->GetRoot();
}

TreeObject* TreeObject::GetObjectByPath(string path)
{
	if (path == "/")
		return GetRoot();
	if (path.substr(0, 2) == "//")
		return GetRoot()->GetObjectByName(path.substr(2, path.size() - 2), true);

	vector<string> objectsNames = StringExtensions::SplitString(path, '/');
	if (objectsNames.size() == 1 && GetObjectByName(objectsNames[0], false) != nullptr)
		return GetObjectByName(objectsNames[0], false);
	if (objectsNames.size() > 1)
	{
		vector<string> nextPathObjects = StringExtensions::SliceVector(objectsNames, 1, objectsNames.size());
		string targetPath = StringExtensions::MakeString(nextPathObjects, "/");
		if (GetObjectByName(objectsNames[0], false) != nullptr)
			return GetObjectByName(objectsNames[0], false)->GetObjectByPath(targetPath);
	}
	return nullptr;
}

void TreeObject::PrintTree(string space)
{
	cout << endl << space << name;
	space += "    ";
	for (size_t i = 0; i < children.size(); i++)
		children[i]->PrintTree(space);
}

void TreeObject::PrintTreeWithStates(string space)
{
	cout << endl << space << name << (IsReady() ? " is ready" : " is not ready");
	space += "    ";
	for (size_t i = 0; i < children.size(); i++)
		children[i]->PrintTreeWithStates(space);
}

void TreeObject::SetConnection(TYPE_SIGNAL signal, TreeObject* object, TYPE_HANDLER handler)
{
	for (auto conn : connections)
		if (conn.signal == signal && conn.object == object && conn.handler == handler)
			return;
	connections.push_back(Connection{ signal, object, handler });
}

void TreeObject::DeleteConnection(TYPE_SIGNAL signal, TreeObject* object, TYPE_HANDLER handler)
{
	for (int i = 0; i < connections.size(); i++)
		if (connections[i].signal == signal && connections[i].object == object && connections[i].handler == handler)
		{
			connections.erase(connections.begin() + i);
			break;
		}
}

string TreeObject::GetAbsolutePath()
{
	if (!parent)
		return "/";
	if (!parent->parent)
		return "/" + GetName();
	return parent->GetAbsolutePath() + '/' + GetName();
}

void TreeObject::EmitSignal(TYPE_SIGNAL signal, string& message)
{
	if (IsReady())
	{
		bool emitted = false;
		cout << endl << "Signal from " << GetAbsolutePath();
		for (auto connection : connections)
		{
			TYPE_SIGNAL p_signal = connection.signal;
			if (p_signal == signal)
			{
				TreeObject* object = connection.object;
				TYPE_HANDLER p_handler = connection.handler;
				if (!emitted)
				{
					(this->*signal)(message);
					emitted = true;
				}
				if (object->IsReady())
					(object->*p_handler)(message);
			}
		}
	}
}