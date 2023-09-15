
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

// Particle structure definition
struct Particle {
    float x, y;       // Position
    float vx, vy;     // Velocity
    float age;        // Current age
    float lifespan;   // Maximum age before the particle dies
};

const int MAX_PARTICLES = 1000;
Particle particles[MAX_PARTICLES];

const float GRAVITY = -0.001f;

// Current mouse position
float mouseX = 0.0f, mouseY = 0.0f;

// Callback to update mouse position
void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    mouseX = (xpos / width) * 2.0f - 1.0f;
    mouseY = 1.0f - (ypos / height) * 2.0f;
}

// Initialize the particles
void initParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = 0.0f;
        particles[i].y = 0.0f;
        particles[i].vx = 0.0f;
        particles[i].vy = 0.0f;
        particles[i].age = -1.0f;
        particles[i].lifespan = 0.0f;
    }
}

// Spawn particles at the current mouse position
void spawnParticlesAtMouse(int count) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].age == -1.0f && count > 0) {
            particles[i].x = mouseX;
            particles[i].y = mouseY;
            particles[i].vx = ((rand() % 50) - 25) / 10000.0f;
            particles[i].vy = 0.02f + (rand() % 10) / 1000.0f;
            particles[i].age = 0.0f;
            particles[i].lifespan = 1.0f + (rand() % 1000) / 1000.0f;
            count--;
        }
    }
}

// Update the particles based on elapsed time
void updateParticles(float deltaTime) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].age != -1.0f) {
            particles[i].x += particles[i].vx * deltaTime;
            particles[i].y += particles[i].vy * deltaTime;
            particles[i].vy += GRAVITY * deltaTime;
            particles[i].age += deltaTime;

            if (particles[i].age > particles[i].lifespan) {
                particles[i].age = -1.0f;
            }
        }
    }
}

// Render the particles
void renderParticles() {
    glColor3f(1.0f, 0.5f, 0.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].age != -1.0f) {
            glVertex2f(particles[i].x, particles[i].y);
        }
    }
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Particle System", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    initParticles();

    glfwSetCursorPosCallback(window, mousePosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        spawnParticlesAtMouse(10);
        updateParticles(0.016f);
        renderParticles();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
