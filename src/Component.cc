
#include "Component.h"

#include "GameObject.h"

Component::Component()
: m_gameObject(nullptr) {

}

Component::~Component() {

}

GameObject* Component::gameObject() {
    return m_gameObject;
}
