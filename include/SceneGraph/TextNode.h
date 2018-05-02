#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "Node.h"


class TextNode : public Node
{
    public:
        TextNode(std::string text = "");
        virtual ~TextNode();
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;

        void SetFontSize(int fontSize);
        void SetText(std::string text);
        void SetColor(sf::Color c);
        void SetMaxLength(int length);

        virtual sf::FloatRect getBoundingBox();
    protected:
        void UpdateString();

        sf::Text m_text;
        int m_maxLength;

    private:
};

#endif // TEXTNODE_H
