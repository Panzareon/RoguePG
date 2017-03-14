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
        virtual void AddOption(std::string name, std::function<void()> func, std::function<void()> onSelect, bool available = true);
        //Add Value at the right on this Option
        virtual void AddValueToOption(int optionNr, std::string value);
        virtual void AddNodeToOption(int optionNr, Node* node);
        virtual void CallOnCancel(std::function<void()> func);
        void CancelAvailable(bool cancel);
        //Does Right Button do something (Default disabled)
        virtual void NextAvailable(bool next);
        //Function to call on Right Button press (Default is function of selected option)
        virtual void CallOnNext(std::function<void()> func);
        //Does Left Button cancel the menu
        virtual void PreviousAvailable(bool prev);

        virtual void CheckKeyboardInput();


        int GetScrollPosition();

        virtual void ShowSelected(bool show);
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
        virtual void MoveUp();
        virtual void MoveDown();
        virtual void MoveRight();
        void Use();
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        virtual void UpdateBackground();

        sf::RectangleShape m_background;

        sf::Drawable* m_selectedDrawable;

        int m_paddingX;
        int m_paddingY;

        int m_fontSize;
        int m_spacing;


        bool m_showSelected;
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_optionHeight;
        unsigned int m_selected;
        unsigned int m_scrollPosition;
        unsigned int m_maxShownNumber;

        std::vector<std::string> m_optionName;
        std::vector<std::string> m_optionValue;
        std::vector<Node*> m_optionNode;
        std::vector<bool> m_optionAvailable;
        std::vector<std::function<void()>> m_optionFunction;
        std::vector<std::function<void()>> m_selectFunction;
        std::function<void()> m_cancelFunction;
        bool m_cancelAvailable;
        std::function<void()> m_nextFunction;
        bool m_nextAvailable;
        bool m_previousAvailable;

        sf::Color m_backgroundColor;
        sf::Color m_foregroundColor;
        sf::Color m_foregroundColorDisabled;
        sf::Color m_selectedColor;
        sf::Color m_outlineColor;
    private:
};

#endif // GUINODE_H
