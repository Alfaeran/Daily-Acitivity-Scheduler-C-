#include <iostream>
#include <string>
using namespace std;

struct Schedule
{
    string title;
    string time;
    Schedule *next;

    Schedule(string t, string tm) : title(t), time(tm), next(nullptr) {}
};

void addSchedule(Schedule *&head, string title, string time)
{
    Schedule *newSchedule = new Schedule(title, time);

    if (!head || head->time > time)  // Jika list kosong atau aktivitas baru harus menjadi head
    {
        newSchedule->next = head;
        head = newSchedule;
        return;
    }

    Schedule *temp = head;
    while (temp->next && temp->next->time < time) // Mencari posisi yang tepat untuk menyisipkan
        temp = temp->next;

    newSchedule->next = temp->next;
    temp->next = newSchedule;
}

void deleteSchedule(Schedule *&head, string title)
{
    if (!head)
        return;

    if (head->title == title)
    {
        Schedule *temp = head;
        head = head->next;
        delete temp;
        cout << "Activity has been deleted!\n";
        return;
    }

    Schedule *temp = head;
    while (temp->next && temp->next->title != title)
        temp = temp->next;

    if (temp->next)
    {
        Schedule *toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Activity has been deleted!\n";
    }
    else
    {
        cout << "Activity not found!\n";
    }
}

void ShowSchedules(Schedule *head)
{
    if (!head)
    {
        cout << "You have not a single Planned Activity Today.\n";
        return;
    }
    cout << " Today Activity :\n";
    while (head)
    {
        cout << "- [" << head->time << "] " << head->title << endl;
        head = head->next;
    }
}

void reverseSublistByActivity(Schedule *&head, string startActivity, string endActivity)
{
    if (!head || !head->next)
        return;

    Schedule *startNode = nullptr, *endNode = nullptr, *curr = head;

    while (curr)
    {
        if (curr->title == startActivity && !startNode)
        {
            startNode = curr;
        }
        if (curr->title == endActivity)
        {
            endNode = curr;
        }
        curr = curr->next;
    }

    if (!startNode || !endNode)
    {
        cout << "Activity not Found!\n";
        return;
    }

    Schedule *left = startNode;
    Schedule *right = endNode;

    while (left != right && left->next != right)
    {
        swap(left->title, right->title);
        left = left->next;
        right = right->next;
    }
    swap(left->title, right->title);
}

void showMenu()
{
    cout << "\n===== Daily Activaty Schedule =====\n";
    cout << "======= Menu ========\n";
    cout << "1. Add Your Activity\n";
    cout << "2. Show your Activity Today\n";
    cout << "3. Switch your Activity Today\n";
    cout << "4. Delete Activity\n";
    cout << "5. Exit\n";
    cout << "=============================\n";
    cout << "choose an Option   : ";
}

int main()
{
    Schedule *scheduleList = nullptr;
    int choice;
    string title, time, startActivity, endActivity;

    do
    {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Input Activity: ";
            getline(cin, title);
            cout << "Input Time (HH:MM): ";
            cin >> time;
            addSchedule(scheduleList, title, time);
            cout << "Activity have been added!\n";
            break;
        case 2:
            ShowSchedules(scheduleList);
            break;
        case 3:
            cout << "input the activity that you want to switch: ";
            getline(cin, startActivity);
            cout << "input the activity that you want to switch to: ";
            getline(cin, endActivity);
            reverseSublistByActivity(scheduleList, startActivity, endActivity);
            cout << "Your Daily Activity Schedules have been switched!\n";
            break;
        case 4:
            cout << "Input the activity to delete: ";
            getline(cin, title);
            deleteSchedule(scheduleList, title);
            break;
        case 5:
            cout << "Exiting Daily Activity Schedules...\n";
            break;
        default:
            cout << "Option not available. Please choose a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}
