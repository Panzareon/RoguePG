#ifndef MENUNODEOPTION_H
#define MENUNODEOPTION_H

#include <string>
#include "SceneGraph/Node.h"
#include <functional>

class MenuNodeOption
{
    public:
        MenuNodeOption(std::string name, bool available = true);
        virtual ~MenuNodeOption();
        void SetValue(std::string value);
        void SetNode(Node* node);
        void SetAvailable(bool available);
        void SetFunction(std::function<void()> addFunction);
        void SetSelectFunction(std::function<void()> addFunction);

        std::string GetName();
        std::string GetValue();
        Node* GetNode();
        bool IsAvailable();

        void CallFunction();
        void CallSelectFunction();

    protected:
        std::string m_name;
        std::string m_value;
        Node* m_node;
        bool m_available;
        std::function<void()> m_function;
        std::function<void()> m_selectFunction;

    private:
};

#endif // MENUNODEOPTION_H
