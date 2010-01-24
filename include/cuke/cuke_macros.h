#ifndef _CUKE_MACROS_H
#define	_CUKE_MACROS_H

#include <gtest/internal/gtest-internal.h>

#define CUKE_STEP_CLASS_NAME_(feature_name, step_name) \
  feature_name##_##step_name##_Step

#define CUKE_GTEST_DISABLE_PREFIX_

// Modified version of GTEST_TEST_CLASS_NAME_
#define CUKE_STEP_(feature_name, step_name, parent_class, parent_id, regex) \
class CUKE_STEP_CLASS_NAME_(feature_name, step_name) : public parent_class { \
 public: \
    CUKE_STEP_CLASS_NAME_(feature_name, step_name)() : parent_class() {} \
 private: \
  virtual void TestBody(); \
  static ::testing::TestInfo* const test_info_; \
  static int cukeRegId; \
  GTEST_DISALLOW_COPY_AND_ASSIGN_( \
      CUKE_STEP_CLASS_NAME_(feature_name, step_name)); \
}; \
 \
::testing::TestInfo* const CUKE_STEP_CLASS_NAME_(feature_name, step_name) \
  ::test_info_ = \
    ::testing::internal::MakeAndRegisterTestInfo( \
        #feature_name, CUKE_GTEST_DISABLE_PREFIX_ #step_name, "", "", \
        (parent_id), \
        parent_class::SetUpTestCase, \
        parent_class::TearDownTestCase, \
        new ::testing::internal::TestFactoryImpl< \
            CUKE_STEP_CLASS_NAME_(feature_name, step_name)>); \
int CUKE_STEP_CLASS_NAME_(feature_name, step_name) \
  ::cukeRegId = \
    ::cuke::StepManager::registerStep(regex, #feature_name, #step_name); \
void CUKE_STEP_CLASS_NAME_(feature_name, step_name)::TestBody()

#define CUKE_STEP_F_(feature_class, step_name, regex) \
    CUKE_STEP_(feature_class, step_name, feature_class, \
        ::testing::internal::GetTypeId<feature_class>(), regex)
#define GIVEN_F(fixture, test_name, regex) CUKE_STEP_F_(fixture, test_name, regex)
#define WHEN_F(fixture, test_name, regex) CUKE_STEP_F_(fixture, test_name, regex)
#define THEN_F(fixture, test_name, regex) CUKE_STEP_F_(fixture, test_name, regex)

#define CUKE_STEP_C_(context, test_name, regex) CUKE_STEP_F_(context##_DefaultFixture, test_name, regex)
#define GIVEN_C(context, test_name, regex) CUKE_STEP_C_(context, test_name, regex)
#define WHEN_C(context, test_name, regex) CUKE_STEP_C_(context, test_name, regex)
#define THEN_C(context, test_name, regex) CUKE_STEP_C_(context, test_name, regex)

#define GIVEN(context, test_name, regex) GIVEN_C(context, test_name, regex)
#define WHEN(context, test_name, regex) WHEN_C(context, test_name, regex)
#define THEN(context, test_name, regex) THEN_C(context, test_name, regex)


#define CUKE_PARAM(index, type, name) type name = ::cuke::fromString<type>(::cuke::StepManager::getCurrentParam(index));


#define CUKE_FIXTURE(FixtureName, ...) \
    class FixtureName : public ::cuke::CukeFixture<__VA_ARGS__>

#define CUKE_CONTEXT(ContextName) \
    struct ContextName; \
    CUKE_FIXTURE(ContextName##_DefaultFixture, ContextName) {}; \
    struct ContextName


//#define GIVEN(test_name, regex) CUKE_STEP_C_(::cuke::EmptyContext, test_name, regex)
//#define WHEN(test_name, regex) CUKE_STEP_C_(::cuke::EmptyContext, test_name, regex)
//#define THEN(test_name, regex) CUKE_STEP_C_(::cuke::EmptyContext, test_name, regex)
//CUKE_CONTEXT(EmptyContext) {};

#endif	/* _CUKE_MACROS_H */

