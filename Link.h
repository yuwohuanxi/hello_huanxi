#ifndef LINK_H
#define LINK_H
#endif
class Link
{
public:
	Link();
	~Link();
	void insertHead(int val);
	void insertTail(int val);
	void remove(int val) ;
	void show();
	private:
	// �ڵ�����
	struct Node
	{
		Node(int data = 0);
		int mdata;
		Node *mpnext;
	};
	Node *mphead;
};