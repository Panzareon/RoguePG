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
        sf::Transform getGlobalTransform();
        void setTransform(sf::Transform newTransform);

        void setVisibility(bool visible);


        void moveNode(float x, float y);

        void setParent(Node* parent);
        void addChild(Node* child);
        void removeChild(Node* child);

        virtual void Tick(float seconds);

        void setBoundingBox(sf::FloatRect bb);
        sf::FloatRect getGlobalBoundingBox();
        sf::FloatRect getBoundingBox();
    protected:
    private:
        virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
        sf::Transform m_transform;
        std::vector<Node*> m_children;
        Node* m_parent;

        //Default: 0x0 at 0,0
        sf::FloatRect m_boundingBox;
        bool m_visible;
};

#endif // NODE_H