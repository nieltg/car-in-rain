#include "Node.h"


// Children relationship.

void Node::parent(std::shared_ptr<Node> _parent) {
  auto prev_parent = parent_data.lock();
  if (prev_parent)
    prev_parent->children.erase(shared_from_this());

  parent_data = _parent;
  if (_parent)
    _parent->children.insert(shared_from_this());
}


// Drawing.

void Node::draw (glm::mat4 _mat_model_parent) {
  draw_children(_mat_model_parent);
}

void Node::draw_children (glm::mat4 _mat_model_parent) {
  for (const std::shared_ptr<Node>& node : children)
    node->draw(_mat_model_parent);
}
