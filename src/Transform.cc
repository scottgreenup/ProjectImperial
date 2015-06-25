#include "Camera.h"

#include "Transform.h"

Transform::Transform()
: position(glm::vec3(0.0f))
, eulerAngles(glm::vec3(0.0f))
, scale(glm::vec3(1.0f)) {

}

Transform::Transform(const glm::vec3& a_pos)
: position(a_pos)
, eulerAngles(glm::vec3(0.0f))
, scale(glm::vec3(1.0f)) {

}

Transform::Transform(const glm::vec3& a_pos, const glm::vec3& a_euler) : position(a_pos)
, eulerAngles(a_euler)
, scale(glm::vec3(1.0f)) {

}

Transform::Transform(const glm::vec3& a_pos, const glm::vec3& a_euler, const glm::vec3& a_scale)
: position(a_pos)
, eulerAngles(a_euler)
, scale(a_scale) {

}

Transform::~Transform() {

}

glm::mat4 Transform::Model() const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);
    model = glm::rotate(model, this->eulerAngles.x, glm::vec3(1,0,0));
    model = glm::rotate(model, this->eulerAngles.y, glm::vec3(0,1,0));
    model = glm::rotate(model, this->eulerAngles.z, glm::vec3(0,0,1));
    model = glm::scale(model, this->scale);

    return model;
}

glm::mat4 Transform::ModelView() const {
    glm::mat4 view = Camera::Get().GetViewMatrix();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);
    model = glm::rotate(model, this->eulerAngles.x, glm::vec3(1,0,0));
    model = glm::rotate(model, this->eulerAngles.y, glm::vec3(0,1,0));
    model = glm::rotate(model, this->eulerAngles.z, glm::vec3(0,0,1));
    model = glm::scale(model, this->scale);

    return view * model;
}

glm::mat4 Transform::MVP() const {
    glm::mat4 projection = Camera::Get().GetProjectionMatrix();
    glm::mat4 view = Camera::Get().GetViewMatrix();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), this->position);
    model = glm::rotate(model, this->eulerAngles.x, glm::vec3(1,0,0));
    model = glm::rotate(model, this->eulerAngles.y, glm::vec3(0,1,0));
    model = glm::rotate(model, this->eulerAngles.z, glm::vec3(0,0,1));
    model = glm::scale(model, this->scale);

    glm::mat4 mvp = projection * view * model;
    return mvp;
}
