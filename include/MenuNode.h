#ifndef GUINODE_H
#define GUINODE_H

#include "Node.h"
#include "Texture.h"
#include <vector>
#include <functional>

class MenuNode : public Node
{
    public:
        MenuNode(int width);
        virtual ~MenuNode();
        virtual void ResetOptions();
        virtual void AddOption(std::string name, std::function<void()> func, bool available = true);
        virtual void AddDisabledOption(std::string name);
        void CancelAvailable(bool cancel);

        virtual void CheckKeyboardInput();
        virtual void MoveUp();
        virtual void MoveDown();
        void Use();

        int GetScrollPosition();

        void SetMaxShownOptions(int nr);
        void SetBackgroundColor(sf::Color c);
        void SetForegroundColor(sf::Color c);
        void SetForegroundColorDisabled(sf::Color c);
        void SetSelectedColor(sf::Color c);
        void SetOutlineColor(sf::Color c);

        void SetSelectedTexture(Texture * texture);

        void SetPadding(int x, int y);
        void SetFontSize(int s);
        void SetSpacing(int s);

    protected:
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        virtual void UpdateBackground();

        sf::RectangleShape m_background;

        sf::Drawable* m_selectedDrawable;

        int m_paddingX;
        int m_paddingY;

        int m_fontSize;
        int m_spacing;


        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_optionHeight;
        unsigned int m_selected;
        unsigned int m_scrollPosition;
        unsigned int m_maxShownNumber;

        std::vector<std::string> m_optionName;
        std::vector<bool> m_optionAvailable;
        std::vector<std::function<void()>> m_optionFunction;
        bool m_cancelAvailable;

        sf::Color m_backgroundColor;
        sf::Color m_foregroundColor;
        sf::Color m_foregroundColorDisabled;
        sf::Color m_selectedColor;
        sf::Color m_outlineColor;
    private:
};

#endif // GUINODE_H
