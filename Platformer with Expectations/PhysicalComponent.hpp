#include "TheGrid\Component.hpp"
#include "Colidable.hpp"
#include "Movable.hpp"
#include "CollisionSystem.hpp"

struct PhysicalComponent : Component<PhysicalComponent>{
	PhysicalComponent(Colidable::Handle & col, Movable::Handle & mov): collision(col.get()), movable(mov.get()){
	}
	
	bool willColide(Entity & ent, sf::Rect<float> * cR){
		if (!ent.hasComponent<Colidable>()){
			return false;
		}
		
		
		sf::Vector2f velo = movable->getVelocity();
		sf::Rect<float> next(
			sf::Vector2f(collision->getPosition().x + velo.x, collision->getPosition().y + velo.y),
			sf::Vector2f(collision->getWidth(), collision->getHeight())
		);
		sf::Rect<float> otherRect = ent.getComponent<Colidable>()->getRect();
		sf::Rect<float> collisionRect = Collides(next, otherRect);
		if ((collisionRect.width == 0 && collisionRect.height == 0) || (collisionRect.width == 32 && collisionRect.height == 32)){
			return false;
		}
		else{
			cR->width = collisionRect.width;
			cR->height = collisionRect.height;
			cR->top = collisionRect.top;
			cR->left = collisionRect.left;
			return true;
		}
	}
	
	void fixMovement(sf::Rect<float> cR){
		sf::Vector2f velo = movable->getVelocity();
		sf::Vector2f position = movable->getPosition();
		sf::Rect<float> currentCr = collision->getRect();
		
		if (velo.x > 0 && cR.left > position.x){
			velo.x = 0;
			collision->setCollision(true, Colidable::CollisionSide::right);
			collision->setCollision(false, Colidable::CollisionSide::left);
		}
		else if (velo.x < 0 && cR.left < position.x){
			velo.x = 0;

			collision->setCollision(false, Colidable::CollisionSide::right);
			collision->setCollision(true, Colidable::CollisionSide::left);
		}

		if (velo.y < 0){
		}
		else if (velo.y>0){
		}

		movable->setVelocity(velo);
	}
	static sf::Rect<float> Collides(Entity & lhs, Entity & rhs){
		return Collides(lhs.getComponent<Colidable>(), rhs.getComponent<Colidable>());
	}

	static sf::Rect<float> Collides(Colidable::Handle & lhs, Colidable::Handle & rhs){
		return Collides(lhs->getRect(), rhs->getRect());
	}
	static sf::Rect<float> Collides(Colidable & lhs, Colidable & rhs){
	
		return Collides(lhs.getRect(), rhs.getRect());
	}

	static sf::Rect<float> Collides(sf::Rect<float> rect, sf::Rect<float> other){
		// Rectangles with negative dimensions are allowed, so we must handle them correctly

		// Compute the min and max of the first rectangle on both axes
		float r1MinX = std::min<float>(rect.left, rect.left + rect.width);
		float r1MaxX = std::max<float>(rect.left, rect.left + rect.width);
		float r1MinY = std::min<float>(rect.top, rect.top + rect.height);
		float r1MaxY = std::max<float>(rect.top, rect.top + rect.height);

		// Compute the min and max of the second rectangle on both axes
		float r2MinX = std::min<float>(other.left, other.left + other.width);
		float r2MaxX = std::max<float>(other.left, other.left + other.width);
		float r2MinY = std::min<float>(other.top, other.top + other.height);
		float r2MaxY = std::max<float>(other.top, other.top + other.height);

		// Compute the intersection boundaries
		float interLeft = std::max<float>(r1MinX, r2MinX);
		float interTop = std::max<float>(r1MinY, r2MinY);
		float interRight = std::min<float>(r1MaxX, r2MaxX);
		float interBottom = std::min<float>(r1MaxY, r2MaxY);

		// If the intersection is valid (positive non zero area), then there is an intersection
		if ((interLeft < interRight) && (interTop < interBottom))
		{
			return sf::Rect<float>(interTop, interLeft, interRight - interLeft, interBottom - interTop);
		}
		else
		{
			return sf::Rect<float>(0, 0, 0, 0);
		}
	}


	~PhysicalComponent(){
		//keep memory leaks from existing
	}
private:
	Colidable* collision;
	Movable* movable;

	sf::Rect<float> colides(){
	}

};

