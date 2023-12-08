#include <iostream>

#include "tododriver.h"
#include "parser.h"

auto TodoDriver::run() -> int {
    Action action;
    while (action.type != ActionType::Quit) {
        if (action.type == ActionType::Create) {
            todoManager.createTodo(action.name);
        } else if (action.type == ActionType::Update) {
            todoManager.updateTodo(action.index, action.name);
        } else if (action.type == ActionType::Delete) {
            todoManager.deleteTodo(action.index);
        } else if (action.type == ActionType::Help) {
            displayHelp();
        } else if (action.type == ActionType::Undo) {
            todoManager.undo();
        }

        displayTodos();
        try {
            action = getAction();
        } catch (std::exception & e) {
            std::cout << "Unknown command" << std::endl;
            action.type = ActionType::Read;
        }
    }
    return 0;
}

Action TodoDriver::getAction() {
    std::string commandLine;
    if (std::cin.eof()) {
        return Action{ActionType::Quit, "", 0};
    }
    std::getline(std::cin, commandLine);
    return parseAction(commandLine);
}

void TodoDriver::displayTodos() {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "TODO Manager 0.1 (my little pony edition)" << std::endl;
    size_t id = 0;
    for (auto const & todo : todoManager.getTodos()) {
        std::cout << " * (id: " << id << ") " << todo.getName() << std::endl;
        ++id;
    }
}

void TodoDriver::displayHelp() {
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Available commands: " << std::endl;
    std::cout << "create <todo> --> Create a new todo" << std::endl;
    std::cout << "read --> List all todos" << std::endl;
    std::cout << "update <id> new name --> Update an existing todo" << std::endl;
    std::cout << "delete <id> --> Delete an existing todo" << std::endl;
}
