#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// هيكل البيانات لتمثيل كتاب
struct Book {
    string title;
    string author;
    int year;
    string isbn;

    // دالة لطباعة تفاصيل الكتاب
    void print() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
        cout << "ISBN: " << isbn << endl;
    }

    // دالة لتحويل الكتاب إلى نص لكتابته في ملف
    string to_string() const {
        stringstream ss;   
        ss << title << "," << author << "," << year << "," << isbn;
        return ss.str();
    }
};

// فئة لإدارة المكتبة
class Library {
private:
    vector<Book> books;      

    // دالة لتحميل البيانات من ملف
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file for reading." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, author, isbn;
            int year;
            getline(ss, title, ',');
            getline(ss, author, ',');
            ss >> year;
            ss.ignore();
            getline(ss, isbn);

            books.push_back({title, author, year, isbn}); 
        }
        file.close();
    }

    // دالة لحفظ البيانات إلى ملف
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
           cerr << "Error opening file for writing." << endl;
            return;
        }
        for (const auto& book : books) {                    
            file << book.to_string() << endl;
        }
        file.close();
    }

public:
    Library() {
        loadFromFile("library_data.txt");
    }

    ~Library() {
        saveToFile("library_data.txt");
    }

    // دالة لإضافة كتاب جديد
    void addBook() {
        Book newBook;
        cout << "Enter book title: ";
        getline(cin, newBook.title);
        cout << "Enter book author: ";
        getline(cin, newBook.author);
        cout << "Enter publication year: ";
        cin >> newBook.year;
        cin.ignore(); // لتجاهل السطر الجديد المتبقي في الدفق
        cout << "Enter book ISBN: ";
        getline(cin, newBook.isbn);

        books.push_back(newBook);
        cout << "Book added successfully!" << endl;
    }

    // دالة للبحث عن كتاب
    void searchBook() const {
        string searchTitle;
        cout << "Enter book title to search: ";
        getline(cin, searchTitle);

        bool found = false;
        for (const auto& book : books) {
            if (book.title == searchTitle) {
                book.print();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found." << endl;
        }
    }

    // دالة لعرض جميع الكتب
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }

        for (const auto& book : books) {
            book.print();
            cout << "------------------------" << endl;
        }
    }
};

// دالة لطباعة قائمة الخيارات للمستخدم
void printMenu() {
    cout << "Library Menu:" << endl;
    cout << "1. Add a book" << endl;
    cout << "2. Search for a book" << endl;
    cout << "3. Display all books" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    Library library;
    int choice;

    do {
        printMenu();
        cin >> choice;
        cin.ignore(); // لتجاهل السطر الجديد المتبقي في الدفق

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.searchBook();
                break;
            case 3:
                library.displayAllBooks();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}