#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 50

/*Structure for details of a person*/
typedef struct {
	char name[MAX];
	char phone[MAX];
	char email[MAX];
	char address[MAX];
} Contact;
/*Structure for creating contacts and maintain count of the contacts*/
typedef struct {
	Contact *contacts;
	int contactCount;
} AddressBook;

/*Function to load data from the file*/
void load_file(AddressBook* address_book);
/*Function to create new contact*/
void create_new_contact(AddressBook* address_book);
/*Function to check the phone number*/
int check_phone_number(char* phone_number);
/*Function to check the valid email address*/
int check_email(char* email);
int count_var(char* email);
/*Function to list all the contacts*/
void list_contacts(AddressBook* address_book);
/*Function to save all the contacts*/
void save_contacts(AddressBook* address_book);
/*Function to search the contacts*/
void search_contact(AddressBook* address_book);
/*Function to search content of the contacts*/
int Search_data(int choice,AddressBook* address_book);
/*Function to delete  the contacts*/
void Delete_contact(AddressBook* address_book);
/*Function to edit the contact*/
void Edit_contact(AddressBook* address_book);

#endif
