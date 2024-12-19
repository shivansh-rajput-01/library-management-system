#include<stdio.h>
#include<conio.h>
#include<string.h>

struct book{
    int bookId;
    char title[20];
    char authorName[20];
    int publicationYear;
};

void addBooks(struct book *, int *,int*);


void viewBooks(struct book *, int );


void searchBooks(struct book * , int , int);


int deleteBooks(struct book * , int);


void sortBooks(struct book * , int);


void capitalString1(char *);


int main(){

    int choice;
    struct book lib[100];
    int repeat = 1;
    int  noOfEnteries = 0;
    int i = 0;//for tracking upto what index structure is filled so that next time when function is called enteries are filled in next locations not overwriting the previous ones
    int n = 0;

        printf("====Library Management System====\n");
        printf("1.Add new books\n2.View the list of books\n3.Search for books by title or author\n4.Delete books from the system\n5.Sort the books based on different criteria (title, author, or publication year)\n");

    while(repeat == 1){
        printf("Enter your choice:");
        scanf("%d",& choice);
        printf("\n");
        if(choice == 1){

            addBooks(lib,&noOfEnteries,&i);
            n = noOfEnteries;

        }else if (choice == 2){

            viewBooks(lib,n);

        }else if (choice == 3){

            int option;
            printf("Enter 0 to seach by title\nEnter 1 to search by Author Name:");
            scanf("%d",&option);
            getchar();
            searchBooks(lib , option , noOfEnteries);

        }else if (choice == 4){

            noOfEnteries = deleteBooks(lib , noOfEnteries);
            n = i = noOfEnteries;

        }else if (choice == 5){
            
            sortBooks(lib , noOfEnteries);
            
        }
        printf("Enter 1 if you want to do more operations and 0 to stop:");
        scanf("%d",&repeat);
    }

    printf("Thank you!");

    return 0;

}

void addBooks(struct book lib[], int * noOfEnteries,int * i){
    int enterAnother = 1;
    while(enterAnother == 1){
         if (*i >= 100) { // Ensure we do not exceed the array bounds
            printf("Library is full. Cannot add more books.\n");
            break;
        }
        printf("Enter book ID:");
        scanf("%d",&lib[*i].bookId);
        getchar();
        printf("Enter book title:");
        fgets(lib[*i].title, sizeof(lib[*i].title), stdin);
        lib[*i].title[strcspn(lib[*i].title , "\n")] = '\0';
        printf("Enter author name:");
        fgets(lib[*i].authorName, sizeof(lib[*i].authorName), stdin);
        lib[*i].authorName[strcspn(lib[*i].authorName , "\n")] = '\0';
        printf("Enter publication year:");
        scanf("%d",&lib[*i].publicationYear);
        getchar();
        (*i)++;
        printf("Enter 1 for more books or 0 for exit:");
        scanf("%d",&enterAnother);
        getchar();
        printf("\n");
    }
    * noOfEnteries = *i;
}

void viewBooks(struct book * lib, int n){
    int i;
    printf("|%-8s|%-25s|%-25s|%-7s\n","Book ID" , "Title" , "Author" , "Publication year");
    for(i = 0 ; i < n ; i++){
        printf("|%-8d|%-25s|%-25s|%-7d\n",lib[i].bookId,lib[i].title,lib[i].authorName,lib[i].publicationYear);
        printf("\n");
    }
    if(n == 0){
        printf("_____________No Books Founded!_______________\n");
        printf("\n");
    }
} 

void searchBooks(struct book * lib , int n , int noOfEnteries){
    int a = 0;//for storing status of whether writer or author is find or not
    int i;
    char search[20];

    if(n == 0){
        printf("Enter the name of title:");
        fgets(search,sizeof(search),stdin);
    }else if(n == 1){
        printf("Enter the name of Author Name:");
        fgets(search,sizeof(search),stdin);
    }
    search[strcspn(search , "\n")] = '\0';
    printf("|%-8s|%-25s|%-25s|%-7s\n","Book ID" , "Title" , "Author" , "Publication year");

    for(i = 0 ; i < noOfEnteries ; i++){

        if(n == 0){

            if(strcmp(search , lib[i].title) == 0){

                printf("|%-8d|%-25s|%-25s|%-7d\n",lib[i].bookId,lib[i].title,lib[i].authorName,lib[i].publicationYear);
                a++;

            }

        }else if(n == 1){

            if(strcmp(search , lib[i].authorName) == 0){

                printf("|%-8d|%-25s|%-25s|%-7d\n",lib[i].bookId,lib[i].title,lib[i].authorName,lib[i].publicationYear);
                a++;

            }

        }
    } 
    
    if(a == 0){

        if(n == 0){
            printf("No record found for title: %s",search);
        }else if(n == 1){
            printf("No record found for author name: %s",search);
        }
       
    }
} 

int deleteBooks(struct book * lib , int noOfEnteries){
    printf("Enter 1 to delete by book id\n");
    printf("Enter 2 to delete by title\n");
    printf("Enter 3 to delete by Author name:");
    int n;
    scanf("%d",&n);
    getchar();
    int id;
    char t[20];

    if(n == 1){

        printf("Enter book id:");
        scanf("%d",&id);
        getchar();

    } else if(n == 2){

        printf("Enter title:");
        fgets(t , sizeof(t) , stdin);

    } else if(n == 3){

        printf("Enter the Author Name:");
        fgets(t , sizeof(t) , stdin);

    }
    t[strcspn(t , "\n")] = '\0';

    int flag = 0;
    int i;
    int index[noOfEnteries];
    int a = 0;//for counting index of index[]

    for(i = 0 ; i < noOfEnteries ; i++){//loop for storing deleted books indexes

        if(n == 1){
            if(lib[i].bookId == id){

                index[a] = i;
                a++;
                flag = 1;

            }
        }else if(n == 2){
            if(strcmp(lib[i].title , t) == 0){

                index[a] = i;
                a++;
                flag = 1;

            }
        }else if(n == 3){
            if(strcmp(lib[i].authorName , t) == 0){

                index[a] = i;
                a++;
                flag = 1;

            }
        }

    }
    if(flag == 0){
        printf("No book to be deleted is founded");
    }else if(flag == 1){
        for(int var1 = 0 ; var1 < a ; var1++){
            for(int var2 = index[var1] ; var2 < noOfEnteries ; var2++){
                //arr[var2] = arr[var2 + 1]
                lib[var2].bookId = lib[var2 + 1].bookId;
                strcpy(lib[var2].title , lib[var2 + 1].title);
                strcpy(lib[var2].authorName , lib[var2 + 1].authorName);
                lib[var2].publicationYear = lib[var2 + 1].publicationYear;
            }
            noOfEnteries--;
        }
    }

    return noOfEnteries;

} 

void sortBooks(struct book * lib , int noOfEnteries){

    int n;

    printf("Enter 1 to sort by publication year\n");
    printf("Enter 2 to sort by title\n");
    printf("Enter 3 to sort by Author Name:");

    scanf("%d",&n);

    int i , j;
    int id , minYear;
    char t1[20] ,t2[20];
    int loc = 0;

    for(i = 0 ; i < noOfEnteries - 1 ; i++){
        loc = i;
        minYear = lib[loc].publicationYear;
        strcpy(t1 , lib[loc].title);
        strcpy(t2 , lib[loc].authorName);

        for(j = i + 1 ; j < noOfEnteries ; j++){
        minYear = lib[loc].publicationYear;
        strcpy(t1 , lib[loc].title);
        strcpy(t2 , lib[loc].authorName);

            if(n == 1){

                if(minYear > lib[j].publicationYear){

                    loc = j;

                }

            }else if(n == 2){

                char T1[20];
                strcpy(T1 , t1);
                capitalString1(T1);
                char compare[20];
                strcpy(compare , lib[j].title);
                capitalString1(compare);
                if(strcmp(T1 , compare) > 0){

                    loc = j;

                }

            }else if(n == 3){

                char compare[20];
                strcpy(compare , lib[j].authorName);
                capitalString1(compare);
                char T2[20];
                strcpy(T2 , t2);
                capitalString1(T2);

                if(strcmp(T2 , compare) > 0){

                    loc = j;

                }

            }
        }

        struct book temp;
        temp = lib[loc];
        lib[loc] = lib[i];
        lib[i] = temp;

    }
    if(noOfEnteries > 0){
    printf("Sorted successfully\n");
    }else if(noOfEnteries == 0){
    printf("No element in library cannot sort!\n");
    }

} 

void capitalString1(char * compare){
    int i = 0;
    while(compare[i] != '\0'){
        if(compare[i] >= 97 && compare[i] <= 122){
            compare[i] = compare[i] - 32;
        }
        i++;
    }
} 