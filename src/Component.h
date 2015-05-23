#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>

class Component  {
friend class GameObject;

public:
    Component();
    virtual ~Component();

    class GameObject* gameObject();
    virtual std::string toString() = 0;

private:
    class GameObject* m_gameObject;
};

#endif
