#include "config.h"
#include "triangle_mesh.h"
#include "material.h"

unsigned int make_module(const std::string& filepath, unsigned int module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;
        bufferedLines << line << '\n';
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
    }

    return shaderModule;
}

unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    //To store all the shader modules
    std::vector<unsigned int> modules;

    //Add a vertex shader module
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));

    //Add a fragment shader module
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    //Attach all the modules then link the program
    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules) {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    //Check the linking worked
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader linking error:\n" << errorLog << '\n';
    }

    //Modules are now unneeded and can be freed
    for (unsigned int shaderModule : modules) {
        glDeleteShader(shaderModule);
    }

    return shader;
}

int main()
{
    //#include <Windows.h>
    //TCHAR NPath[MAX_PATH];
    //GetCurrentDirectory(MAX_PATH, NPath);
    //std::cout << NPath << std::endl;
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "GLFW couldn't start\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(640, 480, "My window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    TriangleMesh* triangle = new TriangleMesh();
#ifdef WINDOWS
    Material* material = new Material("../../img/unicorn-llama.png");
#else
    Material* material = new Material("../img/unicorn-llama.png");
    Material* mask = new Material("../img/mask.jpg");
#endif

    unsigned int shader = make_shader(
#ifdef WINDOWS
        "../../src/shaders/vertex.vert",
        "../../src/shaders/fragment.frag"
#else
        "../src/shaders/vertex.vert",
        "../src/shaders/fragment.frag"
#endif
    );

    //set texture units
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "material"), 0);
    glUniform1i(glGetUniformLocation(shader, "mask"), 1);

    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        material->use(0);
        mask->use(1);
        triangle->draw();

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    delete material;
    delete mask;
    delete triangle;
    glfwTerminate();
    return 0;
}