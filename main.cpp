#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для представления автора
typedef struct {
    int id;
    char name[100];
    char nationality[50];
} Author;

// Структура для представления книги
typedef struct {
    int id;
    char title[100];
    Author author;
    int year;
} Book;

// Структура для представления читателя
typedef struct {
    int id;
    char name[100];
    char address[200];
} Reader;


// Структура для представления заказа
typedef struct {
    int id;
    Book book;
    Reader reader;
    Librarian librarian;
    char order_date[11]; // формат: YYYY-MM-DD
} Order;

// Структура для представления библиотекаря
typedef struct {
    int id;
    char name[100];
    char position[50];
} Librarian;

// Инициализация автора
Author createAuthor(int id, const char* name, const char* nationality) {
    Author author;
    author.id = id;
    strcpy(author.name, name);
    strcpy(author.nationality, nationality);
    return author;
}

// Инициализация книги
Book createBook(int id, const char* title, Author author, int year) {
    Book book;
    book.id = id;
    strcpy(book.title, title);
    book.author = author;
    book.year = year;
    return book;
}

// Инициализация читателя
Reader createReader(int id, const char* name, const char* address) {
    Reader reader;
    reader.id = id;
    strcpy(reader.name, name);
    strcpy(reader.address, address);
    return reader;
}

// Инициализация Заказа
Order createOrder(int id, Book book, Reader reader, Librarian librarian
        , const char* order_date) {
    Order order;
    order.id = id;
    order.book = book;
    order.reader = reader;
    order.librarian = librarian;
    strcpy(order.order_date, order_date);
    return order;
}

// Инициализация библиотекаря
Librarian createLibrarian(int id, const char* name, const char* position) {
    Librarian librarian;
    librarian.id = id;
    strcpy(librarian.name, name);
    strcpy(librarian.position, position);
    return librarian;
}


void inputAuthor(Author* author) {
    printf("Enter Author ID: ");
    scanf("%d", &author->id);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", author->name);
    printf("Enter Author Nationality: ");
    scanf(" %[^\n]", author->nationality);
}

void printAuthor(Author author) {
    printf("Author ID: %d\nName: %s\nNationality: %s\n", author.id, author.name, author.nationality);
}

void inputBook(Book* book) {
    printf("Enter Book ID: ");
    scanf("%d", &book->id);
    printf("Enter Book Title: ");
    scanf(" %[^\n]", book->title);
    printf("Enter Author details:\n");
    inputAuthor(&book->author);
    printf("Enter Year of Publication: ");
    scanf("%d", &book->year);
}



void printBook(Book book) {
    printf("Book ID: %d\nTitle: %s\n", book.id, book.title);
    printAuthor(book.author);
    printf("Year: %d\n", book.year);
}

void inputReader(Reader* reader) {
    printf("Enter Reader ID: ");
    scanf("%d", &reader->id);
    printf("Enter Reader Name: ");
    scanf(" %[^\n]", reader->name);
    printf("Enter Reader Address: ");
    scanf(" %[^\n]", reader->address);
}

void printReader(Reader reader) {
    printf("Reader ID: %d\nName: %s\nAddress: %s\n", reader.id, reader.name, reader.address);
}

void inputOrder(Order* order) {
    printf("Enter Order ID: ");
    scanf("%d", &order->id);
    printf("Enter Book details:\n");
    inputBook(&order->book);
    printf("Enter Reader details:\n");
    inputReader(&order->reader);
    printf("Enter Librarian details:\n");
    inputLibrarian(&order->librarian);
    printf("Enter Order Date (YYYY-MM-DD): ");
    scanf(" %[^\n]", order->order_date);
}

void printOrder(Order order) {
    printf("Order ID: %d\n", order.id);
    printBook(order.book);
    printReader(order.reader);
    printLibrarian(order.librarian);
    printf("Order Date: %s\n", order.order_date);
}



void inputLibrarian(Librarian* librarian) {
    printf("Enter Librarian ID: ");
    scanf("%d", &librarian->id);
    printf("Enter Librarian Name: ");
    scanf(" %[^\n]", librarian->name);
    printf("Enter Librarian Position: ");
    scanf(" %[^\n]", librarian->position);
}
void printLibrarian(Librarian librarian) {
    printf("Librarian ID: %d\nName: %s\nPosition: %s\n", librarian.id, librarian.name, librarian.position);
}

void sendBook(Order* order) {
    printf("Sending book '%s' to reader '%s' on %s\n", order->book.title, order->reader.name, order->order_date);
}

void returnBook(Order* order) {
    printf("Returning book '%s' from reader '%s'\n", order->book.title, order->reader.name);
}

int main() {
    // Создание авторов
    Author author1 = createAuthor(1, "Л. Н. Толстой.", "Русский");
    Author author2 = createAuthor(2, "Харуки Мураками", "Японец");

    // Создание книг
    Book book1 = createBook(1, "Война и мир", author1, 1869);
    Book book2 = createBook(2, "Токийские легенды", author2, 2005);

    // Создание читателей
    Reader reader1 = createReader(1, "Антон", "г. Барнаул, ул. Попова, дом 16");
    Reader reader2 = createReader(2, "Никита", "г. Новосибирск, ул. Фрунзе, дом 52");

    // Создание библиотекаря
    Librarian librarian = createLibrarian(1, "Анна Николаевна", "Заместитель дироектора");



    // Создание заказов
    Order order1 = createOrder(1, book1, reader1, librarian, "2024-10-01");
    Order order2 = createOrder(2, book2, reader2, librarian, "2024-09-30");

    // Ввод данных
    Author newAuthor;
    inputAuthor(&newAuthor);
    printAuthor(newAuthor);

    Book newBook;
    inputBook(&newBook);
    printBook(newBook);

    Reader newReader;
    inputReader(&newReader);
    printReader(newReader);

    Librarian newLibrarian;
    inputLibrarian(&newLibrarian);
    printLibrarian(newLibrarian);

    Order newOrder;
    inputOrder(&newOrder);
    printOrder(newOrder);

    // Бизнес-логика
    sendBook(&order1);
    returnBook(&order1);

    return 0;
}
