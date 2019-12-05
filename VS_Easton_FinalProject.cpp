#include<iostream>
#include<queue>
#include<stack>
#include<vector>

using namespace std;

/*===========
	Product
  ===========*/

struct Product
{
	string name;
	int price;
	int quantity;
	Product *left;
	Product *right;
	Product *parent;
};





/*===========
	Business
  ===========*/

class Business
{
private: 
	string name;
	int busProfit;
	Warehouse bHouse;
	StoreLL stores;
public:
	Business()
	{
		name="";
		busProfit=0;
	}

	Business(string n)
	{
		name=n;
	}
	/*
	function: addProduct
	purpose: adds a product to the Business's warehouse
	return void
	*/
	void addProduct(string product)
	{

	}

	/*
	function: deleteProduct
	purpose: deletes a product from the Business's warehouse
	return void
	*/
	void deleteProduct(string product)
	{

	}

	/*
	function: checkBInventory
	purpose: prints the info of a product in the Business's warehouse
	return void
	*/
	void checkBInventory(string product)
	{

	}

	/*
	function: shipProduct
	purpose: ships a selected number of a product to a store in the Business's StoreLL
	return void
	*/
	void shipProduct(string product, int numShipped, string storeName)
	{

	}

	/*
	function: businessMenu
	purpose: runs the certain business's menu and all of its own features
	return void
	*/
	void businessMenu()
	{

	}

	int getBusProfit()
	{
		return busProfit
	}

	void addProfit(int prof)
	{
		busProfit+=prof;
	}

};





/*===========
   Warehouse
  ===========*/

class Warehouse
{
private:
	Product *root;

public:
	Warehouse()
	{
		root=NULL;
	}

	~Warehouse()
	{
		destruct(root);
	}

	void destruct(Product* node)
	{
		if(node==NULL)
		{
			return;
		}

		destruct(node->left);
		delete node;
		destruct(node->right);

	}

	/*
	function: delete product
	purpouse: deletes a product node from warehouse BST
	return: void
	*/
	void deleteProduct()
	{

	}
	/*
	function: add product
	purpouse: adds to current inventory or creates new BST node 
	return void
	*/
	void addProduct()
	{

	}
	/*
	function: product info
	purpouse: prints all inormation about the product 
	return void
	*/
	void productInfo(string product)
	{

	}
	// MAYBE - print warehouse
	/*
	function search warehouse
	purpouse: helper function to traverse/ find nodes in BST
	returns: the product if found or null if node DNE
	*/
	Product searchWarehouse(string product)
	{

	}



};




/*===========
	Stores
  ===========*/


struct storeNode
{
	string name;
	Warehouse sHouse;
	storeNode *next;

	storeNode(string n)
	{
		name=n;
		next=NULL;
	}
};

class StoreLL
{
private:
	StoreLL *head;
	StoreLL *tail:

public:
	StoreLL()
	{
		head=NULL;
		tail=NULL;
	}

	/* 
	function: insertStore
	purpose: creates a new store and adds it to the end of the storeLL
	return void:
	*/

	void insertStore(string name)
	{
		storeNode newNode= new storeNode(name);
		if(head==NULL)
		{
			head=newNode;
			tail=newNode;
		}else
		{
			tail->next=newNode;
			tail=newNode;
		}

	}

	/* 
	function: deleteStore
	purpose: deletes a store that either has no products, or if chosen to be deleted
	return void
	*/
	
	void deleteStore(string name)
	{
		storeNode* temp=head;
		int prevCount=0;



		while(temp!=NULL && temp->next!=NULL)
		{
			if(temp->name==name)
			{
				break;
			}
			temp=temp->next;
			prevCount++;
		}

		if(temp->name!=name)
		{
			cout<< "Store not found." << endl;
			return;
		}

		if(temp==head)
		{
			head=temp->next;
			temp->sHouse.~Warehouse();
			delete temp;
		}else
		{
			storeNode* prev=head;
			for(int i=1; i<prevCount; i++)
			{
				prev=prev->next;
			}

			prev->next=temp->next;
			temp->sHouse.~Warehouse();
			delete temp;
		}


	}

	/* 
	function: printStores
	purpose: prints the list of stores
	return void
	*/
	
	void printStores()
	{
		storeNode* temp=head;
		while(temp!=NULL && temp->next!=NULL)
		{
			cout<<temp->name<<endl;
			temp=temp->next;
		}

	}

	/* 
	function: buyProduct
	purpose: decrements the quantity of the product in the storeNode's warehouse
	& increments the business's total profit
	return void:
	*/
	
	void buyProduct(string name)
	{

	}



};





/*===========
	Driver
  ===========*/

class Driver
{
public:

	void printMenu()
	{
		cout<<"1. Enter Business"<<endl;
		cout<<"2. Create Business"<<endl;
		cout<<"3. Delete Business"<<endl;
		cout<<"4. Quit"<<endl;

	}

	void runProgram()
	{
		
		while(true)
		{
			printMenu();
			int choice;
			cin>>choice;
			switch(choice)
			{
				case 1:
				{
					//Enter Business
					break;

				}
				case 2:
				{
					//Create Business
					break;

				}
				case 3:
				{
					//Delete Business
					break;

				}
				case 4:
				{
					//Quit;
					break;

				}
				default:
				{
					cout<<"Please choose a number between 1-4"<<endl;
					break;
				}
			}
		}



	}

};




/*===========
	Main
  ===========*/

int main()
{
	cout<<"evan edit"<<endl;
	cout<< "Test" << endl;
	cout<<"Max Edit"<<endl;
}