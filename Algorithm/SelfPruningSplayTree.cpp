#include <bits/stdc++.h>
using namespace std;

int data[20] = {3,6,4,32,54,17,18,19,12,2,7,8,5,2,1,8,16,23,15};
int n = sizeof(data)/sizeof(int);

struct node
{
	int key;
	int startind;
	node *left, *right;
}*root;

struct node* newNode(int key,int si)
{
	node* Node = new node();
	Node->startind=si;
	Node->key = key;
	Node->left = Node->right = NULL;
	return (Node);
}

struct node *rightRotate(node *x)
{
	node *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

node *leftRotate(node *x)
{
	node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

node *splay(node *root, int key)
{

	if (root == NULL || root->key == key)
		return root;

	if (root->key > key)
	{

		if (root->left == NULL) return root;

		if (root->left->key > key)
		{
			root->left->left = splay(root->left->left, key);

			root = rightRotate(root);
		}
		else if (root->left->key < key)
		{
			root->left->right = splay(root->left->right, key);

			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}

		return (root->left == NULL)? root: rightRotate(root);
	}
	else
	{

		if (root->right == NULL) return root;

		if (root->right->key > key)
		{
			root->right->left = splay(root->right->left, key);

			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key)
		{

			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		return (root->right == NULL)? root: leftRotate(root);
	}
}

node *insert(node *root, int k, int si)
{

	if (root == NULL) return newNode(k,si);

	root = splay(root, k);

	if (root->key == k) return root;

	node *newnode = newNode(k,si);

	if (root->key > k)
	{
		newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
	}

	else
	{
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}

	return newnode;
}


int isLeaf (struct node * Node) {
    return (Node->left == NULL) && (Node->right == NULL);
}

void pruneLeaves(struct node * root)
{
    if (root->left != NULL) {
        if (isLeaf (root->left))
        {
            free(root->left);
            root->left=NULL;
        }
        else {
            pruneLeaves(root->left);
        }
    }

    if (root->right != NULL) {
        if (isLeaf (root->right)) {
            free(root->right);
            root->right=NULL;
        }

        else {
            pruneLeaves(root->right);
        }
    }
}

void preOrder(node *root)
{
	if (root != NULL)
	{
		cout<<root->key<<" ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

struct node* delete_key(struct node *root, int key)
{
    struct node *temp;
    if (!root)
        return NULL;
    root = splay(root, key);

    if (key != root->key)
        return root;

    if (!root->left)
    {
        temp = root;
        root = root->right;
    }

    else
    {
        temp = root;

        root = splay(root->left, key);
        root->right = temp->right;
    }

    free(temp);

    return root;

}

int height(node* x)
{
    if (x!=NULL)
        return 1+ max(height(x->left),height(x->right));
    return 0;
}

int levelOrder(node* root)
{
    queue<node*> q;
    q.push(root);
    int p,h;
    p=h=-1;
    while(!q.empty())
    {
        node* temp = q.front();
        q.pop();
        if ((h<0 and !p<0) )
            cout<<'\n';
        cout<<temp->key<<' ';
        if (temp!=NULL)
        {
            if(temp->left!=NULL)
            {
                //h+=1;
                q.push(temp->left);
            }
            if (temp->right!=NULL)
            {
                //h+=1
                q.push(temp->right);
            }
        }
    }
}

int lowerEnd(int a,bool t) // End value index for query
{
    root=splay(root,a);
    int i=0;
    if (root->key==a)
    {
        i = root->startind;
        if(t)
            for (;i<n;i++)
                if (data[i]!=a)
                    return i;
        return i;
    }
    else if (root->key < a)
    {
        for (i=root->startind;i<n;i++)
        {
            if (data[i]>=a)
                break;
        }
        node* newnode = newNode(a,i);
        newnode->left = root;
	    newnode->right = root->right;
	    root->right = NULL;
	    root = newnode;
	    if(height(root)>2)
	        pruneLeaves(root);
	    if(t)
            for (;i<n;i++)
                if (data[i]!=a)
                    return i;
        return i;
    }
    else
    {
        for (i=0;i<n;i++)
        {
            if (data[i]>=a)
                break;
        }
        node* newnode = newNode(a,i);
        newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
		root = newnode;
		if(height(root)>2)
	        pruneLeaves(root);
		if(t)
            for (;i<n;i++)
                if (data[i]!=a)
                    return i;
        return i;
    }
}

int upperStart(int a,bool t) // returns the starting index of the query
{
    root=splay(root,a);
    int i=0;
    if (root->key==a)
    {
        i = root->startind;
        if(!t)
            for (;i<n;i++)
                if (data[i]!=a)
                    return i;
        return i;
    }
    else if (root->key < a)
    {
        for (i=root->startind;i<n;i++)
        {
            if (data[i]>=a)
                break;
        }
        node* newnode = newNode(a,i);
        newnode->left = root;
	    newnode->right = root->right;
	    root->right = NULL;
	    root = newnode;
	    if(height(root)>2)
	        pruneLeaves(root);
	    if(!t)
            for (;i<n;i++)
                if (data[i]!=a)
                    return i;
        return i;
    }
    else
    {
        for (i=0;i<n;i++)
        {
            if (data[i]>=a)
                break;
        }
        node* newnode = newNode(a,i);
        newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
		root = newnode;
		if(height(root)>2)
	        pruneLeaves(root);
		if(!t)
            for (;i<n;i++)
                if (data[i]!=a)
                    return i;
        return i;
    }
}


int query(int a=-1,string d="000",int b=-1)
{
    int i=0;
    if(d[0]=='0')
    {
        if(d[1]=='0')
        {
            a = upperStart(a,(int)d[2]-'0');
            b = n;
        }
        else
        {
            b = lowerEnd(a,(int)d[2]-'0');
            a=0;
        }
    }
    else
    {
        a = upperStart(a,(int)d[1]-'0');
        b = lowerEnd(b,(int)d[2]-'0');
        root = splay(root,(int)(a+b)/2);
    }
    for(i=a;i<b;i++)
        cout<<data[i]<<' ';
    cout<<'\n';
}

int main()
{
    sort(data,data+n);
	root = newNode(0,0);
	query(19,"010");
	query(8,"100",19);
	query(3,"101",8);
	query(6,"111",18);
	query(2,"000");

	cout<<"Preorder traversal of the modified Splay tree is \n";
	preOrder(root);
	cout<<"\nLevel order: \n";
	levelOrder(root);

	return 0;
}