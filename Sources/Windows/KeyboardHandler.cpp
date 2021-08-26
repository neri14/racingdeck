#include "KeyboardHandler.h"

void keysDown(std::vector<WORD> keys)
{
	int inputsSize = keys.size();
	INPUT *inputs = new INPUT[inputsSize];

	for (int i = 0; i < inputsSize; i++) {
		inputs[i].type = INPUT_KEYBOARD;
		inputs[i].ki.wVk = keys[i];
		inputs[i].ki.dwFlags = 0;
	}
	SendInput(inputsSize, inputs, sizeof(INPUT));
	delete[] inputs;
}

void keysUp(std::vector<WORD> keys)
{
	int inputsSize = keys.size();
	INPUT* inputs = new INPUT[inputsSize];

	for (int i = 0; i < keys.size(); i++) {
		inputs[i].type = INPUT_KEYBOARD;
		inputs[i].ki.wVk = keys[inputsSize - i - 1];
		inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
	}
	SendInput(inputsSize, inputs, sizeof(INPUT));
	delete[] inputs;
}
