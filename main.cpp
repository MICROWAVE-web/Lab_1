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


