#pragma once
#include <array>
class Input {
public:
    void keyDown(unsigned char key);
    void keyUp(unsigned char key);
    void specialDown(int key);
    void specialUp(int key);
    bool held(unsigned char key) const;
    bool pressed(unsigned char key) const;
    bool specialHeld(int key) const;
    void endFrame();
private:
    std::array<bool, 256> keys_{};
    std::array<bool, 256> presses_{};
    std::array<bool, 256> special_{};
};
