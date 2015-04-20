#include "TheGrid\Component.hpp"
#include "Colidable.hpp"
#include "Movable.hpp"
#include "CollisionSystem.hpp"

struct PhysicalComponent : Component<PhysicalComponent>{
	PhysicalComponent(Colidable::Handle & col, Movable::Handle & mov): collision(col), movable(mov){}
	
	bool willColide(Entity & ent, sf::Rect<float> * cR){
		if (!ent.hasComponent<Colidable>()){
			return false;
		}
		
		sf::Vector2f velo = movable->getVelocity();
		Colidable next(
			sf::Vector2f(collision->getPosition().x + velo.x, collision->getPosition().y + velo.y),
			sf::Vector2f(collision->getWidth(), collision->getHeight())
		);

		sf::Rect<float> collisionRect = CollisionSystem::Collides(next.getRect(), ent.getComponent<Colidable>()->getRect());
		if (collisionRect.width == 0 && collisionRect.height == 0){
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

		movable->setVelocity(0, velo.y);
		//if (currentCr.width > 32 || cR.width < 32){
		
	//	}

	
	}

	~PhysicalComponent(){
		//keep memory leaks from existing
	}
private:
	Colidable::Handle & collision;
	Movable::Handle & movable;

	sf::Rect<float> colides(){
	}

};

