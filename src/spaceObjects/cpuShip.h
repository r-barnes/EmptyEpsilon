#ifndef CPU_SHIP_H
#define CPU_SHIP_H

#include "pathPlanner.h"
#include "spaceship.h"

enum EAIOrder
{
    AI_Idle,            //Don't do anything, don't even attack.
    AI_Roaming,         //Fly around and engage at will, without a clear target
    AI_StandGround,     //Keep current position, do not fly away, but attack nearby targets.
    AI_DefendLocation,  //Defend against enemies getting close to [order_target_location]
    AI_DefendTarget,    //Defend against enemies getting close to [order_target] (falls back to AI_Roaming if the target is destroyed)
    AI_FlyFormation,    //Fly [order_target_location] offset from [order_target]. Allows for nicely flying in formation.
    AI_FlyTowards,      //Fly towards [order_target_location], attacking enemies that get too close, but disengage and continue when enemy is too far.
    AI_FlyTowardsBlind, //Fly towards [order_target_location], not attacking anything
    AI_Dock,            //Dock with target
    AI_Attack,          //Attack [order_target] very specificly.
};

class CpuShip : public SpaceShip
{
    static const float auto_system_repair_per_second = 0.005f;
    
    EAIOrder orders;                    //Server only
    sf::Vector2f order_target_location; //Server only
    P<SpaceObject> order_target;        //Server only
    float missile_fire_delay;

    bool has_missiles;//Server only, updated every update
    bool has_beams;//Server only, updated every update
    float beam_weapon_range;//Server only, updated every update
    
    PathPlanner pathPlanner;
public:
    CpuShip();
    
    virtual void update(float delta);
    
    void orderIdle();
    void orderRoaming();
    void orderStandGround();
    void orderDefendLocation(sf::Vector2f position);
    void orderDefendTarget(P<SpaceObject> object);
    void orderFlyFormation(P<SpaceObject> object, sf::Vector2f offset);
    void orderFlyTowards(sf::Vector2f target);
    void orderFlyTowardsBlind(sf::Vector2f target);
    void orderAttack(P<SpaceObject> object);
    void orderDock(P<SpaceObject> object);
    
    EAIOrder getOrder() { return orders; }
    
    friend class GameMasterUI;

private:
    P<SpaceObject> findBestTarget(sf::Vector2f position, float radius);
    float targetScore(P<SpaceObject> target);
    bool betterTarget(P<SpaceObject> new_target, P<SpaceObject> current_target);
};
string getAIOrderString(EAIOrder order);

#endif//CPU_SHIP_H