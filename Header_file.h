#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef BBB
#define BBB
#define MAX 50

//structer name :product
// this structer holds the storage of our kitchen products 
// this structer recives the information from the 'Manot.txt' file
typedef struct product 
{
    char* name;
    int price;
    int Quantity;
    struct product *next;
}product, *Pproduct;

//structer name:list
// this is an array structer of the orders for each table , this structers are created by other function
typedef struct list 
{
    char* name;
    int Quantity;
    struct list* next;
}list, * Plist;

//structer name :num_of_table
// ths structer is linked to the 'tables' structer .
//this structer holds the amount of the orders that the table has orderd and not has been deleted, the bill of the table .
typedef struct num_of_table 
{
    struct list* head;
    struct list* tail;
    int bill;
    int n;        //מס' המנות שהוזמנו בשולחן
}num_of_table;

//structer name:tables
//the structer holds num_of_table  array with the size of the amount of the tables that is recived from instructions file
//this structer links through all the other structers (besides product structer)
typedef struct tables //מנהל השולחנות
{
    int amount;
    struct num_of_table* arr;
}tables;

//function name:createPoriducts
//this function recives into linked strcuters the information from the file manot and filles the empty cells
Pproduct CreateProducts(Pproduct head, Pproduct tail, FILE* manot, FILE* out);

//function name:AddItems
//this function adds to specific product structer an amount to his quantity , in case the product is not a part of the porducts 
// list then the function will print the requsted message
void AddItems(Pproduct head, Pproduct tail, int a, char* str, FILE* out);

//function name:OrderItem
//this function creates an order for the specific table the is recived from the file
//it fills all the labels of the linked structers , in case the function recives an order to a table that has already orderd the
//product, it wont create new structer label instead it will add to the quantity of the old order .
void OrderItem(tables t, Pproduct head,int a,int q,char*str ,FILE* out);

//function name:RemoveItem
//this function removes the requested amount that is recived from the instruction file from the specific table and removes the amount
//from the order , or in case the quantity of the order reaches 0 ,the amount of the orders of the specific table will be reduced
void RemoveItem(int a, char* str,int q, tables t, Pproduct head, FILE* out);

//function name:RemoveTable
//this function empties the specifig table information and prints the sum of the bills+tip 
// and this fucntion frees the memory that has been seted for all the linked structers is getting freed
void RemoveTable(int a, tables t, Pproduct head, FILE* out);

//function name: delete_LIST
//this function free the linked structers and frees thier memory
void Delete_List(Pproduct head);

#endif
