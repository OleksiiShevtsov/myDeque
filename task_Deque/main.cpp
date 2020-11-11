#include <iostream>

using namespace std;
const int sizeDataNode = 4;

template <typename T>
class Deque {
public:

	Deque() {
		m_head = 0;
		m_tail = 0;
		m_size = 0;
		m_ptrDataNode = new Node*[0];
		m_sizePtrDataNode = 0;
	}

	void print() {
		cout << "---" << endl;
		for (int i = 0; i < m_sizePtrDataNode; i++) {
			for (int j = 0; j < sizeDataNode; j++) {
				if ((m_ptrDataNode[i])->m_data[j] != 0) {
					cout << (m_ptrDataNode[i])->m_data[j] << endl;
				}
			}
		}
		cout << "---" << endl;
	}

	int GetSize() {
		return m_size;
	}

	void PushBack(T data) {
		Node* curNode = m_tail;
		if (m_size == 0) {
			curNode = new Node(data);
			pushBackNode(curNode);

			curNode->pPrev = new Node(0);
			pushFrontNode(curNode->pPrev);

			m_head = curNode->pPrev;
			m_head->pNext = curNode;

			m_tail = curNode;
			m_size++;
		}
		else {
			if (curNode->fillingArray() == sizeDataNode) {
				curNode->pNext = new Node(data);
				pushBackNode(curNode->pNext);

				m_tail = curNode->pNext;
				m_tail->pPrev = curNode;
				m_size++;
			}
			else {
				curNode->m_data[curNode->fillingArray()] = data;
				m_size++;
			}
		}
	}
	void PushFront(T data) {//âñòàâëÿåò ýëåìåíò ñ ãîëîâû
		Node* curNode = m_head;
		if (m_size == 0) {
			curNode = new Node(data, sizeDataNode - 1);
			pushFrontNode(curNode);

			curNode->pNext = new Node(0);
			pushBackNode(curNode->pNext);

			m_tail = curNode->pNext;
			m_tail->pPrev = curNode;

			m_head = curNode;
			m_size++;
		}
		else {
			if (curNode->fillingArray() == sizeDataNode) {
				curNode->pPrev = new Node(data, sizeDataNode - 1);
				pushFrontNode(curNode->pPrev);

				m_head = curNode->pPrev;
				m_head->pNext = curNode;
				m_size++;
			}
			else {
				curNode->m_data[sizeDataNode - curNode->fillingArray() - 1] = data;
				m_size++;
			}
		}
	}
	
	T& operator[](int index) {
		
		if (index < m_ptrDataNode[0]->fillingArray()) {
			return m_ptrDataNode[0]->m_data[sizeDataNode - m_ptrDataNode[0]->fillingArray() + index];
		}
		else {

			int tempIndex = ((index - m_ptrDataNode[0]->fillingArray()) / sizeDataNode) + 1;
			
			return m_ptrDataNode[tempIndex]->m_data[(index - m_ptrDataNode[0]->fillingArray()) % sizeDataNode];
		}
	}

	~Deque() {
		for (int i = 0; i < m_sizePtrDataNode; i++) {	
			delete m_ptrDataNode[i];
			m_ptrDataNode[i] = 0;
		}
		delete m_ptrDataNode;
		m_ptrDataNode = 0;
	}

private:
	struct Node {

		Node(T data, int index = 0) {
			for (int i = 0; i < sizeDataNode; i++) {
				m_data[i] = 0;
			}
			m_data[index] = data;
			pNext = 0;
			pPrev = 0;
		}

		int fillingArray() {
			int temp = sizeDataNode;
			for (int i = 0; i < sizeDataNode; i++) {
				if (m_data[i] == 0) {
					temp--;
				}
			}
			return temp;
		}

		T m_data[sizeDataNode];
		Node* pNext;
		Node* pPrev;
	};

	void pushBackNode(Node* data) {
		Node** dataTemp = new Node*[m_sizePtrDataNode];

		for (int i = 0; i < m_sizePtrDataNode; i++) {
			dataTemp[i] = m_ptrDataNode[i];
		}

		delete[] m_ptrDataNode;
		m_sizePtrDataNode++;
		m_ptrDataNode = new Node*[m_sizePtrDataNode];

		for (int i = 0; i < m_sizePtrDataNode - 1; i++) {
			m_ptrDataNode[i] = dataTemp[i];
		}
		m_ptrDataNode[m_sizePtrDataNode - 1] = data;

		delete[] dataTemp;
	}
	void pushFrontNode(Node* data) {
		Node** dataTemp = new Node*[m_sizePtrDataNode];

		for (int i = 0; i < m_sizePtrDataNode; i++) {
			dataTemp[i] = m_ptrDataNode[i];
		}

		delete[] m_ptrDataNode;
		m_sizePtrDataNode++;
		m_ptrDataNode = new Node*[m_sizePtrDataNode];

		for (int i = 0; i < m_sizePtrDataNode - 1; i++) {
			m_ptrDataNode[i + 1] = dataTemp[i];
		}
		m_ptrDataNode[0] = data;

		delete[] dataTemp;
	}

	Node* m_head;
	Node* m_tail;

	Node** m_ptrDataNode;
	int m_sizePtrDataNode;

	int m_size;
};

int main() {

	Deque<int> deq;
	
	deq.PushBack(10);
	deq.PushBack(20);
	deq.PushBack(30);
	deq.PushBack(40);
	deq.PushBack(50);
	deq.PushBack(60);

	deq.PushFront(9);
	deq.PushFront(8);
	deq.PushFront(7);
	deq.PushFront(6);
	deq.PushFront(5);
	
	deq.print();
	
	return 0;
}
