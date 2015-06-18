#include "gui2_keyvaluedisplay.h"

GuiKeyValueDisplay::GuiKeyValueDisplay(GuiContainer* owner, string id, float div_distance, string key, string value)
: GuiElement(owner, id), div_distance(div_distance), key(key), value(value), text_size(20)
{
}

void GuiKeyValueDisplay::onDraw(sf::RenderTarget& window)
{
    float div_size = 3.0;
    
    draw9Cut(window, rect, "border_background", sf::Color::White);
    draw9Cut(window, rect, "button_background", sf::Color::White, div_distance);
    drawText(window, sf::FloatRect(rect.left, rect.top, rect.width * div_distance - div_size, rect.height), key, ACenterRight, text_size, sf::Color::Black);
    drawText(window, sf::FloatRect(rect.left + rect.width * div_distance + div_size, rect.top, rect.width * (1.0 - div_distance), rect.height), value, ACenterLeft, text_size);
}

GuiKeyValueDisplay* GuiKeyValueDisplay::setKey(string key)
{
    this->key = key;
    return this;
}

GuiKeyValueDisplay* GuiKeyValueDisplay::setValue(string value)
{
    this->value = value;
    return this;
}

GuiKeyValueDisplay* GuiKeyValueDisplay::setTextSize(float text_size)
{
    this->text_size = text_size;
    return this;
}