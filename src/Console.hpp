#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <mutex>
#include "Environment.hpp"

class Console {
public:
	Console(Environment* env);
	void run();
private:
	std::mutex m;
	bool m_running = true;
	Environment* m_env;

	void interpret(const std::string& command);
};

#endif /* CONSOLE_HPP */