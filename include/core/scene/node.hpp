#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

#include "SFML/Graphics.hpp"

class SceneNode :   public  sf::Transformable,
                    public  sf::Drawable,
                    private sf::NonCopyable{
public:
    typedef std::unique_ptr<SceneNode> Ptr;

    SceneNode();

private:
    std::vector<Ptr> m_children;
    SceneNode* m_parent;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    void    attachChild(Ptr child);
    Ptr     detachChild(const SceneNode& node);
};


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    drawCurrent(target, states);

    for (const Ptr& child : m_children) {
        child->draw(target, states);
    }
}


void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
}


void SceneNode::attachChild(Ptr child){
    child->m_parent = this;   
    m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node){
    auto found = std::find_if(m_children.begin(), m_children.end(), [&] (Ptr& p) -> bool {return p.get() == &node; });
    assert(found != m_children.end() && "The child node does not exist");
    
    Ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return result;
}