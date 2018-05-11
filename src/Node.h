#include <memory>
#include <unordered_set>

#include <glm/glm.hpp>


class Node : public std::enable_shared_from_this<Node> {
public:
  virtual ~Node (void) {
    // Nothing to do.
  }

  // Children relationship.
  std::unordered_set<std::shared_ptr<Node>> children;

  inline std::shared_ptr<Node> parent() {
    return parent_data.lock();
  }
  void parent(std::shared_ptr<Node> _parent);

  // Transformation matrix.
  glm::mat4 mat_model;

  // Drawing.
  virtual void draw (glm::mat4 _mat_model_parent = glm::mat4(1.0f));

protected:
  void draw_children (glm::mat4 _mat_model_parent);

private:
  std::weak_ptr<Node> parent_data;
};
