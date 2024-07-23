#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    // FILE HANDLING CODE
    FILE *fp,*ft;
    int choice;
    char another;

    // CREATING A STRUCTURE FOR BOOKS
    struct books
    {
        char name[20];
        float price;
        int pages;
        int s_no;           //SERIAL NUMBER
        char month[10];     //MONTH OF BOOK ISSUE
    };
    struct books b;         //ASSIGNING A VARIABLE TO STRUCTURE
    char bookname[20];      //TO COMPARE THE NAME OF ENTERED BOOK NAME AND EXISTING BOOK
    long int recsize;

    // OPENING THE FILE
    fp=fopen("(file name)","rb+");
        if(fp==NULL)
        {
            // IF FILE DOES NOT OPEN IN READ MODE THEN OPENING IT IN WRITE MODE SO THAT THE FILE IS CREATED
            fp=fopen("(file name)","wb+");
            if(fp==NULL)
            {
                printf("File cannot open");
                exit(0);
            }
        }

// ASSIGNING VARIABLE RECSIZE ITS DESERVED VALUE
recsize = sizeof(b);

// NOW HAVE TO CREATE THE MAIN CODE OF SWITCH

// PRINTING THE MENU FOR THE USER
printf("1.Add Records\n");
printf("2.List Records\n");
printf("3.Modify Records\n");
printf("4.Delete Records\n");
printf("5.Exit\n");
fflush(stdin);
// SCANING THE OPTION SELECTED BY THE USER
printf("Enter your choice.\n");
scanf("%d",&choice);

// CODING THE SWITCH CASE
switch(choice)
{
    case 1:

// FOR CASE ONE WE NEED THE CURSOR AT THE END OF THE FILE
    fseek(fp,0,SEEK_END);

// WE NEED TO REPEAT THE PROCESS OF ADDING NEW ENTRIES UNTIL THE DATA IS OVER
    another = 'Y';
    while(another == 'Y')
    {
        printf("Enter the name, price, pages, serial number and month of issue of the book.\n");
        scanf("%s %f %d %d %s",b.name,&b.price,&b.pages,&b.s_no,b.month);
        fwrite(&b,recsize,1,fp);
        printf("Enter another record(Y/N)\n");
        fflush(stdin);
        scanf("%c",&another);
    }
    break;  // SO THAT IT DOESNT GO ONTO THE NEXT CASE WITHOUT INPUT FROM USER

    case 2:
    rewind(fp);
    while(fread(&b,recsize,1,fp)==1)
    printf("%s %f %d %d %s",b.name,b.price,b.pages,b.s_no,b.month);
    break;

    case 3:
    printf("Enter the name of the book you want to modify.\n");
    scanf("%s",bookname);
    rewind(fp);
    another = 'Y';
    while(another == 'Y')
    {
        while(fread(&b,recsize,1,fp)==1)
        {
            if(strcmp(bookname,b.name)==0)
            {
                printf("Enter new name, price, pages, serial number, month of issue.\n");
                scanf("%s %f %d %d %s",b.name,&b.price,&b.pages,&b.s_no,b.month);
                fseek(fp,-recsize,SEEK_CUR);
                fwrite(&b,recsize,1,fp);
                break;
            }
        }
    printf("Do you want to modify another record(Y/N)\n");
    fflush(stdin);
    scanf("%c",&another);
    }
    break;

    case 4:
    another='Y';
    while(another=='Y')
    {
        printf("Enter the name of the book you want delete.\n");
        scanf("%s",bookname);
        ft=fopen("","wb");
        rewind(fp);
        while(fread(&b,recsize,1,fp)==1)
        {
            if(strcmp(bookname,b.name)!=0)
            fwrite(&b,recsize,1,ft);
        }
        fclose(fp);
        fclose(ft);
        remove("(file name)");
        rename("(file name)","(file name)");
        fp=fopen("(file name)","rb");
        printf("want to delete another record(Y/N)\n");
        fflush(stdin);
        scanf("%c",&another);
    }
    break;

    case 5:
    fclose(fp);
    exit(0);

}while(choice!=0);
}