#include <bits/stdc++.h>
using namespace std;

// BOOK
class Book
{
    int id;
    string title, author;
    int totalCopies, issuedCopies;
    queue<int> reservationQueue;

public:
    Book(int id, string title, string author, int copies = 5)
        : id(id), title(title), author(author), totalCopies(copies), issuedCopies(0) {}
    int getId()
    {
        return id;
    }
    string getTitle()
    {
        return title;
    }
    string getAuthor()
    {
        return author;
    }
    bool isAvailable()
    {
        return issuedCopies < totalCopies;
    }
    void issueBook()
    {
        issuedCopies++;
    }
    void returnBook()
    {
        issuedCopies--;
    }
    void reserveBook(int memberId)
    {
        reservationQueue.push(memberId);
    }
    bool hasReservation()
    {
        return !reservationQueue.empty();
    }
    int getNextReservation()
    {
        int id = reservationQueue.front();
        reservationQueue.pop();
        return id;
    }
    int availCopies()
    {
        return totalCopies - issuedCopies;
    }
};

// TRANSACTION
class Transaction
{
public:
    int bookId, memberId, issueDay, lateFee;
    Transaction(int b, int m, int d) : bookId(b), memberId(m), issueDay(d), lateFee(0) {}
};

// MEMBER
class Member
{
protected:
    int id;
    string name;
    int booksTaken;
    bool isLibraryMember;

public:
    Member(int id, string name, bool member)
        : id(id), name(name), booksTaken(0), isLibraryMember(member) {}
    virtual int maxBooks() = 0;
    int getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }
    int getBooksTaken()
    {
        return booksTaken;
    }
    void takeBook()
    {
        booksTaken++;
    }
    void returnBook()
    {
        booksTaken--;
    }
    bool hasDiscount()
    {
        return isLibraryMember;
    }
};
class Student : public Member
{
public:
    Student(int id, string name, bool member) : Member(id, name, member) {}
    int maxBooks() override
    {
        return 3;
    }
};
class Teacher : public Member
{
public:
    Teacher(int id, string name, bool member) : Member(id, name, member) {}
    int maxBooks() override
    {
        return 5;
    }
};

// LIBRARY
class Library
{
    vector<Book *> books;
    vector<Member *> members;
    vector<Transaction> transactions;
    int day = 0;

public:
    Library()
    {
        books.push_back(new Book(101, "C++ Basics", "abc", 4));
        books.push_back(new Book(102, "OOP Mastery", "def", 5));
        books.push_back(new Book(103, "DSA Guide", "qwe", 4));
        books.push_back(new Book(104, "Algorithms", "rty", 4));
        books.push_back(new Book(105, "System Design", "yiuo", 5));
        books.push_back(new Book(106, "Operating Systems", "asd", 4));
        books.push_back(new Book(107, "Database Management Systems", "jkl", 4));
        books.push_back(new Book(108, "Computer Network", "vcx", 5));
        books.push_back(new Book(109, "AI Intro", "klh", 4));
        books.push_back(new Book(110, "Machine Learning", "fdg", 5));
    }
    void addMember(Member *m)
    {
        members.push_back(m);
    }
    Book *findBook(int id)
    {
        for (auto b : books)
        {
            if (b->getId() == id)
                return b;
        }
        return nullptr;
    }
    Member *findMember(int id)
    {
        for (auto m : members)
        {
            if (m->getId() == id)
                return m;
        }
        return nullptr;
    }
    void showBooks()
    {
        cout << "\nBOOK LIST : " << endl;
        for (auto b : books)
        {
            cout << b->getId() << " - " << b->getTitle() << " by " << b->getAuthor() << " | Available copies: " << b->availCopies() << endl;
        }
    }
    void issueBook(int bookId, int memberId)
    {
        Book *book = findBook(bookId);
        Member *member = findMember(memberId);
        if (!book || !member)
        {
            cout << "Invalid ID.. Try again.\n";
            return;
        }
        if (member->getBooksTaken() >= member->maxBooks())
        {
            cout << member->getName() << " has already borrowed max books!\n";
            return;
        }
        if (!book->isAvailable())
        {
            cout << "Book not available. Reserved for member " << memberId << endl;
            book->reserveBook(memberId);
            return;
        }
        book->issueBook();
        member->takeBook();
        transactions.push_back(Transaction(bookId, memberId, day));
        cout << "Book issued to " << member->getName() << " on Day " << day << ". Copies left: " << book->availCopies() << endl;
    }
    void returnBook(int bookId, int memberId)
    {
        Book *book = findBook(bookId);
        Member *member = findMember(memberId);
        if (!book || !member)
            return;
        for (auto it = transactions.begin(); it != transactions.end(); ++it)
        {
            if (it->bookId == bookId && it->memberId == memberId)
            {
                int daysKept = day - it->issueDay;
                if (daysKept > 15)
                {
                    int fine = (daysKept - 15) * 10;
                    if (member->hasDiscount())
                        fine *= 0.5;
                    it->lateFee = fine;
                    cout << "Late! Fine: " << fine << " taka" << endl;
                }
                transactions.erase(it);
                break;
            }
        }
        book->returnBook();
        member->returnBook();
        cout << member->getName() << " returned book. Copies available: " << book->availCopies() << endl;
        if (book->hasReservation() && book->isAvailable())
        {
            int nextMember = book->getNextReservation();
            cout << "Auto-issued to reserved member " << nextMember << endl;
            issueBook(bookId, nextMember);
        }
    }
    void nextDay()
    {
        day++;
        cout << "Day advanced to " << day << endl;
    }
    void showTotalLateFees()
    {
        int total = 0;
        for (auto &t : transactions)
            total += t.lateFee;
        cout << "Total late fees collected so far: " << total << " taka\n";
    }
};
int main()
{
    Library lib;
    lib.addMember(new Student(1, "Jack", true));
    lib.addMember(new Student(3, "Lara", true));
    lib.addMember(new Teacher(2, "Rafa", false));
    int choice;
    while (true)
    {
        cout << "\n**** Library Management System ****\n";
        cout << "1. Show All Books" << endl;
        cout << "2. Issue Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. Next Day" << endl;
        cout << "5. Show Total Late Fees" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1)
            lib.showBooks();
        else if (choice == 2)
        {
            int b, m;
            cout << "Book Code: ";
            cin >> b;
            cout << "Member ID: ";
            cin >> m;
            lib.issueBook(b, m);
        }
        else if (choice == 3)
        {
            int b, m;
            cout << "Book Code: ";
            cin >> b;
            cout << "Member ID: ";
            cin >> m;
            lib.returnBook(b, m);
        }
        else if (choice == 4)
            lib.nextDay();
        else if (choice == 5)
            lib.showTotalLateFees();
        else
            break;
    }
    return 0;
}