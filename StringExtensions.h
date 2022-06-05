#ifndef __STRINGEXTENSIONS_H__
#define __STRINGEXTENSIONS_H__

#include <vector>
#include <string>
using std::vector;
using std::string;

class StringExtensions {
public:
	static vector<string> SplitString(string str, char del)
	{
		vector<string> output;
		string temp = "";
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] != '/')
				temp += str[i];
			else
			{
				if (temp != "")
					output.push_back(temp);
				temp = "";
			}
		}
		if (temp != "")
			output.push_back(temp);
		return output;
	}

	static string MakeString(vector<string> value, string del)
	{
		string output = "";
		for (size_t i = 0; i < value.size(); i++)
		{
			output += value[i];
			if (i != value.size() - 1)
				output += del;
		}
		return output;
	}

	static vector<string> SliceVector(vector<string> target, int from, int to)
	{
		if (from == to)
			return vector<string> { target.at(from)};
		if (from < to)
			return vector<string> { target.begin() + from, target.begin() + to };
		return vector<string> {};
	}



	static string* TrimL(string* str)
	{
		str->erase(str->find(" "));
		return str;
	}
};
#endif