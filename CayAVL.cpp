#include <iostream>
using namespace std;

typedef struct Node
{
	int key, bal; 
	Node* left,* right;
}node;

node* TaoNode(int data)
{
	node* p = new node;
	if (p == NULL) return NULL;
	p->key = data;
	p->left= p->right = NULL;
	p->bal = 0;
	return p;
}
//========================================================================
void XoayTrai(node* &p)
{
	node *q;
	q = p->right;
	p->right = q->left;
	q->left = p;
	p = q;
}

void XoayPhai(node* &p)
{
	node *q;
	q = p->left;
	p->left = q->right;
	q->right = p;
	p = q;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Ham xu ly can bang
void CanbangTrai(node* &p)
{
	switch(p->left->bal)
	{
	//Mat can bang Trai-Trai
		case 1: 
			XoayPhai(p);
			p->bal = 0;
			p->right->bal = 0;
		break;
	
	//Mat can bang Trai-Phai
	case 2:
			XoayTrai(p->left);
			XoayPhai(p);
			switch(p->bal){
			case 0:
				p->left->bal= 0;
				p->right->bal= 0;
				break;
			case 1:
				p->left->bal= 0;
				p->right->bal= 2;
				break;
			case 2:
				p->left->bal= 1;
				p->right->bal= 0;
				break;
		}
		p->bal = 0;
		break;
	}
}

void CanbangPhai(node* &p)
{
	switch(p->right->bal)
	{
	//Mat can bang Phai-Trai
	case 1: 
		XoayPhai(p->right);
		XoayTrai(p);
		switch(p->bal){
			case 0:
				p->left->bal= 0;
				p->right->bal= 0;
				break;
			case 1:
				p->left->bal= 1;
				p->right->bal= 0;
				break;
			case 2:
				p->left->bal= 0;
				p->right->bal= 2;
				break;
		}
		p->bal = 0;
		break;
	
	//Mat can bang Phai-Phai
	case 2:
		XoayTrai(p);
		p->bal = 0;
		p->left->bal = 0;
		break;
	}
}
//========================================================================
int Nhap(node* &cay, int x)
{
	int p;
	if(cay == NULL)
	{
			cay = TaoNode(x);
			if(cay == NULL)
			{
				return -1;
			}
		return 2;
	}
	else 
	{
		if(cay->key == x)
		{
			return 0;
		}
	else if(cay->key > x){
		p = Nhap(cay->left,x);
		if(p < 2) {
			return p;
	}
	switch(cay->bal){
		case 0:
			cay->bal = 1;
			return 2;
		case 1:
			CanbangTrai(cay);
			return 1;
		case 2:
			cay->bal = 0;
			return 1;
		}
	}
	else{
		p = Nhap(cay->right,x);
		if(p<2){
			return p;
		}
		switch(cay->bal){
		case 0:
			cay->bal=2;
			return 2;
		case 1:
			cay->bal = 0;
			return 1;
		case 2:
			CanbangPhai(cay);
			return 1;
			}
		}
	}
}
//========================================================================
/*
Xuat thong tin cac node tren cay
Khi ket thuc chuong trinh, xoa cac node tren cay ra khoi bo nho
*/

void Xuat(node* t)
{
	if(t!=NULL)
	{
		Xuat(t->left);
		cout << "Khoa: " << t->key << ", can bang: " << t->bal;
		cout << endl;
		Xuat(t->right);
	}
}
void xoa(node* &t)
{
	if(t!=NULL){
		xoa(t->left);
		xoa(t->right);
		delete t;
	}
}

//========================================================================
int main()
{
	node *cay = NULL;
	int data;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	do
	{
		cout << ("Nhap phan tu, ket thuc nhap '-1': ");
		cin >> data;
		if (data == -1)
		break;
		Nhap(cay, data);
	}while (data != -1);
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	cout << "\n Cay vua tao: \n";
	Xuat(cay);
	xoa(cay);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	return 0;
}
