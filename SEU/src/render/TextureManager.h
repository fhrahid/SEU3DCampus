#pragma once
class TextureManager {
public:
    enum class Type { Floor, Wall, Wood, Sign, Brick };
    static TextureManager& instance();
    void initialize();
    void bind(Type type) const;
private:
    unsigned int textures_[5]{};
    bool initialized_ = false;
    TextureManager() = default;
};
