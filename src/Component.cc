
#include "Component.h"

#include "GameObject.h"

Component::Component() {

}

Component::~Component() {

}

GameObject* Component::gameObject() {
    return m_gameObject;
}
