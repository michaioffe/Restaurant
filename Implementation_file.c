#include "Header_file.h"

//function name:createPoriducts
//this function recives into linked strcuters the information from the file manot and filles the empty cells
Pproduct CreateProducts(Pproduct head, Pproduct tail, FILE* manot, FILE* out)
{
	product item;
	Pproduct pitem, ptemp, Pempty=NULL;
	int count = 0;

	char product_name[MAX];
	while (fscanf(manot, "%s %d %d", product_name, &item.Quantity, &item.price) != EOF)
	{
		ptemp = head;
		if (count > 0)
		{
			while (ptemp != NULL)
			{
				if (!strcmp(product_name, ptemp->name))
				{
					fprintf(out, "error, the product '%s' already exists\n", product_name);
					continue;
				}
				ptemp = ptemp->next;
			}
			if (item.price < 0)
			{
				fprintf(out, "error, the price should be positive and not %d\n", item.price);
				continue;
			}

			if (item.Quantity < 0)
			{
				fprintf(out, "error, the Quantity should be positive and not %d\n", item.Quantity);
				continue;
			}
		}

		pitem = (product*)malloc(sizeof(product));
		if (pitem == NULL)
		{
			fprintf(out, "error\n");
			Delete_List(head);
			exit(1);
		}

		pitem->name = (char*)malloc((1 + strlen(product_name)) * sizeof(char));
		if (pitem->name == NULL)
		{
			free(pitem);
			fprintf(out, "error\n");
			Delete_List(head);
			exit(1);
		}

		strcpy(pitem->name, product_name);
		pitem->Quantity = item.Quantity;
		pitem->price = item.price;

		if (count == 0)
		{
			head = pitem;
			head->next = NULL;
			tail = pitem;
		}

		else
		{
			pitem->next = head;
			head = pitem;
		}

		count++;
	}
	fprintf(out, "The kitchen was created\n");
	return head;
}

///////////////////////////////////////////////////////////////////////////////////
//function name:AddItems
//this function adds to specific product structer an amount to his quantity , in case the product is not a part of the porducts 
// list then the function will print the requsted message
void AddItems(Pproduct head, Pproduct tail, int a, char* str, FILE* out)
{
	product item;
	Pproduct pitem=head;
	
	if (a <= 0)
		fprintf(out, "error, the quantity is not positive\n");

	while (pitem != NULL)
	{
		if (!strcmp(pitem->name, str))
		{
			fprintf(out, "%d %s were added to the kitchen\n",a,str);
			pitem->Quantity = pitem->Quantity + a;
			return;
		}
		pitem = pitem->next;
	}
	fprintf(out, "error, the product '%s' don't exists\n", str);
}

///////////////////////////////////////////////////////////////////////////////
//function name:OrderItem
//this function creates an order for the specific table the is recived from the file
//it fills all the labels of the linked structers , in case the function recives an order to a table that has already orderd the
//product, it wont create new structer label instead it will add to the quantity of the old order .
void OrderItem(tables t, Pproduct head,int a, int q, char* str, FILE* out)
{
	Pproduct pitem=head;
	Plist plist = t.arr[a - 1].head;
	int count = 0;

	if (a > t.amount || a<0)
		fprintf(out, "error,the table doesn't exist\n");
	while (strcmp(str, pitem->name))
	{
		pitem = pitem->next;
		if (pitem == NULL)
		{
			fprintf(out, "we don't have %s, sorry!\n", str);
			return 0;
		}
	}

	if (q > pitem->Quantity || q<=0)
	{
		fprintf(out, "error, the quantity of the %s is only %d\n", pitem->name,pitem->Quantity);
		return 0;
	}
	if (t.arr[a - 1].n > 0)
	{
		while (strcmp(str, plist->name))
		{
			if (plist == NULL)
				break;
			if (!strcmp(str, plist->name))
			{
				plist->Quantity = (plist->Quantity) + q;
				t.arr[a - 1].bill = t.arr[a - 1].bill + q * (pitem->price);
				t.arr[a - 1].n++;
				return;
			}
			plist = plist->next;
		}
	}

		t.arr[a - 1].head = (list*)malloc(sizeof(list));
		if (t.arr[a - 1].head == NULL)
		{
			fprintf(out, "error\n");
			Delete_List(head);
			Delete_List(t.arr[a - 1].head);
			exit(1);
		}

		t.arr[a - 1].head->name = (char*)malloc((1 + strlen(str)) * sizeof(char));
		if (t.arr[a - 1].head->name == NULL)
		{
			Delete_List(head);
			Delete_List(t.arr[a - 1].head);
			fprintf(out, "error\n");
			exit(1);
		}

		strcpy(t.arr[a - 1].head->name, str);
		t.arr[a - 1].head->Quantity = 0;
		t.arr[a - 1].head->Quantity = t.arr[a - 1].head->Quantity + q;
		t.arr[a - 1].bill = t.arr[a - 1].bill+ (pitem->price * q);
		pitem->Quantity = pitem->Quantity - q;

		fprintf(out, "%d %s were added to table number %d\n", q,str,a);
		if (count == 0)
		{
			t.arr[a - 1].head->next = NULL;
			t.arr[a - 1].tail =t.arr[a - 1].head;
		}
		else
		{
			t.arr[a - 1].tail->next = t.arr[a - 1].head;
			t.arr[a - 1].tail = t.arr[a - 1].head;
		}

		t.arr[a - 1].n++;
}

/////////////////////////////////////////////////////////////////////////////////
//function name:RemoveItem
//this function removes the requested amount that is recived from the instruction file from the specific table and removes the amount
//from the order , or in case the quantity of the order reaches 0 ,the amount of the orders of the specific table will be reduced
void RemoveItem(int a, char* str, int q, tables t, Pproduct head, FILE* out)
{
	Pproduct pitem = head;
	Plist plist=t.arr[a-1].head;
	if (t.arr[a - 1].n == 0)
	{
		fprintf(out, "error, there are no orders from this table\n");
		return 0;
	}

	while (strcmp(str, pitem->name))
	{
		pitem = pitem->next;
		if (pitem == NULL)
		{
			fprintf(out, "error, the product '%s' isn't in the menu\n", pitem->name);
			return 0;
		}
	}
		while (plist != NULL)
		{
			if (!strcmp(str, plist->name))
			{
				t.arr[a - 1].bill = (t.arr[a - 1].bill)-(q*(pitem->price));
				plist->Quantity = plist->Quantity - q;
				if(!plist->Quantity)
				t.arr[a - 1].n--;
				fprintf(out, "%d %s was returned to the kitchen from table number %d\n", q,str,a);
			}
			plist = plist->next;
		}
}

//////////////////////////////////////////////////////////////////////////////////
//function name:RemoveTable
//this function empties the specifig table information and prints the sum of the bills+tip 
// and this fucntion frees the memory that has been seted for all the linked structers is getting freed
void RemoveTable(int a, tables t, Pproduct head, FILE* out)
{
	Plist plist = t.arr[a - 1].head;

	if (t.arr[a - 1].n == 0)
	{
		fprintf(out, "the table number %d isn't ordered yet\n", a);
		return;
	}

	while (plist != NULL)
	{
		fprintf(out, "%d ", plist->Quantity);
		fprintf(out, "%s.", plist->name);
		
		plist = plist->next;
	}
		fprintf(out, "%d nis+%.0f nis for tips,please!\n", t.arr[a - 1].bill, (t.arr[a - 1].bill) * 0.1);
		Delete_List(t.arr[a - 1].head);
	
}

/// /////////////////////////////////////////////////////////////////////////////////
//function name: delete_LIST
//this function free the linked structers and frees thier memory
void Delete_List(Pproduct head)
{
	Pproduct temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp);
	}
	return;
}