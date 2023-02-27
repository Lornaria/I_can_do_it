#include "Mediator.h"

void Mediator::passMessage(const std::string& message) {
	pLvlGUI->AddPhrase(message);
}