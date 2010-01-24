#include "cuke/cuke_internal.h"

namespace cuke {

/*
 * StepMatchesResult
 */

void StepMatchesResult::addMatch(StepManager::step_id_type stepId, match_result matchResult) {
    matches.insert(matches_map_type::value_type(stepId, matchResult));
}

bool StepMatchesResult::matched() {
    return !matches.empty();
}

StepManager::step_id_type StepMatchesResult::getAMatch() {
    return matches.begin()->first;
}

StepMatchesResult::match_result StepMatchesResult::getMatchResult(StepManager::step_id_type stepId) {
    return matches[stepId];
}

/*
 * StepManager
 */

StepManager::step_set_type StepManager::steps = StepManager::step_set_type();

StepMatchesResult StepManager::stepMatches(step_text_type stepText) {
    StepMatchesResult result = StepMatchesResult();
    for (step_id_type i=0; i<steps.size(); ++i) {
        boost::match_results<step_regexp_type::const_iterator> matchResult;
        step_info_type currentStep = steps[i];
        if (boost::regex_match(stepText.c_str(), matchResult, currentStep.regex)) {
            result.addMatch(i+1, matchResult);
        }
    }
    return result;
}

std::string StepManager::getStepNameForId(step_id_type stepId) {
    step_info_type stepInfo = steps.at(stepId-1);
    return stepInfo.featureName + "." + stepInfo.stepName;
}

int StepManager::addStep(const char_type *regex, const char *featureName, const char *stepName) {
    StepManager::step_regexp_type r = StepManager::step_regexp_type(regex);
    int stepPos = findStep(r);
    if (stepPos > 0) {
        return stepPos;
    }
    step_info_type stepInfo(r, featureName, stepName);
    steps.push_back(stepInfo);
    return steps.size();
}

int StepManager::findStep(const step_regexp_type &regex) {
    for (step_set_type::size_type i=0; i<steps.size(); ++i) {
        if (steps[i].regex == regex) {
            return i+1;
        }
    }
    return -1;
}

void StepManager::startScenario() {
    scenarioStepCount = 0;
}

int StepManager::getCurrentStepNumber() {
    return ++scenarioStepCount;
}

int StepManager::scenarioStepCount = 0;

int StepManager::registerStep(const char_type *regex, const char *featureName, const char *stepName) {
    StepManager s;
    return s.addStep(regex, featureName, stepName);
}

std::vector<std::string> StepManager::currentParams = std::vector<std::string>(10);

std::string StepManager::getCurrentParam(int i) {
    return currentParams.at(i-1);
}

/*
 * fromString specialization for strings
 */

template<> std::string fromString(const std::string& s) {
    return std::string(s);
}

}
