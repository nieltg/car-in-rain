#include "Scene.h"


const char* defaultVertexShaderSource = R"(
#version 140

attribute vec3 coord3d;
attribute vec2 texcoord;
varying vec2 f_texcoord;
uniform mat4 mvp;

void main(void) {
  gl_Position = mvp * vec4(coord3d, 1.0);
  f_texcoord = texcoord;
}
)";

const char* defaultFragmentShaderSource = R"(
#version 140

varying vec2 f_texcoord;
// uniform sampler2D mytexture;

void main(void) {
  vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
  // gl_FragColor = texture2D(mytexture, flipped_texcoord);
  gl_FragColor = vec4(flipped_texcoord, 0.5, 0.5);
}
)";

const glm::vec3 cubeVertices[] = {
  // front
  { -1.0, -1.0,  1.0 },
  {  1.0, -1.0,  1.0 },
  {  1.0,  1.0,  1.0 },
  { -1.0,  1.0,  1.0 },
  // top
  { -1.0,  1.0,  1.0 },
  {  1.0,  1.0,  1.0 },
  {  1.0,  1.0, -1.0 },
  { -1.0,  1.0, -1.0 },
  // back
  {  1.0, -1.0, -1.0 },
  { -1.0, -1.0, -1.0 },
  { -1.0,  1.0, -1.0 },
  {  1.0,  1.0, -1.0 },
  // bottom
  { -1.0, -1.0, -1.0 },
  {  1.0, -1.0, -1.0 },
  {  1.0, -1.0,  1.0 },
  { -1.0, -1.0,  1.0 },
  // left
  { -1.0, -1.0, -1.0 },
  { -1.0, -1.0,  1.0 },
  { -1.0,  1.0,  1.0 },
  { -1.0,  1.0, -1.0 },
  // right
  {  1.0, -1.0,  1.0 },
  {  1.0, -1.0, -1.0 },
  {  1.0,  1.0, -1.0 },
  {  1.0,  1.0,  1.0 },
};

const glm::vec2 cubeTexcoords[] = {
  // front
  { 0.0, 0.0 },
  { 1.0, 0.0 },
  { 1.0, 1.0 },
  { 0.0, 1.0 },
  // front
  { 0.0, 0.0 },
  { 1.0, 0.0 },
  { 1.0, 1.0 },
  { 0.0, 1.0 },
  // front
  { 0.0, 0.0 },
  { 1.0, 0.0 },
  { 1.0, 1.0 },
  { 0.0, 1.0 },
  // front
  { 0.0, 0.0 },
  { 1.0, 0.0 },
  { 1.0, 1.0 },
  { 0.0, 1.0 },
  // front
  { 0.0, 0.0 },
  { 1.0, 0.0 },
  { 1.0, 1.0 },
  { 0.0, 1.0 },
  // front
  { 0.0, 0.0 },
  { 1.0, 0.0 },
  { 1.0, 1.0 },
  { 0.0, 1.0 },
};

const gl::GLuint cubeIndices[] = {
  // front
  0,  1,  2,
  2,  3,  0,
  // top
  4,  5,  6,
  6,  7,  4,
  // back
   8,  9, 10,
  10, 11,  8,
  // bottom
  12, 13, 14,
  14, 15, 12,
  // left
  16, 17, 18,
  18, 19, 16,
  // right
  20, 21, 22,
  22, 23, 20,
};


Scene::Scene (void) {
  // Shaders.
  g_vertexShaderSource = globjects::Shader::sourceFromString(
    defaultVertexShaderSource);
  g_vertexShaderTemplate = globjects::Shader::applyGlobalReplacements(
    g_vertexShaderSource.get());
  g_vertexShader = globjects::Shader::create(
    gl::GL_VERTEX_SHADER, g_vertexShaderTemplate.get());

  if (!g_vertexShader->compile()) {
    throw std::runtime_error("Unable to compile vertex shader");
  }

  g_fragmentShaderSource = globjects::Shader::sourceFromString(
    defaultFragmentShaderSource);
  g_fragmentShaderTemplate = globjects::Shader::applyGlobalReplacements(
    g_fragmentShaderSource.get());
  g_fragmentShader = globjects::Shader::create(
    gl::GL_FRAGMENT_SHADER, g_fragmentShaderTemplate.get());

  if (!g_fragmentShader->compile()) {
    throw std::runtime_error("Unable to compile fragment shader");
  }

  g_program = globjects::Program::create();
  g_program->attach(g_vertexShader.get(), g_fragmentShader.get());

  g_program->link();

  attr_coord3d = g_program->getAttributeLocation("coord3d");
  attr_texcoord = g_program->getAttributeLocation("texcoord");
  uniform_mvp = g_program->getUniformLocation("mvp");
  // uniform_tex = g_program->getAttributeLocation("mytexture");

  // Buffer.
  m_vao = globjects::VertexArray::create();

  m_vertices = globjects::Buffer::create();
  m_vertices->setData(cubeVertices, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = m_vao->binding(0);
    vao_bind->setAttribute(attr_coord3d);
    vao_bind->setBuffer(m_vertices.get(), 0, sizeof(glm::vec3));
    vao_bind->setFormat(24, gl::GL_FLOAT, gl::GL_FALSE, 0);
    m_vao->enable(0);
  }

  m_texcoord = globjects::Buffer::create();
  m_texcoord->setData(cubeTexcoords, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = m_vao->binding(1);
    vao_bind->setAttribute(attr_texcoord);
    vao_bind->setBuffer(m_vertices.get(), 0, sizeof(glm::vec2));
    vao_bind->setFormat(24, gl::GL_FLOAT, gl::GL_FALSE, 0);
    m_vao->enable(1);
  }

  m_indices = globjects::Buffer::create();
  m_indices->setData(cubeIndices, gl::GL_STATIC_DRAW);

  m_vao->bindElementBuffer(m_indices.get());

  gl::glEnable(gl::GL_BLEND);
  gl::glEnable(gl::GL_DEPTH_TEST);
  gl::glBlendFunc(gl::GL_SRC_ALPHA, gl::GL_ONE_MINUS_SRC_ALPHA);
}

void Scene::draw (void) {
  gl::glClearColor(1.0, 1.0, 1.0, 1.0);
  gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

  float angle = SDL_GetTicks() / 1000.0 * glm::radians(15.0);
  glm::mat4 anim =
    glm::rotate(glm::mat4(1.0f), angle*3.0f, glm::vec3(1, 0, 0))
    * glm::rotate(glm::mat4(1.0f), angle*2.0f, glm::vec3(0, 1, 0))
    * glm::rotate(glm::mat4(1.0f), angle*4.0f, glm::vec3(0, 0, 1));

  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
  glm::mat4 view = glm::lookAt(
    glm::vec3(0.0, 2.0, 0.0),
    glm::vec3(0.0, 0.0, -4.0),
    glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 projection = glm::perspective(
    45.0f, 1.0f * width / height, 0.1f, 10.0f);

  glm::mat4 mvp = projection * view * model * anim;

  g_program->use();
  g_program->setUniform(uniform_mvp, mvp);
  m_vao->drawElements(gl::GL_TRIANGLES, 36, gl::GL_UNSIGNED_INT);
  g_program->release();
}
