#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct
{
    int day;
    int month;
    int year;
} dates;
typedef struct phonebook
{
    char firstname[100];
    char lastname[100];
    char address[100];
    char number[100];
    dates birthday;
    char email[100];
} contact;
//char filename[100];
FILE *F;

int count=0;

void main_menu();
void read_contacts();
void add();
void Delete_contact();
void modify();
void search();
void sort();
void back();
void savetofile();
char ValidityOfFname();
void ValidityOfLname();
void ValidityOfemail();
int ValidityOfnum();
void valid_birthday();
void sortbirth();
int main()
{
    system("color fc");

    contact *p;
    p = (contact*) malloc(sizeof(contact)*100);
    fflush(stdin);
    read_contacts(p);

    main_menu(p);

    return 0;
}
void main_menu(contact *p)
{
    system("cls");
    char c;
    printf("  \n\t\t\t\t\tphonebook\n\n");
    printf("  \t\t\t\tchoose number from 1 to 7");
   // printf("\n---------------------------------------------------------------------------------------");
    printf("\n\tMAIN MENU:");
    printf("\n\t\t1.show all contacts");
    printf("\n\t\t2.add contacts");
    printf("\n\t\t3.search contact");
    printf("\n\t\t4.modify contact");
    printf("\n\t\t5.delete contact");
    printf("\n\t\t6.sort by birthday");
    printf("\n\t\t7.save");
    printf("\n\t\t8.exit");
    printf("\t\n      ----------------------------------------");
    printf("\n\tenter your choice:");
    scanf("%c",&c);
    fflush(stdin);

    system("cls");
    switch(c)
    {
    case '1':
        show_Contacts(p);

        break;
    case '2':
        add(p);

        break;
    case '3':
        search(p);
        break;
    case '4':
        modify(p);
        break;
    case '5':
        Delete_contact(p);
        break;
    case '6':
        sortbirth(p);
        break;
    case '7':
        savetofile(p);
    case '8':
        exit(0);
        break;
    default:
        system("cls");
        printf("\t\t\t\t\t\t****TRY AGAIN****");
        printf("\n\t\t\tpress any key:");
        getche();
        main_menu(p);
    }
}
void back(contact*p)
{
    char b[4];
    printf("\nplease enter any key to go back:");
    getche();
    fflush(stdin);
    main_menu(p);
}
void add(contact *p)
{
    ValidityOfFname(p);
    fflush(stdin);
    ValidityOfLname(p);
    fflush(stdin);
    valid_birthday(p);
    printf("\tenter address:");
    scanf("%[^\n]s",p[count].address);
    fflush(stdin);
    ValidityOfemail(p);
    fflush(stdin);
    printf("\tenter the number:");
    scanf("%s",p[count].number);
    while(!ValidityOfnum(p[count].number)){
        printf(" *invalid input: please enter numbers (ex:01245874585) *\n");
        printf("\tenter the number:");
        scanf("%s",p[count].number);
    }
    fflush(stdin);
    // fprintf(W,"%s,%s,%s,%s,%s,%s,%s\n",p[count].firstname,p[count].lastname,p[count].number,p[count].email,p[count].address,p[count].city,p[count].birthday);
    count ++;
    system("cls");
    // fclose(F);
    main_menu(p);

}
void read_contacts(contact*p)
{
    F=fopen("phonebook.txt","r");
    while(!feof(F))
    {
        fscanf(F,"%[^,],",p[count].firstname);
        fscanf(F,"%[^,],",p[count].lastname);
        fscanf(F,"%d-",&p[count].birthday.day);
        fscanf(F,"%d-",&p[count].birthday.month);
        fscanf(F,"%d,",&p[count].birthday.year);
        fscanf(F,"%[^,],",p[count].address);
        fscanf(F,"%[^,],",p[count].email);
        fscanf(F,"%s\n",&p[count].number);
        count++;
        // printf("inside read");
    }
    fclose(F);
}
void show_Contacts(contact*p)
{
    int i;
    printf("contacts:\n");
    if(count!=0)
    {

        sort(p);
        printf("\nYour contacts are sorted by last Name:\n\n");
        for( int j = 0; j < count; j++ )
        {
            printf("\n(%d)\n", j+1);
            printf("\tFIRSTNAME:%s\n\tLASTNAME:%s\n\tBIRTHDAY:%d/%d/%d\n\tADDRESS:%s\n\tEMAIL:%s\n\tNUMBER:%s\n",p[j].firstname,p[j].lastname,p[j].birthday.day,p[j].birthday.month,p[j].birthday.year,p[j].address,p[j].email,p[j].number);
            printf("\n\n");

        }
    }
    else
    {
        printf("there's no contacts");
    }

    fflush(stdin);
    back(p);
}
void search(contact *p)
{
    int found=0;
    int i;
    char l,n[20];
    printf("1.Search by firstname\n");
    printf("2.Search by lastname\n");
    printf("3.Search by phone number\n");
    printf("4.Search by email\n");
    printf("5.Search by address\n");
    printf("6.Search by birthday\n\n");
    printf("Enter your choice in search:");
    scanf("%c",&l);
    fflush(stdin);
    system("cls");
    switch(l)
    {
    case '1':
        //  printf("enter firstname:");
        // gets(n);
        ValidityOfFname(p);
        //  strcpy(n,ValidityOfFname(p));
        for(i=0; i<count; i++)
        {
            if(strcasecmp(p[i].firstname,p[count].firstname)==0)
            {
                printf("\nFirst Name: %s",p[i].firstname);
                printf("\nLast Name: %s",p[i].lastname);
                printf("\nBirthday: %d/%d/%d",p[i].birthday.day,p[i].birthday.month,p[i].birthday.year);
                printf("\nAddress: %s",p[i].address);
                printf("\nEmail: %s",p[i].email);
                printf("\nNumber: %s\n\n",p[i].number);
                found=1;
            }

        }
        if(found==0)
            printf("*NOT FOUND*");
        break;
    case '2':
        ValidityOfLname(p);
        for(i=0; i<count; i++)
        {
            if(strcasecmp(p[i].lastname,p[count].lastname)==0)
            {
                printf("\nFirst Name: %s",p[i].firstname);
                printf("\nLast Name: %s",p[i].lastname);
                printf("\nBirthday: %d/%d/%d",p[i].birthday.day,p[i].birthday.month,p[i].birthday.year);
                printf("\nAddress: %s",p[i].address);
                printf("\nEmail: %s",p[i].email);
                printf("\nNumber: %s\n\n",p[i].number);
                found=1;
            }

        }
        if(found==0)
            printf("*NOT FOUND*");
        break;
    case '3':
        printf("\tenter the number:");
        scanf("%s",p[count].number);
        while(!ValidityOfnum(p[count].number)){
        printf(" *invalid input: please enter numbers (ex:01245874585) *\n");
        printf("\tenter the number:");
        scanf("%s",p[count].number);
    }
        for(i=0; i<count; i++)
        {
            if(strcasecmp(p[i].number,p[count].number)==0)
            {
                printf("\nFirst Name: %s",p[i].firstname);
                printf("\nLast Name: %s",p[i].lastname);
                printf("\nBirthday: %d/%d/%d",p[i].birthday.day,p[i].birthday.month,p[i].birthday.year);
                printf("\nAddress: %s",p[i].address);
                printf("\nEmail: %s",p[i].email);
                printf("\nNumber: %s\n\n",p[i].number);
                found=1;
            }

        }
        if(found==0)
            printf("*NOT FOUND*");
        break;
    case '4':
        ValidityOfemail(p);
        for(i=0; i<count; i++)
        {
            if(strcasecmp(p[i].email,p[count].email)==0)
            {
                printf("\nFirst Name: %s",p[i].firstname);
                printf("\nLast Name: %s",p[i].lastname);
                printf("\nBirthday: %d/%d/%d",p[i].birthday.day,p[i].birthday.month,p[i].birthday.year);
                printf("\nAddress: %s",p[i].address);
                printf("\nEmail: %s",p[i].email);
                printf("\nNumber: %s\n",p[i].number);
                found=1;
            }

        }
        if(found==0)
            printf("*NOT FOUND*");
        break;
    case '5':
        printf("enter address:");
        gets(n);
        for(i=0; i<count; i++)
        {
            if(strcasecmp(p[i].address,n)==0)
            {
                printf("\nFirst Name: %s",p[i].firstname);
                printf("\nLast Name: %s",p[i].lastname);
                printf("\nBirthday: %d/%d/%d",p[i].birthday.day,p[i].birthday.month,p[i].birthday.year);
                printf("\nAddress: %s",p[i].address);
                printf("\nEmail: %s",p[i].email);
                printf("\nNumber: %s\n\n",p[i].number);
                found=1;
            }

        }
        if(found==0)
            printf("*NOT FOUND*");
        break;
    case '6':
        valid_birthday(p);
        for(i=0; i<count; i++)
        {
            if(p[i].birthday.day==p[count].birthday.day && p[i].birthday.month ==p[count].birthday.month && p[i].birthday.year== p[count].birthday.year)
            {
                printf("\nFirst Name: %s",p[i].firstname);
                printf("\nLast Name: %s",p[i].lastname);
                printf("\nBirthday: %d/%d/%d",p[i].birthday.day,p[i].birthday.month,p[i].birthday.year);
                printf("\nAddress: %s",p[i].address);
                printf("\nEmail: %s",p[i].email);
                printf("\nNumber: %s\n\n",p[i].number);
                found=1;
            }

        }
        if(found==0)
            printf("*NOT FOUND*");
        break;

    default:
        system("cls");
        printf("\t\t\t\t\t\t****TRY AGAIN****");
        printf("\n\t\t\tpress any key:");
        getche();
        system("cls");
        search(p);

    }


    back(p);
    main_menu(p);
}
void Delete_contact(contact *p)
{
    int i,j;
    char save[5];
    char first[20];
    char last[20];
    int found=0;

    printf("enter first name to delete:");
    scanf("%s",first);
    printf("enter last name to delete:");
    scanf("%s",last);
    for(i=0; i<=count-1; i++)
    {
        if(strcasecmp(p[i].firstname,first)==0)
        {
            if(strcasecmp(p[i].lastname,last)==0)
            {
                for(j=i; j<=count-2; j++)
                {
                    strcpy(p[j].firstname,p[j+1].firstname);
                    strcpy(p[j].lastname,p[j+1].lastname);
                    p[j].birthday.day=p[j+1].birthday.day;
                    p[j].birthday.month=p[j+1].birthday.month;
                    p[j].birthday.year=p[j+1].birthday.year;
                    strcpy(p[j].address,p[j+1].address);
                    strcpy(p[j].email,p[j+1].email);
                    strcpy(p[j].number,p[j+1].number);



                }
                found++;
                count--;
            }
        }

    }
    if(found!=0)
        printf("contact deleted");
    else
        printf("That contact was not found, please try again.");
    back(p);
    main_menu(p);
}
void sort(contact*p)
{
    contact temp;
    int i,j;
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if(strcasecmp(p[i].lastname,p[j].lastname)>0)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
            else if(strcasecmp(p[i].lastname,p[j].lastname)==0)
            {
                if(strcasecmp(p[i].firstname,p[j].firstname)>0)
                {
                    temp=p[i];
                    p[i]=p[j];
                    p[j]=temp;
                }

            }
        }
    }
}

void savetofile(contact*p)
{
    F=fopen("phonebook.txt","w");
    if ( F == NULL )
    {
        printf("ERROR");
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int i=0; i<count; i++)
        {
            // fflush(stdin);
            fprintf(F,"%s,%s,%d-%d-%d,%s,%s,%s\n",p[i].firstname,p[i].lastname,p[i].birthday.day,p[i].birthday.month,p[i].birthday.year,p[i].address,p[i].email,p[i].number);

        }
        printf("changes saved");
    }

    fclose(F);
    back(p);
    main_menu(p);

}
void modify(contact* p)
{
    char n[20];
    ValidityOfLname(p);
    int j=1;
    int i;
    for( i=0; i<count; i++)
    {
        if(strcasecmp(p[count].lastname,p[i].lastname)==0)
        {
            printf("\nContact number:%d",j);
            printf("\nFIRSTNAME: %s",p[i].firstname);
            printf("\nLASTNAME: %s",p[i].lastname);
            printf("\nBIRTHDAY: %d/%d/%d",p[i].birthday.day,p[i].birthday.month,p[i].birthday.year);
            printf("\nADDRESS: %s",p[i].address);
            printf("\nEMAIL: %s",p[i].email);
            printf("\nNUMBER: %s\n",p[i].number);
            j++;

            //break;
        }
    }

    if(j>2)
    {
        //int first[50];

        ValidityOfFname(p);
        for(int k=0; k<count; k++)
        {
            if(strcasecmp(p[k].firstname,p[count].firstname)==0&&strcasecmp(p[k].lastname,p[count].lastname)==0)
            {
                printf("\tenter new first name:");
                scanf("%s",p[k].firstname);
                fflush(stdin);
                printf("\tenter new last name:");
                scanf("%s",p[k].lastname);
                fflush(stdin);
                printf("\tenter new birthday:");
                printf("\tDay:");
                scanf("%d",&p[k].birthday.day);
                fflush(stdin);
                printf("\tMonth:");
                scanf("%d",&p[k].birthday.month);
                fflush(stdin);
                printf("\tYear:");
                scanf("%d",&p[k].birthday.year);
                fflush(stdin);
                printf("\tenter new address:");
                scanf("%s",p[k].address);
                fflush(stdin);
                printf("\tenter new email:");
                scanf("%s",p[k].email);
                fflush(stdin);
                printf("\tenter new number:");
                scanf("%s",p[k].number);
                 while(!ValidityOfnum(p[k].number)){
        printf(" *invalid input: please enter numbers (ex:01245874585) *\n");
        printf("\tenter the number:");
        scanf("%s",p[k].number);
    }
                fflush(stdin);

            }
        }
    }
    else if(j==2)
    {
        for (i=0; i<count; i++)
        {
            if(strcasecmp(p[i].lastname,p[count].lastname)==0)
            {
                printf("\tenter first new name:");
                scanf("%s",p[i].firstname);
                fflush(stdin);
                printf("\tenter last new name:");
                scanf("%s",p[i].lastname);
                fflush(stdin);
                printf("\tenter new birthday:");
                printf("\tDay:");
                scanf("%d",&p[i].birthday.day);
                fflush(stdin);
                printf("\tMonth:");
                scanf("%d",&p[i].birthday.month);
                fflush(stdin);
                printf("\tYear:");
                scanf("%d",&p[i].birthday.year);
                fflush(stdin);
                printf("\tenter new address:");
                scanf("%s",p[i].address);
                fflush(stdin);
                printf("\tenter new email:");
                scanf("%s",p[i].email);
                fflush(stdin);
                printf("\tenter new number:");
                scanf("%s",p[i].number);
                while(!ValidityOfnum(p[i].number)){
        printf(" *invalid input: please enter numbers (ex:01245874585) *\n");
        printf("\tenter the number:");
        scanf("%s",p[i].number);}
                fflush(stdin);

            }
        }

    }
    else
    {
        printf("not found");
    }
    back(p);
    main_menu(p);


}
char ValidityOfFname(contact*p)
{
    int error;
    do
    {
        error=0;
        printf("\tenter first name:");
        gets(p[count].firstname);
        fflush(stdin);
        // printf("%s",p[count].number);
        if((*p[count].firstname>='a' && *p[count].firstname<='z')||(*p[count].firstname>='A' && *p[count].firstname<='Z'))
        {
            break;


        }
        else
        {
            printf (" *invalid input: please enter letters*\n");
            error=1;
        }
    }
    while(error==1);
    return(p[count].firstname);
}
void ValidityOfLname(contact*p)
{
    int error;
    do
    {
        error=0;
        printf("\tenter last name:");
        gets(p[count].lastname);
        fflush(stdin);

        if((*p[count].lastname>='a' && *p[count].lastname<='z')||(*p[count].lastname>='A' && *p[count].lastname<='Z'))
        {
            break;


        }
        else
        {
            printf(" *invalid input: please enter letters*\n");
            error=1;
        }
    }
    while(error==1);


}
void ValidityOfemail(contact*p)
{
    int error;
    do
    {
        error=0;
        printf("\tenter email:");
        gets(p[count].email);
        char e[4]= {'@'};
        char c[4]= {'.'};
        if((strstr(p[count].email,e)!=NULL) && (strstr(p[count].email,c)!=NULL))
        {
            break;

        }
        else
        {
            printf(" *invalid input: please enter (ex: valid@hotmail.com)*\n");
            error=1;
        }
    }
    while(error==1);


}
int ValidityOfnum(char valid[])
{
    int i;
        for(i=0;i<strlen(valid);i++){
            if(valid[i]<48 || valid[i]>57){
                return 0;

        }else{
        return 1;}
        }
}


void valid_birthday(contact*p)
{
    printf("\tenter your birth:\n");
    printf("\tDay:");
    scanf("%d",&p[count].birthday.day);
    fflush(stdin);
    printf("\tMonth:");
    scanf("%d",&p[count].birthday.month);
    fflush(stdin);
    printf("\tYear:");
    scanf("%d",&p[count].birthday.year);
    fflush(stdin);
    do
    {
        if(p[count].birthday.day>=1 && p[count].birthday.day<=31)
        {
            if(p[count].birthday.month>=1 && p[count].birthday.month<=12)
            {
                if(p[count].birthday.year>=1000 && p[count].birthday.year<=9999)
                {
                    break;
                }
                else
                {
                    printf(" invalid year input: please enter numbers (ex:1998) ");
                    printf("\t\nYear:");
                    scanf("%d",&p[count].birthday.year);
                    fflush(stdin);
                }
            }
            else
            {
                // error++;
                printf(" invalid months input: please enter numbers from 1 to 12");
                printf("\t\nMonth:");
                scanf("%d",&p[count].birthday.month);
                fflush(stdin);
            }
        }
        else
        {
            //  error++;
            printf(" invalid day input: please enter numbers (ex: from 1 to 31)");
            printf("\t\nDay:");
            scanf("%d",&p[count].birthday.day);
            fflush(stdin);

        }
    }
    while(1);
}
void sortbirth(contact*p)
{
    contact temp,temp1,temp2;
    int i,j;
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if(p[i].birthday.year>p[j].birthday.year )
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;

            }
            if( p[i].birthday.year==p[j].birthday.year && p[i].birthday.month>p[j].birthday.month)
            {
                temp1=p[i];
                p[i]=p[j];
                p[j]=temp1;

            }
            if( p[i].birthday.year==p[j].birthday.year && p[i].birthday.month==p[j].birthday.month && p[i].birthday.day>p[j].birthday.day)
            {
                temp2=p[i];
                p[i]=p[j];
                p[j]=temp2;
            }

        }
    }
    printf("\nYour contacts are sorted by birthday:\n\n");
    for( int k = 0; k < count; k++ )
    {
        printf("\n(%d)\n", k+1);
        printf("\tFIRSTNAME:%s\n\tLASTNAME:%s\n\tBIRTHDAY:%d/%d/%d\n\tADDRESS:%s\n\tEMAIL:%s\n\tNUMBER:%s\n",p[k].firstname,p[k].lastname,p[k].birthday.day,p[k].birthday.month,p[k].birthday.year,p[k].address,p[k].email,p[k].number);
        // printf("\n\n");

    }


    back(p);

}
