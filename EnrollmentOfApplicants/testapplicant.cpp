#include "Applicant.hpp"
#include <limits>   // для getIntInRange
#include <cstdlib>

using namespace std;

void clear_screen() {   // Функція для очищення екрану
    system("cls");
}

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

// Збереження абітурієнтів у бінарний файл
void saveApplicantsToFile(const string& filename) {
    ofstream file(filename, ios::binary); // Відкриваємо файл в бінарному режимі
    if (!file.is_open()) {
        cout << "Error: Unable to open file for saving." << endl;
        return;
    }
    for (int i = 0; i < 4; i++) {
        applicants[i].saveToFile(file);
    }
    file.close();
    cout << "Applicants saved successfully!" << endl;
}

// Завантаження абітурієнтів з бінарного файлу
void loadApplicantsFromFile(const string& filename) {
    ifstream file(filename, ios::binary); // Відкриваємо файл в бінарному режимі
    if (!file.is_open()) {
        cout << "Error: Unable to open file for loading." << endl;
        return;
    }
    for (int i = 0; i < 4; i++) {
        applicants[i].loadFromFile(file);
    }
    file.close();
    cout << "Applicants loaded successfully!" << endl;
}

void getNumber(int menu_option) { // Функція для виключення перевіряє вірність введення
    if (menu_option < 0 || menu_option > 6) {
        throw NumCheck();
    }
}

int main() {
    // Призначення початкових даних абітурієнту
    Applicant Applicant1("Patsukevych Dmytro Olexandrovich", 18, "121 Software Engineering", 9.5, "Contract");
    Applicant Applicant2;
    Applicant2 = Applicant1; // Використав оператор присвоєння

    // Призначення початкових даних абітурієнту 3 з освітою
    Applicant3 Applicant3("Nechiporenko Oleg Viktorovych", 19, "121 Software Engineering", 6.8, "Contract", "High school");
    // Призначення початкових даних абітурієнту 4 з адресою
    Applicant4 Applicant4("Olena Ukrainka Serhiivna", 17, "121 Software Engineering", 3.9, "Contract", "Kyiv, Svyatoshinska 83");

    Current current;

    applicants[0] = Applicant1;
    applicants[1] = Applicant2;
    applicants[2] = Applicant3;
    applicants[3] = Applicant4;

    do {
        clear_screen();
        cout << "[1] User" << endl;
        cout << "[2] Admin" << endl;
        cout << "[3] Manager" << endl;
        cout << "[4] Supervisor" << endl;
        cout << "[5] Save applicants to file" << endl;
        cout << "[6] Load applicants from file" << endl;
        cout << "[0] Exit" << endl << endl;
        cout << "Choose your role or option: ";

        int menu_option = getIntInRange(0, 6);

        try { // Використовую виключення
            getNumber(menu_option);

        }
        catch (NumCheck& ex) {
            cout << "Invalid input." << ex.what() << endl;
        }

        switch (menu_option) {
        case 1: { // Меню опція для User
            clear_screen();
            User user;
            current.getAllowedActions(&user);
            break;
        }
        case 2: { // Меню опція для Admin
            clear_screen();
            Admin admin;
            current.getAllowedActions(&admin);
            break;
        }
        case 3: { // Меню опція для Manager
            clear_screen();
            Manager manager;
            current.getAllowedActions(&manager);
            break;
        }
        case 4: {
            clear_screen(); // Меню опція для Supervisor
            Supervisor supervisor;
            current.getAllowedActions(&supervisor);
            break;
        }
        case 5: { // Збереження абітурієнтів у файл
            saveApplicantsToFile("applicants.bin");
            break;
        }
        case 6: { // Завантаження абітурієнтів із файлу
            loadApplicantsFromFile("applicants.bin");
            break;
        }
        case 0: // Вихід з меню
            return 0;
        default:
            cout << "Invalid option!" << endl;
            break;
        }
        cout << "\nPress enter to get back." << endl;
        cin.ignore();
        cin.get();

    } while (true);

    return 0;
}
