#include "brickType.h"
//save all info of a level.
brickType::brickType(GLboolean iscolor, glm::vec3 col) : isColor(iscolor), color(col) {}
brickType::brickType(GLboolean iscolor, Texture2D texture) : isColor(iscolor), tex(texture) {}