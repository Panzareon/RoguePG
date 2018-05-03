#ifndef GUINODE_H
#define GUINODE_H

#include "Node.h"
#include "Texture.h"
#include <vector>
#include <functional>
#include "SceneGraph/MenuNodeOption.h"

class MenuNode : public Node
{
    public:
        MenuNode(int width);
        virtual ~MenuNode();
        virtual void ResetOptions();
        virtual void AddOption(std::string name, std::function<void()> func, bool available = true);
        virtual void AddDisabledOption(std::string name);
        virtual void AddDisabledOption(std::string name, std::function<void()> onSelect);
        virtual void AddOption(std::string name, std::function<void()> func, std::function<void()> onSelect, bool available = true);
        //Add Value at the right on this Option
        virtual void AddValueToOption(int optionNr, std::string value);
        virtual void AddNodeToOption(int optionNr, Node* node);
        virtual void SetAvailableForOption(int option, bool available);
        virtual void CallOnCancel(std::function<void()> func);
        //Function is called after Sorting, first value is the sorted item, second value is the new position
        void EnableSorting(std::function<void(int,int)> onSort);
        void CancelAvailable(bool cancel);
        //Does Right Button do something (Default disabled)
        virtual void NextAvailable(bool next);
        //Function to call on Right Button press (Default is function of selected option)
        virtual void CallOnNext(std::function<void()> func);
        //Does Left Button cancel the menu
        virtual void PreviousAvailable(bool prev);

        virtual void CheckKeyboardInput();


        int GetScrollPosition();
        int GetNrOptions();

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

        //Is this Menu still visible when a submenu of this is active
        void SetVisibleWithSubmenu(bool visible);

    protected:
        virtual void MoveUp();
        virtual void MoveDown();
        virtual void MoveRight();
        void Use();
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        virtual void UpdateBackground();
        virtual void SortOption();

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

        std::vector<MenuNodeOption*> m_options;
        std::function<void(int, int)> m_sortFunction;
        std::function<void()> m_cancelFunction;
        bool m_cancelAvailable;
        std::function<void()> m_nextFunction;
        bool m_nextAvailable;
        bool m_previousAvailable;

        bool m_sortingAvailable;
        bool m_isMovingOption;
        int m_startingPosition;

        bool m_visibleWithSubmenu;

        sf::Color m_backgroundColor;
        sf::Color m_foregroundColor;
        sf::Color m_foregroundColorDisabled;
        sf::Color m_selectedColor;
        sf::Color m_outlineColor;
    private:
};

#endif // GUINODE_H
