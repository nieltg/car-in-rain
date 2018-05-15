#include "OBJ_Loader.h"

#include "Mesh.h"


Mesh::Mesh (void) {
  // Shaders.
  shader_v_src = globjects::Shader::sourceFromFile("misc/mesh.v.glsl");
  shader_v_preprocessed = globjects::Shader::applyGlobalReplacements(
    shader_v_src.get());
  shader_v = globjects::Shader::create(
    gl::GL_VERTEX_SHADER, shader_v_preprocessed.get());

  shader_f_src = globjects::Shader::sourceFromFile("misc/mesh.f.glsl");
  shader_f_preprocessed = globjects::Shader::applyGlobalReplacements(
    shader_f_src.get());
  shader_f = globjects::Shader::create(
    gl::GL_FRAGMENT_SHADER, shader_f_preprocessed.get());

  program = globjects::Program::create();
  program->attach(shader_v.get(), shader_f.get());

  i_attr_coord3d = program->getAttributeLocation("coord3d");
  i_attr_texcoord = program->getAttributeLocation("texcoord");
  i_uniform_mvp = program->getUniformLocation("mvp");
  i_uniform_tex = program->getAttributeLocation("mytexture");

  program->setUniform(i_uniform_tex, 0);

  // OBJ loader.
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> texcoord;
  std::vector<gl::GLuint> indices;

  {
    objl::Loader loader;

    if (!loader.LoadFile("misc/mesh.obj")) {
      throw std::runtime_error("Unable to load misc/mesh.obj");
    }

    for (const auto& v : loader.LoadedVertices) {
      const auto& pos = v.Position;
      vertices.push_back(glm::vec3(pos.X, pos.Y, pos.Z));
      const auto& tex = v.TextureCoordinate;
      texcoord.push_back(glm::vec2(tex.X, tex.Y));
    }

    indices = loader.LoadedIndices;
  }

 draw_len = indices.size();

  // Buffer.
  vao = globjects::VertexArray::create();

  b_vertices = globjects::Buffer::create();
  b_vertices->setData(vertices, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = vao->binding(0);
    vao_bind->setAttribute(i_attr_coord3d);
    vao_bind->setBuffer(b_vertices.get(), 0, sizeof(glm::vec3));
    vao_bind->setFormat(vertices.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
    vao->enable(0);
  }

  b_texcoord = globjects::Buffer::create();
  b_texcoord->setData(texcoord, gl::GL_STATIC_DRAW);

  {
    auto vao_bind = vao->binding(1);
    vao_bind->setAttribute(i_attr_texcoord);
    vao_bind->setBuffer(b_texcoord.get(), 0, sizeof(glm::vec2));
    vao_bind->setFormat(texcoord.size(), gl::GL_FLOAT, gl::GL_FALSE, 0);
    vao->enable(1);
  }

  b_indices = globjects::Buffer::create();
  b_indices->setData(indices, gl::GL_STATIC_DRAW);

  vao->bindElementBuffer(b_indices.get());

  // Texture.
  {
    auto res_texture = IMG_Load("misc/mesh.png");

    if (!res_texture) {
      throw std::runtime_error("Unable to load misc/mesh.png");
    }

    texture = globjects::Texture::create(gl::GL_TEXTURE_2D);
    texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR);
    texture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);
    texture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_CLAMP_TO_EDGE);
    texture->setParameter(gl::GL_TEXTURE_WRAP_T, gl::GL_CLAMP_TO_EDGE);

    texture->image2D(
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

void Mesh::resize (int _w, int _h) {
  width = _w;
  height = _h;

  gl::glViewport(0, 0, _w, _h);
}

void Mesh::draw (void) {
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

  gl::glActiveTexture(gl::GL_TEXTURE0);
  texture->bind();

  program->use();
  program->setUniform(i_uniform_mvp, mvp);
  vao->drawElements(gl::GL_TRIANGLES, draw_len, gl::GL_UNSIGNED_INT);
  program->release();

  texture->unbind();
}
