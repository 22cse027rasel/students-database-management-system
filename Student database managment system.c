#include<stdio.h>
#include<conio.h>
void addstudent();
void studentrecord();
void searchstudent();
void Delete();

struct student
{
    char first_name[20];
    char last_name[20];
    int Class;
    char group[20];
    int roll_no;
    char vill[20];
    int phone;
};

void main()
{
    int choice;
    while(choice != 5)
    {
        printf("\n\t\t\t=======STUDENT DATABASE MANAGEMENT SYSTEM=======");
        printf("\n\n\n\t\t\t\t  1. Add Student\n");
        printf("\t\t\t\t  2. Student Records\n");
        printf("\t\t\t\t  3. Search Students\n");
        printf("\t\t\t\t  4. Delete Student\n");
        printf("\t\t\t\t  5. Exit\n");
        printf("\t\t\t\t  ___________________________\n");
        printf("\t\t\t\t  ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            addstudent();
            break;
        case 2:
            studentrecord();
            printf("\t\t\t\tPress any key to exit\n");
            getch();
            break;
        case 3:
            searchstudent();
            printf("\n\t\t\t\tPress any key exit\n");
            getch();
            break;
        case 4:
            Delete();
            printf("\n\t\t\t\tPress any key exit\n");
            getch();
            break;
        }
    }
}

void addstudent()
{
   char another;
   FILE *fp;
   struct student info;

   do
   {
       printf("\t\t\t\t=====Add Student info=====\n\n\n");
       fp = fopen("student_info.txt", "a");

       printf("\n\t\t\tEnter first name      : ");
       scanf("%s", &info.first_name);
       printf("\t\t\tEnter last name       : ");
       scanf("%s", &info.last_name);
       printf("\t\t\tEnter class (digit)   : ");
       scanf("%d", &info.Class);
       printf("\t\t\tEnter group           : ");
       scanf("%s", &info.group);
       printf("\t\t\tEnter roll number     : ");
       scanf("%d", &info.roll_no);
       printf("\t\t\tEnter address         : ");
       scanf("%s", &info.vill);
       printf("\t\t\tEnter phone number    : ");
       scanf("%d", &info.phone);
       printf("\t\t\t___________________\n");

       if(fp == NULL)
       {
           printf("\t\t\tFile can't open !!\n");
       }
       else
       {
            printf("\t\t\tThe student has been successfuly added to the record file.\n");
       }
       fwrite(&info, sizeof(struct student), 1, fp);
       fclose(fp);

       printf("\n\t\t\tPress   y   for add next student  : ");
       scanf("%s", &another);
   }while(another == 'y');
}

void studentrecord()
{
    FILE *fp;
    struct student info;
    fp = fopen("student_info.txt", "r");
    printf("\n\t\t\t\t=====Student Records=====\n");

    if(fp == NULL)
    {
         printf("\t\t\tFile is empty !!\n");
    }

    else
    {
        printf("\t\t\t\t");
    }
    while(fread(&info, sizeof(struct student), 1, fp))
    {
        printf("\n\t\t\t\tStudent name   : %s %s", info.first_name, info.last_name);
        printf("\n\t\t\t\tClass          : %d", info.Class);
        printf("\n\t\t\t\tGroup          : %s", info.group);
        printf("\n\t\t\t\tRoll no        : %d", info.roll_no);
        printf("\n\t\t\t\tAddress        : %s", info.vill);
        printf("\n\t\t\t\tPhone number   : %d", info.phone);
        printf("\n\t\t\t\t___________________________\n");
    }
    fclose(fp);
}

void searchstudent()
{
    int roll_no, Class, found = 1;
    FILE *fp;
    struct student info;
    fp = fopen("student_info.txt", "r");

    printf("\t\t\t\t======Search Student=======\n\n\n");
    printf("\t\t\tEnter class : ");
    scanf("%d", &Class);
    printf("\t\t\tEnter roll_no : ");
    scanf("%d", &roll_no);
    while(fread(&info, sizeof(struct student), 1, fp))
    {
        if(info.roll_no == roll_no && info.Class == Class)
        {
            found = 0;
            printf("\n\t\t\t\tStudent name   : %s %s", info.first_name, info.last_name);
            printf("\n\t\t\t\tClass          : %d", info.Class);
            printf("\n\t\t\t\tGroup          : %s", info.group);
            printf("\n\t\t\t\tRoll no        : %d", info.roll_no);
            printf("\n\t\t\t\tAddress        : %s", info.vill);
            printf("\n\t\t\t\tPhone number   : %d", info.phone);
            printf("\n\t\t\t\t___________________________\n");
        }
    }
    if(found)
        printf("\n\t\t\tRecord not found !!\n");

    fclose(fp);
}

void Delete()
{
    int roll_no, Class, found = 0;
    FILE *fp, *fp1;
    struct student info;

   printf("\t\t\t\t=====Delete Student Record=====\n\n\n");
   fp = fopen("student_info.txt", "r");
   fp1 = fopen("temp.txt", "w");
   printf("\t\t\tEnter class : ");
   scanf("%d", &Class);
   printf("\t\t\tEnter roll no : ");
   scanf("%d", &roll_no);
   while(fread(&info, sizeof(struct student), 1, fp))
   {
       if(info.roll_no == roll_no && info.Class == Class)
       {
            found = 1;
       }
       else
       {
           fwrite(&info, sizeof(struct student), 1, fp1);
       }
   }
   fclose(fp);
   fclose(fp1);

   if(found)
   {
       remove("student_info.txt");
       rename("temp.txt", "student_info.txt");
       printf("\n\t\t\tRecord deleted successfully\n");
   }
   else
   {
        printf("\n\t\t\tRecord not found !!\n");
   }
}
