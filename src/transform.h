#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <glm/glm.hpp>

/**
 * The Transform class is the base for any object that has a position in the
 * game world.
 *
 */
class Transform {
public:

    Transform();
    Transform(const glm::vec3& pos);
    Transform(const glm::vec3& pos, const glm::vec3& euler);
    Transform(const glm::vec3& pos, const glm::vec3& euler, const glm::vec3& scale);

    glm::mat4 MVP();

    virtual ~Transform();

    glm::vec3 position;
    glm::vec3 eulerAngles;
    glm::vec3 scale;
};

#endif
