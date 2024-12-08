#include <iostream>
#include <string>
#include <utility>
#include <windows.h>
#include <stdexcept> // Для std::runtime_error
#include <vector>
#include <regex>

// Абстрактный класс
class LibraryEntity {
public:
    virtual void printEntity() const = 0; // Чисто виртуальная функция
    virtual ~LibraryEntity() = default;
};

// Базовый класс Author
class Author : public LibraryEntity {
protected:
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

    // Деструктор
    ~Author() override {
        authorCount--;
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

    virtual void printAuthor() const {
        std::cout << "Author ID: " << id << "\nName: " << name << "\nNationality: " << nationality << std::endl;
    }

    static int getAuthorCount() { // Статический метод для получения количества авторов
        return authorCount;
    }

    Author &setName(const std::string &newName) { // Метод задания имени с использованием указателя
        this->name = newName;
        return *this;
    }

    Author &operator=(const Author &other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            nationality = other.nationality;
        }
        return *this;
    }

    virtual std::string getDetails() const {
        return "Author: " + name + ", Nationality: " + nationality;
    }

    void printEntity() const override {
        printAuthor();
    }

};

// Инициализация статического поля
int Author::authorCount = 0;

// Производный класс SpecialAuthor
class SpecialAuthor : public Author {
private:
    std::string award;

public:
    SpecialAuthor(int id, const std::string &name, const std::string &nationality, std::string award)
            : Author(id, name, nationality), award(std::move(award)) {}

    void printAuthor() const override {
        Author::printAuthor(); // Вызов метода базового класса
        std::cout << "Award: " << award << std::endl;
    }

    std::string getDetails() const override {
        return Author::getDetails() + ", Award: " + award;
    }

    SpecialAuthor &operator=(const Author &other) {
        if (this != &other) {
            Author::operator=(other); // Присваиваем базовую часть
            award = "No Award"; // Специфическое значение для производного
        }
        return *this;
    }
};

class Book {
private:
    int id;
    std::string title;
    Author author;
    int year;

    void validateYear(int y) {
        if (y <= 0) {
            throw std::invalid_argument("Year must be a positive number.");
        }
    }

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
            : id(id), title(std::move(title)), author(std::move(author)), year(year) {
        try {
            validateYear(year);
            this->year = year;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error in Book constructor: " << e.what() << std::endl;
            this->year = 1; // Устанавливаем год по умолчанию
        }
    }

    static void inputBook(Book &book) {
        std::cout << "Enter Book ID: ";
        std::cin >> book.id;
        std::cin.ignore();
        std::cout << "Enter Book Title: ";
        std::getline(std::cin, book.title);

        try {
            std::cout << "Enter Author details:\n";
            Author::inputAuthor(book.author);
            std::cout << "Enter Year of Publication: ";
            std::cin >> book.year;

            book.validateYear(book.year);
        } catch (const std::exception &e) {
            std::cerr << "Error during input: " << e.what() << "\nSetting default year to 2000." << std::endl;
            book.year = 2000;
        }
    }

    void printBook() const {
        std::cout << "Book ID: " << id << "\nTitle: " << title << std::endl;
        author.printAuthor();
        std::cout << "Year: " << year << std::endl;
        std::cout << "" << std::endl;
    }

    std::string getTitle() const {
        return title;
    }

    friend bool sameAuthor(const Book &b1, const Book &b2); // Вызов дружественной функции
};

bool sameAuthor(const Book &b1, const Book &b2) { // Дружественная функция для сопоставления авторов 2 книг
    return b1.author.name == b2.author.name;
}

class Reader : public LibraryEntity {
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

    // Реализация чисто виртуальной функции из LibraryEntity
    void printEntity() const override {
        printReader(); // Можно просто вызвать существующую функцию
    }
};

class Librarian : public LibraryEntity {
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

    // Реализация чисто виртуальной функции из LibraryEntity
    void printEntity() const override {
        printLibrarian(); // Можно просто вызвать существующую функцию
    }
};

class Order {
private:
    int id;
    Book book;
    Reader reader; // Фикс, сделать указатель на абстрактную функцию
    Librarian librarian; // Фикс, сделать указатель на абстрактную функцию
    std::string order_date;


    void validateOrderDate(const std::string &date) {
        // Проверка формата YYYY-MM-DD
        std::regex dateRegex(R"((\d{4})-(\d{2})-(\d{2}))");
        std::smatch match;
        if (!std::regex_match(date, match, dateRegex)) {
            throw std::invalid_argument("Order date must be in format YYYY-MM-DD.");
        }

        // Извлечение года, месяца и дня из строки
        int year = std::stoi(match[1].str());
        int month = std::stoi(match[2].str());
        int day = std::stoi(match[3].str());

        // Проверка диапазона месяца
        if (month < 1 || month > 12) {
            throw std::invalid_argument("Month must be between 1 and 12.");
        }

        // Проверка диапазона дня
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Учитываем високосный год
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear) {
            daysInMonth[1] = 29; // Февраль имеет 29 дней в високосном году
        }

        if (day < 1 || day > daysInMonth[month - 1]) {
            throw std::invalid_argument("Incorrect day. Check your calendar");
        }
    }

public:
    Order(int id, Book book, Reader *reader, Librarian *librarian, std::string order_date)
            : id(id), book(std::move(book)), reader(*reader), librarian(*librarian) {
        try {
            validateOrderDate(order_date);
            this->order_date = std::move(order_date);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error in Order constructor: " << e.what() << "\nSetting default date to 2000-01-01."
                      << std::endl;
            this->order_date = "2000-01-01";
        }
    }

    static void inputOrder(Order &order) {
        std::cout << "Enter Order ID: ";
        std::cin >> order.id;
        std::cin.ignore();
        std::cout << "Enter Book details:\n";
        Book::inputBook(order.book);
        std::cout << "Enter Reader details:\n";
        Reader::inputReader(reinterpret_cast<Reader &>(order.reader));
        std::cout << "Enter Librarian details:\n";
        Librarian::inputLibrarian(reinterpret_cast<Librarian &>(order.librarian));
        std::cout << "Enter Order Date (YYYY-MM-DD): ";
        std::getline(std::cin, order.order_date);
        try {
            // Валидируем дату
            order.validateOrderDate(order.order_date);
        } catch (const std::exception &e) {
            std::cerr << "Error during input: " << e.what() << "\nSetting default date to 2000-01-01." << std::endl;
            order.order_date = "2000-01-01";
        }
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


// возврат значения из метода через вспомогательный класс;
class Utils {
public:
    // Метод для преобразования строки в верхний регистр
    static std::string toUpperCase(const std::string &str) {
        std::string result = str;
        for (char &ch: result) {
            ch = toupper(ch);
        }
        return result;
    }

    // Метод для подсчета книг с определенным автором
    static int countBooksByAuthor(const std::vector<Book> &books, const std::string &authorName) {
        int count = 0;
        for (Book book: books) {
            if (book.getTitlePointer() != nullptr && book.getTitleReference() == authorName) {
                count++;
            }
        }
        return count;
    }

    // Метод для поиска книги по названию
    static Book *findBookByTitle(const std::vector<Book> &books, const std::string &title) {
        for (const Book &book: books) {
            if (book.getTitle() == title) {
                return new Book(book); // Возвращаем копию объекта
            }
        }
        return nullptr;
    }

    // Метод для вывода всех книг
    static void printAllBooks(const std::vector<Book> &books) {
        for (const Book &book: books) {
            book.printBook();
        }
    }
};

// Шаблон класса
template<typename T>
class LibraryContainer {
private:
    std::vector<T> items;

public:
    void addItem(const T &item) {
        items.push_back(item);
    }

    void printAllItems() const {
        for (const auto &item: items) {
            item.printEntity();
            std::cout << "" << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru-RU");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Author author1(1, "John Doe", "USA");
    SpecialAuthor author2(2, "Jane Smith", "UK", "Nobel Prize");

    std::cout << "Базовый автор:" << std::endl;
    author1.printAuthor();

    std::cout << "\nОсобый автор:" << std::endl;
    author2.printAuthor();

    // Перегрузка оператора присваивания
    std::cout << "\nРезультат присваивания:" << std::endl;
    author2 = author1;
    author2.printAuthor();

    // Демонстрация виртуальных функций
    Author *basePtr = &author2;
    std::cout << "\nДетали из базового указателя: " << basePtr->getDetails() << std::endl;

    // Шаблонный класс
    LibraryContainer<Author> library;
    library.addItem(author1);
    library.addItem(author2);

    std::cout << "\nБиблиотека:" << std::endl;
    library.printAllItems();

    return 0;
}