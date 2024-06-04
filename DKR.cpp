#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

class Tariff {
private:
    std::string name;
    double monthlyFee;
    int clientsCount;

public:
    // Конструктори
    Tariff() : name(""), monthlyFee(0.0), clientsCount(0) {}
    Tariff(std::string n, double m, int c) : name(n), monthlyFee(m), clientsCount(c) {}

    // Методи set і get
    void setName(std::string n) { name = n; }
    std::string getName() const { return name; }

    void setMonthlyFee(double m) { monthlyFee = m; }
    double getMonthlyFee() const { return monthlyFee; }

    void setClientsCount(int c) { clientsCount = c; }
    int getClientsCount() const { return clientsCount; }

    // Метод toString
    std::string toString() const {
        std::ostringstream oss;
        oss << "Tariff: " << name << ", Monthly Fee: " << monthlyFee << ", Clients Count: " << clientsCount;
        return oss.str();
    }

    // Перевантаження оператора <<
    friend std::ostream& operator<<(std::ostream& os, const Tariff& tariff) {
        os << tariff.toString();
        return os;
    }
};

// Функція для шифрування (простий приклад шифрування)
std::string encrypt(const std::string& data) {
    std::string encrypted = data;
    for (char& c : encrypted) {
        c += 1; // Просте шифрування: зрушення на 1
    }
    return encrypted;
}

// Функція для збереження в файл
void saveToFile(const std::vector<Tariff>& tariffs, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Tariff& tariff : tariffs) {
            file << encrypt(tariff.toString()) << std::endl;
        }
        file.close();
    }
}

// Клас для логування
class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
};

// Функція для сортування тарифів за розміром абонентської плати
void sortTariffsByFee(std::vector<Tariff>& tariffs) {
    std::sort(tariffs.begin(), tariffs.end(), [](const Tariff& a, const Tariff& b) {
        return a.getMonthlyFee() < b.getMonthlyFee();
        });
}

// Функція для пошуку тарифу за заданим діапазоном параметрів
Tariff findTariff(const std::vector<Tariff>& tariffs, double minFee, double maxFee) {
    for (const Tariff& tariff : tariffs) {
        if (tariff.getMonthlyFee() >= minFee && tariff.getMonthlyFee() <= maxFee) {
            return tariff;
        }
    }
    // Повертаємо "порожній" тариф, якщо нічого не знайдено
    return Tariff();
}

int main() {
    // Створення списку тарифів
    std::vector<Tariff> tariffs = {
        Tariff("Basic", 10.0, 100),
        Tariff("Premium", 20.0, 200),
        Tariff("Gold", 30.0, 150)
    };

    // Підрахунок загальної чисельності клієнтів
    int totalClients = 0;
    for (const Tariff& tariff : tariffs) {
        totalClients += tariff.getClientsCount();
    }
    std::cout << "Total Clients: " << totalClients << std::endl;

    // Сортування тарифів за розміром абонентської плати
    sortTariffsByFee(tariffs);
    std::cout << "Sorted Tariffs:" << std::endl;
    for (const Tariff& tariff : tariffs) {
        std::cout << tariff << std::endl;
    }

    // Пошук тарифу за заданим діапазоном параметрів
    double minFee = 15.0;
    double maxFee = 25.0;
    Tariff foundTariff = findTariff(tariffs, minFee, maxFee);
    std::cout << "Found Tariff in range [" << minFee << ", " << maxFee << "]:" << std::endl;
    std::cout << foundTariff << std::endl;

    // Збереження даних у файл
    saveToFile(tariffs, "tariffs.txt");

    // Логування
    Logger logger("log.txt");
    logger.log("Program finished successfully.");

    return 0;
}
