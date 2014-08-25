#include<iostream>
using namespace std;

//�����
template<typename T>
class TreeNode
{
	//����Ϊ��������������Ԫ��
	template<class T> friend class BinarySearchTree;
	//����<<���������ʽ���Ա
	template<typename T> friend ostream& operator<<(ostream &os, BinarySearchTree<T>&BST);

private:
	T value;
	TreeNode<T>* lchild;
	TreeNode<T>* rchild;
	TreeNode<T>* parent;//��parent���Ҫ����Ķ�

	TreeNode<T>* _increase();//�������������µĺ��
	TreeNode<T>* _decrease();//�Լ����������µ�ǰ��
public:
	//�������캯��
	TreeNode() :value(0), lchild(NULL), rchild(NULL), parent(NULL){}
	TreeNode(T v) :value(v), lchild(NULL), rchild(NULL), parent(NULL){}
	TreeNode(TreeNode<T> &node) :value(node.value), lchild(node.lchild), rchild(node.rchild), parent(node.parent){}
	virtual ~TreeNode(){} //������������Ϊ�麯��
	void _test_display()  //�˺���ֻ�ǲ���ʹ�ã�Ӧ��ɾȥ
	{
		cout << "value: " << this->value << "     ";
		if (this->lchild != NULL)
			cout << "lchild: " << this->lchild->value << "  ";
		else  cout << "lchild: NULL" << "  ";
		if (this->rchild != NULL)
			cout << "rchild: " << this->rchild->value << "  ";
		else  cout << "rchild: NULL" << "  ";
		if (this->parent != NULL)
			cout << "parent: " << this->parent->value << "  ";
		else  cout << "parent: NULL" << "  ";
		cout << endl;
	}

};

//������������
template<typename T>
class BinarySearchTree
{

private:
	TreeNode<T> *root; //���ڵ�
	int size;    //�������

	TreeNode<T>* _copy(TreeNode<T> *node, TreeNode<T>* q); //˽�к�����node��ʾ������nodeΪ���ڵ����������qʵ����ָ��node�ĸ��ڵ㣬��ʵ�ֵ�С����
	TreeNode<T>* _mininum(TreeNode<T>* node);             //˽�к������ҵ���nodeΪ���ڵ�����е���С���
	TreeNode<T>* _maxinum(TreeNode<T>* node);

	virtual TreeNode<T>* _insert(T& value, TreeNode<T>* node);//˽�к���������ʵ��Insert����
	virtual void _delete(TreeNode<T>* _delete_node, TreeNode<T>* node);//˽�к���������ʵ��Delete����
	TreeNode<T>* _search(T& value, TreeNode<T>* node);               //˽�к���������ʵ��Search����
	virtual void _init(T* array, int length);                //ͨ�������ʼ������������
	virtual void _clear(TreeNode<T>* node);                   //���nodeΪ���ڵ����



public:
	//�������������
	BinarySearchTree() :root(NULL), size(0){}
	BinarySearchTree(T* array, int length)    { _init(array, length); }
	BinarySearchTree(BinarySearchTree<T> &tree){ root = _copy(tree.root, NULL); size = tree.size; }
	virtual ~BinarySearchTree() { _clear(root); size = 0; }
	//��ֵ������������
	virtual BinarySearchTree<T>& operator=(BinarySearchTree<T> &tree){ _clear(root); root = _copy(tree.root, NULL);  size = tree.size; return *this; }
	//�ж����Ƿ�Ϊ��
	bool isEmpty() { return size == 0; }
	//�������н�����
	int Size()   { return size; }
	//����������Insert��Delete��Search
	virtual TreeNode<T>*  Insert(T& value){ return _insert(value, root); }
	virtual void Delete(TreeNode<T>* node){ return _delete(node, root); }
	TreeNode<T>* Search(T& value){ return _search(value, root); }

	//��������value������С�Ľ���value
	T& mininum(){ return _mininum(root)->value; }
	T& maxinum(){ return _maxinum(root)->value; }
	//����ĳ���ڵ��parent
	TreeNode<T>* parent(TreeNode<T> *node){ return node->parent; }
	//<<��������������Ϊ��Ԫ���������ǳ�Ա
	template<typename T> friend ostream& operator<<(ostream &os, BinarySearchTree<T>&BST);

	//һ�����Ժ���
	void __test(){ cout << "����_ decrease" << --(this->root->rchild->lchild->lchild)->value << endl; };

};

template<typename T>
TreeNode<T>* BinarySearchTree<T>::_copy(TreeNode<T>* node, TreeNode<T>* q)
{
	//����q����node�ĸ��ڵ㣬����ʱ��ʼ��ΪNULL��root��parentΪNULL��

	if (node == NULL)
		return NULL;

	TreeNode<T>* p = new TreeNode<T>(node->value);
	p->parent = q;
	p->lchild = _copy(node->lchild, p);//�ݹ鸴��
	p->rchild = _copy(node->rchild, p);
	return p;
}


template<typename T>
TreeNode<T>* BinarySearchTree<T>::_mininum(TreeNode<T>* node)//����˽��Ϊ��С
{
	TreeNode<T> * p = node;
	TreeNode<T>* q = NULL;
	while (p != NULL)
	{
		q = p;
		p = p->lchild;
	}
	return q;
}
template<typename T>
TreeNode<T>* BinarySearchTree<T>::_maxinum(TreeNode<T>* node)//���Ҷ˽��Ϊ���
{
	TreeNode<T>* p = node;
	TreeNode<T>* q = NULL;
	while (p != NULL)
	{
		q = p;
		p = p->rchild;
	}
	return q;
}
template<typename T>
TreeNode<T>* TreeNode<T>::_increase()
{
	if (this == NULL)
		return NULL;
	else
	{
		if (this->rchild != NULL)         //��ǰ���������Һ��ӣ�����Ϊ����������С�Ľ��
		{
			TreeNode<T> * p = this->rchild;
			TreeNode<T>* q = p;
			while (p != NULL)
			{
				q = p;
				p = p->lchild;
			}

			return q;
		}
		else                                        //���������ϻ��ݣ�ֱ����һ�γ��� q �� p �����ӽ��Ϊֹ
		{
			TreeNode<T> *q = this;
			TreeNode<T> *p = this->parent;
			//cout<<"parent:" << p->value << endl;
			//cout <<"cur:   "<< q->value << endl;
			while (q != p->lchild)
			{
				q = p;
				p = p->parent;
				if (p == NULL)
					break;
			}
			//cout << "parent: " << p->value << endl;

			return p;
		}
	}

}
template<typename T>
TreeNode<T>* TreeNode<T>::_decrease()
{
	if (this == NULL)
		return NULL;
	else
	{
		if (this->lchild != NULL)                 //��ǰ�����������ӣ�����Ϊ�����������Ľ��
		{
			TreeNode<T> *p = this->lchild;
			TreeNode<T> *q = p;
			while (p != NULL)
			{
				q = p;
				p = p->rchild;
			}
			return q;
		}
		else                                        //���������ϻ��ݣ�ֱ����һ�γ��� q �� p ���Һ��ӽ��Ϊֹ
		{
			TreeNode<T> *q = this;
			TreeNode<T> *p = this->parent;
			while (q != p->rchild)
			{
				q = p;
				p = p->parent;
				if (p == NULL)
					break;
			}
			return p;
		}
	}

}

template<typename T>
TreeNode<T>*  BinarySearchTree<T>::_insert(T& value, TreeNode<T>* node)  //insert�����ķ���ֵΪָ��������ָ��
{
	TreeNode<T> *p = new TreeNode<T>(value);
	TreeNode<T> *parent_node = NULL;

	while (node != NULL)
	{
		if (p->value < node->value)
		{
			parent_node = node;
			node = node->lchild;
		}
		else
		{
			parent_node = node;
			node = node->rchild;
		}
	}
	// �ҵ���������parent_node
	if (parent_node != NULL)
	{
		p->parent = parent_node;
		if (p->value < parent_node->value)
		{
			parent_node->lchild = p;
		}
		else
		{
			parent_node->rchild = p;
		}
	}
	else   //��ǰ��Ϊ��
	{
		root = p;
	}
	return p;

}
template<typename T>
void BinarySearchTree<T>::_delete(TreeNode<T>* _delete_node, TreeNode<T>* node)
{
	TreeNode<T> *y, *x;
	if (_delete_node->lchild == NULL || _delete_node->rchild == NULL)  //�����ɾ�������һ�����ӻ���û�к��ӣ���ôҪ���Ƴ��Ľ��������Լ�
		y = _delete_node;
	else y = _delete_node->_increase();        //�����������㣬��ôҪ�Ƴ��Ľ��������ĺ�̣�Ȼ������ĺ�̵�value��ֵ������

	if (y->lchild != NULL)
		x = y->lchild;    //���y�����Ӳ��յĻ�����ֵ��x
	else x = y->rchild;        //�����������Һ��ӿղ��գ�����ֵ��x

	TreeNode<T> *parent_of_y = parent(y);

	if (y != _delete_node)
	{
		_delete_node->value = y->value;
		x->parent = parent_of_y;
		if (y == parent_of_y->lchild)
			parent_of_y->lchild = x;
		else
			parent_of_y->rchild = x;
		delete y;
	}
	else
	{
		x->parent = parent_of_y;
		if (parent_of_y == NULL)
		{
			node = x;

			delete y;
		}
		else
		{
			if (parent_of_y->lchild == y)
				parent_of_y->lchild = x;
			else
				parent_of_y->rchild = x;
			delete y;
		}
	}

}
template<typename T>
TreeNode<T>* BinarySearchTree<T>::_search(T& value, TreeNode<T>* node)  //search�������ó��Ĳ���������ֵΪ�ҵ�����ָ��
{
	TreeNode<T>* p = node;
	while (p != NULL)
	{
		if (value < p->value)
			p = p->lchild;
		else if (value > p->value)
			p = p->rchild;
		else return p;
	}
	return NULL;
}
template<typename T>
void BinarySearchTree<T>::_init(T* array, int length)     //��������insert��������ʼ������������size
{

	for (int i = 0; i < length; ++i)
	{
		_insert(array[i], root);
		++size;
	}
}

template<typename T>
void BinarySearchTree<T>::_clear(TreeNode<T>* node)    //�ݹ������ɾ��
{
	if (node == NULL)
		return;

	TreeNode<T>* p = node->lchild;
	TreeNode<T>* q = node->rchild;
	delete node;
	_clear(p);
	_clear(q);
}

template<typename T>
ostream& operator<<(ostream &os, BinarySearchTree<T>& BST)    //������ʵ��һ�������棨���ø���stack���ķ���
{
	TreeNode<T>* node = BST.root;
	while (true)
	{
		if (node->lchild != NULL)        //һֱ���ʵ���ǰ����߽��
			node = node->lchild;
		else
		{
			os << node->value << "  ";  //�����ǰ����value
			while (node->rchild == NULL)          //������Һ��ӣ���������̣�ע��������ѭ��
			{

				node = node->_increase();

				if (node != NULL)
					os << node->value << "  ";
				else break;
			}
			if (node != NULL)                //������Һ��ӣ��������Һ��ӣ�������һ��β�ݹ��Ż������ĵ�����������⣩
			{
				node = node->rchild;
			}
			else break;

		}

	}
	return os;
}
int main()
{
	const int length = 9;
	int array[length] = { 13, 9, 17, 5, 12, 15, 18, 2, 19 };
	//���_init    _insert    operator<<    _increase
	BinarySearchTree<int> BST(array, length);
	cout << "BST: " << BST << endl;
	int v = 14;
	BST.Insert(v);
	cout << "BST insert one node with value 14: " << BST << endl;


	//���_copy,okay
	BinarySearchTree<int> Bst(BST);
	cout << Bst << endl;

	//���operator=,okay
	BinarySearchTree<int> bst, bsT;
	bsT = bst = Bst;
	cout << "!" << bst << endl;
	cout << "!" << bsT << endl;

	//���_mininum  _maxinum,okay
	cout << "maxinum" << BST.maxinum() << endl;
	cout << "mininum" << BST.mininum() << endl;

	//��� _decrease,okay
	BST.__test();

	//���_search,okay
	TreeNode<int> *p = BST.Search(array[0]);
	p->_test_display();
	p = BST.Search(array[7]);
	p->_test_display();
	p = BST.Search(array[8]);
	p->_test_display();


	//���_delete,okay
	p = BST.Search(array[2]);
	BST.Delete(p);
	cout << "delete the node with value 17" << endl;
	cout << BST << endl;

	//����size 
	cout << "BST size: " << BST.Size() << endl;
	cout << "bsT size: " << bsT.Size() << endl;
	system("pause");

}