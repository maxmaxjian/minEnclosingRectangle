#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

class solution {
public:
	void removeInvalidParen(const string & s) {
		stack<size_t> st;
		size_t idx = 0;
		while (idx < s.length()) {
			if (s[idx] == '(' || s[idx] == ')') {
				if (st.empty())
					st.push(idx);
				else if (s[st.top()] == '(' && s[idx] == ')')
					st.pop();
				else
					st.push(idx);
			}
			idx++;
		}

		vector<size_t> indices;
		while (!st.empty()) {
			indices.insert(indices.begin(), st.top());
			st.pop();
		}

		cout << "Indices to remove:\n";
		for (size_t i : indices)
			cout << i << " ";
		cout << endl;

		vector<vector<size_t>> toRemove;
		int curr = 0;
		while (curr < indices.size()) {
			if (s[indices[curr]] == '(') {
				size_t end = curr + 1 < indices.size() ? indices[curr + 1] : s.size();
				vector<size_t> temp;
				for (size_t i = indices[curr]; i < end; i++)
					if (s[i] == '(')
						temp.push_back(i);
				toRemove.push_back(temp);
			}
			else if (s[indices[curr]] == ')') {
				size_t start = curr - 1 >= 0 ? indices[curr - 1]+1 : 0;
				vector<size_t> temp;
				for (size_t i = start; i <= indices[curr]; i++)
					if (s[i] == ')')
						temp.push_back(i);
				toRemove.push_back(temp);
			}
			curr++;
		}

		cout << "Indices that can be removed:" << endl;
		for (auto vec : toRemove) {
			for (auto i : vec)
				cout << i << " ";
			cout << endl;
		}

		vector<string> result{ s };
		for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) {
			vector<string> temp;
			for (auto pos : *it) {
				for (auto str : result) {
					str.erase(pos, 1);
					temp.push_back(str);
				}
			}
			result = temp;
		}

		vector<string>::iterator it = unique(result.begin(), result.end());
		result.resize(distance(result.begin(), it));

		cout << "After removing invalid parentheses:" << endl;
		for (auto str : result)
			cout << str << " ";
		cout << endl;
	}
};

int main() {

	//string s{ "()())(()" };
	//string s{ "))(" };
	string s{ "(a)())()" };

	solution soln;
	soln.removeInvalidParen(s);

	return 0;
}