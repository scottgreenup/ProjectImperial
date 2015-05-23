
#include "component.h"

#include "gameobject.h"

Component::Component() {

}

Component::~Component() {

}

GameObject* Component::gameObject() {
    return m_gameObject;
}
