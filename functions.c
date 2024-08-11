#include "contact.h"
int choice;
/*Load saved contacs into the structure member
 Open the address_bok.csv in read mode and read the count of no.of contacts in the file.
 Allocate the memory dynamically and store the information into structure member.*/
void load_file(AddressBook* address_book)
{
	FILE* fptr = fopen("address_book.csv","r");		//Open the file in read mode
	if(fptr == NULL)
	{
		printf("Unable to open file\n");
		return ;
	}
	char str[100];
	fscanf(fptr,"%[^\n]\n",str);
	//char* temp = (strtok(str+1,"#"));
	int count = atoi(strtok(str,"#"));
	address_book->contacts = malloc (count * sizeof(Contact));		//Based on count allocate the memory dynamically
	/*Load the contact information into the member*/
	for(int i = 0; fscanf(fptr,"%[^\n]\n",str) != EOF;i++)
	{
		strcpy(address_book->contacts[i].name,strtok(str,","));
		strcpy(address_book->contacts[i].phone,strtok(NULL,","));
		strcpy(address_book->contacts[i].email,strtok(NULL,","));
		strcpy(address_book->contacts[i].address,strtok(NULL,","));
	}
	/*Keep the contact count*/
	address_book->contactCount = count;
	fclose(fptr);
}
/*Function to create the new contact
 Function has address of structure member as input paramater.
 Take all information such as name,phonennumber,email and address
 Allocate the memory dynamically for storing information inside structure member.*/
void create_new_contact(AddressBook* address_book)
{
	int index = address_book->contactCount,ret;
	/*Reallocate memory for new contact with existing contacts*/
	address_book->contacts = realloc(address_book->contacts,(index+1)*sizeof(Contact));
	char name[MAX];
	printf("Enter name: ");
	getchar();
	scanf("%[^\n]",address_book->contacts[index].name);		//Read the name and store 
	while(1)
	{
		printf("Enter phone number: ");
		scanf("%s",name);
		ret = check_phone_number(name);					//Read phone number and validate the phone number
		if(ret == 1)
		{
			strcpy(address_book->contacts[index].phone,name);		//If satisified store in member
			break;
		}
		else
		{
			printf("Enter a valid Phone number\n");
		}
	}
	while(1)
	{
		printf("Enter E-mail ID : ");					//Read email id
		scanf("%s",name);
		ret = check_email(name);						//Validate and store the email id
		if(ret == 1 )
		{
			strcpy(address_book->contacts[index].email,name);
			break;
		}
		else
		{
			printf("Please enter vaild email address\n");
		}
	}
	printf("Enter address : ");
	getchar();
	scanf("%[^\n]",address_book->contacts[index].address);			//Read address and store in member
	address_book->contactCount++;
	printf("\n------------------------------\n");
	printf("Contact created Successfully\n");
	printf("------------------------------\n");

}
/*Function to list all the contacts
 Function takes the address of structire member as input.
 It print all the information inside the structe to stdin.*/
void list_contacts(AddressBook* address_book)
{
	printf("----------------------------------------------------------------\n");
	printf("Name\t\tPhone number\tEmail\t\t\tAddress\n");
	printf("----------------------------------------------------------------\n");
	/*Run loop till the contact count and print all the details*/
	for(int i = 0; i < address_book->contactCount;i++)
	{
		printf("%s\t\t%s\t%s\t\t%s\n",address_book->contacts[i].name,address_book->contacts[i].phone,address_book->contacts[i].email,address_book->contacts[i].address);
	}
	printf("----------------------------------------------------------------\n");
}
/*Function to save the contacts
 Receive the structure member address as input.
 Open the file in write mode and print the all information intio file and save it.*/
void save_contacts(AddressBook* address_book)
{
	int count = address_book->contactCount;
	FILE* fptr = fopen("address_book.csv","w");			//Open the file in write mode
	if(fptr == NULL)
	{
		printf("Unable to open file\n");
		return;
	}
	fprintf(fptr,"#%d#\n",count);					//Print all the content into file and save it
	for(int i = 0; i < count ; i++)
	{
		fprintf(fptr,"%s,%s,%s,%s\n",address_book->contacts[i].name,address_book->contacts[i].phone,address_book->contacts[i].email,address_book->contacts[i].address);
	}
	fclose(fptr);									//Close the file
	printf("\n-----------------\n");
	printf("Saved Successfully\n");
	printf("-----------------\n");
}
/*Function to search the contact
 Funtion has structure member address as input.
 Search the information based on different choices and print the information.*/
void search_contact(AddressBook* address_book)
{
	int index;
	char again;
	do
	{
		/*Print the opetions for user to search the contact*/
		printf("1.Search by name\n2.Search by phone number\n3.Search by email\n4.Search by address\nEnter your choice: ");
		scanf("%d",&choice);  //read choice and call the function and it prints the content
		index = Search_data(choice,address_book);
		printf("Do you want to search again(y/n)? ");
		scanf(" %c",&again);
		if(again == 'y')				//Read if user want to continue search
		{
			index=address_book->contactCount;
		}
		else if(again == 'n')
		{
			break;
		}

	}while(index == address_book->contactCount);


}
/*Function to serach the data and return the index.
 2.Function takes the user choice and structure member address as input
 3.Based on choice it compare the information present in structure.
 4.Upon finding it returns the index value of particular information.*/
int Search_data(int choice,AddressBook* address_book)
{
	int i=0,flag=0;
	char search[50];
	/*Based on choice search the details*/
	switch(choice)
	{
		case 1:
			printf("Enter name: ");
			getchar();
			scanf("%[^\n]",search);
			/*Read the name from user and compare with all the contact names*/
			for(i=0;i<address_book->contactCount;i++)
			{
				/*If matched print the information*/
				if(!strcmp(search,address_book->contacts[i].name))
				{
					printf("------------------------------------------------------\n");
					printf("%s\t\t%s\t%s\t%s\n",address_book->contacts[i].name,address_book->contacts[i].phone,address_book->contacts[i].email,address_book->contacts[i].address);
					printf("------------------------------------------------------\n");
					flag = 1;
					return i;		//return index value
				}
			}
			if(flag == 0)
			{
				/*Based on flag print the message*/
				printf("----------------------\n");
				printf("Name not found!!!!!!!!\n");
				printf("----------------------\n");
			}
			return i;
			break;
		case 2:
			/*Read phone number and validate it*/
			while(1)
			{
				printf("Enter Phone number : ");
				scanf("%s",search);
				if(check_phone_number(search))
				{
					/*Check all the contact phone numbers if matched print information and return index*/
					for(i=0;i<address_book->contactCount;i++)
					{
						if(!strcmp(search,address_book->contacts[i].phone))
						{
							printf("------------------------------------------------------\n");
							printf("%s\t\t%s\t%s\t%s\n",address_book->contacts[i].name,address_book->contacts[i].phone,address_book->contacts[i].email,address_book->contacts[i].address);
							printf("------------------------------------------------------\n");
							flag = 1;
							return i;

						}
					}
					if(flag == 0)
					{
						/*Based in flag print message*/
						printf("----------------------\n");
						printf("Phone number not found\n");
						printf("----------------------\n");
					}
					return i;
				}
				else
				{
					/*If phone number is incorrect print error message*/
					printf("----------------------\n");
					printf("Enter valid Phone number\n");
					printf("----------------------\n");
				}
			}
			break;
		case 3:
			while(1)
			{
				/*Read email id and validate it*/
				printf("Enter Email-ID : ");
				scanf("%s",search);
				if(check_email(search))
				{
					/*Run loop and compare all the email ids*/
					for(i=0;i<address_book->contactCount;i++)
					{
						/*If matched print the content and return the index*/
						if(!strcmp(search,address_book->contacts[i].email))
						{
							printf("------------------------------------------------------\n");
							printf("%s\t\t%s\t%s\t%s\n",address_book->contacts[i].name,address_book->contacts[i].phone,address_book->contacts[i].email,address_book->contacts[i].address);
							printf("------------------------------------------------------\n");
							flag = 1;
							return i;
						}

					}
					if(flag == 0)
					{
						printf("----------------------\n");
						printf("Email address not found\n");
						printf("----------------------\n");
					}
					return i;
				}
				else
				{
					printf("----------------------\n");
					printf("Invalid Email-ID!!!!!!!!\n");
					printf("----------------------\n");
				}
			}
			break;
		case 4:
			printf("Enter the address: ");
			getchar();
			scanf("%[^\n]",search);
			for(i = 0 ; i < address_book->contactCount;i++)
			{
				/*run loop and compare the address if matched print and retur index*/
				if(!strcmp(search,address_book->contacts[i].address))
				{
					printf("------------------------------------------------------\n");
					printf("%s\t\t%s\t%s\t%s\n",address_book->contacts[i].name,address_book->contacts[i].phone,address_book->contacts[i].email,address_book->contacts[i].address);
					printf("------------------------------------------------------\n");
					flag = 1;
					return i;
				}

			}
			if(flag == 0)
			{
				printf("-----------------------------------\n");
				printf("No contact found with given address\n");
				printf("-----------------------------------\n");
			}
			return i;
			break;
		default:
			printf("---------------------------\n");
			printf("Please enter a valid choice\n");
			printf("---------------------------\n");

	}
}
/*1.Function to edit the contact
 2.Function will receive the structe member address as input.
 3.Display menu for user and based on choice read updated information from user.
 4.Editing the contact successfully.*/
void Edit_contact(AddressBook* address_book)
{
	int index,i;
	char again,phone[11],email[50];
	do
	{
		/*Display options for menu*/
		printf("1.Edit name\n2.Edit Phone number\n3.Edit Email-ID\n4.Edit address\nEnter your choice : ");
		scanf("%d",&choice);
		index = Search_data(choice,address_book);		//Find the index
		if(index != address_book->contactCount)			//If index found
		{
			switch(choice)
			{
				/*Based on choice read the updated information*/
				case 1:
					printf("Enter new name: ");
					getchar();
					scanf("%[^\n]",address_book->contacts[index].name);
					break;
				case 2:
					while(1)
					{
						/*Read new phone number and validate it*/
						printf("Enter new Phone number: ");
						scanf("%s",phone);
						if(check_phone_number(phone))
						{
							strcpy(address_book->contacts[index].phone,phone);
							break;
						}
						else
						{
							printf("Invalid Phone Number!!!!\n");
						}
					}
					break;
				case 3:
					while(1)
					{
						/*Read new email id*/
						printf("Enter Email-ID: ");
						scanf("%s",email);
						if(check_email(email))
						{
							strcpy(address_book->contacts[index].email,email);
							break;
						}
						else
						{
							printf("Invalid Email-Id!!!!!\n");
						}
					}
					break;
				case 4:
					/*Read new address*/
					printf("Enter new address: ");
					scanf(" %[^\n]",address_book->contacts[index].address);
					break;
			}
			printf("Edit Successful\n");
			printf("Do you want to edit again(y/n)\n");
		}
		else
		{
			/*prompt user whether to continue again*/
			printf("Do you want to try again(y/n)\n");
		}
		scanf(" %c",&again);
		if(again == 'y' || again == 'Y')
		{
			i = address_book->contactCount;
		}
		else if(again == 'n' || again == 'N')
		{
			break;
		}
	}while(i == address_book->contactCount);
}
/*1.Function to delete a contact
 2.This function takes the structure member address as input.
 3.Read the choice from user and delete the particular contact and reduce the contact count.*/
void Delete_contact(AddressBook* address_book)
{
	int index,i;
	char again;
	do
	{
		/*Display menu for user*/
		printf("1.Delete by name\n2.Delete by phone number\n3.Delete by Email-ID\n4.Delete by address\nEnter your choice: ");
		scanf("%d",&choice);
		index = Search_data(choice,address_book);
		/*Based on index overwrite the content*/
		if(index >= 0 && index < address_book->contactCount)
		{
			for( i = index ; i < address_book->contactCount; i++)
			{
				address_book->contacts[i] = address_book->contacts[i+1];
			}
			address_book->contactCount--;		//decrement the count
			printf("Contac deleted Successfully\n");
			printf("Do you want to delete again(y/n) :");
		}
		else
		{
			printf("Do you want to try again(y/n)\n");
		}

		scanf(" %c",&again);
		if(again == 'y' || again == 'Y')
		{
			i = address_book->contactCount;
		}
		else if(again == 'n' || again == 'N')
		{
			break;
		}

	}while(i==address_book->contactCount);  //Based on choice continue deleting

}
/*1.Function to validate the phone number
 2.The function takes the phone number as input and count the digits int it.
 3.If count is 10 it returns 1 otherwise it returns 0  */
int check_phone_number(char* phone_number)
{
	int i=0,count=0;
	while( phone_number[i] != '\0')
	{
		if( phone_number[i] >= '0' && phone_number[i] <='9')
		{
			count++;
		}
		else
		{
			break;
		}
		i++;
	}
	if(count != 10)
	{
		return 0;
	}
	return 1;

}
/*1.Function to validate the email
 2.It takes the email string as input and validate whether it has '@' character and ".com" in it.
 3.If conditions true returns 1 ,if false returns 0*/
int check_email(char* email)
{
	if( (strchr(email,'@') == 0) || (strstr(email,".com") == 0) || (count_var(email) == 0) )
	{
		return 0;
	}
	return 1;
}
/*1.Count values before @ character
 2.Function takes the email as input and validate the characters before finding @ character.There should be atleast 1 character before @ character.
 3. If condition true returns 1 other wise returns 0*/
int count_var(char* email)
{
	int count = 0,i=0;
	while( email[i] != '\0')
	{
		if( email[i] == '@')
		{
			break;
		}
		else
		{
			count++;
		}
		i++;
	}
	if( count == 0)
	{
		return 0;
	}
	return 1;
}
