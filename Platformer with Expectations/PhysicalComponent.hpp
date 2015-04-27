#include "TheGrid\Component.hpp"
#include "Colidable.hpp"
#include "Movable.hpp"
#include "CollisionSystem.hpp"

struct PhysicalComponent : Component<PhysicalComponent>{
	PhysicalComponent(Colidable::Handle & col, Movable::Handle & mov, Gravity::Handle & gr): collision(col.get()), movable(mov.get()), grav(gr.get()){
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
			cR->width = 0; 
			cR->height = 0;
			cR->left = 0;
			cR->top = 0;
			return false;
		}
		else{
			cR->width = collisionRect.width;
			cR->height = collisionRect.height;
			cR->top = collisionRect.top;
			cR->left = collisionRect.left;
			std::cout << "Will colide @ cr: " << cR->width << ", " << cR->height << "(" << cR->left << "," << cR->top << ")" << "With velo << " << velo.x << " - " << velo.y << std::endl;
			return true;
		}
	}
	
	void fixMovement(sf::Rect<float> cR){
		sf::Vector2f velo = movable->getVelocity();
		sf::Vector2f position = movable->getPosition();
		sf::Rect<float> currentCr = collision->getRect();
		if (grav->isFalling()){
			if (cR.height < 32){
				if (velo.y > 0){
					if (velo.y - cR.height >= 0){
						velo.y -= cR.height;
					}
					else{
						velo.y = 0;
					}
					grav->setFalling(false);
					velo.y = 0;
					collision->setPosition(collision->getPosition().x, collision->getPosition().y - cR.height);
					movable->setPosition(movable->getPosition().x, movable->getPosition().y - cR.height);
				}
			}
		}

		if (velo.x > 0){
			if (velo.x - cR.width >= 0)
			{
				velo.x -= cR.width;
			}
			else{
				velo.x = 0;
			}
			collision->setCollision(true, Colidable::CollisionSide::right);
			collision->setCollision(false, Colidable::CollisionSide::left);
		}
		
		if (velo.x < 0){
			if (velo.x + cR.width <= 0)
			{
				velo.x += cR.width;
			}
			else{
				velo.x = 0;
			}

			collision->setCollision(false, Colidable::CollisionSide::right);
			collision->setCollision(true, Colidable::CollisionSide::left);
		}

		if (velo.x == 0 && velo.y == 0){
			if (cR.top > collision->getRect().left){
				collision->setPosition(collision->getPosition().x - cR.width, collision->getPosition().y);
				movable->setPosition(movable->getPosition().x - cR.width, movable->getPosition().y);
			}
			else if(cR.top < collision->getRect().left){
				collision->setPosition(collision->getPosition().x + cR.width, collision->getPosition().y);
				movable->setPosition(movable->getPosition().x + cR.width, movable->getPosition().y);
			}
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
	Gravity* grav;

};

