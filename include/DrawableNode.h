#ifndef DRAWABLENODE_H
#define DRAWABLENODE_H

#include <Node.h>


class DrawableNode : public Node
{
    public:
        DrawableNode(sf::Drawable * drawable);
        virtual ~DrawableNode();
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
    protected:
    private:
        sf::Drawable* m_drawable;
};

#endif // DRAWABLENODE_H
