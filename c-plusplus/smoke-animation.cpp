#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float lifetime;
    float maxLifetime;
};

class SmokeSystem {
private:
    std::vector<Particle> particles;
    GLuint VAO, VBO;
    const int maxParticles = 1000;

public:
    SmokeSystem() {
        setupParticles();
    }

    void setupParticles() {
        // Creates simple quad vertices
        float vertices[] = {
            -0.1f, -0.1f, 0.0f,
             0.1f, -0.1f, 0.0f,
             0.1f, 0.1f, 0.0f,
            -0.1f, 0.1f, 0.0f

        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void emitParticles() {
        if (particles.size() < maxParticles) {
            for (int i = 0; i < 5; i++) {
                Particle p;
                p.position = glm::vec3(0.0f, -0.5f, 0.0f);

                // Disperses randomly
                float angle = (rand() % 360) * 3.14159f / 180.0f;
                float speed = 0.5f + (rand() % 100) / 200.0f;

                p.velocity.x = std::cos(angle) * speed;
                p.velocity.y = 1.0f;
                p.velocity.z = std::sin(angle) * speed;

                p.lifetime = 1.0f;
                p.maxLifetime = 1.0f;

                particles.push_back(p);
            }
        }
    }

    void update(float deltaTime) {
        emitParticles();

        for (auto it = particles.begin(); it != particles.end();) {
            it->lifetime -= deltaTime;
            it->position += it->velocity * deltaTime;

            // Fades
            it->velocity.y *= 0.98f;
            it->velocity.x *= 0.99f;
            it->velocity.z *= 0.99f;

            if (it->lifetime <= 0.0f) {
                it = particles.erase(it);
            } else {
                ++it;
            }
        }
    }

    void render(GLuint shaderProgram) {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        for (const auto& p : particles) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, p.position);

            float alpha = p.lifetime / p.maxLifetime;

            GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
            GLint alphaLoc = glGetUniformLocation(shaderProgram, "alpha");

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
            glUniform1f(alphaLoc, alpha);

            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
    }
};

// Shader sources determine the RGBA color of the visual graphic
const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform mat4 model;

    void main() {
    gl_position = model * vec4(aPos, 1.0);
    }
)";


const char* fragmentShaderSource = R"(
    #version 330 core
    uniform float alpha;

    out vec4 FragColor;

    void main() {
        FragColor = vec4(0.6, 0.2, 0.8, alpha * 0.5);
        // Purple
    }
)";

GLuint compileShaders() {
   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);

   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1 , &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);

   GLuint shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);

   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   return shaderProgram;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Purple Smoke", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint shaderProgram = compileShaders();
    SmokeSystem smoke;

    float lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime = lastTime;
        lastTime = currentTime;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        smoke.update(deltaTime);
        smoke.render(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
