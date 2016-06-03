#include "MouseAndKeyboard.h"

MouseAndKeyboard::MouseAndKeyboard()
{
}
MouseAndKeyboard::~MouseAndKeyboard()
{
}
bool MouseAndKeyboard::oneKeyPressed(Window &window, int key)
{
	if (keyBoard[key] == 0 && glfwGetKey(window.window, key))
	{
		keyBoard[key] = 1;

		return true;
	}
	if (!glfwGetKey(window.window, key))
	{
		keyBoard[key] = 0;
	}
	return false;
}
bool MouseAndKeyboard::oneButtonPressed(Window &window, int key)
{
	if (buttonBoard[key] == 0 && glfwGetMouseButton(window.window, key))
	{
		buttonBoard[key] = 1;

		return true;
	}
	if (!glfwGetMouseButton(window.window, key))
	{
		buttonBoard[key] = 0;
	}
	return false;
}
bool MouseAndKeyboard::permaKeyPressed(Window &window, int key)
{
	if (oneKeyPressed(window, key))
	{
		keyboardFlags[key] = !keyboardFlags[key];
	}
	return keyboardFlags[key];
}
bool MouseAndKeyboard::permaButtonPressed(Window &window, int key)
{
	if (oneButtonPressed(window, key))
	{
		mouseFlags[key] = !mouseFlags[key];
	}
	return mouseFlags[key];
}
void MouseAndKeyboard::closeWindow(Window &window)
{
	if (glfwGetKey(window.window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window.window, GL_TRUE);
		return;
	}
}
std::string MouseAndKeyboard::getKeybord(Window &window)
{
	if (oneKeyPressed(window, GLFW_KEY_A) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('a');
	}
	else if (oneKeyPressed(window, GLFW_KEY_B) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('b');
	}
	else if (oneKeyPressed(window, GLFW_KEY_C) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('c');
	}
	else if (oneKeyPressed(window, GLFW_KEY_D) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('d');
	}
	else if (oneKeyPressed(window, GLFW_KEY_E) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('e');
	}
	else if (oneKeyPressed(window, GLFW_KEY_F) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('f');
	}
	else if (oneKeyPressed(window, GLFW_KEY_G) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('g');
	}
	else if (oneKeyPressed(window, GLFW_KEY_H) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('h');
	}
	else if (oneKeyPressed(window, GLFW_KEY_I) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('i');
	}
	else if (oneKeyPressed(window, GLFW_KEY_J) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('j');
	}
	else if (oneKeyPressed(window, GLFW_KEY_K) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('k');
	}
	else if (oneKeyPressed(window, GLFW_KEY_L) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('l');
	}
	else if (oneKeyPressed(window, GLFW_KEY_M) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('m');
	}
	else if (oneKeyPressed(window, GLFW_KEY_N) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('n');
	}
	else if (oneKeyPressed(window, GLFW_KEY_O) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('o');
	}
	else if (oneKeyPressed(window, GLFW_KEY_P) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('p');
	}
	else if (oneKeyPressed(window, GLFW_KEY_Q) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('q');
	}
	else if (oneKeyPressed(window, GLFW_KEY_R) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('r');
	}
	else if (oneKeyPressed(window, GLFW_KEY_S) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('s');
	}
	else if (oneKeyPressed(window, GLFW_KEY_T) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('t');
	}
	else if (oneKeyPressed(window, GLFW_KEY_U) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('u');
	}
	else if (oneKeyPressed(window, GLFW_KEY_V) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('v');
	}
	else if (oneKeyPressed(window, GLFW_KEY_W) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('w');
	}
	else if (oneKeyPressed(window, GLFW_KEY_X) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('x');
	}
	else if (oneKeyPressed(window, GLFW_KEY_Y) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('y');
	}
	else if (oneKeyPressed(window, GLFW_KEY_Z) && !oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('z');
	}
	else if (oneKeyPressed(window, GLFW_KEY_A) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('A');
	}
	else if (oneKeyPressed(window, GLFW_KEY_B) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('B');
	}
	else if (oneKeyPressed(window, GLFW_KEY_C) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('C');
	}
	else if (oneKeyPressed(window, GLFW_KEY_D) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('D');
	}
	else if (oneKeyPressed(window, GLFW_KEY_E) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('E');
	}
	else if (oneKeyPressed(window, GLFW_KEY_F) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('F');
	}
	else if (oneKeyPressed(window, GLFW_KEY_G) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('G');
	}
	else if (oneKeyPressed(window, GLFW_KEY_H) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('H');
	}
	else if (oneKeyPressed(window, GLFW_KEY_I) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('I');
	}
	else if (oneKeyPressed(window, GLFW_KEY_J) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('J');
	}
	else if (oneKeyPressed(window, GLFW_KEY_K) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('K');
	}
	else if (oneKeyPressed(window, GLFW_KEY_L) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('L');
	}
	else if (oneKeyPressed(window, GLFW_KEY_M) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('M');
	}
	else if (oneKeyPressed(window, GLFW_KEY_N) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('N');
	}
	else if (oneKeyPressed(window, GLFW_KEY_O) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('O');
	}
	else if (oneKeyPressed(window, GLFW_KEY_P) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('P');
	}
	else if (oneKeyPressed(window, GLFW_KEY_Q) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('Q');
	}
	else if (oneKeyPressed(window, GLFW_KEY_R) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('R');
	}
	else if (oneKeyPressed(window, GLFW_KEY_S) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('S');
	}
	else if (oneKeyPressed(window, GLFW_KEY_T) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('T');
	}
	else if (oneKeyPressed(window, GLFW_KEY_U) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('U');
	}
	else if (oneKeyPressed(window, GLFW_KEY_V) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('V');
	}
	else if (oneKeyPressed(window, GLFW_KEY_W) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('W');
	}
	else if (oneKeyPressed(window, GLFW_KEY_X) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('X');
	}
	else if (oneKeyPressed(window, GLFW_KEY_Y) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('Y');
	}
	else if (oneKeyPressed(window, GLFW_KEY_Z) && oneKeyPressed(window, GLFW_KEY_LEFT_SHIFT))
	{
		sentence.push_back('Z');
	}
	else if (oneKeyPressed(window, GLFW_KEY_0))
	{
		sentence.push_back('0');
	}
	else if (oneKeyPressed(window, GLFW_KEY_1))
	{
		sentence.push_back('1');
	}
	else if (oneKeyPressed(window, GLFW_KEY_2))
	{
		sentence.push_back('2');
	}
	else if (oneKeyPressed(window, GLFW_KEY_3))
	{
		sentence.push_back('3');
	}
	else if (oneKeyPressed(window, GLFW_KEY_4))
	{
		sentence.push_back('4');
	}
	else if (oneKeyPressed(window, GLFW_KEY_5))
	{
		sentence.push_back('5');
	}
	else if (oneKeyPressed(window, GLFW_KEY_6))
	{
		sentence.push_back('6');
	}
	else if (oneKeyPressed(window, GLFW_KEY_7))
	{
		sentence.push_back('7');
	}
	else if (oneKeyPressed(window, GLFW_KEY_8))
	{
		sentence.push_back('8');
	}
	else if (oneKeyPressed(window, GLFW_KEY_9))
	{
		sentence.push_back('9');
	}
	else if (oneKeyPressed(window, GLFW_KEY_BACKSPACE))
	{
		sentence.pop_back();
	}
	if (oneKeyPressed(window, GLFW_KEY_ENTER))
	{
		sentence2 = sentence;
		sentence = "";
		return sentence2;
	}
	else
	{
		return sentence2;
	}
}