#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>

class Component  {
friend class GameObject;

public:
    Component();
    virtual ~Component();

    class GameObject* gameObject();

private:
    class GameObject* m_gameObject;
};

#endif
