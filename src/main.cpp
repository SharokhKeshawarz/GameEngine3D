#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

#include <AL/al.h>
#include <AL/alc.h>

#include <btBulletDynamicsCommon.h>

int main()
{
    glfwInit();
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Could not init FreeType Library" << std::endl;
    }
    glm::mat4 lol(1.0f);

    ALCdevice* device = alcOpenDevice(nullptr); // open default device
    if (!device) {
        std::cerr << "Cound not init OPENAL" << std::endl;
    }
    
    btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfig);
    dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
        std::cout <<  "Hello" << std::endl;
    glfwTerminate();
    return 0;
}
