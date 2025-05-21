#ifndef APPLICANT_HPP
#define APPLICANT_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

// const string& filename = "applicants.bin";

enum ApplicantStatus { // Статуси абітурієнта
    ACTIVE,   // Активний
    ENROLLED, // Зрахований
    DELETED   // Видалений
};

class Applicant {
private:
    string SFP;         // ПІБ
    int age;            // Вік
    string specialty;   // Спеціальність
    float avg_grade;    // Середній бал
    string financing;   // Фінансування
    ApplicantStatus status; // Статус абітурієнта
public:
    // Оголошення перевантажувального оператора == для порівняння статуса
    bool operator==(const ApplicantStatus& status) const;
    // Оголошення перевантажувального оператора != для виведення повідомлення про відсутність абітурієнтів
    bool operator!=(const ApplicantStatus& status) const;
    // Оголошення перевантажувального оператора присвоєння
    Applicant& operator=(const Applicant& other);
    // Оголошення перевантажувального оператора виведення
    friend ostream& operator<<(ostream& os, const Applicant& applicant);
    // Конструктор за замовчуванням
    Applicant();
    // Оголошення конструктора ініціалізації
    Applicant(string, int, string, float, string);
    // Оголошення конструктора копіювання
    Applicant(const Applicant&);
    // Оголошення деструктора
    ~Applicant();
    // Призначення інформації апліканту
    void applicantSetData(string S, int a, string s, float a_g, string f);
    // Призначення групи
    void SetGroup(void);
    // Отримання інформації про абітурієнта
    void GetApplicantInfo(void);
    // Призначення статусу
    void SetStatus(ApplicantStatus new_status);
    // Отримання статусу
    ApplicantStatus GetStatus() const;

    void saveToFile(ofstream& file) const; // Збереження в файл
    void loadFromFile(ifstream& file);    // Завантаження з файлу
};

extern Applicant applicants[4];

// Похідний клас для абітурієнта з інформацією про освіту
class Applicant3 : public Applicant {
private:
    string education;
public:
    void saveToFile(ofstream& file) const; // Збереження в файл
    void loadFromFile(ifstream& file);    // Завантаження з файлу
    Applicant3(); // конструктор за замовчуванням похідного класу для Applicant3
    Applicant3(string, int, string, float, string, string); // конструктор ініціалізації похідного класу для Applicant3
    Applicant3(const Applicant3&);  // Оголошення конструктора копіювання для Applicant3

    friend ostream& operator<<(ostream& os, const Applicant3& applicant); // Оголошення перевантажувального оператора виведення для Applicant3
};

// Похідний клас для абітурієнта з інформацією про адресу проживання
class Applicant4 : public Applicant {
private:
    string address;
public:
    void saveToFile(ofstream& file) const; // Збереження в файл
    void loadFromFile(ifstream& file);    // Завантаження з файлу
    Applicant4(); // конструктор за замовчуванням похідного класу для Applicant4
    Applicant4(string, int, string, float, string, string); // конструктор ініціалізації похідного класу для Applicant4
    Applicant4(const Applicant4&);  // Оголошення конструктора копіювання для Applicant4

    friend ostream& operator<<(ostream& os, const Applicant4& applicant); // Оголошення перевантажувального оператора виведення для Applicant4
};

class Role { // Базовий повністю віртуальний клас
public:
    virtual void getAllowedActions() = 0; // Повністю віртуальний метод
};

class User : virtual public Role { // User може переглядати
public:
    User(); // Оголошення конструктора за замовчуванням
    virtual void read(Applicant*); // Зробив метод для читання віртуальним
    void getAllowedActions() override; // Метод для доступних опцій
};

class Admin : virtual public User { // Admin може переглядати та видаляти
public:
    Admin(); // Оголошення конструктора за замовчуванням
    void deleteApplicant(Applicant*); // Метод для видалення
    void viewDeleted(Applicant*); // Метод для перегляду видалених абітурієнтів
    void getAllowedActions() override; // Метод для доступних опцій
};

class Manager : virtual public User { // Manager може переглядати та зараховувати
public:
    Manager(); // Оголошення конструктора за замовчуванням
    void enrollApplicant(Applicant*); // Метод для зарахування
    void viewEnrolled(Applicant*); // Метод для перегляду зарахованих абітурієнтів
    void getAllowedActions() override; // Метод для доступних опцій
};


class Supervisor : public Admin, public Manager {  // Supervisor може переглядати, видаляти та зараховувати
public:
    Supervisor(); // Оголошення конструктора за замовчуванням
    void getAllowedActions() override; // Метод для доступних опцій

};


class Current { // Клас для поточного користувача
public:
    void getAllowedActions(Role*); // Метод для поточного користувача
};


class NumCheck : public exception { // Клас для заданих виключень
public:
    NumCheck();
};


#endif
