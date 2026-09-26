#pragma once
class TextureManager {
public:
    enum class Type { Floor, Wall, Wood, Sign };
    static TextureManager& instance();
    void initialize();
    void bind(Type type) const;
private:
    unsigned int textures_[4]{};
    bool initialized_ = false;
    TextureManager() = default;
};
