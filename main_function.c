#include "Header_file.h"

int main()
{
	FILE* manot, * instruction,*out; //set names for the files
	Pproduct head=NULL,tail=NULL; //sets head and tail and pointers to Pproucdt and sets them as NULL
	list tlist;
	num_of_table tnum_of_table;
	tables ttables;
	ttables.amount = 0;
	int i,m,a,q, b;
	char st[MAX];
	out = fopen("output.txt", "w");
	if (out == NULL)
	{
		fprintf(out, "error");
		exit(1);
	}
	manot = fopen("Manot.txt", "r");
	if (manot == NULL)
	{
		fprintf(out,"error");
		exit(1);
	}
	instruction= fopen("Instructions.txt", "r");
	if (instruction == NULL)
	{
		fprintf(out, "error");
		exit(1);
	}
	fscanf(instruction, "%d", &m); //recives the number of the tables in this file
	ttables.amount = m;
	ttables.arr = (num_of_table*)malloc(m * sizeof(num_of_table));//set tables.arr m memory slots of the num_of_table structer
	if (ttables.arr == NULL)
	{
		fprintf(out, "error");
		exit(1);
	}
	for (i = 0; i < m; i++)//set variables in the arr as 0 and null
	{
		ttables.arr[i].head = NULL;
		ttables.arr[i].bill = 0;
		ttables.arr[i].n = 0;
	}
	fclose(out);
	while (fscanf(instruction,"%d",&b)!=EOF)//this loop will run untill we reach the end of file ,each scan will recive another number from the instruction file
	{
		out = fopen("output.txt", "a");
		if (out == NULL)
		{
			fprintf(out, "error");
			exit(1);
		}

		if (b == 1)
		{
			head=CreateProducts(head, tail, manot, out);
			fclose(manot);
		}
		if (b == 2)
		{
			fscanf(instruction, "%s %d",st, &a);
			AddItems(head, tail, a, st, out);
		}
		if (b == 3)
		{
			fscanf(instruction, "%d %s %d", &a,st, &q);
			OrderItem(ttables, head, a, q, st, out);
		}
		if (b == 4)
		{
			fscanf(instruction, "%d %s %d", &a, st, &q);
			RemoveItem(a, st, q, ttables, head, out);
		}
		if (b == 5)
		{
			fscanf(instruction, "%d", &a);
			RemoveTable(a,ttables, head, out);
		}
			fclose(out);
	}
	fclose(instruction);//close incstruction file
	free(ttables.arr);//free the memory the arr
	return 0;
}