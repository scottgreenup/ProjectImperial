#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <vector>

class GameObject {
public:
    GameObject();
    virtual ~GameObject();

    void update();
    void render();

    void addComponent(class Component* component);

    template<class T>
    T* getComponent() {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        T* t = dynamic_cast<T*>(*it);

        if (t != nullptr) {
            return t;
        }
    }

    return nullptr;
}

private:
    std::vector<class Component*> m_components;
}; 

#endif
