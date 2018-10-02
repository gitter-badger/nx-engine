#pragma once

#include <string>

#include "font-manager/Font.h"
#include "vectors/Vector2.h"
#include "common/Color.h"

enum TextAlignFlags
{
    FREE = 0x0,
    // Horizontal alignment
    LEFT = 0x1,
    CENTER = 0x2,
    RIGHT = 0x4,
    // Vertical
    TOP = 0x8,
    MIDDLE = 0x10,
    BOTTOM = 0x20,
};

class Text
{
  private:
    std::string m_text;
    Font *m_font = nullptr;
    Vector2 m_position;
    Color m_color;
    unsigned int align;

    float m_paddingLeft = 5.0f;
    float m_paddingTop = 5.0f;
    float m_paddingRight = 5.0f;
    float m_paddingBottom = 5.0f;

  public:
    Text(const std::string &text, Font *font, const Vector2 &position, const Color &color);
    Text(const std::string &text, Font *font, const Vector2 &position, const Color &color, unsigned int align);

    ~Text();

    const std::string &getText() const;
    const Vector2 &getPosition() const;
    const Font *getFont() const;
    const Color &getColor() const;
    const Vector2 getTextDims();
    unsigned int getAlignmentFlags() const;

    float getPaddingLeft() const;
    float getPaddingRight() const;
    float getPaddingTop() const;
    float getPaddingBottom() const;

    void setText(const std::string &text);
    void setPosition(const Vector2 &position);
    void setColor(const Color &color);
    void setAlignmentFlags(unsigned int flags) const;

    void setPaddings(float left, float top, float right, float bottom);
    void setPaddingLeft(float p);
    void setPaddingRight(float p);
    void setPaddingTop(float p);
    void setPaddingBottom(float p);
};