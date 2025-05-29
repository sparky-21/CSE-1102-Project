#include "new_func.h"


//Defining struct to create linked list
typedef struct events{

   int day;               //To store event day
   int month;             //To store event month
   int year;              //To store event details
   char details[300];     //To store event details
   struct events* next;   //To store address of the next node


}events;                 //Typedefining sturct event as event
events * head = NULL;    //Globally declaring the head node

int event_count=0, len=500;

/*--------------------------------------------------------------------*/
/*----------------------------HELPER FUNCTIONS------------------------*/
/*--------------------------------------------------------------------*/


// Function to save all the information of linked list in the event file
void exit_program(){

    FILE *event_file = fopen("event_file.txt", "w"); //Opening event_file in write mode
    if(event_file==NULL){
        printf("No events file found.\n");
        return;
    }
    events * temp=head, *done;      //Temporary structure pointer to traverse through the linked list
    while(temp!=NULL){
        fprintf(event_file, "Date: %d/%d/%d - Event: %s\n", temp->day, temp->month, temp->year, temp->details);
        done = temp;
        temp = temp->next;
        free(done);       //Freeing the memory of the nodes after printing the data in the file
    }
    fclose(event_file); //Closing event file


    //Courtesy ^_^
    clr;
    printf("------------------------------------------------\n");
    printf("Credit:\n1.Juairia Binte Zaman - 2307086\n2.Lailatunnesa Lamisa - 2307068\n3.Nuzhat Jaman Mity - 2307072\n");
    printf("------------------------------------------------\n");
    exit(0);    //Exiting the program
}



//Function to load data form the existing event file into a linked list so that it becomes easy to add, print and delete events
void load_events(){
    FILE *event_file = fopen("event_file.txt", "r");
    if(event_file==NULL){
        printf("No events file found.\n");
        return;
    }



    events * temp=NULL;

    char line[len];         //To read data from file
    int day, month, year;   //To fetch day, month and year
    char details[300];      //To read event details form file



    while(fgets(line, sizeof(line), event_file)){  //This loop will continue so long there is something to read in the file
        if(sscanf(line, "Date: %d/%d/%d - Event: %[^\n]", &day, &month, &year, details)==4){ //Reading formatted input from file
            events * node = (events*)malloc(sizeof(events));  //Creating new node
            if(!node){
                printf("Memory allocation failed.\n");
                fclose(event_file);
                return;
            }

            node->day= day;
            node->month= month;
            node->year= year;


            strncpy(node->details, details, sizeof(node->details)-1); //Copying the string from details, limiting the size to leave room for the null terminator
            node->details[sizeof(node->details)-1] = '\0'; //Adding null terminator

            node->next = NULL;

            if(head==NULL) head=node; //If the link is empty, the new node will be the head
            else temp->next=node;     //Else, the new node will be linked to the previous one

            temp = node;              //Moving temp to next node
            event_count++;            //Increasing number of events
        }
    }

    fclose(event_file);
}



//Checking if the input date is valid
bool is_valid_date(int day, int month, int year){

    if(month<1 || month>12) return false;
    int days_in_month[] = {31, (year%4==0 && (year%100!=0 || year%400==0))? 29:28,31,30,31,30,31,31,30,31,30,31};
    if(day<1 || day>days_in_month[month-1]) return false;

    return true;
}


//Checking if a day has event
bool has_event(int day, int month, int year){

     events *temp = head;
     while(temp!=NULL){
        if(temp->day==day && temp->month==month && temp->year==year)return true;
        else temp= temp->next;
     }

     return false;
}



/*------------------------------------------------------------------------------*/
/*----------------------------END OF HELPER FUNCTIONS---------------------------*/
/*------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*----------------------------NAVIGATION MENU-------------------------*/
/*--------------------------------------------------------------------*/
void nav_menu(void){
        clr;
        printf("\n.........................WELCOME..........................\n");
        printf("\n================ Smart Academic Calendar =================\n");
        printf("\n1. View Calendar\n");
        printf("2. Add Events\n");
        printf("3. Delete Events\n");
        printf("4. View Notifications\n");
        printf("5. Track Progress\n");
        printf("6. Sayonara!\n");
        printf("\n==========================================================\n");
        printf("Choose an option: ");

        int n;
        scanf("%d",&n);
        switch(n){
            case 1:
                view_cal();
                break;
            case 2:
                add();
                break;
            case 3:
                del();
                break;
            case 4:
                notific();
                break;
            case 5:
                progress_tracker();
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                exit_program();
            default:
                printf("Please choose a valid option (1-6).\n");
        }
        return;
}

/*------------------------------------------------------------------------*/
/*----------------------------VIEW CALENENDER-----------------------------*/
/*------------------------------------------------------------------------*/

void view_cal(void) {
    clr;
    int year, month,days;

    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month(1-12): ");
    scanf("%d", &month);


    //Printing the monthly calender
    char *months[12]={"January","February","March","April","May","June","July","August","September","October","November","December" };

    if(month<1 || month>12){
        printf("Invalid month. Please enter a number between 1 and 12.\n");
        return;
    }


    if(month==2){
        if((year%4==0 && year%100!=0) || (year%400==0))days=29;
        else days = 28;
    }
    else if(month==4 || month==6 || month==9 || month==11)days=30;
    else days=31;



    printf("\n==============================\n");
    printf("       %s, %d\n", months[month - 1], year);
    printf("==============================\n");
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");


    int start =(year-1)*365 + (year-1)/400 + (year-1)/4 - (year-1)/100;
    for(int i=1; i<month; i++){
        if(i==2){
            if((year%4==0 && year%100!=0) || (year%400==0)) start+=29;
            else start += 28;
        }else if(i==4||i==6||i==9||i==11) start+=30;
        else start+=31;
    }
    int day_of_week=(start+1)%7;

    for(int i=0; i<day_of_week; i++)printf("    ");

    for(int i=1; i<=days; i++){
        if(has_event(i, month, year))printf("%3d*",i); //If a day has event, print it with asteric
        else printf("%3d ",i);
        if((i+day_of_week)%7==0)printf("\n");
    }

    printf("\n");


    int option;
    printf("1. View Event on a specific date\n");
    printf("2. Go back to main menu\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    if(option==1){
        int event_day;
        printf("Enter Date: ");
        scanf("%d", &event_day);

        if(event_day>=1 && event_day<=days) view_today(event_day, month, year); //Calling view_today() function for that day
        else printf("Invalid date.\n");

    }else if(option==2) nav_menu();
    else printf("Invalid option.\n");
}


/*--------------------------------------------------------------------*/
/*-----------------------------VIEW EVENTS----------------------------*/
/*--------------------------------------------------------------------*/

void view_today(int day, int month, int year){
    clr;

    bool found=false;
    int event_number=0;

    printf("\nEvents on %d/%d/%d:\n", day, month, year);
    printf("--------------------------------------------------\n");


    //Iterating through linked list to find match
    events * temp = head;
    while(temp!=NULL){
            if(temp->day==day && temp->month==month && temp->year==year){
                found=true;                                                 //If a day matches, counting number of events on that day
                event_number++;
                printf("%d. %s\n", event_number, temp->details);            //Printing matched events serially
            }
            temp=temp->next; //Moving temp to next node
    }

    if(!found)printf("No events found for this date.\n");
    printf("--------------------------------------------------\n");


    //Loop to take input again and again unless the user wants to exit the program
    while(true){
       int op;
       printf("\n1.Go back to main menu\n");
       printf("2.Exit the program\n");
       scanf("%d", &op);
       if(op==1)nav_menu();
       else if(op==2) exit_program();
       else printf("Please enter a valid option: ");
    }
}


/*--------------------------------------------------------------------*/
/*--------------------------------ADD FUNCTION------------------------*/
/*--------------------------------------------------------------------*/

void add(void){
    clr;

    FILE *event_file;
    event_file = fopen("event_file.txt","a");

    if(event_file==NULL){
        printf("Error opening file!\n");
        return;
    }

    int day, month, year;
    char details[len];

    while(true){
        printf("Enter event date:\n");
        printf("Day: ");
        scanf("%d", &day);
        printf("Month(1-12): ");
        scanf("%d", &month);
        printf("Year: ");
        scanf("%d", &year);

        if(!is_valid_date(day,month,year)){
            printf("Invalid Date!");
            return;
        }


        getchar();
        printf("Enter event details: ");
        fgets(details, sizeof(details),stdin);
        details[strcspn(details, "\n")]=0;


        fprintf(event_file, "Date: %d/%d/%d - Event: %s\n", day, month, year, details); //Printing event details in file
        printf("-----------------------------------------\n");
        printf("Event added on %d/%d/%d: %s\n", day, month, year, details);
        printf("-----------------------------------------\n");


        // Adding events to the linked list
        events *node = (events*)malloc(sizeof(events));
        if(!node){
            printf("Memory allocation failed!\n");
            fclose(event_file);
            return;
        }

        node->day = day;
        node->month = month;
        node->year = year;
        strncpy(node->details, details, sizeof(node->details) - 1);
        node->details[sizeof(node->details) - 1] = '\0';
        node->next = NULL;

        if(head == NULL)head = node;
        else{
            events *temp = head;
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = node;
        }


        char choice;
        printf("Do you want to add another event? (y/n): ");
        scanf(" %c", &choice);

        if(choice!='y' && choice!='Y')break; //If the user wants to exit, then break the loop

    }

    fclose(event_file);
    printf("-----------------------------------------\n");
    printf("Events saved to event_file.txt\n");
    printf("-----------------------------------------\n");
    while(true){
       int op;
       printf("\n1.Go back to main menu\n");
       printf("2.Exit the program\n");
       scanf("%d", &op);
       if(op==1)nav_menu();
       else if(op==2) exit_program();
       else printf("Please enter a valid option: ");
    }
}


/*--------------------------------------------------------------------*/
/*----------------------------DELETE EVENTS---------------------------*/
/*--------------------------------------------------------------------*/


void del(void) {
    clr;
    int del_day,del_month,del_year;

    printf("Enter the date to delete events from:\n");
    printf("Day: ");
    scanf("%d", &del_day);
    printf("Month(1-12): ");
    scanf("%d", &del_month);
    printf("Year: ");
    scanf("%d", &del_year);

    if(!is_valid_date(del_day,del_month, del_year)){
        printf("Invalid Input.\n");
        return;
    }
    if(!has_event(del_day, del_month, del_year)){
        printf("----------------------------------------------\n");
        printf("There is no event to delete on %d/%d/%d.\n", del_day, del_month, del_year);
        printf("----------------------------------------------\n");
        return;
    }

    int count=0;
    events * temp=head;

    printf("\nEvents on %d/%d/%d:\n", del_day, del_month, del_year);
    printf("-----------------------------------------------------------------\n");
    while(temp!=NULL){
        if(temp->day==del_day && temp->month==del_month && temp->year==del_year){ //Searching for matched
            printf("%d. %s\n", ++count, temp->details);
        }
        temp = temp->next;
    }
    if(count==0)printf("No events found.\n");
    printf("-----------------------------------------------------------------\n");

    char d_more='y';
    while(d_more=='y' || d_more=='Y'){
        int choice;
        printf("\nEnter the number of the event you want to delete (1-%d): ",count);
        scanf("%d", &choice);

        if(choice<1 || choice>count){
            printf("\nInvalid choice. Try again.\n");
            continue;
        }

        temp=head;
        events *prev=NULL;
        int current=1;
        while(temp!=NULL){
            if(temp->day==del_day && temp->month==del_month && temp->year==del_year){ // Check if the current node matches the specified date


                if(current == choice){
                    if(prev==NULL)head=temp->next; // Updating head to point to the next node
                    else prev->next=temp->next;    // Bypassing the matched node by linking 'prev' to 'temp->next'

                    free(temp);   //Freeing the matched node (deleting)
                    printf("\nEvent deleted successfully.\n");

                }
                current++; //Incrementing 'current' to track the next the matching event
            }
            prev=temp; //Updating prev to the current node
            temp=temp->next; //Moving temp to the next node in the linked list
        }

        count--; //Decrementing the total event count

        if(!count){
            printf("---------------------------------------------\n");
            printf("\nNo more events left to delete on this day.\n");
            printf("---------------------------------------------\n");
            break;
        }

        printf("\nDo you want to delete another event on %d/%d/%d? (y/n): ",del_day,del_month,del_year);
        scanf(" %c", &d_more);
    }
    while(true){
       int op;
       printf("\n1.Go back to main menu\n");
       printf("2.Exit the program\n");
       scanf("%d", &op);
       if(op==1)nav_menu();
       else if(op==2) exit_program();
       else printf("Please enter a valid option: ");
    }
}




/*--------------------------------------------------------------------*/
/*----------------------------NOTIFICATIONS---------------------------*/
/*--------------------------------------------------------------------*/
void notific(void){
    clr;

    //Fetching the current time

    time_t t=time(NULL);
    struct tm *current_time = localtime(&t);

    int day = current_time->tm_mday;
    int month = current_time->tm_mon + 1;
    int year = current_time->tm_year + 1900;

    //If there is an event on that day, call view_today
    if(has_event(day, month, year)){
        printf("Reminder:\n");
        view_today(day, month, year);
    }else{
        printf("---------------------------\n");
        printf("No Notifications for today.\n");
        printf("---------------------------\n");

    }

    while(true){
       int op;
       printf("\n1.Go back to main menu\n");
       printf("2.Exit the program\n");
       scanf("%d", &op);
       if(op==1)nav_menu();
       else if(op==2) exit_program();
       else printf("Please enter a valid option: ");
    }
}


/*--------------------------------------------------------------------*/
/*-------------------------PROGRESS TRACKER---------------------------*/
/*--------------------------------------------------------------------*/
void progress_tracker(void){
    clr;
    printf("1. Add Exam\n2. View Progress\n3. Exit\n");
    int n;
    printf("Enter an option: ");
    scanf("%d", &n);

    switch(n){
        case 1:
            ad_xm();
            break;
        case 2:
            view_progress();
            break;
        default:
            nav_menu();
            break;
    }
    return;
}

/*--------------------------------------------------------------------*/
/*---------------------------ADD EXAM---------------------------------*/
/*--------------------------------------------------------------------*/
void ad_xm(void){
    clr;
    char xm[30], f_xm[30];  // `xm` stores exam name; `f_xm` stores exam name read from file
    float marks, tmarks, f_marks, f_tmarks; // `marks` and `tmarks` store input marks and total marks, `f_marks` and `f_tmarks` store marks read from file
    int flag;  // Input user's choice

    FILE *fp=fopen("exam.txt", "r+");
    if(fp==NULL){
        printf("Error opening file!\n");
        return;
    }

    // Loop to allow multiple entries until the user decides to stop
    while(true){
        printf("Enter name of the exam (use uppercase letters only): ");
        scanf("%s", xm);
        printf("Enter obtained marks: ");
        scanf("%f", &marks);
        printf("Enter total marks: ");
        scanf("%f", &tmarks);

        FILE *temp = fopen("temp_exm.txt", "w");
        if (temp == NULL) {
            printf("Unable to open temporary file.\n");
            fclose(fp);
            return;
        }

        //Rewinding the main file to start reading from the beginning
        rewind(fp);
        bool found=false; // Flag to check if the exam already exists in the file


        // Read data from the main file and copy it to the temporary file
        while(fscanf(fp,"%s %f %f\n", f_xm,&f_marks,&f_tmarks)==3){
            // If the current exam matches the user's input, updating its marks
            if (strcmp(xm, f_xm) == 0){
                marks += f_marks;     // Adding marks to the existing entry
                tmarks += f_tmarks;
                found=true;
                fprintf(temp,"%s %.2f %.2f\n", xm,marks,tmarks);


            }else fprintf(temp,"%s %.2f %.2f\n",f_xm,f_marks,f_tmarks); //Copying the original entry to the temporary file
        }

        // If the exam was not found, adding it as a new entry
        if(!found)fprintf(temp,"%s %.2f %.2f\n",xm,marks,tmarks);

        fclose(fp);
        fclose(temp);

        //Replacing the original file with the updated temporary file
        remove("exam.txt");
        rename("temp_exm.txt", "exam.txt");


        //Prompting the user to continue or exit
        printf("\nDo you want to continue?\n1. Yes\n2. No\n");
        scanf("%d", &flag);
        if(flag==2)break;
        else if(flag!=1){
            printf("Invalid Option.\n");
            break;
        }

        // Reopening the main file for further updates
        fp=fopen("exam.txt", "r+");
        if(fp==NULL){
            printf("Error reopening file!\n");
            return;
        }
    }

    fclose(fp);
    progress_tracker();
    return;
}
/*--------------------------------------------------------------------*/
/*-----------------------------VIEW PROGRESS--------------------------*/
/*--------------------------------------------------------------------*/
void view_progress(void){
    clr;
    char xm[30], src[30];
    float marks, tmarks;
    bool found = false;

    FILE *fp=fopen("exam.txt","r");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name of the exam (use uppercase letters only): ");
    scanf("%s", src);

    while(fscanf(fp, "%s %f %f", xm, &marks, &tmarks)==3){
        if(strcmp(src, xm)==0){
            if(tmarks==0){
                printf("Total marks cannot be zero for %s.\n", src);
                fclose(fp);
                return;
            }

            //Calculating the percentage of marks
            float percentage=(marks/tmarks)*100;
            int progress=(int)percentage;


            //Displaying progress details
            printf("\n");
            for(int i=0; i<=100; i++)printf("-");
            printf("\n");
            printf("Exam: %s\n", src);
            printf("Obtained Marks: %.1f / %.1f\n", marks, tmarks);
            printf("Percentage: %.1f%%\n", percentage);

            //Generating the progress bar
            printf("Progress:\n");
            printf("[");
            for(int i=0; i<progress; i++)printf("#");
            for(int i=progress; i<100; i++)printf(".");
            printf("] %.1f%%\n", percentage);
            printf("\n");
            for(int i=0; i<=100; i++)printf("-");
            printf("\n");

            found=true; //Setting flag to true since the record was found
            break;
        }
    }

    if (!found) {
        printf("\n-----------------------------------------\n");
        printf("Sorry, no record found for '%s'.\n", src);
        printf("-----------------------------------------\n");
    }

    fclose(fp);

    int flag;
    printf("\nDo you want to continue?\n1. Yes\n2. No\n");
    scanf("%d", &flag);

    if(flag==1)return view_progress();
    else progress_tracker();

    return;
}


