#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#define LINE_MAX 1024

using namespace std;

struct node
{
    int burst;
    int arrival;
    int priority;
    int index;
    struct node *next;
};
string toString(double x)
{
    stringstream ss;
    ss << x;
    return ss.str();
}
void my_swapp(struct node *node_1, struct node *node_2)
{
    int b, a, p, x;
    b = node_1->burst;
    a = node_1->arrival;
    p = node_1->priority;
    x = node_1->index;

    node_1->burst = node_2->burst;
    node_1->arrival = node_2->arrival;
    node_1->priority = node_2->priority;
    node_1->index = node_2->index;
    node_2->burst = b;
    node_2->arrival = a;
    node_2->priority = p;
    node_2->index = x;
}

struct node *createnode(int b, int a, int p, int x)
{
    struct node *temp = NULL;
    temp = (struct node *)malloc(sizeof(node));
    temp->burst = b;
    temp->arrival = a;
    temp->priority = p;
    temp->index = x;
    temp->next = NULL;
    return temp;
}
struct node *insertback(struct node *header, int b, int a, int p, int x)
{
    struct node *temp = (createnode(b, a, p, x));
    struct node *findback;
    if (header == NULL)
    {
        header = temp;
        return header;
    }
    findback = header;
    while (findback->next != NULL)
        findback = findback->next;
    findback->next = temp;
    return header;
}
void my_swapFCFS(struct node *node_1, struct node *node_2)
{
    int b, a, p, x;
    b = node_1->burst;
    a = node_1->arrival;
    p = node_1->priority;
    x = node_1->index;

    node_1->burst = node_2->burst;
    node_1->arrival = node_2->arrival;
    node_1->priority = node_2->priority;
    node_1->index = node_2->index;
    node_2->burst = b;
    node_2->arrival = a;
    node_2->priority = p;
    node_2->index = x;
}

void writeToFile(string n)
{
    ofstream write_file("output.txt");

    if (!write_file)
    {
        write_file.open("output.txt");
        write_file << n << endl;

        write_file.close();
        cout << "file has been updated ! \n";
    }
    else
    {
        write_file << n << endl;
        write_file.close();
        cout << "file has been updated ! \n";
    }
}


// read from file
struct node *readFile(struct node *head) // reading file
{

    FILE *fp;
    char line[LINE_MAX];

    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        cout << " could not read file !" << endl;
        return 0;
    }
    int x = 1;
    while (fgets(line, LINE_MAX, fp) != NULL)
    {
        int num[3];
        sscanf(line, "%d:%d:%d\n", &num[0], &num[1], &num[2]);
        // printf("num1=%u num2=%u num3=%u\n",num[0],num[1],num[2]);
        //  cout<<num[0]<<" "<<num[1]<<" "<<num[2]<<" \n";
        head = insertback(head, num[0], num[1], num[2], x);
        x = x + 1;
    }
    fclose(fp);

    return head;
}
int size(struct node *header)
{
    int x = 0;
    while (header != NULL)
    {
        x++;
        header = header->next;
    }
    return x;
}
void display(struct node *header)
{
    if (header == NULL)
    {
        cout << " linklist is empty \n";
    }

    struct node *temp = header;
    while (temp != NULL)
    {
        cout << temp->burst << " " << temp->arrival << " " << temp->priority << " index " << temp->index << " --> ";
        temp = temp->next;
    }
    cout << endl;
}
struct node *addprocess(struct node *head)
{
    int x = size(head);
    while (true)
    {
        char c;
        cout << "\n Do you want to add a process?\n press Y to access and any key to decline: ";
        cin >> c;
        if (c == 'y' || c == 'Y')
        {
            x += 1;
            int b, a, p;
            cout << "Enter burst Time: ";
            cin >> b;
            cout << "Arival time: ";
            cin >> a;
            cout << "Enter Priority: ";
            cin >> p;
            head = insertback(head, b, a, p, x);
        }
        else
        {
            display(head);
            return head;
        }
    }
}

void ShortestFirst_P(struct node *head)
{
    int sz = size(head);
    struct node *temp = NULL;
    struct node *temp1 = NULL;
    bubble_sortFCFS(head);

    //	display(head);

    std::string output = "  \nScheduling Method: Shortest Job First ( Premtive )  \n Process Waiting Times: \n";

    int wait = 0;
    int keeptrack = 0;
    double sum = 0, tsum = 0;
    double avg;
    int time = 0;
    int a, b, c, p, i;
    a = head->arrival;
    b = head->burst;
    p = head->priority;
    i = head->index;
    head = head->next;
    // display(head);
    bool check = true;
    do
    {
        // cout<<head->arrival;
        if (time == head->arrival && b > head->burst)
        {
            check = false;
        }
        else if (b == 0)
        {
            output = output + "P" + toString(i) + ": " + toString(0) + " ms \n";
            check = false;
        }
        else
        {
            time += 1;
            b -= 1;
            keeptrack += time;
            // display(head);
        }

    } while (check == true);
    sum += time;

    bubble_sortshortNP(head);
    // cout<<time<<" "<<b<<"\n";
    if (b != 0)
        head = insertback(head, b, a, p, i);
    // display(head);
    int getburst;
    while (head != NULL)
    {
        // cout<<head->arrival;
        getburst = head->burst;

        if (getburst != -1)
        {
            cout << head->burst;
            if (time == head->arrival && b > head->burst)
            {
                // cout<<"intdsfsd";
                head = insertback(head, head->burst, head->arrival, head->priority, head->index);
                head = head->next;
                getburst = 0;
            }
            else if (head->burst == 0)
            {
                output = output + "P" + toString(head->index) + ": " + toString(time - head->arrival) + " ms \n";
                display(head);
                // cout<<"intdsfsd";
                getburst = 0;
                head = head->next;
            }
            else
            {
                time += 1;
                head->burst -= 1;
                keeptrack += time;
                // display(head);

                getburst -= 1;
                // cout<<getburst<<" ";
            }
        }
        sum += time;
    }

    // cout<<"sum"<<sum<<" "<<wait;
    avg = sum / sz;
    output = output + "Average Waiting Time:  " + toString(avg) + " ms \n";
    cout << output;
    writeToFile(output);
}

void ShortestFirst_NP(struct node *head)
{
    int sz = size(head);
    struct node *temp = NULL;
    struct node *temp1 = NULL;
    bubble_sortFCFS(head);

    //display(head);

    std::string output = "  \nScheduling Method: Shortest Job First ( Non-Premtive ) \n Process Waiting Times: \n";

    int wait = 0;
    int keeptrack = 0;
    double sum = 0, tsum = 0;
    double avg;

    while (head != NULL)
    {

        output = output + "P" + toString(head->index) + ": " + toString(keeptrack) + " ms \n";
        keeptrack += head->burst - head->arrival;
        wait += head->burst - head->arrival;
        sum += wait;
        break;
    }
    head = head->next;
    bubble_sortshortNP(head);
    //display(head);

    cout << "\n"
         << sum;
    while (head != NULL)
    {

        if (head->next != NULL)
        {
            sum -= head->arrival;
            output = output + "P" + toString(head->index) + ": " + toString(keeptrack - head->arrival) + " ms \n";
            keeptrack += head->burst;
            wait += head->burst;
            sum += wait;
        }
        else if (head->next == NULL)
        {
            sum -= head->arrival;
            output = output + "P" + toString(head->index) + ": " + toString(keeptrack - head->arrival) + " ms \n";
            keeptrack += head->burst;
            wait += head->burst - head->arrival;
        }

        head = head->next;
    }
    //	cout<<"sum"<<sum<<" "<<wait;
    avg = sum / sz;
    output = output + "Average Waiting Time:  " + toString(avg) + " ms \n";
    cout << output;
    writeToFile(output);
}

int main(void)
{
    cout << "Enter the option below" << endl;

    cout << "1. Scheduling Method" << endl;
    cout << "2. Premtive Mode" << endl;
    cout << "3. Show result" << endl;
    cout << "4. Exit" << endl;

    int option;
    cin >> option;

    if (option == 1)
    {
        cout << "Enter the scheduling method" << endl;
        cout << "1. First come first serve" << endl;
        cout << "2. Shortest Job" << endl;
        cout << "3. Priority Scheduling" << endl;
        cout << "4. Robin Round" << endl;

        int option1;
        cin >> option1;

        if (option1 == 1)
        {
            struct node *head = NULL;
            head = readFile(head);
            head = addprocess(head);
            // display(head);
            firstCFS(head);
        }
        else if (option1 == 2)
        {
            cout << "\n 1-> Non Preemtive Method";
            cout << "\n 2-> preemtive method";
            int a;

            cout << "\n please select the method : ";
            cin >> a;

            switch (a)
            {
            case 1:
            {
                struct node *head = NULL;
                head = readFile(head);
                head = addprocess(head);
                // display(head);
                ShortestFirst_NP(head);
            }
            break;
            case 2:
            {
                struct node *head = NULL;
                head = readFile(head);
                head = addprocess(head);
                // display(head);
                ShortestFirst_P(head);
            }
            break;
            default:
            {
                cout << " it can either be 1 or 2";
            }
            break;
            }
        }
        else if (option1 == 3)
        {
            cout << "\n 1-> Non Preemtive Method";
            cout << "\n 2-> preemtive method";
            int a;

            cout << "\n please select the method : ";
            cin >> a;

            {
            case 1:
            {
                struct node *head = NULL;
                head = readFile(head);
                head = addprocess(head);
                // display(head);
                priority_NP(head);
            }
            break;
            case 2:
            {
                // cord has to be here
            }
            break;
            default:
            {
                cout << "could'n get the algorithm" << endl;
            }
            break;
            }
        }
        else if (option1 == 4)
        {
            cout << "Enter the time quantum ";
            int time_quantum;
            cin >> time_quantum;
        }
    }
    if (option == 2)
    {
        cout << "Premtive Mode" << endl;
    }
    if (option == 3)
    {
        string answer;

        ifstream out("output.txt");

        if (out.is_open())
        {
            while (getline(out, answer))
            {
                cout << answer << endl;
            }
            out.close();
        }
    }
    if (option == 4)
    {
        return 0;
    }
    return 0;
}
