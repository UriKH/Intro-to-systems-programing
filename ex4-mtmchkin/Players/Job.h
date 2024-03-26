#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>
#include "Player.h"
#include "Card.h"

class Job : public Player{
protected:
    std::string m_jobTitle;
public:
    Job(const std::string& name, int hp, int level, int force, int coins, std::shared_ptr<Behavior> behavior, const std::string& jobTitle);

    /**
     * Function that operates on a given player and returns a value 
    */
    typedef int (*PlayerAction)(Player&, const Card*);

    /**
     * Map of form:
     * {
     *      CardType1: {
     *          default: defaultAction, Job1: action1 ...
     *      },
     *      CardType2: {
     *          default: defaultAction, Job1: action1 ...
     *      }
     * }
    */
    typedef std::map<std::string, std::map<std::string, PlayerAction>> CardPlayerActionMap;

    /**
     * Calculates the combat power of the character
     * @return the combat power
    */
    virtual int calculateCombatPower() const;

    /**
     * Generates a string representation of the character with respect to it's job
     * @return the string representation
    */
    virtual std::string getDescription() const override;

    /**
     * Gets the job type name
     * @return the name of the job
    */
    virtual std::string getJobName() const = 0;

    /**
     * Retrieve a specific player type action for a card
     * @param job the player type to search an action for
     * @param card the card type to search an action for
     * @throws ActionNotFound - if no action found for the given job and card (and no default found) 
    */
    static PlayerAction getPlayerAction(const Job& job, const Card& card);

    /**
     * Set the default actions for the cards
     * @param defaultActions the default actions 
    */
    static void initializeMap(CardPlayerActionMap defaultActions);

    /**
     * Gets the default actions for known cards
     * @returns the default actions
    */
    static CardPlayerActionMap getDefaultActions();

    /**
     * Action not found error class representing error that occures when a wanted
     * PlayerAction could not be found
    */
    class ActionNotFound : public std::exception{
        std::string m_message;
    public:
        ActionNotFound(const std::string& cardName, const std::string& jobName);
        const char* what() const noexcept override;
    };

    /**
     * Invalid initialitaion error class representing error that occures
     * when trying to initialize the Action map more than once
    */
    class InvalidInitialization : public std::exception{
    public:
        const char* what() const noexcept override;
    };
private:
    static CardPlayerActionMap& getfunctionalityMap();
};