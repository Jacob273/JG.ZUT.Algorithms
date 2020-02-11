namespace JG_Collections

{
	struct Node
	{
		int _key;
		Node* _next;
	};

	class List
	{

	private:
		Node* _head, * _tail;
		int _hashTblSize;

	public:

		List();
		~List();
		void InsertNode(int _key);
		void InsertNodeAtBeggining(int _key);
		void Display();
		bool Exists(int _key);
		void DeleteNode(Node* nodeToBeDeleted);
		void DeleteNode(int positionToBeDeleted);
	};

}