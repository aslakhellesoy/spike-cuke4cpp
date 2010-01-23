#include <gtest/gtest.h>
#include "cuke/cuke.h"

#include <json/json.h>

#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
using boost::asio::ip::tcp;

using namespace std;
using namespace cuke;

string unrecognizedCommand() {
    return "[\"fail\",null]";
}

string beginScenario() {
    StepManager s;
    s.startScenario();
    return "[\"success\",null]";
}

string endScenario() {
    // to destroy the scenario we need to register a "context destroyer" on the step manager
    // ContextDestroyer<T>, extending a type-independent interface for destrpying the context
    // note: we should simply delete che context here and let the step create it if it doesn't exist
    //       so we won't need startScenario anymore
    return "[\"success\",null]";
}

string stepMatches(StepManager::step_text_type stepText) {
    StepManager s;
    std::ostringstream output;
    output << "[\"step_matches\",[";
    StepMatchesResult stepMatchResult = s.stepMatches(stepText);
    StepManager::step_id_type stepId = stepMatchResult.getAMatch();
    if (stepId) {
        output << "{\"id\":\"" << stepId << "\", \"args\":[";
        StepMatchesResult::match_result regexMatchResult = stepMatchResult.getMatchResult(stepId);
        for (StepMatchesResult::match_result::size_type i = 1; i < regexMatchResult.size(); ++i) {
            StepMatchesResult::match_result::value_type subMatch = regexMatchResult[i];
            if (i > 1) {
                output << ",";
            }
            output << "{\"val\":\"" << subMatch.str() << "\", \"pos\":" << regexMatchResult.position(i) << "}";
        }
        output << "]}";
    }
    output << "]]";
    return output.str();
}

string invokeStep(StepManager::step_id_type stepId) {
    string output;
    // should test if the fixture is the same as the last test
    StepManager s;
    // should test if the fixture is the same as the last test
    string stepName = s.getStepNameForId(stepId);
    ::testing::GTEST_FLAG(filter) = stepName.c_str();
    try {
        int error = ::testing::UnitTest::GetInstance()->Run();
        if (error) {
            output = "[\"step_failed\",{\"message\":\"WTF2\"}]";
        } else {
            output = "[\"success\",null]";
        }
    } catch (...) {
        output = "[\"step_failed\",{\"message\":\"WTF\", \"exception\":\"ExceptionName\"}]";
    }
    return output;
}

// TODO Use a command object!
// TODO the response should be encoded with the json library
string invoke(Json::Value jsonRequest) {
    Json::Value jsonResponse;
    string command = jsonRequest[0u].asString();
    if (command == "step_matches") {
        string nameToMatch = jsonRequest[1u]["name_to_match"].asString();
        jsonResponse = stepMatches(nameToMatch);
    } else if (command == "invoke") {
        Json::Value commandSpecs = jsonRequest[1u];
        StepManager::step_id_type stepId;
        istringstream s(commandSpecs["id"].asString());
        s >> stepId;
        Json::Value stepParams = commandSpecs["args"];
        for (Json::Value::ArrayIndex i = 0; i < stepParams.size(); ++i) {
            StepManager::currentParams[i] = stepParams[i].asString();
        }
        jsonResponse = invokeStep(stepId);
    } else if (command == "begin_scenario") {
        jsonResponse = beginScenario();
    } else if (command == "end_scenario") {
        jsonResponse = endScenario();
    } else {
        jsonResponse = unrecognizedCommand();
    }
    return jsonResponse.asString();
}

void session(tcp::iostream* streamPtr) {
    tcp::iostream& stream = (*streamPtr);
    std::string request, response;
    Json::Reader reader;
    try {
        while (stream) {
            getline(stream, request); // TODO: unicode? utf-8? what?
            Json::Value jsonRequest;
            if (request.size() > 0) {
                //cerr << "REQUEST: " << request << endl;
                if (!reader.parse(request, jsonRequest)) {
                    response = "[\"fail\",\"cannot parse json request\"]";
                } else {
                    response = invoke(jsonRequest);
                }
                //cerr << "RESPONSE: " << response << endl;
                stream << response << endl;
            } else {
                //cerr << "SKIPPING BLANK REQUEST" << endl;
            }
        }
    } catch (std::exception& e) {
        cerr << "Exception in thread: " << e.what() << endl;
    }
}

void server(boost::asio::io_service& io_service, short port, bool runOnce) {
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    do {
        tcp::iostream stream;
        a.accept(*stream.rdbuf());
        boost::thread t(boost::bind(session, &stream));
        if (runOnce)
            t.join();
    } while (!runOnce);
}

int main(int argc, char* argv[]) {
    try {
        int fake_argc = argc > 0 ? 1 : 0;
        char *fake_argv[1];
        fake_argv[0] = argv[0];

        testing::InitGoogleTest(&fake_argc, fake_argv);

        ::testing::GTEST_FLAG(also_run_disabled_tests) = true;
        ::testing::GTEST_FLAG(throw_on_failure) = true;

        int port = 3901;
        if (argc > 1) {
            port = atoi(argv[1]);
        }
        boost::asio::io_service io_service;
        server(io_service, port, true);
    } catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    return 0;
}

