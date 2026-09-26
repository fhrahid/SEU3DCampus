#include "Input.h"
#include <cctype>
namespace { unsigned char normalized(unsigned char key) { return static_cast<unsigned char>(std::tolower(key)); } }
void Input::keyDown(unsigned char key) {
    key = normalized(key);
    if (!keys_[key]) presses_[key] = true;
    keys_[key] = true;
}
void Input::keyUp(unsigned char key) { keys_[normalized(key)] = false; }
void Input::specialDown(int key) { if (key >= 0 && key < 256) special_[key] = true; }
void Input::specialUp(int key) { if (key >= 0 && key < 256) special_[key] = false; }
bool Input::held(unsigned char key) const { return keys_[normalized(key)]; }
bool Input::pressed(unsigned char key) const { return presses_[normalized(key)]; }
bool Input::specialHeld(int key) const { return key >= 0 && key < 256 && special_[key]; }
void Input::endFrame() { presses_.fill(false); }
