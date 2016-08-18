#include "material.h"

Material::Material()
{    
    ambient = QVector4D(.3, .3, .3, 1.0);
    diffuse = QVector4D(1, 1, 1, 1.0);
    specular = QVector4D(1, 1, 1, 1.0);
    shininess = 100.0;
}
