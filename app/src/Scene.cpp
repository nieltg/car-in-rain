#include "OBJ_Loader.h"

#include "Scene.h"


const std::vector<glm::vec3> cubeVertices = {
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

const std::vector<glm::vec2> cubeTexcoords = {
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

const std::vector<gl::GLuint> cubeIndices = {
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
  g_vertexShaderSource = globjects::Shader::sourceFromFile("mesh.v.glsl");
  g_vertexShaderTemplate = globjects::Shader::applyGlobalReplacements(
    g_vertexShaderSource.get());
  g_vertexShader = globjects::Shader::create(
    gl::GL_VERTEX_SHADER, g_vertexShaderTemplate.get());

  if (!g_vertexShader->compile()) {
    throw std::runtime_error("Unable to compile vertex shader");
  }

  g_fragmentShaderSource = globjects::Shader::sourceFromFile("mesh.f.glsl");
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
  attr_norm = g_program->getAttributeLocation("norm");
  uniform_mvp = g_program->getUniformLocation("mvp");
  uniform_tex = g_program->getAttributeLocation("mytexture");

  g_program->setUniform(uniform_tex, 0);

  // OBJ loader.
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texcoord;
  std::vector<gl::GLuint> indices;

  {
    objl::Loader loader;

    if (!loader.LoadFile("mesh.obj")) {
      throw std::runtime_error("Unable to load mesh.obj");
    }

    for (const auto& v : loader.LoadedVertices) {
      const auto& pos = v.Position;
      vertices.push_back(glm::vec3(pos.X, pos.Y, pos.Z));
      const auto& norm = v.Normal;
      normals.push_back(glm::vec3(norm.X, norm.Y, norm.Z));
      const auto& tex = v.TextureCoordinate;
      texcoord.push_back(glm::vec2(tex.X, tex.Y));
    }

    indices = loader.LoadedIndices;
  }

 indices_len = indices.size();

  // Buffer.
  m_vao = globjects::VertexArray::create();

  m_vertices = globjects::Buffer::create();
  m_vertices->setData(vertices, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = m_vao->binding(0);
    vao_bind->setAttribute(attr_coord3d);
    vao_bind->setBuffer(m_vertices.get(), 0, sizeof(glm::vec3));
    vao_bind->setFormat(vertices.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
    m_vao->enable(0);
  }

  m_normals = globjects::Buffer::create();
  m_normals->setData(normals, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = m_vao->binding(2);
    vao_bind->setAttribute(attr_norm);
    vao_bind->setBuffer(m_normals.get(), 0, sizeof(glm::vec3));
    vao_bind->setFormat(normals.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
    m_vao->enable(2);
  }
  

  m_texcoord = globjects::Buffer::create();
  m_texcoord->setData(texcoord, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = m_vao->binding(1);
    vao_bind->setAttribute(attr_texcoord);
    vao_bind->setBuffer(m_texcoord.get(), 0, sizeof(glm::vec2));
    vao_bind->setFormat(texcoord.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
    m_vao->enable(1);
  }

  m_indices = globjects::Buffer::create();
  m_indices->setData(indices, gl::GL_STATIC_DRAW);

  m_vao->bindElementBuffer(m_indices.get());

  // Texture.
  {
    auto res_texture = IMG_Load("mesh.png");

    m_texture = globjects::Texture::create(gl::GL_TEXTURE_2D);
    m_texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
    m_texture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
    m_texture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_CLAMP_TO_EDGE);
    m_texture->setParameter(gl::GL_TEXTURE_WRAP_T, gl::GL_CLAMP_TO_EDGE);

    m_texture->image2D(
      0,
      gl::GL_RGBA,
      glm::ivec2(res_texture->w, res_texture->h),
      0,
      gl::GL_RGBA,
      gl::GL_UNSIGNED_BYTE,
      res_texture->pixels);

    SDL_FreeSurface(res_texture);
  }

  // OpenGL.
  gl::glEnable(gl::GL_BLEND);
  gl::glEnable(gl::GL_DEPTH_TEST);
  gl::glBlendFunc(gl::GL_SRC_ALPHA, gl::GL_ONE_MINUS_SRC_ALPHA);
}

void Scene::resize (int _w, int _h) {
  width = _w;
  height = _h;

  gl::glViewport(0, 0, _w, _h);
}

void Scene::draw (void) {
  gl::glClearColor(0.0, 0.0, 0.0, 1.0);
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

  gl::glActiveTexture(gl::GL_TEXTURE0);
  m_texture->bind();

  g_program->use();
  g_program->setUniform(uniform_mvp, mvp);
  m_vao->drawElements(gl::GL_TRIANGLES, indices_len, gl::GL_UNSIGNED_INT);
  g_program->release();

  m_texture->unbind();
}
