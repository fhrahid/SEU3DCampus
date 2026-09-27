#pragma once
class Input;
namespace render { void text2d(int, int, const char*, struct Color); }
class MiniGame {
public:
    virtual ~MiniGame() = default;
    virtual void reset() = 0;
    virtual void update(const Input& input) = 0;
    virtual void render(int width, int height) const = 0;
    virtual const char* title() const = 0;
};
