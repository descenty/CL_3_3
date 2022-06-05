#include "TreeApplication.h"
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"
#include "Class6.h"

string TreeApplication::BuildTree()
{
	string name1, name2;
	int n;
	cin >> name1;
	this->SetName(name1);
	state = 1;
	while (cin >> name1 && name1 != "endtree")
	{
		TreeObject* parent = this->GetObjectByPath(name1);
		if (name1 != "/" && parent == nullptr)
			return name1;
		TreeObject* child;
		cin >> name2 >> n;
		if (this->GetObjectByName(name2, true))
		{
			child = GetObjectByName(name2, true);
			child->SetParent(parent);
			continue;
		}
		switch (n)
		{
		case 2:
			child = new Class2(parent, name2);
			child->state = 1;
			break;
		case 3:
			child = new Class3(parent, name2);
			child->state = 1;
			break;
		case 4:
			child = new Class4(parent, name2);
			child->state = 1;
			break;
		case 5:
			child = new Class5(parent, name2);
			child->state = 1;
			break;
		case 6:
			child = new Class6(parent, name2);
			child->state = 1;
			break;
		}
	}
	return "";
}

void TreeApplication::SetObjectsStates()
{
	string name;
	int state;
	while (cin >> name)
	{
		cin >> state;
		if (this->GetObjectByName(name, true))
			this->GetObjectByName(name, true)->SetState(state);
	}
}

void TreeApplication::CommandLoop()
{
	string command, path;
	TreeObject* relativeObject = GetRoot();
	while (true)
	{
		cin >> command;
		if (command == "END")
			return;
		cout << endl;
		cin >> path;
		TreeObject* target;
		if (command == "FIND")
		{
			if (path == ".")
				target = relativeObject;
			else
				target = relativeObject->GetObjectByPath(path);
			cout << path;
			if (target != nullptr)
				cout << "     Object name: " << target->GetName();
			else
				cout << "     Object is not found";
		}
		else
		{
			if (path == ".")
				target = relativeObject;
			else
				target = relativeObject->GetObjectByPath(path);
			if (target != nullptr)
			{
				relativeObject = target;
				cout << "Object is set: " << relativeObject->GetName();
			}
			else
				cout << "Object is not found: " << relativeObject->GetName() << " " << path;
		}
	}
}

TYPE_SIGNAL TreeApplication::GetSignal(TreeObject* target)
{
	TYPE_SIGNAL signal_d = nullptr;
	switch (target->classNum)
	{
	case 1:
		signal_d = SIGNAL_D(TreeApplication::Signal_1);
		break;
	case 2:
		signal_d = SIGNAL_D(Class2::Signal_2);
		break;
	case 3:
		signal_d = SIGNAL_D(Class3::Signal_3);
		break;
	case 4:
		signal_d = SIGNAL_D(Class4::Signal_4);
		break;
	case 5:
		signal_d = SIGNAL_D(Class5::Signal_5);
		break;
	case 6:
		signal_d = SIGNAL_D(Class6::Signal_6);
		break;
	}
	return signal_d;
}

TYPE_HANDLER TreeApplication::GetHandler(TreeObject* target)
{
	TYPE_HANDLER handler_d = nullptr;
	switch (target->classNum)
	{
	case 1:
		handler_d = HANDLER_D(TreeApplication::Handler_1);
		break;
	case 2:
		handler_d = HANDLER_D(Class2::Handler_2);
		break;
	case 3:
		handler_d = HANDLER_D(Class3::Handler_3);
		break;
	case 4:
		handler_d = HANDLER_D(Class4::Handler_4);
		break;
	case 5:
		handler_d = HANDLER_D(Class5::Handler_5);
		break;
	case 6:
		handler_d = HANDLER_D(Class6::Handler_6);
		break;
	}
	return handler_d;
}


void TreeApplication::ConnectTreeObjects(TreeObject* from, TreeObject* to)
{
	TYPE_SIGNAL signal_d = GetSignal(from);
	TYPE_HANDLER handler_d = GetHandler(to);
	from->SetConnection(signal_d, to, handler_d);
}

void TreeApplication::DisconnectTreeObjects(TreeObject* from, TreeObject* to)
{
	TYPE_SIGNAL signal_d = GetSignal(from);
	TYPE_HANDLER handler_d = GetHandler(to);
	from->DeleteConnection(signal_d, to, handler_d);
}

void TreeApplication::ConnectionLoop()
{
	string path1, path2;
	TreeObject* object1;
	TreeObject* object2;
	while (true)
	{
		cin >> path1;
		if (path1 == "end_of_connections")
			return;
		object1 = GetObjectByPath(path1);
		if (object1 == nullptr)
		{
			cout << endl << "Object " << path1 << " not found";
			cin >> path2;
			continue;
		}
		cin >> path2;
		object2 = GetObjectByPath(path2);
		if (object2 == nullptr)
		{
			cout << endl << "Handler object " << path2 << " not found";
			continue;
		}
		ConnectTreeObjects(object1, object2);
	}
}

void TreeApplication::SignalLoop()
{
	string command, path, message;
	TreeObject* object;
	while (true)
	{
		cin >> command;
		if (command == "END")
			return;
		cin >> path;
		std::getline(cin, message);
		message = message.substr(1);
		//StringExtensions::TrimL(&message);
		object = GetObjectByPath(path);
		if (object == nullptr)
		{
			cout << endl << "Object " << path << " not found";
			continue;
		}
		if (command == "EMIT")
		{
			TYPE_SIGNAL signal_d = GetSignal(object);
			object->EmitSignal(signal_d, message);
		}
		else if (command == "DELETE_CONNECT")
		{
			TreeObject* object2 = GetObjectByPath(message);
			if (object2 == nullptr)
			{
				cout << endl << "Handler object " << message << " not found";
				continue;
			}
			DisconnectTreeObjects(object, object2);
		}
		else if (command == "SET_CONDITION")
			object->SetState(std::stoi(message));
		else if (command == "SET_CONNECT")
		{
			TreeObject* object2 = GetObjectByPath(message);
			if (object2 == nullptr)
			{
				cout << endl << "Handler object " << message << " not found";
				continue;
			}
			ConnectTreeObjects(object, object2);
		}
	}
}

int TreeApplication::Exec(bool error)
{
	cout << "Object tree";
	PrintTree("");
	if (!error)
	{
		ConnectionLoop();
		SignalLoop();
	}
	//SetObjectsStates();
	//cout << endl << "The tree of objects and their readiness";
	//PrintTreeWithStates("");
	return 0;
}

void TreeApplication::Handler_1(string message)
{
	cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message;
}

void TreeApplication::Signal_1(string& message)
{
	message += " (class: " + std::to_string(classNum) + ")";
}