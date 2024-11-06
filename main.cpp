#include <iostream>
#include <string>
#include <utility>

class Author {
private:
    int id;
    std::string name;
    std::string nationality;
    static int authorCount; // Статическое поле для подсчета авторов

public:
    Author(): id(0), name(""), nationality("") {
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
    // Default constructor
    Book() : id(0), title(""), author(), year(0) {}

    // Parameterized constructor
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
    }

    std::string getTitle() const {
        return title;
    }
};


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
    std::cout << "Total Authors: " << Author::getAuthorCount() << std::endl;

    // Создание авторов
    Author author1(1, "Л. Н. Толстой.", "Русский");
    Author author2(2, "Харуки Мураками", "Японец");

    std::cout << "Total Authors: " << Author::getAuthorCount() << std::endl;

    // Создание книг
    Book book1(1, "Война и мир", author1, 1869);
    Book book2(2, "Токийские легенды", author2, 2005);

    // Создание читателей
    Reader reader1(1, "Антон", "г. Барнаул, ул. Попова, дом 16");
    Reader reader2(2, "Никита", "г. Новосибирск, ул. Фрунзе, дом 52");

    // Создание библиотекаря
    Librarian librarian(1, "Анна Николаевна", "Заместитель дироектора");


    // Создание заказов
    Order order1(1, book1, reader1, librarian, "2024-10-01");
    Order order2(2, book2, reader2, librarian, "2024-09-30");

    // Ввод данных
    Author newAuthor(0, "", "");
    Author::inputAuthor(newAuthor);
    newAuthor.printAuthor();

    Book newBook(0, "", newAuthor, 0);
    Book::inputBook(newBook);
    newBook.printBook();

    Reader newReader(0, "", "");
    Reader::inputReader(newReader);
    newReader.printReader();

    Librarian newLibrarian(0, "", "");
    Librarian::inputLibrarian(newLibrarian);
    newLibrarian.printLibrarian();

    Order newOrder(0, newBook, newReader, newLibrarian, "");
    Order::inputOrder(newOrder);
    newOrder.printOrder();

    // Бизнес-логика
    order1.sendBook();
    order1.returnBook();

// Работа с динамическим массивом объектов класса
    int numBooks = 3;
    Book *books = new Book[numBooks]{
            Book{3, "Гранатовый браслет", Author(3, "Александр Куприн", "Русский"),       1910},
            Book{4, "Заячьи лапы",        Author(4, "Константин Паустовский", "Русский"), 1937},
            Book{5, "Предания веков",     Author(5, "Николай Карамзин", "Русский"),       1988}
    };

    std::cout << "\nДинамический список объектов:\n";
    for (int i = 0; i < numBooks; ++i) {
        books[i].printBook();
    }

    delete[] books;

// Работа с массивом динамических объектов класса
    int numReaders = 2;
    auto **readers = new Reader *[numReaders];
    readers[0] = new Reader(3, "Алёша", "г. Барнаул, ул. Чкалова, дом 3");
    readers[1] = new Reader(4, "Кирилл", "г. Тула, ул. Гололя, дом 6");

    std::cout << "\nСписок Динамических объектов:\n";
    for (int i = 0; i < numReaders; ++i) {
        readers[i]->printReader();
    }

    for (int i = 0; i < numReaders; ++i) {
        delete readers[i];
    }
    delete[] readers;


    return 0;
}
