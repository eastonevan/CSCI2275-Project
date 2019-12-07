#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<string>

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

	Product(string n, int p, int q)
	{
		name=n;
		price=p;
		quantity=q;
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
	void addProduct(string name, int price, int quantity)
	{
		Product* temp= searchWarehouse(root, name);

		if(temp!=NULL)
		{
			cout<<"This product already exists, would you like to update its price and quantity?(0=no, 1=yes)"<<endl;
			int choice;
			cin>>choice;

			if(choice==0)
			{
				return;
			}else if(choice==1)
			{
				temp->price=price;
				temp->quantity+=quantity;
			}else{
				cout<<"Not valid input, product not updated."<<endl;
				return;
			}
		}else
		{
			temp= new Product(name, price, quantity);

			if(root==NULL)
			{
				root=temp;
				return;
			}else{
				Product* iter=root;
				Product* parent=NULL;

				while(iter!=NULL)
				{
					parent=iter;
					if(iter->name>temp->name)
					{
						iter=iter->left;
					}else{
						iter=iter->right;
					}
				}

				if(parent->name>temp->name)
				{
					parent->left=temp;
					temp->parent=parent;
				}else{
					parent->right=temp;
					temp->parent=parent;
				}
			}

		}

	}
	/*
	function: product info
	purpouse: prints all inormation about the product 
	return void
	*/
	void productInfo(string product)
	{
		Product* temp= searchWarehouse(root, product);

		if(temp==NULL)
		{
			cout<<"Product does not exist."<<endl;
			return;
		}else
		{
			cout<<"Name: "<<temp->name<<"\nPrice: "<<temp->price<<"\nQuantity: "<<temp->quantity<<endl;
			return;
		}

	}
	/*
	function print warehouse
	purpouse: prints all of the items in the warehouse
	returns: void
	*/
	void printWarehouse(Product* root)
	{
		if(root==NULL)
		{
			return;
		}
		printWarehouse(root->left);
		productInfo(root->name); 
		printWarehouse(root->right);
	}



	/*
	function search warehouse
	purpouse: helper function to traverse/ find nodes in BST
	returns: the product if found or null if node DNE
	*/
	Product* searchWarehouse(Product* node, string product)
	{
		Product* temp= node;

		while(temp->name!=product)
		{
			if(temp->name < product)
			{
				temp=temp->right;
			}else {
				temp=temp->left;
			}

			if(temp==NULL)
			{
				return temp;
			}

		}
		return temp;
	}

	Product* getRoot()
	{
		return root;
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

	void storeMenu()
	{
		while(true)
		{
			cout<<"====Available Products===="<<endl;
			sHouse.printWarehouse(sHouse.getRoot());
			cout<<"1. Buy product."<<endl;
			cout<<"2. Leave store."<<endl;


			int choice;
			cin>>choice;

			if(choice==1)
			{
				cout<<"Type the name of the product you want to buy."<<endl;

				cin.clear();
				cin.ignore();

				string pName;
				getline(cin, pName);

				Product* wanted= sHouse.searchWarehouse(sHouse.getRoot(), pName);

				if(wanted==NULL)
				{
					cout<<"Product not found."<<endl;
					continue;
				}

				cout<<"Enter the number you would like to buy."<<endl;
				string q;
				getline(cin, q);

				int qWanted=stoi(q);

				//finish



			}else if(choice==2)
			{
				return;
			}else
			{
				cout<<"Please pick a number 1-2." <<endl;
			}

		}
	}



	/* 
	function: buyProduct
	purpose: decrements the quantity of the product in the storeNode's warehouse
	& increments the business's total profit
	returns: the total price of the items
	*/
	
	int buyProduct(string pName, int qWanted)
	{
		return 0;

	}




};

class StoreLL
{
private:
	storeNode *head;
	storeNode *tail;

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
		storeNode *newNode= new storeNode(name);
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

	storeNode* findStore(string sName)
	{
		storeNode* iter= head;

		while(iter!=NULL)
		{
			if(iter->name==sName)
			{
				break;
			}
		}

		return iter;
	}



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
		while(true)
		{
			cout<<"1. Add product to Business Warehouse"<<endl;
			cout<<"2. Check a product's inventory."<<endl;
			cout<<"3. Ship product to store"<<endl;
			cout<<"4. Go to store."<<endl;
			cout<<"5. Leave Business."<<endl;

			int choice;
			cin>>choice;
			switch(choice)
			{
				case 1:
				{
					//Add Product

				}
				case 2:
				{
					//Check inventory

				}
				case 3:
				{
					//ship product

				}
				case 4:
				{
					//go to store
					cin.clear();
					cin.ignore();

					cout<<"Enter the name of the store."<<endl;

					string sName;
					cin>>sName;

					storeNode* tempStore= stores.findStore(sName);

					if(tempStore==NULL)
					{
						cout<<"There is not a store under that name."<<endl;
						break;
					}

					tempStore->storeMenu();
					break;

				}
				case 5:
				{
					//leave business
					cout<<"Returning to main menu..."<<endl;
					return;

				}
				default:
				{
					cout<<"Please choose a number between 1 and 5."<<endl;
					break;
				}
			}

		}



	}

	int getBusProfit()
	{
		return busProfit;
	}

	string getBusName()
	{
		return name;
	}

	void addProfit(int prof)
	{
		busProfit+=prof;
	}

};



/*===========
	Driver
  ===========*/

class Driver
{
public:
	vector<Business> businessVec;

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
					cin.clear();
					cin.ignore();

					cout<<"Enter the name of the business you would like to enter."<<endl;
					string busName;
					cin>>busName;

					Business* temp=NULL;
					for(int i=0; i< businessVec.size(); i++)
					{
						if(businessVec[i].getBusName()==busName)
						{
							temp=&businessVec[i];
							break;
						}

					}

					if(temp==NULL)
					{
						cout<<"Business not found."<<endl;
						break;
					}

					temp->businessMenu();

					break;

				}
				case 2:
				{
					//Create Business
					cin.clear();
					cin.ignore();

					string newName;

					cout<<"Please enter the name of tbe business you would like to create."<<endl;
					getline(cin,newName);

					Business newBus(newName);

					businessVec.push_back(newBus);

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
					cout<<"Goodbye."<<endl;
					exit(1);
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
	Driver d;
	d.runProgram();
}