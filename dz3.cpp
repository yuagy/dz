#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <windows.h>

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const std::string& msg) = 0;
};

// Три конкретные реализации логгеров

class ConsoleLogger : public Logger {
public:
    void log(const std::string& msg) override {
        std::cout << "[Console] " << msg << std::endl;
    }
};

class FileLogger : public Logger {
private:
    std::ofstream file_; // Поток для записи в файл

public:
    // Конструктор принимает имя файла
    explicit FileLogger(const std::string& filename) : file_(filename, std::ios::app) {} // Открываем файл в режиме "дописывания"

    void log(const std::string& msg) override {
        if (file_.is_open()) { // Проверка: удалось ли открыть файл
            file_ << "[File] " << msg << std::endl;
        }
    }
};

class NullLogger : public Logger {
public:
    void log(const std::string& /*msg*/) override {}
};

// Абстрактная фабрика и три конкретные фабрики

class LoggerFactory {
public:
    virtual ~LoggerFactory() = default;
    virtual std::unique_ptr<Logger> createLogger() = 0;
};

class ConsoleLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<ConsoleLogger>();
    }
};

class FileLoggerFactory : public LoggerFactory {
private:
    std::string filename_;
public:
    explicit FileLoggerFactory(const std::string& filename) : filename_(filename) {}

    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<FileLogger>(filename_);
    }
};

class NullLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<Logger> createLogger() override {
        return std::make_unique<NullLogger>();
    }
};

// Application 

class Application {
private:
    std::unique_ptr<Logger> logger_;
public:
    explicit Application(std::unique_ptr<LoggerFactory> factory) : logger_(factory->createLogger()) {}

    void run() {
        logger_->log("Application started");
        logger_->log("Processing data...");
        logger_->log("Application finished");
    }
};

int main() {
    SetConsoleCP(65001);    
    SetConsoleOutputCP(65001);
    std::cout << "=== Console Logger ===\n";
    {
        auto app = Application(std::make_unique<ConsoleLoggerFactory>());
        app.run();
    }

    std::cout << "\n=== File Logger ===\n";
    {
        
        auto app = Application(std::make_unique<FileLoggerFactory>("app.log"));
        app.run();
        std::cout << "(Логи записаны в файл app.log)\n";
    }

    std::cout << "\n=== Null Logger ===\n";
    {
        
        auto app = Application(std::make_unique<NullLoggerFactory>());
        app.run();
        std::cout << "(NullLogger успешно подавил весь вывод)\n";
    }

    return 0;
}