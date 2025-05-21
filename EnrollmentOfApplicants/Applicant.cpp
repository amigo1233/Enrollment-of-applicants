#include "Applicant.hpp"
#include <limits>   // для getIntInRange
using namespace std;

// Функція для вводу числа в діапазоні [min, max]
static int getIntInRange(int min, int max) {
    int num;
    while (true) {
        if (!(cin >> num)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between "
                << min << " and " << max << ": ";
        }
        else if (num < min || num > max) {
            cout << "Invalid input. Please enter a number between "
                << min << " and " << max << ": ";
        }
        else {
            return num;
        }
    }
}

Applicant applicants[4];

void Applicant::saveToFile(ofstream& file) const {
    file << SFP << endl;  // записуємо ПІБ, додаємо новий рядок
    file << age << endl;  // записуємо вік, додаємо новий рядок
    file << specialty << endl;  // записуємо спеціальність, додаємо новий рядок
    file << avg_grade << endl;  // записуємо середній бал, додаємо новий рядок
    file << financing << endl;  // записуємо фінансування, додаємо новий рядок
    file << status << endl;  // записуємо статус, додаємо новий рядок
}

void Applicant::loadFromFile(ifstream& file) {
    char buffer[256];  // буфер для рядків
    file.read(buffer, sizeof(buffer));
    SFP = string(buffer);  // записуємо ПІБ

    file.read(reinterpret_cast<char*>(&age), sizeof(age));  // зчитуємо вік

    file.read(buffer, sizeof(buffer));
    specialty = string(buffer);  // зчитуємо спеціальність

    file.read(reinterpret_cast<char*>(&avg_grade), sizeof(avg_grade));  // зчитуємо середній бал

    file.read(buffer, sizeof(buffer));
    financing = string(buffer);  // зчитуємо фінансування

    file.read(reinterpret_cast<char*>(&status), sizeof(status));  // зчитуємо статус
}


void Applicant3::saveToFile(ofstream& file) const {
    Applicant::saveToFile(file); // Зберігаємо основні дані з базового класу
    file.write(education.c_str(), education.size() + 1); // Записуємо освіту
}

void Applicant3::loadFromFile(ifstream& file) {
    Applicant::loadFromFile(file); // Завантажуємо основні дані з базового класу
    char buffer[256]; // Буфер для освіти
    file.read(buffer, sizeof(buffer)); education = string(buffer);
}

void Applicant4::saveToFile(ofstream& file) const {
    Applicant::saveToFile(file); // Зберігаємо основні дані
    file.write(address.c_str(), address.size() + 1); // Записуємо адресу
}

void Applicant4::loadFromFile(ifstream& file) {
    Applicant::loadFromFile(file); // Завантажуємо основні дані
    char buffer[256]; // Буфер для адреси
    file.read(buffer, sizeof(buffer)); address = string(buffer);
}

// Реалізація перевантажувального оператора == для порівняння статуса
bool Applicant::operator==(const ApplicantStatus& status) const {
    return this->status == status;
}
// Реалізація перевантажувального оператора != для виведення повідомлення про відсутність абітурієнтів
bool Applicant::operator!=(const ApplicantStatus& status) const {
    return this->status != status;
}
// Реалізація перевантажувального оператора присвоєння
Applicant& Applicant::operator=(const Applicant& other) {
    if (this == &other) return *this; // Перевірка на самоприсвоєння
    SFP = other.SFP;
    age = other.age;
    specialty = other.specialty;
    avg_grade = other.avg_grade;
    financing = other.financing;
    status = other.status;

    return *this;
}
// Реалізація перевантажувального оператора виведення
ostream& operator<<(ostream& os, const Applicant& applicant) {
    os << "Name: " << applicant.SFP << endl;
    os << "Age: " << applicant.age << endl;
    os << "Specialty: " << applicant.specialty << endl;
    os << "Average Grade: " << applicant.avg_grade << endl;
    os << "Financing: " << applicant.financing << endl;
    return os;
}
// Реалізація конструктора за замовчуванням
Applicant::Applicant() : status(ACTIVE) {

}
//Реалізація конструктора ініціалізації
Applicant::Applicant(string S, int a, string s, float a_g, string f) : status(ACTIVE) {
    applicantSetData(S, a, s, a_g, f);
}
//Реалізація конструктора копіюванння
Applicant::Applicant(const Applicant& X) : status(X.status) {
    SFP = X.SFP;                // Копіювання ПІБ
    age = X.age;                // Копіювання віку
    specialty = X.specialty;     // Копіювання спеціальності
    avg_grade = X.avg_grade;     // Копіювання середнього балу
    financing = X.financing;     // Копіювання типу фінансування
}
// Призначення початкових даних абітурієнту
void Applicant::applicantSetData(string S, int a, string s, float a_g, string f) {
    SFP = S;
    age = a;
    specialty = s;
    avg_grade = a_g;
    financing = f;
}

// Отримання інформації про абітурієнта
void Applicant::GetApplicantInfo(void) {
    cout << "Name: " << SFP << endl;
    cout << "Age: " << age << endl;
    cout << "Specialty: " << specialty << endl;
    cout << "Average Grade: " << avg_grade << endl;
    cout << "Financing: " << financing << endl;
}
// Призначення статусу
void Applicant::SetStatus(ApplicantStatus new_status) {
    status = new_status;
}
// Отримання статусу
ApplicantStatus Applicant::GetStatus() const {
    return status;
}
// Реалізація деконструктора
Applicant::~Applicant() {
    cout << "Deleted" << endl;
}

// Реалізація конструктора за замовчуванням для Applicant3
Applicant3::Applicant3() {
}
//Реалізація конструктора ініціалізації для Applicant3
Applicant3::Applicant3(string S, int a, string s, float a_g, string f, string edu) : Applicant(S, a, s, a_g, f) {
    education = edu;
}

//Реалізація конструктора копіювання
Applicant3::Applicant3(const Applicant3& X) : Applicant(X) {
    education = X.education;
}

// Реалізація перевантажувального оператора виведення для Applicant3
ostream& operator<<(ostream& os, const Applicant3& applicant) {
    os << static_cast<const Applicant&>(applicant);
    os << "Education: " << applicant.education << endl; // Вивід освіти
    return os;
}

// Реалізація конструктора за замовчуванням для Applicant4
Applicant4::Applicant4() {

}
//Реалізація конструктора ініціалізації для Applicant4
Applicant4::Applicant4(string S, int a, string s, float a_g, string f, string add) : Applicant(S, a, s, a_g, f) {
    address = add;
}

//Реалізація конструктора копіювання
Applicant4::Applicant4(const Applicant4& X) : Applicant(X) {
    address = X.address; // Копіювання типу адреси
}

// Реалізація перевантажувального оператора виведення для Applicant4
ostream& operator<<(ostream& os, const Applicant4& applicant) {
    os << static_cast<const Applicant&>(applicant);
    os << "Address: " << applicant.address << endl; // Вивід адреси
    return os;
}

User::User() {}; // Конструктор за замовчуванням

void User::read(Applicant* applicants) { // Реалізація метода читання
    cout << "-------------Available applicants-------------" << endl << endl;

    for (int i = 0; i < 4; i++) {
        if (applicants[i] == ACTIVE) {
            cout << "Applicant #" << i + 1 << " Info:" << endl;
            cout << applicants[i] << endl;
        }
    }
};

void User::getAllowedActions() { // Реалізація метода для доступних опцій для User
    cout << "Allowed actions for User:"; // Вивід меню
    cout << endl << "[1] Available applicants";
    cout << endl << "Choose option: ";
    int a = getIntInRange(1, 1);
    switch (a)
    {
    case 1: // Опція читання
        read(applicants);
    default:
        break;
    }

}

Admin::Admin() {}; // Конструктор за замовчуванням

void Admin::deleteApplicant(Applicant* applicants) { // Реалізація метода для видалення абітурієнтів
    cout << "Which applicant do you want to remove (1-4): ";
    int a = getIntInRange(1, 4);
    if (a == 1) { // Перевірки для видалення вірного абітурієнта
        a = 0;
    }
    else {
        a -= 1;
    }
    applicants[a].SetStatus(DELETED); // Призначаю статус "видалений"
    cout << "Applicant ";
    if (a == 0) {  // Перевірки для вірного вивода інформації
        a = 1;
        cout << a << " was deleted!" << endl;
    }
    else {
        a + 1;
        cout << a + 1 << " was deleted!" << endl;
    }

}

void Admin::viewDeleted(Applicant* applicants) { // Метод для перегляду видалених

    cout << "-------------Deleted applicants-------------" << endl << endl;

    for (int i = 0; i < 4; i++) {
        if (applicants[i] == DELETED) {
            cout << "Applicant #" << i + 1 << " Info:" << endl;
            cout << applicants[i] << endl;
        }
    }
};

void Admin::getAllowedActions() { // Реалізація метода для доступних опцій для Admin
    cout << "Allowed actions for Admin:"; // Вивід меню
    cout << endl << "[1] Available applicants";
    cout << endl << "[2] Delete applicants";
    cout << endl << "[3] View deleted applicants";
    cout << endl << "Choose option: ";
    int a = getIntInRange(1, 3);
    switch (a)
    {
    case 1: // Опція читання
        read(applicants);
        break;
    case 2: // Опція видалення
        deleteApplicant(applicants);
        break;
    case 3: // Опція перегляду видалених
        viewDeleted(applicants);
        break;
    default:
        break;
    }

}

Manager::Manager() {}; // Конструктор за замовчуванням

void Manager::enrollApplicant(Applicant* applicants) { // Реалізація метода для зарахування абітурієнтів
    cout << "Which applicant do you want to enroll (1-4): ";
    int a = getIntInRange(1, 4);
    if (a == 1) { // Перевірки для вірного абітурієнта
        a = 0;
    }
    else {
        a -= 1;
    }
    applicants[a].SetStatus(ENROLLED); // Призначаю статус "зарахований"
    cout << "Applicant ";
    if (a == 0) {  // Перевірки для вірного вивода інформації
        a = 1;
        cout << a << " was enrolled!" << endl;
    }
    else {
        a + 1;
        cout << a + 1 << " was enrolled!" << endl;
    }

}

void Manager::viewEnrolled(Applicant* applicants) {

    cout << "-------------Enrolled applicants-------------" << endl << endl;

    for (int i = 0; i < 4; i++) {
        if (applicants[i] == ENROLLED) {
            cout << "Applicant #" << i + 1 << " Info:" << endl;
            cout << applicants[i] << endl;
        }
    }
};

void Manager::getAllowedActions() { // Реалізація метода для доступних опцій для Manager
    cout << "Allowed actions for Manager:"; // Вивід меню
    cout << endl << "[1] Available applicants";
    cout << endl << "[2] Enroll applicants";
    cout << endl << "[3] View enrolled applicants";
    cout << endl << "Choose option: ";
    int a = getIntInRange(1, 3);
    switch (a)
    {
    case 1: // Опція читання
        read(applicants);
        break;
    case 2: // Опція зарахування
        enrollApplicant(applicants);
        break;
    case 3: // Опція перегляду зарахованих
        viewEnrolled(applicants);
        break;
    default:
        break;
    }

}

Supervisor::Supervisor() {}; // Конструктор за замовчуванням

void Supervisor::getAllowedActions() { // Реалізація метода для доступних опцій для Supervisor
    cout << "Allowed actions for Supervisor:"; // Вивід меню
    cout << endl << "[1] Available applicants";
    cout << endl << "[2] Enroll applicants";
    cout << endl << "[3] Delete applicants";
    cout << endl << "[4] View enrolled applicants";
    cout << endl << "[5] View deleted applicants";
    cout << endl << "Choose option: ";
    int a = getIntInRange(1, 5);
    switch (a)
    {
    case 1: // Опція читання
        read(applicants);
        break;
    case 2: // Опція зарахування
        enrollApplicant(applicants);
        break;
    case 3: // Опція видалення
        deleteApplicant(applicants);
        break;
    case 4: // Опція перегляду зарахованих
        viewEnrolled(applicants);
        break;
    case 5: // Опція перегляду видалених
        viewDeleted(applicants);
        break;
    default:
        break;
    }

}

void Current::getAllowedActions(Role* role) { // Реалізація методу для поточного користувача
    role->getAllowedActions();
}

NumCheck::NumCheck() {} // Конструктор за замовчуванням
