#ifndef NODE_H
#define NODE_H
#include <SFML/Graphics.hpp>
#include <vector>


class Node
{
    public:
        Node();
        virtual ~Node();
        void draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const;

        sf::Transform getTransform();
        void setTransform(sf::Transform newTransform);

        void addChild(Node* child);
        void removeChild(Node* child);
    protected:
    private:
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        sf::Transform m_transform;
        std::vector<Node*> m_children;
};

#endif // NODE_H
