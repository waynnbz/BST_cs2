#include <iostream>
#include <string>
#include <sstream>
using namespace std;

typedef string ItemType;

struct WordNode {
	ItemType m_data;
	WordNode *m_left;
	WordNode *m_right;
	int frequent;

	WordNode(ItemType i) {
		m_data = i;
		m_left = m_right = nullptr;
		frequent = 1;
	}

	string toString() {
		stringstream ss;
		ss << m_data << " " << frequent << "\n";
		return ss.str();
	}
};

class WordTree {

private:
	WordNode *root;

	void insert(WordNode *&nodePtr, ItemType val) {

		if (nodePtr == nullptr) {
			nodePtr = new WordNode(val);
			return;
		}

		if (nodePtr->m_data == val) {
			nodePtr->frequent++;
			return;
		}

		if (val < nodePtr->m_data) {
			insert(nodePtr->m_left, val);
		}
		else
			insert(nodePtr->m_right, val);
		return;
	}

	string print(WordNode *nodePtr) const {
		if (nodePtr == nullptr)
			return {};

		return print(nodePtr->m_left) + nodePtr->toString() + print(nodePtr->m_right);
	}

	//why must I add const behind??? Because the public method totalWords can only access const method
	int totWords(WordNode *nodePtr) const {
		if (nodePtr == nullptr)
			return 0;

		return totWords(nodePtr->m_left) + totWords(nodePtr->m_right) + nodePtr->frequent;
	}

	int distWords(WordNode *nodePtr) const {
		if (nodePtr == nullptr)
			return 0;

		return distWords(nodePtr->m_left) + distWords(nodePtr->m_right) + 1;
	}

	void deleteNode(WordNode *nodePtr) {
		if (nodePtr != nullptr) {
			deleteNode(nodePtr->m_left);
			deleteNode(nodePtr->m_right);
			delete nodePtr;
		}
	}

	void append(const WordTree &other) {
		//if (!other.totalWords()) 
			//return;

		stringstream ss;
		ss << other;

		ItemType t_data;
		int t_f;

		while (ss >> t_data >> t_f) {
			for (int i = 0; i < t_f; i++) {
				add(t_data);
			}
		}
		return;
	}
public:


	WordTree() : root(nullptr) { };

	// copy constructor
	WordTree(const WordTree& rhs) :root(nullptr) {
		append(rhs);
	}

	// assignment operator
	const WordTree& operator=(const WordTree& rhs) {
		deleteNode(root);
		root = nullptr;
		append(rhs);
		return *this;
	}


	void add(ItemType v) {
		insert(root, v);
	}


	int distinctWords() const {
		return distWords(root);
	}


	int totalWords() const {
		return totWords(root);
	}


	//this function does not being to the class
	friend ostream& operator<<(ostream &out, const WordTree& rhs) {
		out << rhs.print(rhs.root);
		return out;
	}


	~WordTree() {
		deleteNode(root);
	}
};

int main() {
	WordTree t;

	t.add("Skyler");
	t.add("Walter");
	t.add("Walter");
	t.add("Hank");
	t.add("Gus");
	t.add("Walter");
	t.add("Gus");

	cout << t;
	cout << endl << t.distinctWords();
	cout << endl << t.totalWords();

	WordTree n(t);
	cout << "\nnew:\n" << n;

	WordTree s;
	s.add("stupid");
	s.add("boring");
	s.add("boring");

	cout << "\nnew\n" << s;
	cout << endl << s.distinctWords();
	cout << endl << s.totalWords();

	s = n;
	cout << "\nnew\n" << s;

	WordTree em;

	WordTree em2(em);

	cout << em2 << em2.totalWords();

	t = em2;

	cout << "\nnow em version of t:\n" << t;
	cout << t.totalWords();

	return 0;
}
