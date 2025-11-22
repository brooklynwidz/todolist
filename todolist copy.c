#include <stdio.h>
#include <string.h>

#define MAX_TASK 100

struct Task
{
    int id;
    char title[50];
    int completed; // 0 = not done, 1 = done
};
struct Task tasks[MAX_TASK];
int count = 0;

void menu();
void addTask();
void viewTask();
void markCompleted();
void deleteTask();
void saveTasksToFile();
void loadTasksFromFile();

int i;


int main()
{
    loadTasksFromFile();
    menu();
}
void menu()
{

    while (count < 100)
    {
        printf("===== TO-DO LIST =====\n1. Add Task\n2. View Tasks\n3. Mark Task Completed\n4. Delete Task\n5. SaveTask\n6. New Task List\n7. Exit\n\n\n");
        int choice;
        printf("enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            addTask();
    

        }
        else if (choice == 2)
        {
            viewTask();
        }
        else if (choice == 3)
        {
            markCompleted();
        }
        else if (choice == 4)
        {
            deleteTask();
        }
        else if (choice == 5)
        {
            saveTasksToFile();
        }
        else if (choice == 6){
            count = 0;
            saveTasksToFile();
        }
        else if (choice == 7)
        {
            printf("Program over");
            break;
        }
        
        else
        {
            printf("Enter a valid choice\n");
            // break;
        }

    }
}

void addTask()
{

    if (count >= MAX_TASK)
    {
        printf("Task limit reached! cannot add more.\n");
        return;
    }

    tasks[count].id = count + 1;
    tasks[count].completed = 0;

    printf("Enter the Title: ");
    scanf(" %[^\n]", tasks[count].title);
    count++;



    printf("task added succesfully\n\n\n\n");
}

void viewTask()
{
    // printf("%d", count);
    int k = 0;
    printf("\n===== YOUR TASKS =====\n");
    while (k < count)
    {
        printf("ID: %d | Title: %s | Status: %s\n ", tasks[k].id, tasks[k].title, (tasks[k].completed == 0) ? "Not Done" : "Done");
        k++;
    }
    printf("\n\n\n");
}

void markCompleted()
{
    int id;
    printf("\n");
    printf("Enter the id which you want to mark as completed: ");
    scanf("%d", &id);
    int k = 0;
    if (id < 1 || id > count)
    {
        printf("please enter a valid id..");
        markCompleted();
    }
    else
    {
        while (k < count)
        {
            if (id == tasks[k].id)
            {
                tasks[k].completed = 1;
                printf("\n Marked as done..\n\n");
                break;
            }
            k++;
        }
    }
}

void deleteTask()
{
    int id;
    printf("\nEnter the id of Task which you want to Delete: ");
    scanf("%d", &id);
    if (id < 1 || id < count)
    {
        printf("invalid id please enter valid id.");
        deleteTask();
    }
    else
    {
        for (int i = id - 1; i < count; i++)
        {
            tasks[i] = tasks[i + 1];
            tasks[i].id = i + 1;
        }
    }

    count--;
    printf("\nTask deleted successfully..\n\n");
    viewTask();
}


void saveTasksToFile(){
    FILE *fp;
    fp = fopen("tasksave.csv","w");
    fprintf(fp,"ID\tTask\tStatus\n");
    for (i = 0;i<count;i++){
        fprintf(fp,"%d\t%s\t%s\n",tasks[i].id,tasks[i].title,tasks[i].completed ? "Done" : "NOT done" );
    }
    fclose(fp);
}


void loadTasksFromFile() {
    FILE *fp = fopen("tasksave.csv", "r");

    if (fp == NULL) {
        printf("No saved file found. Starting fresh...\n");
        return;
    }

    char status[20];
    char header[100];

    // read and ignore header line
    fgets(header, sizeof(header), fp);

    count = 0; // reset current tasks before loading

    while (fscanf(fp, "%d\t%[^\t]\t%[^\n]\n",
                  &tasks[count].id,
                  tasks[count].title,
                  status) == 3) {

        tasks[count].completed = (strcmp(status, "Done") == 0) ? 1 : 0;
        count++;
    }

    fclose(fp);

    printf("\nTasks successfully loaded from file!\n\n");
}