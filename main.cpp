#include <iostream>
#include <string>
#include <utility>
#include <windows.h>

class Author {
private:
    int id;
    std::string nationality;
    static int authorCount; // Статическое поле для подсчета авторов

public:
    std::string name; // Сделаем поле name публичным

    Author() : id(0), name(""), nationality("") {
        authorCount++;
    }

    Author(int id, std::string name, std::string nationality)
            : id(id), name(std::move(name)), nationality(std::move(nationality)) {
        authorCount++;
    }

    static void inputAuthor(Author &author) {
        std::cout << "Enter Author ID: ";
        std::cin >> author.id;
        std::cin.ignore();
        std::cout << "Enter Author Name: ";
        std::getline(std::cin, author.name);
        std::cout << "Enter Author Nationality: ";
        std::getline(std::cin, author.nationality);
    }

    void printAuthor() const {
        std::cout << "Author ID: " << id << "\nName: " << name << "\nNationality: " << nationality << std::endl;
    }

    static int getAuthorCount() { // Статический метод для получения количества авторов
        return authorCount;
    }

    Author &setName(const std::string &newName) { // Метод задания имени с использованием указателя
        this->name = newName;
        return *this;
    }


};

// Инициализация статического поля
int Author::authorCount = 0;

class Book {
private:
    int id;
    std::string title;
    Author author;
    int year;

public:
    // Перегрузка оператора + для сложения название 2 книг
    Book operator+(const Book &other) const {
        Book combined;
        combined.title = this->title + " & " + other.title; // 5) сложение двух строк std::string
        combined.author = this->author;  // Оставляем автора 1 книги
        combined.year = (this->year + other.year) / 2; // Для теста оставляем средний год выпуска 2-х книг
        return combined;
    }

    // Префиксная перегрузка оператора ++
    Book &operator++() {
        ++year;
        return *this;
    }

    // Постфиксной перегрузка оператора ++
    Book operator++(int) {
        Book temp = *this;
        year++;
        return temp;
    }

    // метод возврата через указатель
    std::string *getTitlePointer() {
        return &title;
    }

    // метод возврата через ссылку
    std::string &getTitleReference() {
        return title;
    }

    // Обычный конструктор
    Book() : id(0), title(""), author(), year(0) {}

    // Обычный с параметрами
    Book(int id, std::string title, Author author, int year)
            : id(id), title(std::move(title)), author(std::move(author)), year(year) {}

    static void inputBook(Book &book) {
        std::cout << "Enter Book ID: ";
        std::cin >> book.id;
        std::cin.ignore();
        std::cout << "Enter Book Title: ";
        std::getline(std::cin, book.title);
        std::cout << "Enter Author details:\n";
        Author::inputAuthor(book.author);
        std::cout << "Enter Year of Publication: ";
        std::cin >> book.year;
    }

    void printBook() const {
        std::cout << "Book ID: " << id << "\nTitle: " << title << std::endl;
        author.printAuthor();
        std::cout << "Year: " << year << std::endl;
        std::cout << ""<< std::endl;
    }

    std::string getTitle() const {
        return title;
    }

    friend bool sameAuthor(const Book &b1, const Book &b2); // Вызов дружественной функции
};

bool sameAuthor(const Book &b1, const Book &b2) { // Дружественная функция для сопоставления авторов 2 книг
    return b1.author.name == b2.author.name;
}

class Reader {
private:
    int id;
    std::string name;
    std::string address;

public:
    Reader(int id, std::string name, std::string address)
            : id(id), name(std::move(name)), address(std::move(address)) {}

    static void inputReader(Reader &reader) {
        std::cout << "Enter Reader ID: ";
        std::cin >> reader.id;
        std::cin.ignore();
        std::cout << "Enter Reader Name: ";
        std::getline(std::cin, reader.name);
        std::cout << "Enter Reader Address: ";
        std::getline(std::cin, reader.address);
    }

    void printReader() const {
        std::cout << "Reader ID: " << id << "\nName: " << name << "\nAddress: " << address << std::endl;
    }

    std::string getName() const {
        return name;
    }
};

class Librarian {
private:
    int id;
    std::string name;
    std::string position;

public:
    Librarian(int id, std::string name, std::string position)
            : id(id), name(std::move(name)), position(std::move(position)) {}

    static void inputLibrarian(Librarian &librarian) {
        std::cout << "Enter Librarian ID: ";
        std::cin >> librarian.id;
        std::cin.ignore();
        std::cout << "Enter Librarian Name: ";
        std::getline(std::cin, librarian.name);
        std::cout << "Enter Librarian Position: ";
        std::getline(std::cin, librarian.position);
    }

    void printLibrarian() const {
        std::cout << "Librarian ID: " << id << "\nName: " << name << "\nPosition: " << position << std::endl;
    }
};

class Order {
private:
    int id;
    Book book;
    Reader reader;
    Librarian librarian;
    std::string order_date;

public:
    Order(int id, Book book, Reader reader, Librarian librarian, std::string order_date)
            : id(id), book(std::move(book)), reader(std::move(reader)), librarian(std::move(librarian)),
              order_date(std::move(order_date)) {}

    static void inputOrder(Order &order) {
        std::cout << "Enter Order ID: ";
        std::cin >> order.id;
        std::cin.ignore();
        std::cout << "Enter Book details:\n";
        Book::inputBook(order.book);
        std::cout << "Enter Reader details:\n";
        Reader::inputReader(order.reader);
        std::cout << "Enter Librarian details:\n";
        Librarian::inputLibrarian(order.librarian);
        std::cout << "Enter Order Date (YYYY-MM-DD): ";
        std::getline(std::cin, order.order_date);
    }

    void printOrder() const {
        std::cout << "Order ID: " << id << std::endl;
        book.printBook();
        reader.printReader();
        librarian.printLibrarian();
        std::cout << "Order Date: " << order_date << std::endl;
    }

    void sendBook() const {
        std::cout << "Sending book '" << book.getTitle() << "' to reader '" << reader.getName() << "' on " << order_date
                  << std::endl;
    }

    void returnBook() const {
        std::cout << "Returning book '" << book.getTitle() << "' from reader '" << reader.getName() << "'" << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru-RU");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // 1) Демонстрация возвращения через указатель и через ссылку
    Book book1(1, "C++ Основы", Author(1, "John Doe", "США"), 2018);
    std::string *titlePtr = book1.getTitlePointer();
    std::string &titleRef = book1.getTitleReference();
    std::cout << "Title (pointer): " << *titlePtr << "\nTitle (reference): " << titleRef << std::endl;

    // 2) Демонстрация использования оператора this
    Author author1;
    author1.setName("Jane Doe").setName("Jane Austen");
    author1.printAuthor();

    // 3) Сравнение автора 2 книг
    Book book2(2, "Продвинутый C++", Author(2, "John Doe", "США"), 2022);
    std::cout << "Same author: " << (sameAuthor(book1, book2) ? "Yes" : "No") << std::endl;

    // 4) Демонстрация сложения 2 книг
    Book combinedBook = book1 + book2;
    combinedBook.printBook();

    // Префиксный оператор увеличения ++
    ++book1;
    book1.printBook();

    // Постфиксный оператор увеличения ++
    book1++;
    book1.printBook();

    return 0;
}
