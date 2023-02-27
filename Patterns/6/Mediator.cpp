#include "Mediator.h"

void Mediator::passMessage(std::string& message) {
	pLvlGUI->AddPhrase(message);
}