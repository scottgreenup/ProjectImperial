#include "gameobject.h"

#include "component.h"

GameObject::GameObject() {
}

GameObject::~GameObject() {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        delete (*it);
    }
}

void GameObject::addComponent(Component* component) {
    m_components.push_back(component);
    component->m_gameObject = this;
}

