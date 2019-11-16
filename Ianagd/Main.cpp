#include "GameCore.h"
#undef main

int main() {

	ian::GameCore::init();

	ian::GameCore::getInstance()->run();

	return 0;
}