#include <iostream>
#include <string>

using namespace std;

// Структура элемента списка
struct Node {
    string name;
    int age;
    double score;
    Node* next;

    Node(string n, int a, double s) : name(n), age(a), score(s), next(nullptr) {}
};

// Класс односвязного списка
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Добавление элемента в начало списка
    void addToFront(string name, int age, double score) {
        Node* newNode = new Node(name, age, score);
        newNode->next = head;
        head = newNode;
    }

    // Добавление элемента в конец списка
    void addToEnd(string name, int age, double score) {
        Node* newNode = new Node(name, age, score);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    // Добавление элемента после указанного имени
    void addAfter(string target, string name, int age, double score) {
        Node* temp = head;
        while (temp && temp->name != target) temp = temp->next;
        if (temp) {
            Node* newNode = new Node(name, age, score);
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Добавление элемента перед указанным именем
    void addBefore(string target, string name, int age, double score) {
        if (!head) return;
        if (head->name == target) {
            addToFront(name, age, score);
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->name != target) temp = temp->next;
        if (temp->next) {
            Node* newNode = new Node(name, age, score);
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Удаление элемента по имени
    void removeByName(string name) {
        if (!head) return;
        if (head->name == name) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->name != name) temp = temp->next;
        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    // Вывод списка
    void printList() {
        Node* temp = head;
        while (temp) {
            cout << "Имя: " << temp->name << ", Возраст: " << temp->age << ", Оценка: " << temp->score << endl;
            temp = temp->next;
        }
    }

    // Деструктор для освобождения памяти
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Основная функция
int main() {
    LinkedList list;

    list.addToFront("Алиса", 20, 85.5);
    list.addToEnd("Борис", 22, 90.2);
    list.addAfter("Алиса", "Виктор", 21, 88.0);
    list.addBefore("Борис", "Галина", 23, 92.1);

    cout << "Список после добавлений:" << endl;
    list.printList();

    list.removeByName("Виктор");
    cout << "\nСписок после удаления Виктора:" << endl;
    list.printList();

    return 0;
}
