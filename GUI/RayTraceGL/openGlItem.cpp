#include "openGlItem.h"

OpenGLItem::OpenGLItem() {

}

void OpenGLItem::setColor(const glm::vec3 &c) {
    color = c;
}

void OpenGLItem::setPosition(const glm::vec3 &pos) {
    mPos = pos;
}

void OpenGLItem::setAlpha(const float &a) {
    alpha = a;
}

glm::vec3 OpenGLItem::getPoint(int index) {
    glm::vec3 tempPos(0.0f);
    if(index > (vertices.size() / 3)) {
        return tempPos;
    }
    int vertPos = index * 3;
    tempPos.x = vertices[vertPos++];
    tempPos.y = vertices[vertPos++];
    tempPos.z = vertices[vertPos];
    return tempPos;
}
