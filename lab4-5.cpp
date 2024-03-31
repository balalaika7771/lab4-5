#include <iostream>
#include <fstream>
#include <sstream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class DoublyCircularLinkedList {
private:
    Node* head;

    Node* createNode(int data) {
        return new Node(data);
    }

public:
    DoublyCircularLinkedList() : head(nullptr) {}

    ~DoublyCircularLinkedList() {
        clear();
    }

    void insertAtHead(int data) {
        Node* newNode = createNode(data);
        if (!head) {
            head = newNode;
            head->next = head->prev = head;
        }
        else {
            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }

    void deleteFromTail() {
        if (!head) return;
        if (head == head->next) {
            delete head;
            head = nullptr;
        }
        else {
            Node* toDelete = head->prev;
            toDelete->prev->next = head;
            head->prev = toDelete->prev;
            delete toDelete;
        }
    }

    Node* find(int data) {
        Node* current = head;
        if (!current) return nullptr;

        do {
            if (current->data == data) return current;
            current = current->next;
        } while (current != head);

        return nullptr;
    }

    void printList() {
        Node* current = head;
        if (!current) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }

    void clear() {
        if (!head) return;

        Node* current = head;
        do {
            Node* next = current->next;
            delete current;
            current = next;
        } while (current != head);

        head = nullptr;
    }

    void readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss(line);
            int number;
            while (iss >> number) {
                insertAtHead(number);
            }
        }
        file.close();
    }
};

int main() {
    DoublyCircularLinkedList list;

    // Загрузка данных из файла
    list.readFromFile("data.txt");

    // Вывод списка
    std::cout << "Initial list: ";
    list.printList();

    // Вставка элемента в голову списка
    list.insertAtHead(99);
    std::cout << "After inserting at head: ";
    list.printList();

    // Удаление с конца
    list.deleteFromTail();
    std::cout << "After deleting from tail: ";
    list.printList();

    // Поиск элемента
    int searchValue = 5;
    Node* found = list.find(searchValue);
    if (found) {
        std::cout << "Found value: " << found->data << std::endl;
    }
    else {
        std::cout << "Value " << searchValue << " not found." << std::endl;
    }

    return 0;
}
