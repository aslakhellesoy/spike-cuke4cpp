#ifndef _CUKE_INTERNAL_H
#define	_CUKE_INTERNAL_H

#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>

#include <boost/regex.hpp>

#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <list>
#include <map>

namespace cuke {

/*
 * StepManager
 *
 * Note: it is a monostate object
 */

class StepMatchesResult;

class StepManager {
public:
    typedef char char_type;
    typedef const std::basic_string<char_type> step_text_type;
    typedef boost::basic_regex<char_type> step_regexp_type;
    struct step_info_type {
        step_regexp_type regex;
        std::string featureName;
        std::string stepName;
        step_info_type() {};
        step_info_type(step_regexp_type regex, std::string featureName, std::string stepName)
                : regex(regex), featureName(featureName), stepName(stepName) {};
    };
    typedef std::vector<step_info_type> step_set_type;
    typedef step_set_type::size_type step_id_type;

    StepMatchesResult stepMatches(step_text_type stepText);
    std::string getStepNameForId(step_id_type);
    int addStep(const char_type *regex, const char *featureName, const char *stepName);

    void startScenario();
    int getCurrentStepNumber(); // Has to be called exactly once for every step

    static int registerStep(const char_type *regex, const char *featureName, const char *stepName);
    static std::string getCurrentParam(int i);
    static std::vector<std::string> currentParams; // TODO

protected:
    int findStep(const step_regexp_type &regex);

    static step_set_type steps;
    static int scenarioStepCount;
};


/*
 * StepMatchesResult
 */

class StepMatchesResult {
public:
    typedef boost::match_results<StepManager::step_regexp_type::const_iterator> match_result;
    typedef std::map<StepManager::step_id_type, match_result> matches_map_type;
    bool matched();
    StepManager::step_id_type getAMatch(); // TODO
    match_result getMatchResult(StepManager::step_id_type);

protected:
     matches_map_type matches;

private:
    friend class StepManager;
    void addMatch(StepManager::step_id_type, match_result matchResult);
};

template<class T>
    T fromString(const std::string& s)
{
     std::istringstream stream (s);
     T t;
     stream >> t;
     if (stream.fail()) {
         throw std::invalid_argument("Cannot convert parameter");
     }
     return t;
}

template <class T>
class CukeFixture : public ::testing::Test {
public:
    CukeFixture();
protected:
    static T *context;
};

template <class T> T *CukeFixture<T>::context = 0;

template <class T> CukeFixture<T>::CukeFixture() {
    StepManager s;
    int stepNumber = s.getCurrentStepNumber();
    if (stepNumber == 1 && context) {
        //std::cerr << "Deleting context" << std::endl;
        delete context;
        context = 0;
    }
    if (!context) {
        //std::cerr << "Creating context" << std::endl;
        context = new T();
    }
}

}

#endif	/* _CUKE_INTERNAL_H */

