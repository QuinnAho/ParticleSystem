#include <GLFW/glfw3.h>


// Particle structure definition
struct Particle {
    float x, y;       // Position
    float vx, vy;     // Velocity
    float age;        // Current age
    float lifespan;   // Maximum age before the particle dies
};

const int MAX_PARTICLES = 1000;
Particle particles[MAX_PARTICLES];

// Initialize the particles
void initParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = 0.0f;
        particles[i].y = 0.0f;
        particles[i].vx = ((rand() % 200) - 100) / 1000.0f;  // Random velocity between -0.1 and 0.1
        particles[i].vy = ((rand() % 200) - 100) / 1000.0f;
        particles[i].age = 0.0f;
        particles[i].lifespan = 1.0f + (rand() % 1000) / 1000.0f;  // Random lifespan between 1.0 and 2.0 seconds
    }
}

// Update the particles based on elapsed time
void updateParticles(float deltaTime) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x += particles[i].vx * deltaTime;
        particles[i].y += particles[i].vy * deltaTime;
        particles[i].age += deltaTime;
        
        if (particles[i].age > particles[i].lifespan) {
            // Reset particle to the center when it dies
            particles[i].x = 0.0f;
            particles[i].y = 0.0f;
            particles[i].vx = ((rand() % 200) - 100) / 1000.0f;
            particles[i].vy = ((rand() % 200) - 100) / 1000.0f;
            particles[i].age = 0.0f;
        }
    }
}

// Render the particles
void renderParticles() {
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        glVertex2f(particles[i].x, particles[i].y);
    }
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
       
        initParticles();


        updateParticles(0.016f);  // Assuming 60 FPS
renderParticles();

        glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.0f);
        glEnd();

        //draw a line

        glBegin(GL_LINES);

        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.5f, 0.5f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}