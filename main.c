#include "contact.h"
int main()
{
	AddressBook address_book;   //Create a structure variable and load the content of the file
	load_file(&address_book);
	int choice;
	do
	{
		printf("Adress Book Menu:\n");  /*Display the menu for user*/
		printf("1. Create contact\n2. Search contact\n3. Edit contact\n4. Delete contact\n5. List all contacts\n6. Save changes\n7. Exit\n");
		scanf("%d",&choice);
		switch(choice)					//Based on choce call the function
		{
			case 1:
				create_new_contact(&address_book);		/*Function call to add the new contact*/
				break;
			case 2:
				search_contact(&address_book);			/*Function call to search the contact*/
				break;
			case 3:
				Edit_contact(&address_book);			/*Function call to edit contact*/
				break;	
			case 4:
				Delete_contact(&address_book);			/*Function call to delete a contact*/
				break;
			case 5:
				list_contacts(&address_book);			/*Function call to list all contacts*/
				break;
			case 6:
				save_contacts(&address_book);			/*Function call to save all the contacts into a file*/
				break;
		}
	}while(choice != 7);
	return 0;
}

