#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <cstring>

class MagicSpell {
private:
    char* spellName_;
    int powerLevel_;
    
public:
    // Конструктор
    explicit MagicSpell(const char* name, int power = 0) 
        : powerLevel_(power) {
        size_t len = std::strlen(name) + 1;
        spellName_ = new char[len];
        std::strcpy(spellName_, name);
        std::cout << "MagicSpell created: " << spellName_ << std::endl;
    }
    
    // 1. Деструктор
    ~MagicSpell() {
        std::cout << "MagicSpell destroyed: " << (spellName_ ? spellName_ : "null") << std::endl;
        delete[] spellName_;
    }
    
    // 2. Копирующий конструктор
    MagicSpell(const MagicSpell& other) 
        : powerLevel_(other.powerLevel_) {
        size_t len = std::strlen(other.spellName_) + 1;
        spellName_ = new char[len];
        std::strcpy(spellName_, other.spellName_);
        std::cout << "MagicSpell copied: " << spellName_ << std::endl;
    }
    
    // 3. Копирующий оператор присваивания
    MagicSpell& operator=(const MagicSpell& other) {
        if (this != &other) {
            // Освобождаем старые ресурсы
            delete[] spellName_;
            
            // Копируем новые ресурсы
            powerLevel_ = other.powerLevel_;
            size_t len = std::strlen(other.spellName_) + 1;
            spellName_ = new char[len];
            std::strcpy(spellName_, other.spellName_);
            std::cout << "MagicSpell copy-assigned: " << spellName_ << std::endl;
        }
        return *this;
    }
    
    // 4. Move-конструктор
    MagicSpell(MagicSpell&& other) noexcept 
        : spellName_(other.spellName_), powerLevel_(other.powerLevel_) {
        // "Забираем" ресурсы у other
        other.spellName_ = nullptr;
        other.powerLevel_ = 0;
        std::cout << "MagicSpell moved (constructor)" << std::endl;
    }
    
    // 5. Move-оператор присваивания
    MagicSpell& operator=(MagicSpell&& other) noexcept {
        if (this != &other) {
            // 1. Освобождаем свои ресурсы
            delete[] spellName_;
            
            // 2. Забираем ресурсы у other
            spellName_ = other.spellName_;
            powerLevel_ = other.powerLevel_;
            
            // 3. Обнуляем other
            other.spellName_ = nullptr;
            other.powerLevel_ = 0;
            
            std::cout << "MagicSpell moved (assignment)" << std::endl;
        }
        return *this;
    }
    
    void cast() const {
        if (spellName_) {
            std::cout << "Casting spell: " << spellName_ << " (power: " << powerLevel_ << ")" << std::endl;
        } else {
            std::cout << "Spell is empty (was moved)" << std::endl;
        }
    }
    
    void boostPower(int amount) {
        powerLevel_ += amount;
    }
};


class Wizard {
private:
    std::unique_ptr<MagicSpell> exclusiveSpell_;
    std::string name_;
    
public:
    explicit Wizard(const std::string& name) : name_(name) {
        std::cout << "Wizard " << name_ << " created" << std::endl;
    }
    
    ~Wizard() {
        std::cout << "Wizard " << name_ << " destroyed" << std::endl;
    }
    
    // Принимаем владение заклинанием
    void learnSpell(std::unique_ptr<MagicSpell> spell) {
        exclusiveSpell_ = std::move(spell);  // Явное перемещение
        std::cout << name_ << " learned a new spell!" << std::endl;
    }
    
    // Передаем владение заклинанием другому волшебнику
    std::unique_ptr<MagicSpell> transferSpell() {
        std::cout << name_ << " transfers spell ownership" << std::endl;
        return std::move(exclusiveSpell_);  
    }
    
    void castSpell() const {
        std::cout << name_ << " attempts to cast: ";
        if (exclusiveSpell_) {
            exclusiveSpell_->cast();
        } else {
            std::cout << "No spell learned!" << std::endl;
        }
    }
    
    bool hasSpell() const {
        return exclusiveSpell_ != nullptr;
    }
};


class Arena {
public:
    std::string name;
    
    explicit Arena(const std::string& arenaName) : name(arenaName) {
        std::cout << "Arena '" << name << "' created" << std::endl;
    }
    
    ~Arena() {
        std::cout << "Arena '" << name << "' destroyed" << std::endl;
    }
    
    void battleInfo() const {
        std::cout << "Battle taking place at: " << name << std::endl;
    }
};

class Team {
private:
    std::shared_ptr<Arena> battleArena_;
    std::string teamName_;
    
public:
    Team(const std::string& name, std::shared_ptr<Arena> arena)
        : teamName_(name), battleArena_(std::move(arena)) {
        std::cout << "Team '" << teamName_ << "' formed" << std::endl;
        std::cout << "Arena use_count: " << battleArena_.use_count() << std::endl;
    }
    
    void displayArenaInfo() const {
        if (battleArena_) {
            std::cout << "Team '" << teamName_ << "' is at arena: ";
            battleArena_->battleInfo();
            std::cout << "Current use_count: " << battleArena_.use_count() << std::endl;
        }
    }
    
    std::shared_ptr<Arena> getArena() const {
        return battleArena_;
    }
    
    std::string getName() const {
        return teamName_;
    }
};


class Spectator {
private:
    std::weak_ptr<Arena> observedArena_;
    std::string name_;
    
public:
    Spectator(const std::string& name, std::weak_ptr<Arena> arena)
        : name_(name), observedArena_(arena) {
        std::cout << "Spectator '" << name_ << "' arrived" << std::endl;
    }
    
    void watchBattle() {
        // Безопасный доступ через lock()
        std::shared_ptr<Arena> arena = observedArena_.lock();
        
        if (arena) {
            std::cout << name_ << " is watching battle at: " << arena->name << std::endl;
            std::cout << "Arena is still alive (use_count: " << arena.use_count() << ")" << std::endl;
        } else {
            std::cout << name_ << " sees no battle - arena is destroyed!" << std::endl;
        }
    }
};

// Тесты
void testMagicSpell() {
    std::cout << "\n=== Testing MagicSpell (Rule of Five) ===" << std::endl;
    
    // Создание
    MagicSpell fireball("Fireball", 100);
    fireball.cast();
    
    // Копирование
    MagicSpell fireballCopy = fireball;
    fireballCopy.boostPower(50);
    fireballCopy.cast();
    
    // Перемещение
    MagicSpell movedSpell = std::move(fireball);
    movedSpell.cast();
    fireball.cast();  // фаербол теперь в пустом состоянии
    
    // Присваивание
    MagicSpell lightning("Lightning Bolt", 75);
    lightning = std::move(movedSpell);
    lightning.cast();
}

void testWizard() {
    std::cout << "\n=== Testing Wizard (unique_ptr) ===" << std::endl;
    
    Wizard gandalf("Gandalf");
    Wizard saruman("Saruman");
    
    // Создаем заклинание
    auto spell = std::make_unique<MagicSpell>("Ice Storm", 90);
    
    // Гэндальф изучает заклинание
    gandalf.learnSpell(std::move(spell));
    gandalf.castSpell();
    
    // Передача владения Саруману
    saruman.learnSpell(gandalf.transferSpell());
    
    // Проверяем состояние
    gandalf.castSpell();  // У Гендальфа больше нет заклинания
    saruman.castSpell();  // Теперь заклинание у Сарумана
}

void testTeamAndSpectator() {
    std::cout << "\n=== Testing Team and Spectator (shared_ptr/weak_ptr) ===" << std::endl;
    
    // Создаем арену
    auto arena = std::make_shared<Arena>("Grand Colosseum");
    std::cout << "Initial use_count: " << arena.use_count() << std::endl;
    
    // Создаем команды, разделяющие арену
    Team team1("Blue Dragons", arena);
    Team team2("Red Phoenix", arena);
    
    std::cout << "\nAfter creating teams:" << std::endl;
    team1.displayArenaInfo();
    team2.displayArenaInfo();
    
    // Создаем зрителя 
    Spectator spectator("Elrond", arena);
    
    // Зритель наблюдает
    std::cout << "\nSpectator watching:" << std::endl;
    spectator.watchBattle();
    
    // Команды покидают арену
    std::cout << "\nTeams leaving..." << std::endl;
    {
        Team team3("Green Serpents", arena);
        team3.displayArenaInfo();
    } // team3 уничтожается здесь
    
    std::cout << "\nAfter team3 destruction:" << std::endl;
    std::cout << "use_count: " << arena.use_count() << std::endl;
    
    // Уничтожаем первые две команды
    std::cout << "\nDestroying all teams..." << std::endl;
    arena.reset();  
    
    // Зритель пытается наблюдать после уничтожения арены
    std::cout << "\nSpectator trying to watch after arena destruction:" << std::endl;
    spectator.watchBattle();
}

int main() {
    std::cout << "===== HOMEWORK: Smart Pointers and Move Semantics =====\n" << std::endl;
    
    // Запуск всех тестов
    testMagicSpell();
    testWizard();
    testTeamAndSpectator();
    
    std::cout << "\n===== All tests completed =====" << std::endl;
    return 0;
}